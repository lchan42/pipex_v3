#include "pipex.h"

int    px_entrycheck_ac_file(int ac, char **av)
{
    if (ft_strncmp(av[1], "here_doc", 9) == 0)
    {
        if (ac <= 5)
            px_perr_exit(NOT_ENOUGH_ARG, " ");
        fprintf(stderr, "here_doc is here\n");
        return (1);
    }
    else if (ac <= 4)
        px_perr_exit(NOT_ENOUGH_ARG, " ");
    return (0);
}
/*****************************************
 * Using a n = 9 in ft_strncmp
 *      see if the entry is just "here_doc" and not "here_doc"+garbage
 * ***************************************/

int px_entrycheck_isaccess_f_x(char *path)
{
    if (access(path, F_OK) != 0 && access(path, X_OK) != 0)
        return (0);
    return (1);
}