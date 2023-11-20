/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:25:38 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/20 13:57:59 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "structure.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define SIZE_PATH 4096

extern int			g_signal;

/*Prompt*/
char				*read_line(void);

/*Lexer fonctions*/
t_tokenlist			*lexer(char *command_line);
int					command_len(t_lexer **lexer);
int					option_len(t_lexer **lexer);
t_token				*string_token(t_lexer **lexer);
t_token				*command_token(t_lexer **lexer);
t_token				*option_variable_token(t_tokentype type, t_lexer **lexer);
t_token				*redirection_token(t_lexer **lexer);
t_token				*create_token(t_tokentype type, const char *value,
						t_lexer **lexer);
t_token				*heredoc_token(t_lexer **lexer);
int					ft_word_char(int c);
int					check_parsing(t_tokenlist **t);
int					ft_string_char(int c);
void				merge_tokenlist(t_tokenlist **head_a, t_tokenlist **head_b);
// int					check_parsing(t_token **token);

/*Parser functions*/
t_command_parser	*new_node(t_token **token);
t_command			*init_command(void);
t_command			*fill_command(t_tokenlist **token);
t_command_parser	*parse_tokens(t_tokenlist *token);
void				append(t_command_parser **head, t_tokenlist **token,
						int is_pipe_before);
int					fill_redirection(t_tokenlist **token, t_command **command);
void				print_parser(t_command_parser *head);

/*Execution functions*/
// MAIN
int					execute_command(t_minishell **m, char ***env);
// ASSIGNEMENTS
int					handle_assignments(t_command_parser **current, char ***env,
						t_env_var **env_var);
// BUILTINS
int					execute_builtin_command(t_minishell **current,
						char ***env, int *prev_pipe, int pipefd[2]);
// ERROR
void				ft_error(const char *str, ...);
void	free_env_var(t_env_var *env_var);

// EXPANSION
void				expand_command_arguments(t_command *cmd,
						t_env_var *env_var);
char				*apply_quotes_removal(char *str, int quotes);
char				*remove_quotes(const char *str, int flag);
char				*remove_quotes_from_str(const char *str, char quote_char,
						char *result);
char				*allocate_without_quotes(const char *str, int quotes_nb);
int					count_quotes(const char *str, int quote_type);
char				*get_var_value(t_env_var *env_var, char *var_name);
char				*replace_name(const char *str, const char *var_name,
						const char *var_value, int i);
char				*remove_backslashes(char *str, int *index);
int					handle_quotes(char current_char, int quotes);
char				*expand_variable(const char *str, t_env_var *env_var,
						int i);
// FORK
void				handle_parent_process(t_minishell **current,
						int *pipefd, int *prev_pipe_read_fd);
void				handle_child_process(t_minishell **current,
						int *pipefd, char **env, int *prev_pipe_read_fd);
void				handle_pipe_redirection(t_command_parser *current,
						int *pipefd, int *prev_pipe_read_fd);
// HEREDOC
int					handle_heredoc(t_redirection *heredoc, int *read_end);
// PATH
char				*find_command_in_path(const char *command, char **env);
// REDIRECTION
void				handle_redirection(t_command *cmd);
void				exit_with_error(const char *error_msg);
// SIGNALS
void				put_sig(int sig_code);
void				handle_exec_signal(void);
void				handle_input_signal(void);
// UTILS
int					is_assignment(const char *cmd);
int					execute_builtin(t_minishell **cur, char ***env);
char				**remove_from_list(char **list, char *arg, int i);
void				init_execution_context(int *prev_pipe_read_fd, int *pipefd);
void				ft_error_exit(const char *format, const char *filename);
void				split_assignment(const char *assignment, char **key,
						char **value);
void				replace_and_free(char **old_str, char *new_str);
char				*get_var_name(const char *str, int i);
int					is_builtin(char *cmd);
char				*get_value_from_global_env(char **env, const char *key);
pid_t				fork_and_execute(t_minishell **current, int *pipefd,
						int *prev_pipe_read_fd, char **env);
void				handle_piping(t_command *cmd, int *pipefd);
void				add_missing_keys(t_env_var **local_env_var,
						char **global_env);
void				update_existing_env_var(char ***env,
						const char *key, const char *value, int i);
void				add_new_env_var(char ***env, const char *key,
						const char *value, int i);
int					set_flag(t_command_parser **first_command);

/*Free functions*/
void				ft_free(t_minishell **minishell);
void				free_tokenlist(t_tokenlist *h);
void				free_cmdlist(t_command_parser *h);
void				free_redirection(t_redirection *h);
void				ft_free_arrays_i(char **arrays, int index);


/*Builtins*/
int					pwd(char **args, char **envp);
int					echo(char **args, char **env);
int					cd(char **args, char **env);
int					export(char **args, char ***env);
int					unset(char **args, char ***env, t_minishell **minishell);
int					ft_env(char **args, char **envp);
void				ft_exit(t_minishell **cur, char **args, char **env);
void				export_no_args(char **env);

#endif