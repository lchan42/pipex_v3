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
/*
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
*/


/*
void    px_firstborn_legacy(t_px *px, t_child *child)
{
    if (pipe(child->next_fds) == -1)
        px_end_struct_exit(px);
}

void    px_lastborn_legacy(t_px *px, t_child *child)
{
    t_child *prev_child;

    prev_child = px_get_prev_nod(px->child, child->id);
    child->fds = prev_child->fds;
}

void    px_interborn_legacy(t_px *px, t_child *child)
{
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
    if (child->id > 1)
        px_close_first_fds(px->child);
}
*/

