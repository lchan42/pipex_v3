#include "pipex.h"

void    px_close_prev_fd(t_px *px, t_child *child, int fd_end)
{
    t_child *prev_child;

    prev_child = px_get_prev_nod(px->child, child->id);
    if (prev_child)
        px_close_fd(&prev_child->fds[fd_end]);
}

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