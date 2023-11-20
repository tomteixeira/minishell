/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hebernar <hebernar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:38:37 by toteixei          #+#    #+#             */
/*   Updated: 2023/11/20 15:01:32 by hebernar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_int_i(int **arrays, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(arrays[i]);
		i++;
	}
	free(arrays);
}

void	ft_free_arrays_i(char **arrays, int index)
{
	int	i;

	i = -1;
	if (index == -1)
	{
		while (arrays[++i])
			free(arrays[i]);
		free(arrays);
		return ;
	}
	while (++i < index)
	{
		if (arrays[i])
			free(arrays[i]);
	}
	if (arrays)
		free(arrays);
}
