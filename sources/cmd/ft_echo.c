/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elima-me <elima-me@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:10:40 by elima-me          #+#    #+#             */
/*   Updated: 2021/11/30 21:50:19 by elima-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_echo(char **argv)
{
	int	i;
	int	flag;

	if (argv[0] == NULL)
	{
		write(1, "\n", 1);
		return ;
	}
	flag = ft_strncmp("-n", argv[0], 3);
	i = -1;
	if (!flag)
		i++;
	while (argv[++i])
	{
		ft_putstr_fd(argv[i], 1);
		write(1, " ", 1);
	}
	if (flag)
		write(1, "\n", 1);
}