/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_fonctions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toteixei <toteixei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 15:03:19 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/05 17:13:57 by toteixei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		command_len(t_lexer **lexer)
{
	int	i;
	int	count;
	
	i = (*lexer)->position;
	count = 0;
	while ((*lexer)->input_string[i] != '\0' 
		&& ft_isalpha((*lexer)->input_string[i]))
	{
		i++;
		count++;
	}
	return (count);
}

int		string_len(t_lexer **lexer)
{
	int		i;
	int		count;
	char	quote;
	
	i = (*lexer)->position;
	count = 1;
	quote = (*lexer)->input_string[i++];
	while ((*lexer)->input_string[i] != '\0')
	{
		if ((*lexer)->input_string[i] == quote
			&& (*lexer)->input_string[i - 1] != '\\')
		{
			count++;
			return (count);
		}
		i++;
		count++;
	}
	return (count);
}

int	option_len(t_lexer **lexer)
{
	int	i;
	int	count;
	
	i = (*lexer)->position + 1;
	count = 1;
	while ((*lexer)->input_string[i] != '\0' && ft_word_char((*lexer)->input_string[i]))
	{
		i++;
		count++;
	}
	return (count);
}

int	ft_word_char(int c)
{
	if (c == '|' || c == '\'' || c == '$' || c == '\"' || c == '>' || c == '<')
		return (0);
	if (c > 32 && c < 127)
		return (1);
	else 
		return (0);
}

// void	*ft_realloc(void* ptr, size_t new_size)
// {
//     void	*new_ptr;
// 	size_t	old_size;
// 	size_t	copy_size;
	
// 	if (new_size == 0)
// 	{
//         free(ptr);
//         return NULL;
//     }
//     if (ptr == NULL)
//         return malloc(new_size);
//     new_ptr = malloc(new_size);
//     if (new_ptr != NULL) {
//         // Copy the content from the old block to the new block
//         old_size = malloc_usable_size(ptr);  // Requires GNU extension
//         copy_size = (new_size < old_size) ? new_size : old_size;
//         ft_memcpy(new_ptr, ptr, copy_size);

//         // Free the old block
//         free(ptr);
//     }

//     return new_ptr;
// }