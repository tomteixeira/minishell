/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/05 12:53:30 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Next To Do:
// 1. Implementer < et > et >>
// 2. Gestion d'erreur
// 3. Gestion du Heredoc

void handle_redirection(t_command *cmd)
{
    int fd;
    t_redirection *redir;

    fd = -1;
    // Handle output redirections (last one takes precedence)
    redir = cmd->out_redirection;
    while (redir)
    {
        if (fd != -1) // close any previous file descriptor
            close(fd);

        if (redir->type == R_OUT)
        {
            fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        }
        else if (redir->type == A_R_OUT)
        {
            fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        }

        if (fd == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }

        redir = redir->next;
    }

    if (fd != -1)  // if a file was opened for writing
    {
        if (dup2(fd, 1) == -1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(fd);
    }

    fd = -1;
    // Handle input redirections (last one takes precedence)
    redir = cmd->in_redirection;
    while (redir)
    {
        if (fd != -1) // close any previous file descriptor
            close(fd);

        fd = open(redir->file, O_RDONLY);
        if (fd == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }

        redir = redir->next;
    }

    if (fd != -1)  // if a file was opened for reading
    {
        if (dup2(fd, 0) == -1)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(fd);
    }
}

// Utility function to join two strings with a '/'
static char	*join_with_slash(const char *s1, const char *s2)
{
	int len1;
	int len2;
	char *result;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 2);
	if (!result)
		return NULL;
	strcpy(result, s1);
	result[len1] = '/';
	strcpy(result + len1 + 1, s2);
	return result;
}

static char	*find_command_in_path(const char *command)
{
	char *path;
	char *path_copy;
	char *token;
	char *possible_command;

	path = getenv("PATH");
	path_copy = ft_strdup(path);
	token = strtok(path_copy, ":");
	while (token != NULL) {
		possible_command = join_with_slash(token, command);
		if (!possible_command) {
			free(path_copy);
			return NULL;
		}
		if (access(possible_command, F_OK) != -1) {
			free(path_copy);
			return possible_command;
		}
		free(possible_command);
		token = strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}



void write_error_msg(const char *msg1, const char *msg2)
{
	write(2, msg1, ft_strlen(msg1));
	if (msg2)
		write(2, msg2, ft_strlen(msg2));
	write(STDERR_FILENO, "\n", 1);
}

void execute_command(t_command_parser *first_command, char **env)
{
	t_command_parser *current;
	char *full_path;
	pid_t pid;
	int status;
	int num_children = 0;

	int pipefd[2];  // for the current pipe
	int prev_pipe_read_fd = -1;  // to store the read end of the previous pipe

	current = first_command;
	while (current)
	{
		if (current->command->pipe_after)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
		}

		pid = fork();
		if (pid == 0)  // child process
		{
			if (prev_pipe_read_fd != -1)
			{
				dup2(prev_pipe_read_fd, 0);  // Set stdin to previous pipe's read end
				close(prev_pipe_read_fd);
			}
			if (current->command->pipe_after)
			{
				close(pipefd[0]);
				dup2(pipefd[1], 1);
				close(pipefd[1]);
			}
			handle_redirection(current->command);
			full_path = find_command_in_path(current->command->command_args[0]);
			if (full_path && access(full_path, X_OK) != -1)
			{
				execve(full_path, current->command->command_args, env);
				free(full_path);
			}
			else
			{
				write_error_msg(current->command->command_args[0], ": command not found");
				exit(EXIT_FAILURE);
			}
		}
		else if (pid > 0)  // parent process
		{
			num_children++;
			if (prev_pipe_read_fd != -1)
				close(prev_pipe_read_fd);

			if (current->command->pipe_after)
			{
				close(pipefd[1]);
				prev_pipe_read_fd = pipefd[0];
			}
			else
			{
				wait(&status);  // Wait only if it's the last command
			}
		}
		else
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		current = current->next;
	}
	while (num_children > 0)
	{
		wait(NULL);
		num_children--;
	}
}
