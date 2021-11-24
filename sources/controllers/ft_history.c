/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elima-me <elima-me@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 19:10:29 by lyuri-go          #+#    #+#             */
/*   Updated: 2021/11/24 19:07:05 by elima-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*ft_get_history_file_path(void)
{
	char	*home_path;
	char	*history_path;

	home_path = ft_strdup(ft_get_env("HOME"));
	history_path = ft_strjoin(home_path, HISTORY_FILE);
	free(home_path);
	return (history_path);
}

void	ft_load_history(void)
{
	int		fd;
	char	*line;
	char	*history_path;

	history_path = ft_get_history_file_path();
	fd = open(history_path, O_CREAT | O_RDWR | O_APPEND, 0777);
	while (get_next_line(fd, &line) > 0)
	{
		add_history(line);
		free(line);
	}
	close(fd);
	free(history_path);
}

void	ft_add_history(char *cmd)
{
	int		fd;
	char	*history_path;

	if (!cmd[0])
		return ;
	history_path = ft_get_history_file_path();
	fd = open(history_path, O_CREAT | O_RDWR | O_APPEND, 0777);
	ft_putstr_fd(cmd, fd);
	ft_putstr_fd("\n", fd);
	add_history(cmd);
	close(fd);
	free(history_path);
}
