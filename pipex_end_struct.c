#include "pipex.h"

void    px_free_tab(char **tab)
{
    int i;

    i = -1;
    while (tab[++i])
        free(tab[i]);
    free (tab);
}

void    px_close_fds(int *fds)
{
    if (fds[0] > 2)
        px_close_fd(&fds[RD_END]);
    if (fds[1] > 2)
        px_close_fd(&fds[WR_END]);
}

void    px_del_content(t_child *child)
{
    if (!child)
        return ;
    if (child->path)
        free(child->path);
    if (child->cmd)
        px_free_tab(child->cmd);
    if (child->fds)
    {
        px_close_fds(child->fds);
        free(child->fds);
        child->fds = NULL;
    }
    free(child);
    child = NULL;
}

void    px_end_struct(t_px *px)
{
    if (px)
    {
        if (px->pid_list)
            free(px->pid_list);
        if (px->child)
            ft_lstclear(&(px->child), (void*)(*px_del_content));
        free(px);
    }
}

void	px_end_struct_exit(t_px *px)
{
	px_end_struct(px);
	perror(" ");
	exit(errno);
}