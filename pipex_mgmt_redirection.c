#include "pipex.h"

/*
void    px_dup2_n_close(int *fd, int fd2)
{
    dup2(fd, fd2);
    px_close_fd(fd);
}
*/
void    px_firstborn_redirect(t_px *px, t_child *child)
{
    int infile;
    fprintf(stderr, "child %d, is doing his redirection(first)\n", child->id);
    px_close_fd(&(child->next_fds[RD_END]));
    infile = open(px->infile, O_RDONLY);
    px_check_open_sucess(infile, px->infile, px);
    if (dup2(infile, STDIN_FILENO) == -1
        || dup2(child->next_fds[WR_END], STDOUT_FILENO) == -1)
        px_end_struct_exit(px);
    px_close_fd(&infile);
}

void    px_lastborn_redirect(t_px *px, t_child *child)
{
    int outfile;
    
    fprintf(stderr, "child %d, is doing his redirection(last)\n", child->id);
    px_close_fd(&(child->prev_fds[WR_END]));
    outfile = open(px->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    px_check_open_sucess(outfile, px->outfile, px);
    if (dup2(outfile, STDOUT_FILENO) == -1
    || dup2(child->prev_fds[RD_END], STDIN_FILENO) == -1)
        px_end_struct_exit(px);
    px_close_fd(&outfile);
}

void    px_interborn_redirect(t_px *px, t_child *child)
{
    fprintf(stderr, "child %d, is doing his redirection (inter)\n", child->id);
    px_close_fd(&(child->prev_fds[WR_END]));
    px_close_fd(&(child->next_fds[RD_END]));
    if (dup2(child->prev_fds[RD_END], STDIN_FILENO) == -1
    || dup2(child->next_fds[WR_END], STDOUT_FILENO) == -1)
        px_end_struct_exit(px);
}


void    px_mgmt_redirection(t_px *px, t_child *child)
{
    if (child->id == 0)
        px_firstborn_redirect(px, child);
    else if (child->id == px->nbr_cmd - 1)
        px_lastborn_redirect(px, child);
    else
        px_interborn_redirect(px, child);
    //exceve(child->path, child->cmd, px->entry.envp);
    //px_end_struct(px);
    //exit(errno);
    //px_end_struct(px); //gonna have to end and exit with error code
}
