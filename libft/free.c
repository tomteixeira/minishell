/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 16:38:37 by toteixei          #+#    #+#             */
/*   Updated: 2023/03/16 18:21:43 by toteixei         ###   ########.fr       */
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

	i = 0;
	while (i < index)
	{
		free(arrays[i]);
		i++;
	}
	free(arrays);
}
