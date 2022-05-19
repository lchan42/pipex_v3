#include "pipex.h"

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
		//v_print_child_struct(px, current_child);
		px_no_birthcontrol_zone(px, child_index, current_child);
	}
	child_index = -1;
	while (++child_index < px->nbr_cmd)
	{
		current_child = px_get_child_nod(px->child, child_index);
		px_close_fds(current_child->fds);
	}
	child_index = -1;
	while (++child_index < px->nbr_cmd)
	{
		fprintf(stderr, "waiting for pid %d to finish\n", px->pid_list[child_index]);
		waitpid(px->pid_list[child_index], &status, 0);
	}
	px_end_struct(px);
	return(0);
}
