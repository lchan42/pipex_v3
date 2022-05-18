#include "pipex.h"

void    px_child_exceve(t_px *px, t_child *child)
{
    px_mgmt_redirection(px, child);
    if (px_entrycheck_isaccess_f_x(child->path))
    {
        fprintf(stderr, "child %d, is gonna do his execve\n", child->id);
        execve(child->path, child->cmd, px->entry.envp);
    }
    else
    {
        px_err_cmd_not_found(child->cmd[0]);
        exit(errno);
    }
}

void    px_no_birthcontrol_zone(t_px *px, int i, t_child *current_child)
{
    px->pid_list[i] = fork();
    if (px->pid_list[i] == -1)
        px_end_struct_exit(px);
    else if (px->pid_list[i] == 0)
        px_child_exceve(px, current_child);
}