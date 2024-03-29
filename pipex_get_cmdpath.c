/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_get_cmdpath.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 23:50:14 by lchan             #+#    #+#             */
/*   Updated: 2022/05/23 15:16:26 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	px_find_last_slash(char *path)
{
	int	i;
	int	slash;

	i = -1;
	slash = i + 1;
	while (path[++i])
		if (path[i] == '/')
			slash = i + 1;
	return (slash);
}

char	*px_creat_cmdpath(char *cmd, char **split_path)
{
	int		i;
	char	*path;

	i = -1;
	while (split_path[++i])
	{
		path = ft_strjoin(split_path[i], cmd);
		if (px_entrycheck_isaccess_f_x(path))
			return (path);
		free(path);
	}
	return (ft_strdup(cmd));
}

void	px_set_cmd_n_path(char *cmd, char **split_path, t_child *child)
{
	char	*tmp;

	if (ft_strlen(cmd) == 0)
	{
		child->cmd = ft_split(cmd, ' ');
		child->path = ft_strdup("access denied\n");
	}
	else if (px_entrycheck_isaccess_f_x(cmd) || !split_path)
	{
		if (ft_strchr(cmd, ' '))
			child->path = ft_strtrim(cmd, ft_strchr(cmd, ' '));
		else
			child->path = ft_strdup(cmd);
		tmp = ft_strdup(cmd + px_find_last_slash(child->path));
		child->cmd = ft_split(tmp, ' ');
		free(tmp);
	}
	else
	{
		if (cmd[0] != ' ')
			child->cmd = ft_split(cmd, ' ');
		else
			child->cmd = ft_split(cmd, 0);
		child->path = px_creat_cmdpath(child->cmd[0], split_path);
	}
}
