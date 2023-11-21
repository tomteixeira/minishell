/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/21 15:27:18 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_file(t_redirection *out)
{
	int	fd;

	while (out)
	{
		if (out->type == R_OUT)
			fd = open(out->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (out->type == A_R_OUT)
			fd = open(out->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			perror("open");
		else
			close(fd);
		out = out->next;
	}
}

// Function to wait for signal
static int	wait_for_children(pid_t pid,
	int flag_last)
{
	int		status;

	if (pid == 0)
		return (0);
	while (waitpid(pid, &status, 0) != -1)
		;
	if (WIFSIGNALED(status))
	{
		put_sig(WTERMSIG(status));
		if (flag_last == 0)
			g_signal = 128 + WTERMSIG(status);
		return (g_signal);
	}
	else if (WIFEXITED(status) && flag_last == 0)
		g_signal = WEXITSTATUS(status);
	return (g_signal);
}

void	update_local_env_with_global(t_env_var **local_env_var,
	char **global_env)
{
	t_env_var	*current_var;
	t_env_var	*tmp;
	char		*global_value;

	tmp = *local_env_var;
	current_var = *local_env_var;
	while (current_var != NULL)
	{
		global_value = get_value_from_global_env(global_env, current_var->key);
		if (global_value != NULL
			&& ft_strcmp(global_value, current_var->value) != 0)
		{
			if (current_var->value != NULL)
				free(current_var->value);
			current_var->value = global_value;
		}
		else
			free(global_value);
		current_var = current_var->next;
	}
	*local_env_var = tmp;
	add_missing_keys(local_env_var, global_env);
}

static int	process_command(t_command_parser *current,
	char ***env, t_env_var **env_var, int *pipefd)
{
	if (handle_assignments(&current, env, env_var) == 1)
	{
		g_signal = 0;
		return (1);
	}
	expand_command_arguments(current->command, *env_var);
	handle_piping(current->command, pipefd);
	return (0);
}

// Utility function to read and write lines for heredoc
static pid_t	execute_command_loop(t_minishell **cur,
	char ***env, int *pipefd)
{
	int					p_pipe;
	pid_t				pid;
	t_command_parser	*buffer;

	pid = 0;
	p_pipe = -1;
	buffer = (*cur)->f_c;
	while ((*cur)->f_c)
	{
		if (process_command((*cur)->f_c, env, &(*cur)->env_var, pipefd) == 1)
			break ;
		if ((*cur)->f_c->command->cargs
			&& is_builtin((*cur)->f_c->command->cargs[0]))
		{
			if (execute_builtin_command(cur, env, &p_pipe, pipefd))
				continue ;
		}
		if (!(*cur)->f_c->command->cargs
			&& ((*cur)->f_c->command->in_redirection
				|| (*cur)->f_c->command->out_redirection))
		{
			heredoc_read_and_write_bis((*cur)-> f_c->command->in_redirection);
			create_file((*cur)->f_c->command->out_redirection);
			if ((*cur)->f_c->command->pipe_after)
			{
				if (pipefd[1] != -1)
					close(pipefd[1]);
				p_pipe = pipefd[0];
			}
			(*cur)->f_c = (*cur)->f_c->next;
		}
		else
			pid = fork_and_execute(cur, pipefd, &p_pipe, *env);
	}
	(*cur)->f_c = buffer;
	return (pid);
}

int	execute_command(t_minishell **m, char ***env)
{
	int					pipefd[2];
	int					prev_pipe;
	pid_t				pid;
	int					flag_last;

	flag_last = set_flag(&(*m)->f_c);
	init_execution_context(&prev_pipe, pipefd);
	update_local_env_with_global(&(*m)->env_var, *env);
	pid = execute_command_loop(m, env, pipefd);
	return (wait_for_children(pid, flag_last));
}
