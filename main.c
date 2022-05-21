#include "pipex.h"

void	px_close_all_fds(t_list *child)
{
	while (child)
	{
		px_close_fds(((t_child *)(child->content))->fds);
		child = child->next;
	}
}

void	px_wait_for_pids(t_px *px)
{
	int		child_index;
	int		status;

	child_index = -1;
	while (++child_index < px->nbr_cmd)
		waitpid(px->pid_list[child_index], &status, 0);
}

int ft_strcmp(const char *s1, const char *s2)
{
    size_t min_len;
    int len_s1;
    int len_s2;

    if (!s1 || !s2)
        min_len = 0;
    else
    {
        len_s1 = ft_strlen(s1);
        len_s2 = ft_strlen(s2);
    }
    if (len_s1 < len_s2)
        min_len = len_s1;
    else
        min_len = len_s2;
    return(ft_strncmp(s1, s2, min_len + 1));
}

int	px_limiter_strncomp(const char *lim, const char *gnl, size_t lim_len)
{
	size_t	i;
	size_t	gnl_len;

	i = 0;
	gnl_len = ft_strlen(gnl);
	while (i < lim_len)
	{
		if (lim[i] != gnl[i])
			return ((unsigned char)lim[i] - (unsigned char)gnl[i]);
		if (!lim[i] || !gnl[i])
			return ((unsigned char)lim[i] - (unsigned char)gnl[i]);
		i++;
	}
	if (gnl_len > lim_len &&  gnl[i] == '\n')
		return (0);
	else
		return (-1);
}

void     px_init_here_doc(t_px *px)
{
    int infile;
    char *gnl;

    infile = open(px->infile, O_RDWR | O_TRUNC | O_CREAT, 0644);
    px_check_open_sucess(infile, px->infile, px);
    while (1)
    {
        gnl = get_next_line(STDIN_FILENO);
        if (px_limiter_strncomp(px->entry.av[2], gnl, ft_strlen(px->entry.av[2])) == 0)
		{
			free(gnl);
            return ;
		}
        ft_putstr_fd(gnl, infile);
		free(gnl);
    }
}

int main(int ac, char **av, char **envp)
{
	t_px	*px;
	int		child_index;
	t_child	*current_child;

	child_index = -1;
	px = px_init_struct(ac, av, envp);
	if (px->hdoc_flag)
		px_init_here_doc(px);
	while (++child_index < px->nbr_cmd)
	{
		current_child = px_get_child_nod(px->child, child_index);
		px_mgmt_pipe(px, current_child);
		px_no_birthcontrol_zone(px, child_index, current_child);
	}
	px_close_all_fds(px->child);
	px_wait_for_pids(px);
	px_end_struct(px); 
	return(0);
}
