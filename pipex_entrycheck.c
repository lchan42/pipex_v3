#include "pipex.h"

void    px_entrycheck_ac_file(int ac, char **av)
{
//    char *infile;
//    char *outfile;

    (void) av;
//    infile = av[1];
//    outfile = av[ac - 1];
    if (ac <= 4)
        px_perr_exit(NOT_ENOUGH_ARG, " ");
/*    if (access(infile, F_OK) == -1)
        px_perr_exit(CANT_FIND_INFILE, infile);
    else if (access(infile, R_OK) == -1)
        px_perr_exit(CANT_READ_INFILE, infile);
    else if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
        px_perr_exit(CANT_WRITE_OUTFILE, outfile);*/
}

int px_entrycheck_isaccess_f_x(char *path)
{
    if (access(path, F_OK) != 0 && access(path, X_OK) != 0)
        return (0);
    return (1);
}