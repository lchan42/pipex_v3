/*#include "pipex.h"

char	*px_parsing_creat_accesspath(char *cmd, char **split_path)
{
	int		i;
	char	*path;

	i = -1;
	while (split_path[++i])
	{
		path = ft_strjoin(split_path[i], cmd);
		if (px_entrycheck_isaccess_f_x(path))
			return (path);
		free(path);
	}
	return (cmd);
}

int		px_parsing_creatpath(int ac, char **av, char **split_path)
{
	int	i;

	i = 1;
	while (++i < ac -1)
	{
		if (px_entrycheck_isaccess_f_x(av[i]))
			av[i] = ft_strdup(av[i]);
		else
		{
			av[i] = px_parsing_creat_accesspath(av[i], split_path);
			if (!px_entrycheck_isaccess_f_x(av[i]))
				return (i);
		}
	}
	return (0);
}

void    px_parsing_getpath(int ac, char **av, char **envp)
{
	char **split_path;
	int cnf_index;

	split_path = px_parsing_path(envp);
	if (!split_path)
		px_entrycheck_case_no_env(ac, av);
	cnf_index = px_parsing_creatpath(ac, av, split_path);
	if (split_path)
		px_free_tab(split_path);
	if (cnf_index)
		px_entrycheck_case_cnf(ac, av, cnf_index);
	del_print_tab_ac(ac, av);///////////////
}
*/
/*************************************************************
 * cnf = cmd not found
 * in order:
 * entrycheck_ac_file --> check nbr of arg and access to infile/outfile
 * split path
 * if no env, check if entry is all direct path to cmd
 * creat and add direct path to av
 * 
 * ***********************************************************/
