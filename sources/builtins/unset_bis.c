/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:23:21 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/21 15:54:48 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_local(char *var, t_minishell **minishell)
{
	t_env_var	*cur;

	cur = (*minishell)->env_var;
	while (cur)
	{
		if (ft_strncmp(var, cur->key, ft_strlenchr(cur->key, '=')) == 0)
			return (1);
		cur = cur->next;
	}
	return (0);
}
