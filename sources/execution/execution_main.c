/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:56:18 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/20 17:45:50 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static pid_t	execute_command_loop(t_minishell **cur,
	char ***env,  int *pipefd)
{
	int		p_pipe;
	pid_t	pid;
	t_command_parser *buffer;
	t_env_var *env_buffer;

	env_buffer = (*cur)->env_var;
	pid = 0;
	p_pipe = -1;
	buffer = (*cur)->first_command;
	while ((*cur)->first_command)
	{
		if (process_command((*cur)->first_command, env, &(*cur)->env_var, pipefd) == 1)
			break ;
		if ((*cur)->first_command->command->command_args
			&& is_builtin((*cur)->first_command->command->command_args[0]))
		{
			if (execute_builtin_command(cur, env, &p_pipe, pipefd))
				continue ;
		}
		if (!(*cur)->first_command->command->command_args
			&& (*cur)->first_command->command->in_redirection->type == HEREDOC)
			handle_heredoc((*cur)->first_command->command->in_redirection, &p_pipe);
		else
			pid = fork_and_execute(cur, pipefd, &p_pipe, *env);
	}
	(*cur)->first_command = buffer;
	(*cur)->env_var = env_buffer;
	return (pid);
}

void print_local_env(t_env_var *env_var)
{
    t_env_var *current = env_var;
	t_env_var *buffer = env_var;

    while (current != NULL) {
        printf("Key: %s, Value: %s\n", current->key, current->value);
        current = current->next;
    }
	env_var = buffer;
}


int	execute_command(t_minishell **m, char ***env)
{
	int					pipefd[2];
	int					prev_pipe;
	pid_t				pid;
	int					flag_last;

	flag_last = set_flag(&(*m)->first_command);
	init_execution_context(&prev_pipe, pipefd);
	update_local_env_with_global(&(*m)->env_var, *env);
	pid = execute_command_loop(m, env, pipefd);
	return (wait_for_children(pid, flag_last));
}
