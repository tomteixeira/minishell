/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:23:17 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/09 17:07:01 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd(char **args, char **envp)
{
	char	cwd[PATH_MAX];

	(void)args;
	(void)envp;
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (EXIT_FAILURE);
	printf("%s\n", cwd);
	return (EXIT_SUCCESS);
}
