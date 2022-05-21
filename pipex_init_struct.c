#include "pipex.h"

t_child *px_init_child_block(char *cmd, int i, char **split_path)
{
    t_child *tmp;

    tmp = malloc(sizeof(t_child));
    if (!tmp)
        return (NULL);
    tmp->id = i;
    px_set_cmd_n_path(cmd, split_path, tmp);
    tmp->fds = (int *)ft_calloc(2, sizeof(int));
    if (!tmp->path || !tmp->cmd || !tmp->fds)
        px_del_content(tmp);
    return(tmp);
}

t_list *px_init_t_list_nod(char *cmd, int i, char **split_path)
{
    t_child *child;

    child = px_init_child_block(cmd, i, split_path);
    return (ft_lstnew(child));
}

t_list  *px_init_t_list(t_px *px, char **cmd)
{    
    int     i;
    char    **split_path;
    t_list  *nod;
    t_list  *child;

    i = -1;
    split_path = px_parsing_path(px->entry.envp);
    child = NULL;
    while (++i < px->nbr_cmd)
    {
        nod = px_init_t_list_nod(cmd[i], i, split_path);
        ft_lstadd_back(&child, nod);
    }
    if (split_path)
        px_free_tab(split_path);
    return (child);   
}

void    init_t_entry(int ac, char **av, char **envp, t_px *px)
{
    px->entry.ac = ac;
    px->entry.av = av;
    px->entry.envp = envp;
}

t_px    *px_init_struct(int ac, char **av, char **envp)
{
    t_px    *px;
    int     shift;
    int     here_doc;

    here_doc = px_entrycheck_ac_file(ac, av); 
    shift = 2 + here_doc;
    px = malloc(sizeof(t_px));
    px_check_malloc_success(px, px);
    init_t_entry(ac, av, envp, px);
    px->infile = av[1];
    px->outfile = av[ac - 1];
    px->nbr_cmd = ac - (shift + 1);
    px->pid_list = (int *)ft_calloc(px->nbr_cmd, sizeof(int));
    px_check_malloc_success(px, px->pid_list);
    px->child = px_init_t_list(px, av + shift);
    return (px);
}