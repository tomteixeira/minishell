/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomteixeira <tomteixeira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:22:57 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/26 17:12:10 by tomteixeira      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    echo_bis(char **args, int i, int opt)
{
    while (args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }
    if (opt == 0)
        printf("\n");
}

int     echo(char **args, char **env)
{
    int opt;
    int i;

    (void)env;
    opt = 0;
    i = 1;
    if (!args[i])
    {
        printf("\n");
        return (EXIT_SUCCESS);
    }
    if (ft_strcmp(args[i], "-n") == 0)
    {
        opt = 1;
        i++;
    }
    if (!args[i])
    {
        printf("\n");
        return (EXIT_SUCCESS);
    }
    echo_bis(args, i, opt);
    return (EXIT_SUCCESS);
}
