#include "pipex.h"

void	px_err_cmd_not_found(char *input)
{
	ft_putstr_fd("./pipex: command not found: ", 2);
	ft_putstr_fd(input, 2);
	ft_putstr_fd("\n", 2);
}

void	px_perror(char *input)
{
	ft_putstr_fd("./pipex: ", 2);
	ft_putstr_fd(input, 2);
	perror(" ");
}

void	px_perr_exit(int n, char *input)
{
	if (n == NOT_ENOUGH_ARG)
		ft_putstr_fd("./pipex: not enough arg\n", 2);
	if (n == PATH_N_ACCESS_NOT_FOUND || n == CMD_NOT_FOUND)
		px_err_cmd_not_found(input);
	if (n != NOT_ENOUGH_ARG)
		px_perror(input);
	exit(errno);
}