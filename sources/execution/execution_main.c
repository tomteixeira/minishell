/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/26 14:00:41 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_signal = 0;

static int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);

	// List of built-in commands
	char *builtins[] = {
		"echo",
		"export",
		"cd",
		"env",
		"exit",
		"pwd",
		"unset",
		NULL  // End marker
	};

	int i = 0;
	while (builtins[i])
	{
		if (strcmp(cmd, builtins[i]) == 0)
			return (1);  // It's a built-in
		i++;
	}

	return (0);  // Not a built-in
}


// Handle Piping
static void	handle_piping(t_command *cmd, int *pipefd)
{
	if (cmd->pipe_after)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
}

// Function to handle the fork and execute logic
static pid_t	fork_and_execute(t_command_parser **current, pid_t pid,
	int *pipefd, int *prev_pipe_read_fd, char **env)
{
	pid = fork();
	if (pid == 0)
	{
		if (!(*current)->command->pipe_after && pipefd[1] != -1)
			close(pipefd[1]);
		handle_child_process(*current, pipefd, env, prev_pipe_read_fd);
	}
	else if (pid > 0)
	{
		if ((*current)->command->pipe_after && pipefd[1] != -1)
			close(pipefd[1]);
		if (*prev_pipe_read_fd != -1)
			close(*prev_pipe_read_fd);
		handle_parent_process(*current, pipefd, prev_pipe_read_fd);
	}
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

// Function to wait for all child processes to complete
static int	wait_for_children(pid_t pid)
{
	int		status;

	while (waitpid(pid, &status, 0) != -1)
		;
	if (WIFSIGNALED(status))
	{
		put_sig(WTERMSIG(status));
		g_signal = 128 + WTERMSIG(status);
		return (g_signal);
	}
	else if (WIFEXITED(status))
		g_signal = WEXITSTATUS(status);
	return (g_signal);
}

// Utility function to handle assignments $> a=b
int	handle_assignments(t_command_parser **current, char ***env)
{
	char	*assignment_args[3];

	if (!(*current)->command->command_args)
		return (0);
	if (is_assignment((*current)->command->command_args[0])
		&& (*current)->command->command_args[1]
		== NULL && (*current)->next == NULL)
	{
		assignment_args[0] = "export";
		assignment_args[1] = (*current)->command->command_args[0];
		assignment_args[2] = NULL;
		export(assignment_args, env);
		*current = (*current)->next;
		return (1);
	}
	else if (is_assignment((*current)->command->command_args[0]))
		(*current)->command->command_args
			= remove_from_list((*current)->command->command_args,
				(*current)->command->command_args[0]);
	return (0);
}

// Utility function to execute a command
int	execute_command(t_command_parser *first_command, char ***env)
{
	t_command_parser	*current;
	int					pipefd[2];
	int					prev_pipe;
	pid_t				pid;

	pipefd[0] = -1;
	pipefd[1] = -1;
	pid = 0;
	init_execution_context(&current, &prev_pipe, first_command);
	while (current)
	{
		if (handle_assignments(&current, env))
			continue ;
		expand_command_arguments(current->command, *env);
		handle_piping(current->command, pipefd);
		if (current->command->command_args && is_builtin(current->command->command_args[0]))
		{
			int original_stdout = dup(STDOUT_FILENO);
			int original_stdin = dup(STDIN_FILENO);
			if (original_stdout == -1 || original_stdin == -1)
			{
				perror("dup");
				exit(EXIT_FAILURE);
			}
			if (current->command->pipe_after)
				dup2(pipefd[1], STDOUT_FILENO);
			handle_redirection(current->command);
			execute_builtin(current->command, env);
			dup2(original_stdout, STDOUT_FILENO);
			dup2(original_stdin, STDIN_FILENO);
			close(original_stdout);
			close(original_stdin);
			if (!current->command->pipe_after && prev_pipe != -1)
				close(prev_pipe);
			if (current->command->pipe_after)
			{
				close(pipefd[1]);
				prev_pipe = pipefd[0];
			}
			else
			{
				if (pipefd[0] != -1)
					close(pipefd[0]);
				if (pipefd[1] != -1)
					close(pipefd[1]);
			}
			current = current->next;
			continue;
		}
		if (!current->command->command_args && current->command->in_redirection->type == HEREDOC)
		{
			handle_heredoc(current->command->in_redirection, &prev_pipe);
			g_signal = 0;
			return(0);
		}
		else
			pid = fork_and_execute(&current, pid, pipefd, &prev_pipe, *env);
		current = current->next;
	}
	return (wait_for_children(pid));
}
