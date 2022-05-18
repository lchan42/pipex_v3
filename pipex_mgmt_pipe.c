#include "pipex.h"

void    px_swap_fds(int **fds1, int **fds2)
{
    int *tmp;

    tmp = *fds1;
    *fds1 = *fds2;
    *fds2 = tmp; 
}

void    px_firstborn_legacy(t_px *px, t_child *child)
{
    child->prev_fds[RD_END] = -2;
    child->prev_fds[WR_END] = -2;
    if (pipe(child->next_fds) == -1)
        px_end_struct_exit(px);
}

void    px_lastborn_legacy(t_px *px, t_child *child)
{
    (void) px;

    px_close_fd(&(child->prev_fds[RD_END]));
    px_close_fd(&(child->prev_fds[WR_END]));
    px_swap_fds(&(child->prev_fds), &(child->next_fds));
}

void    px_interborn_legacy(t_px *px, t_child *child)
{
    px_close_fd(&(child->prev_fds[RD_END]));                //close old fds
    px_close_fd(&(child->prev_fds[WR_END]));                //close old fds
    px_swap_fds(&(child->prev_fds), &(child->next_fds));    //next fds 
    if (pipe(child->next_fds) == -1)
        px_end_struct_exit(px);
}

void    px_mgmt_pipe(t_px *px, t_child *child)
{
    if (child->id == 0)
        px_firstborn_legacy(px, child);
    else if (child->id == px->nbr_cmd - 1)
        px_lastborn_legacy(px, child);
    else
        px_interborn_legacy(px, child);
}

/*
void    px_init_child(t_px *px, int i)
{
    int shift;

    shift = 2;
     px->child.id = i;
     px_init_cmd_n_path(px, px->entry.av[i + shift]);
}
*/