/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 23:51:14 by lchan             #+#    #+#             */
/*   Updated: 2022/05/22 00:35:10 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	px_check_malloc_success(t_px *px, void *elem)
{
	if (!elem)
	{
		perror("./pipex");
		px_end_struct(px);
		exit(errno);
	}
}

void	px_check_open_sucess(int fd, char *input, t_px *px)
{
	if (fd == -1)
	{
		px_perror(input);
		px_end_struct(px);
		exit (errno);
	}
}

void	px_close_fd(int *fd)
{
	if (*fd > 2)
		close(*fd);
	*fd = -2;
}

t_child	*px_get_child_nod(t_list *child, int index)
{
	while (child)
	{
		if (((t_child *)(child->content))->id == index)
			return ((t_child *)child->content);
		child = child->next;
	}
	return (NULL);
}

t_child	*px_get_prev_nod(t_list *child, int index)
{
	if (index > 0)
	{
		while (child)
		{
			if (((t_child *)(child->content))->id == index - 1)
				return ((t_child *)child->content);
			child = child->next;
		}
	}
	return (NULL);
}
