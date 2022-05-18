#include "pipex.h"

void    px_free_tab(char **tab)
{
    int i;

    i = -1;
    while (tab[++i])
        free(tab[i]);
    free (tab);
}

void    px_close_free_fds(int *fds)
{
        if (fds[0] > 2)
            close (fds[0]);
        if (fds[1] > 2)
            close (fds[1]);
        free(fds);
        fds = NULL;
}

void    px_del_content(t_child *child)
{
    if (!child)
        return ;
    if (child->path)
        free(child->path);
    if (child->cmd)
        px_free_tab(child->cmd);
    if (child->prev_fds)
        px_close_free_fds(child->prev_fds);
    if (child->next_fds)
        px_close_free_fds(child->next_fds);
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