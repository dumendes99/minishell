/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elima-me <elima-me@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 18:26:18 by elima-me          #+#    #+#             */
/*   Updated: 2022/01/26 23:20:45 by elima-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_is_number(char *str)
{
	int	count;

	count = -1;
	while (str[++count])
		if (!ft_isdigit(str[count]))
			return (0);
	return (1);
}

static int	too_many_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 1)
		return (1);
	return (0);
}

void	ft_exit(t_exec *exec)
{
	int	exit_code;

	if (too_many_args(exec->args))
	{
		ft_free(exec);
		ft_putstr_fd("exit: too many arguments\n", 2);
		exit(1);
	}
	else if (exec->args[0] && (!ft_is_number(exec->args[0])))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(exec->args[0], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ft_free(exec);
		exit(2);
	}
	else if (exec->args[0])
	{
		exit_code = ft_atoi(exec->args[0]);
		ft_putstr_fd("exit\n", 1);
		ft_free(exec);
		exit(exit_code);
	}
	else
	{
		ft_free(exec);
		ft_putstr_fd("exit\n", 1);
		exit (EXIT_SUCCESS);
	}
}
