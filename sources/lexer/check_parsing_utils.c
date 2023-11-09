/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:56:36 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/09 16:58:31 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	merge_tokenlist(t_tokenlist **head_a, t_tokenlist **head_b)
{
	t_tokenlist	*lastnode_a;

	lastnode_a = *head_a;
	while (lastnode_a->next)
		lastnode_a = lastnode_a->next;
	lastnode_a->next = *head_b;
}
