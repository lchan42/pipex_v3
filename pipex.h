/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 23:49:17 by lchan             #+#    #+#             */
/*   Updated: 2022/05/23 11:41:05 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include "./libraries/libft/libft.h"

# define RD_END 0
# define WR_END 1

typedef struct s_entry{
	int		ac;
	char	**av;
	char	**envp;
}t_entry;

typedef struct s_child{
	int		id;
	char	*path;
	char	**cmd;
	int		*fds;
}t_child;

typedef struct s_px{
	t_entry	entry;
	int		hdoc_flag;
	char	*infile;
	char	*outfile;
	int		nbr_cmd;
	int		*pid_list;
	t_list	*child;
}t_px;

enum e_error{
	NOT_ENOUGH_ARG,
	CANT_FIND_INFILE,
	CANT_READ_INFILE,
	CANT_WRITE_OUTFILE,
	PATH_NOT_FOUND,
	PATH_N_ACCESS_NOT_FOUND,
	CMD_NOT_FOUND,
};

//pipex_entrycheck.c
int		px_entrycheck_ac_file(int ac, char **av);
int		px_entrycheck_isaccess_f_x(char *path);

//pipex_get_cmdpath.c
void	px_set_cmd_n_path(char *cmd, char **split_path, t_child *child);

//pipex_parsing_envp.c
char	**px_parsing_path(char **envp);

//pipex_init_struct.c
t_px	*px_init_struct(int ac, char **av, char **envp);

//px_print_err.c
void	px_err_cmd_not_found(char *input);
void	px_err_permission_denied(char *input);
void	px_perror(char *input);
void	px_perr_exit(int n, char *input);

////pipex_mgmt_redirection.c
void	px_mgmt_redirection(t_px *px, t_child *child);

////pipex_mgmt_pipe.c
void	px_mgmt_pipe(t_px *px, t_child *child);

////pipex_no_birthcontrol_zone.c
void	px_no_birthcontrol_zone(t_px *px, int i, t_child *current_child);

////pipex_utils.c
void	px_check_malloc_success(t_px *px, void *elem);
void	px_check_open_sucess(int fd, char *input, t_px *px);
void	px_close_fd(int *fd);
t_child	*px_get_child_nod(t_list *child, int index);
t_child	*px_get_prev_nod(t_list *child, int index);

//pipex_end_struct.c
void	px_free_tab(char **tab);
void	px_close_fds(int *fds);
void	px_del_content(t_child *child);
void	px_end_struct(t_px *px);
void	px_end_struct_exit(t_px *px);

//del_print.c
void	del_print_split_path(char **pasth_tab);
void	del_print_tab_ac(int ac, char **av);
void	del_print_child(t_child child);
void	visual_print_px(t_px *px);
void	v_print_t_list(t_px *px, t_list *child);
void	v_print_child_struct(t_px *px, t_child *child);

#endif




