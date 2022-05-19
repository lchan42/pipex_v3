#include "pipex.h"

/*
void    px_dup2_n_close(int *fd, int fd2)
{
    dup2(fd, fd2);
    px_close_fd(fd);
}
*/


void    px_firstborn_dup(t_px *px, t_child *child)
{
    int infile;

  //fprintf(stderr, "child %d, is doing his redirection(first)\n", child->id);
    infile = open(px->infile, O_RDONLY);
    px_check_open_sucess(infile, px->infile, px);
    if (dup2(infile, STDIN_FILENO) == -1
        || dup2(child->fds[WR_END], STDOUT_FILENO) == -1)
        px_end_struct_exit(px);
    px_close_fd(&infile);
    px_close_fd(&(child->fds[RD_END]));
    //px_close_fd(&(child->fds[WR_END]));
}

void    px_lastborn_dup(t_px *px, t_child *child, t_child *prev_child)
{
    int outfile;
    (void)  child;

    
    outfile = open(px->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    px_check_open_sucess(outfile, px->outfile, px);
    if (dup2(prev_child->fds[RD_END], STDIN_FILENO) == -1
        || dup2(outfile, STDOUT_FILENO) == -1)
        px_end_struct_exit(px);
    px_close_fd(&outfile);
    px_close_fd(&(prev_child->fds[WR_END]));
    //px_close_fd(&(prev_child->fds[RD_END]));
}

void    px_interborn_dup(t_px *px, t_child *child, t_child *prev_child)
{
    //fprintf(stderr, "child %d, is doing his redirection (inter)\n", child->id);

    if (dup2(prev_child->fds[RD_END], STDIN_FILENO) == -1
        || dup2(child->fds[WR_END], STDOUT_FILENO) == -1)
        px_end_struct_exit(px);
    px_close_fd(&(prev_child->fds[WR_END]));
    //px_close_fd(&(child->fds[RD_END]));
    px_close_fd(&(child->fds[WR_END]));
}


void    px_mgmt_redirection(t_px *px, t_child *child)
{
    if (child->id == 0)
        px_firstborn_dup(px, child);
    else if (child->id == px->nbr_cmd - 1)
        px_lastborn_dup(px, child, px_get_prev_nod(px->child, child->id));
    else
        px_interborn_dup(px, child, px_get_prev_nod(px->child, child->id));
}
