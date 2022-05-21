/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_mgmt_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 23:50:41 by lchan             #+#    #+#             */
/*   Updated: 2022/05/21 23:50:43 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    px_close_first_fds(t_list *head)
{
    while (head->next)
    {
         if (((t_child *)(head->content))->fds[0] > 2)
         {
            px_close_fd(&(((t_child *)(head->content))->fds[RD_END]));
            px_close_fd(&(((t_child *)(head->content))->fds[WR_END]));
            return ;
         }
         head = head->next;
    }
}

void    px_pipe_fds(t_px *px, t_child *child)
{
    if (pipe(child->fds) == -1)
        px_end_struct_exit(px);
}

void    px_mgmt_pipe(t_px *px, t_child *child)
{
    if (child->id != px->nbr_cmd - 1)
        px_pipe_fds(px, child);
    if (child->id > 1)
        px_close_first_fds(px->child);
}