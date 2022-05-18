#include "pipex.h"

/*
void	del_print_tab_ac(int ac, char **av)
{
	int i = -1;
	fprintf( stderr, ""------------current av[i] :------------\n");
	while (++i != ac)
		fprintf( stderr, "av[%d] = %s\n", i, av[i]);
	fprintf( stderr, ""---------------------------------------\n");
	fprintf( stderr, "\n");
}

void	del_print_fds(t_px *px)
{
	fprintf( stderr, "infile =	fd %d\n", px->infile);
	fprintf( stderr, "outfile =	fd %d\n", px->outfile);
	fprintf( stderr, "px_tmp_file =	fd %d\n", px->tmp_file);
	fprintf( stderr, "px->pipefd[0] =	fd %d\n", px->pipefd[0]);
	fprintf( stderr, "px->pipefd[1] =	fd %d\n", px->pipefd[1]);
}

void	del_print_child(t_child child)
{
	fprintf( stderr, "--------struct of child nbr %d-----------\n", child.id);
	fprintf( stderr, "path = %s\n", child.path);
	fprintf( stderr, "cmd = %s\nopt = %s\n", child.cmd[0], child.cmd[1]);
}

void	del_print_main_struct(t_px *px)
{
	del_print_t_entry(px->entry);
	fprintf( stderr, "nbr_cmd =	%d\n", px->nbr_cmd);
	del_print_fds(px);
	del_print_child(px->child);
	del_print_split_path(px->split_path);
}*/

void del_print_split_path(char **path_tab)
{
	int	i = -1;
	fprintf( stderr, "--------path_tab------\n");
	if (path_tab)
		while (path_tab[++i])
			fprintf( stderr, "%d : %s\n", i, path_tab[i]);
	else
		fprintf( stderr, "Env hasn't been found\n");
}

void	v_print_tab_ac(int ac, char **av)
{
	int i = -1;
	fprintf( stderr, "------------current av[i] :------------\n");
	while (++i != ac)
		fprintf( stderr, "av[%d] = %s\n", i, av[i]);
	fprintf( stderr, "---------------------------------------\n");
	fprintf( stderr, "\n");
}

void	v_print_t_entry(t_entry entry)
{
	fprintf( stderr, "ac = %d\n", entry.ac);
	v_print_tab_ac(entry.ac, entry.av);
}

void	v_print_pid_list(int size, int *pid_list)
{
	int	i = -1;
	fprintf( stderr, "---------- pid_list : --------\n");
	while (++i < size)
		fprintf( stderr, "pid_list[%d] = %d\n", i, pid_list[i]);
}

void	v_print_child_struct(t_px *px, t_child *child)
{
	(void) px; 
	fprintf( stderr, "----- child %i -----\n", child->id);
	fprintf( stderr, "path = %s\n", child->path);
	if (child->cmd)
		fprintf( stderr, "cmd = %s & ops = %s\n", child->cmd[0], child->cmd[1]);
	else
		fprintf( stderr, "cmd = %p", child->cmd);
	if (child->prev_fds)
		fprintf( stderr, "prev_fds[0] = %d & prev_fds[1] = %d\n", 
		child->prev_fds[0], child->prev_fds[1]);
	if (child->next_fds)
		fprintf( stderr, "next_fds[0] = %d & next_fds[1] = %d\n", 
		child->next_fds[0], child->next_fds[1]);
	fprintf( stderr, "\n");
}

void	v_print_t_list(t_px *px, t_list *child)
{
	while (child)
	{
		v_print_child_struct(px, child->content);
		child = child->next;
	}
}

void	visual_print_px(t_px *px)
{
	v_print_t_entry(px->entry);
	fprintf( stderr, "infile = %s\n", px->infile);
	fprintf( stderr, "outfile = %s\n", px->outfile);
	fprintf( stderr, "nbr_cmd = %d\n", px->nbr_cmd);
	v_print_pid_list(px->nbr_cmd, px->pid_list);
	if (px->child)
		v_print_t_list(px, px->child);
}