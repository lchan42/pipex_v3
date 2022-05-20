#include "pipex.h"

void	px_close_all_fds(t_list *child)
{
	while (child)
	{
		px_close_fds(((t_child *)(child->content))->fds);
		child = child->next;
	}
}

int main(int ac, char **av, char **envp)
{
	t_px	*px;
	int		child_index;
	t_child	*current_child;
	int		status;

	child_index = -1;
	px_entrycheck_ac_file(ac, av);
	px = px_init_struct(ac, av, envp);
	while (++child_index < px->nbr_cmd)
	{
		current_child = px_get_child_nod(px->child, child_index);
		px_mgmt_pipe(px, current_child);
		px_no_birthcontrol_zone(px, child_index, current_child);
	}
	px_close_all_fds(px->child);
	child_index = -1;
	while (++child_index < px->nbr_cmd)
		waitpid(px->pid_list[child_index], &status, 0);
	px_end_struct(px); 
	return(0);
}
