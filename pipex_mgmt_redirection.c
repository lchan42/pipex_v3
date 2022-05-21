#include "pipex.h"

int ft_strcmp(const char *s1, const char *s2)
{
    size_t min_len;
    int len_s1;
    int len_s2;

    if (!s1 || !s2)
        min_len = 0;
    else
    {
        len_s1 = ft_strlen(s1);
        len_s2 = ft_strlen(s2);
    }
    if (len_s1 < len_s2)
        min_len = len_s1;
    else
        min_len = len_s2;
    return(ft_strncmp(s1, s2, min_len + 1));
}

int     px_init_here_doc(t_px *px)
{
    int infile;
    char *gnl;
    int limiter_len;

    infile = open(px->infile, O_RDWR | O_TRUNC | O_CREAT, 0644);
    limiter_len = ft_strlen(px->entry.av[2]);
    px_check_open_sucess(infile, px->infile, px);
    while (1)
    {
        gnl = get
        if (strcmp(px->entry.av[2], gnl) == 0);
            break ;
    }

    return (infile);
}

void    px_firstborn_dup(t_px *px, t_child *child)
{
    int infile;
    int here_doc_flag;

    here_doc_flag = ft_strncmp(px->infile, "here_doc", 9);
    if (here_doc_flag == 0)
        infile = px_init_here_doc;
    else
    {
        infile = open(px->infile, O_RDONLY);
        px_check_open_sucess(infile, px->infile, px);
    }
    if (dup2(infile, STDIN_FILENO) == -1
        || dup2(child->fds[WR_END], STDOUT_FILENO) == -1)
        px_end_struct_exit(px);
    px_close_fd(&infile);
    if (here_doc_flag == 0)
        unlink(infile);
    px_close_fds(child->fds);
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
    px_close_fds(prev_child->fds);
}

void    px_interborn_dup(t_px *px, t_child *child, t_child *prev_child)
{
    if (dup2(prev_child->fds[RD_END], STDIN_FILENO) == -1
        || dup2(child->fds[WR_END], STDOUT_FILENO) == -1)
        px_end_struct_exit(px);
    px_close_fds(prev_child->fds);
    px_close_fds(child->fds);
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
