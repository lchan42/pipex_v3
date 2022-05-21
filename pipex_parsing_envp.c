/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parsing_envp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 23:51:01 by lchan             #+#    #+#             */
/*   Updated: 2022/05/21 23:51:03 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	px_trim_n_add_slash(char **split_path)
{
	char	*tmp;
	int		i;

	i = -1;
	while (split_path[++i])
	{
		tmp = split_path[i];
		split_path[i] = ft_strjoin(tmp, "/");
		free(tmp);
		if (ft_strncmp(split_path[i], "PATH", 4) == 0)
		{
			tmp = split_path[i];
			split_path[i] = ft_strtrim(split_path[i], "PATH=");
			free(tmp);
		}
	}
}

char	*px_find_path_in_envp(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			return (envp[i]);
	return (NULL);
}

char	**px_parsing_path(char **envp)
{
	char	*path;
	char	**split_path;

	path = px_find_path_in_envp(envp);
	split_path = ft_split(path, ':');
	if (split_path)
		px_trim_n_add_slash(split_path);
	return (split_path);
}

/****************************************
 * in order
 * save line that contains PATH in a char *
 * split char *
 * add a '/' at the end of each line
 * return split_path
 * **************************************/