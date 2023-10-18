/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomteixeira <tomteixeira@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:22:49 by toteixei          #+#    #+#             */
/*   Updated: 2023/10/18 11:01:42 by tomteixeira      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int     cd_home()
{
    char *home;

    home = getenv("HOME");
    if (home == NULL)
    {
        ft_putstr_fd("bash: cd: HOME not set\n", 2);
        return (EXIT_FAILURE);
    }
    if (chdir(home) != 0)
    {
        printf("bash: cd: %s: No such file or directory\n", home);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

int     cd(char **args, char **env)
{
    (void)env;
    if (!args[1])
        return (cd_home());
    if (chdir(args[1]) != 0)
    {
        printf("bash: cd: %s: No such file or directory\n", args[1]);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);      
}