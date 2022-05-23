/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_mgmt_redirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 23:50:48 by lchan             #+#    #+#             */
/*   Updated: 2022/05/23 16:03:48 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	px_firstborn_dup(t_px *px, t_child *child, int infile)
{
	//int	infile;

	//infile = open(px->infile, O_RDONLY);
	//px_check_open_sucess(infile, px->infile, px);
	if (dup2(infile, STDIN_FILENO) == -1
		|| dup2(child->fds[WR_END], STDOUT_FILENO) == -1)
		px_end_struct_exit(px);
	px_close_fd(&infile);
	if (px->hdoc_flag)
		unlink(px->infile);
	px_close_fds(child->fds);
}

void	px_lastborn_dup(t_px *px, t_child *prev_child, int outfile)
{
	//int		outfile;

/*	if (px->hdoc_flag)
		outfile = open(px->outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else
		outfile = open(px->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	px_check_open_sucess(outfile, px->outfile, px);*/
	if (dup2(prev_child->fds[RD_END], STDIN_FILENO) == -1
		|| dup2(outfile, STDOUT_FILENO) == -1)
		px_end_struct_exit(px);
	px_close_fd(&outfile);
	px_close_fds(prev_child->fds);
}

void	px_interborn_dup(t_px *px, t_child *child, t_child *prev_child)
{
	if (dup2(prev_child->fds[RD_END], STDIN_FILENO) == -1
		|| dup2(child->fds[WR_END], STDOUT_FILENO) == -1)
		px_end_struct_exit(px);
	px_close_fds(prev_child->fds);
	px_close_fds(child->fds);
}

void	px_mgmt_redirection(t_px *px, t_child *child, int open_file)
{
	if (child->id == 0)
		px_firstborn_dup(px, child, open_file);
	else if (child->id == px->nbr_cmd - 1)
		px_lastborn_dup(px, px_get_prev_nod(px->child, child->id), open_file);
	else
		px_interborn_dup(px, child, px_get_prev_nod(px->child, child->id));
}
