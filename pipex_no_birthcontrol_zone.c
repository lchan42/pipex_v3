/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_no_birthcontrol_zone.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 23:50:54 by lchan             #+#    #+#             */
/*   Updated: 2022/05/23 16:02:17 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	px_child_openfile(t_px *px, t_child *child)
{
	int	file;

	file = -2;
	if (child->id == 0)
	{
		file = open(px->infile, O_RDONLY);
		px_check_open_sucess(file, px->infile, px);
	}
	else if (child->id == px->nbr_cmd - 1)
	{
		if (px->hdoc_flag)
			file = open(px->outfile, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			file = open(px->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		px_check_open_sucess(file, px->outfile, px);
	}
	return (file);
}

void	px_child_exceve(t_px *px, t_child *child)
{
	int	open_file;

	open_file = px_child_openfile(px, child);
	if (px_entrycheck_isaccess_f_x(child->path))
	{
		px_mgmt_redirection(px, child, open_file);
		execve(child->path, child->cmd, px->entry.envp);
	}
	px_close_fd(&open_file);
	if (px->hdoc_flag)
		unlink(px->infile);
	if (ft_strncmp(child->path, "access denied", 13) == 0)
		px_err_permission_denied("");
	else
		px_err_cmd_not_found(child->cmd[0]);
	px_end_struct(px);
	exit(1);
}

void	px_no_birthcontrol_zone(t_px *px, int i, t_child *current_child)
{
	px->pid_list[i] = fork();
	if (px->pid_list[i] == -1)
		px_end_struct_exit(px);
	else if (px->pid_list[i] == 0)
		px_child_exceve(px, current_child);
}
