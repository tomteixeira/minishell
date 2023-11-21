/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:22:53 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/21 16:07:42 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	set_and_update_new_env(char *var, char ***env)
{
	char	**new_env;

	new_env = set_new_env(var, *env);
	ft_free_arrays_i(*env, -1);
	*env = new_env;
	if (!*env)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
