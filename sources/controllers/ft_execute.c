/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyuri-go <lyuri-go@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 19:41:12 by lyuri-go          #+#    #+#             */
/*   Updated: 2022/01/27 19:17:59 by lyuri-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_execute_cmd(t_exec *exec, int shouldfork)
{
	if (!ft_strncmp(exec->cmd, "echo", 4) && ft_strlen(exec->cmd) == 4)
		ft_echo(exec->args);
	else if (!ft_strncmp(exec->cmd, "cd", 2) && ft_strlen(exec->cmd) == 2)
		return (ft_cd(exec->args, shouldfork));
	else if (!ft_strncmp(exec->cmd, "pwd", 3) && ft_strlen(exec->cmd) == 3)
		ft_pwd();
	else if (!ft_strncmp(exec->cmd, "export", 6) && ft_strlen(exec->cmd) == 6)
		ft_export(exec->args);
	else if (!ft_strncmp(exec->cmd, "unset", 5) && ft_strlen(exec->cmd) == 5)
		ft_unset(exec->args);
	else if (!ft_strncmp(exec->cmd, "env", 3) && ft_strlen(exec->cmd) == 3)
		ft_env();
	else if (!ft_strncmp(exec->cmd, "exit", 4) && ft_strlen(exec->cmd) == 4)
		ft_exit(exec);
	else if (exec->cmd[0])
	{
		ft_exec_bin(exec->cmd, exec->args, shouldfork);
		if (!shouldfork)
			exit(EXIT_SUCCESS);
		return ;
	}
	if (!shouldfork)
		exit(EXIT_SUCCESS);
	mini_s()->last_exec_code = 0;
}

void	ft_execute(char *line)
{
	t_exec	*exec_info;

	if (!line)
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	exec_info = malloc(sizeof(t_exec) * 4000);
	if (ft_validate_quotes(line))
		return ;
	ft_parser(line, exec_info);
	if (ft_validate_redirects(exec_info))
	{
		ft_free_parser(exec_info);
		return ;
	}
	if (exec_info->next_type == LAST)
		ft_execute_cmd(&exec_info[0], 1);
	else
		ft_redirects(exec_info, 0, -1, 0);
	ft_free_parser(exec_info);
}
