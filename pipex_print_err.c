/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_print_err.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 23:51:07 by lchan             #+#    #+#             */
/*   Updated: 2022/05/22 00:43:34 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	px_err_cmd_not_found(char *input)
{
	char	*err_msg;
	char	*tmp;

	tmp = ft_strjoin("./pipex: command not found: ", input);
	err_msg = ft_strjoin(tmp, "\n");
	free(tmp);
	ft_putstr_fd(err_msg, 2);
	free(err_msg);
}

void	px_err_permission_denied(char *input)
{
	char	*err_msg;
	char	*tmp;

	tmp = ft_strjoin("./pipex: permission denied: ", input);
	err_msg = ft_strjoin(tmp, "\n");
	free(tmp);
	ft_putstr_fd(err_msg, 2);
	free(err_msg);
}

void	px_perror(char *input)
{
	char	*err_msg;

	err_msg = ft_strjoin("./pipex: ", input);
	perror(err_msg);
	free(err_msg);
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
