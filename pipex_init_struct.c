#include "pipex.h"

t_child *px_init_child_block(char *cmd, int i, char **split_path)
{
    t_child *tmp;

    tmp = malloc(sizeof(t_child));
    if (!tmp)
        return (NULL);
    tmp->id = i;
    px_init_cmd_n_path(cmd, split_path, tmp);
    //tmp->prev_fds = (int *)ft_calloc(2, sizeof(int));
    tmp->prev_fds = NULL;
    tmp->next_fds = (int *)ft_calloc(2, sizeof(int));
    if (!tmp->path || !tmp->cmd || !tmp->prev_fds || !tmp->next_fds)
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

    shift = 2; //add function px_getshift(av); if here doc bonus
    px = malloc(sizeof(t_px));
    px_check_malloc_success(px, px);
    init_t_entry(ac, av, envp, px);
    px->infile = av[1];
    px->outfile = av[ac - 1];
    px->nbr_cmd = ac - (shift + 1);
    px->pid_list = (int *)ft_calloc(px->nbr_cmd, sizeof(int));
    //px->pid_list = (int *)malloc (sizeof(int) * px->nbr_cmd); //depends if I prefere to use calloc or malloc
    px_check_malloc_success(px, px->pid_list);
    px->child = px_init_t_list(px, av + shift);
    return (px);
}

/*
    px->infile = open(av[1], O_RDONLY);
    checkinit_open_sucess(px->infile, av[1], px);
    px->outfile = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
    checkinit_open_sucess(px->outfile, av[ac - 1], px);
    px->tmp_file = open("px_tmp_file", O_RDWR | O_APPEND | O_CREAT, 0644);
    checkinit_open_sucess(px->tmp_file, "px_tmp_file", px);
    px->split_path = px_parsing_path(envp);
    return (px);
}*/































/*
t_px    *px_init_struct(int ac, char **av, char **envp)
{
    t_px    *px;

    px = malloc(sizeof(t_px));
    checkinit_struct_sucess(px);
    px->entry.ac = ac;
    px->entry.av = av;
    px->entry.envp = envp;
    px->nbr_cmd = ac - 3;
    px->infile = open(av[1], O_RDONLY);
    checkinit_open_sucess(px->infile, av[1], px);
    px->outfile = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
    checkinit_open_sucess(px->outfile, av[ac - 1], px);
    px->tmp_file = open("px_tmp_file", O_RDWR | O_APPEND | O_CREAT, 0644);
    checkinit_open_sucess(px->tmp_file, "px_tmp_file", px);
    px->split_path = px_parsing_path(envp);
    px->pid_list = (int *)malloc (sizeof(int) * px->nbr_cmd);
    checkinit_malloc_success(px);
    px->child.path = NULL;
    px->child.cmd = NULL;
    return (px);
}*/

/*
t_px    *px_init_struct(int ac, char **av, char **envp)
{
    t_px    *px;

    px = NULL;
    px = malloc(sizeof(t_px));
    checkinit_struct_sucess(px);
    px->entry.ac = ac;
    px->entry.av = av;
    px->entry.envp = envp;
    px->nbr_cmd = ac - 3;
    px->infile = open(av[1], O_RDONLY);
    checkinit_open_sucess(px->infile, av[1], px);
    px->outfile = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
    checkinit_open_sucess(px->outfile, av[ac - 1], px);
    px->tmp_file = open("px_tmp_file", O_RDWR | O_APPEND | O_CREAT, 0644);
    checkinit_open_sucess(px->tmp_file, "px_tmp_file", px);
    px_init_pipe(px);
    px->split_path = px_parsing_path(envp);
    px->pid_list = (int *)malloc (sizeof(int) * px->nbr_cmd);
    checkinit_malloc_success(px);
    px->child.path = NULL;
    px->child.cmd = NULL;
    return (px);
}
*/
/*
void    px_init_struct(int ac, char **av, char **envp, t_px *px)
{
    //px = NULL;
    //px = malloc(sizeof(t_px));
    //check_struct_sucess(px);
    px->entry.ac = ac;
    px->entry.av = av;
    px->entry.envp = envp;
    px->nbr_cmd = ac - 3;
    px->infile = open(av[1], O_RDONLY);
    check_open_sucess(px->infile, av[1], px);
    px->outfile = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
    check_open_sucess(px->outfile, av[ac - 1], px);
    px->tmp_file = open("px_tmp_file", O_RDWR | O_TRUNC | O_CREAT, 0644);
    check_open_sucess(px->tmp_file, "px_tmp_file", px);
    //px->split_path = px_parsing_path(envp);
    px->split_path = NULL;
    px->child.path = NULL;
    px->child.cmd = NULL;
}*/