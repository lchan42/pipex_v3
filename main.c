/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 00:39:25 by lchan             #+#    #+#             */
/*   Updated: 2022/05/23 11:50:06 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	px_close_all_fds(t_list *child)
{
	while (child)
	{
		px_close_fds(((t_child *)(child->content))->fds);
		child = child->next;
	}
}

void	px_wait_for_pids(t_px *px)
{
	int		child_index;
	int		status;

	child_index = -1;
	while (++child_index < px->nbr_cmd)
		waitpid(px->pid_list[child_index], &status, 0);
}

void	px_init_here_doc(t_px *px)
{
	int		infile;
	char	*gnl;

	infile = open(px->infile, O_RDWR | O_TRUNC | O_CREAT, 0644);
	px_check_open_sucess(infile, px->infile, px);
	while (1)
	{
		gnl = get_next_line_pipex(STDIN_FILENO, px->entry.av[2]);
		if (!gnl)
		{
			close(infile);
			return ;
		}
		ft_putstr_fd(gnl, infile);
		free(gnl);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_px	*px;
	int		child_index;
	t_child	*current_child;

	child_index = -1;
	px = px_init_struct(ac, av, envp);
	if (px->hdoc_flag)
		px_init_here_doc(px);
	//visual_print_px(px);
	while (++child_index < px->nbr_cmd)
	{
		current_child = px_get_child_nod(px->child, child_index);
		px_mgmt_pipe(px, current_child);
		px_no_birthcontrol_zone(px, child_index, current_child);
	}
	px_close_all_fds(px->child);
	px_wait_for_pids(px);
	px_end_struct(px);
	return (0);
}
