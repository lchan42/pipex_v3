#include "pipex.h"

void    px_child_exceve(t_px *px, t_child *child)
{
    px_mgmt_redirection(px, child);
    if (px_entrycheck_isaccess_f_x(child->path))
    {
        //fprintf(stderr, "child %d, is gonna do his execve\n", child->id);
        execve(child->path, child->cmd, px->entry.envp);
        fprintf(stderr, "Failed to execute %s\n", child->path);
        exit(1);
    }
    else
    {
        fprintf(stderr, "WE ARE IN  THE ELSE\n");
        px_err_cmd_not_found(child->cmd[0]);
        px_end_struct_exit(px);
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