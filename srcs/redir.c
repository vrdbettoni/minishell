/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   redir.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 20:50:37 by lumeyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 20:54:21 by lumeyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		redir_cleanup(t_all *all)
{
	t_list	*prev;
	t_list	*tmp;
	t_list	*lst;
	int		i;

	i = 0;
	lst = all->args;
	while (lst && lst->next && !which_prd(lst->next) && !lst->prd)
		lst = lst->next;
	prev = lst;
	lst = lst->next;
	if (!lst || (lst && !ft_strcmp("|", lst->content)))
		return (1);
	while (i < 2)
	{
		tmp = lst->next;
		lst->content = free_safe(lst->content);
		lst = free_safe(lst);
		lst = tmp;
		i++;
	}
	prev->next = lst;
	return (0);
}

int		redir_stdin(t_all *all)
{
	int		fd;
	int		stdin_backup;
	char	*file;

	file = all->args_rd->next->content;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (print_n_set_error(all, file, "could not open file", 1));
	stdin_backup = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (!redir_cleanup(all))
	{
		all->args_rd = NULL;
		parse_rd(all);
		if (all->args_rd)
			redirect_io(all, all->args_rd);
		else
			find_command(all);
	}
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	return (0);
}

int		redir_stdout(t_all *all, char *op)
{
	int		fd;
	int		stdout_backup;
	char	*file;

	file = all->args_rd->next->content;
	fd = !ft_strcmp(">", op) ? open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644)
	: open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (print_n_set_error(all, file, "could not open file", 1));
	stdout_backup = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	if (!redir_cleanup(all))
	{
		all->args_rd = NULL;
		parse_rd(all);
		if (all->args_rd)
			redirect_io(all, all->args_rd);
		else
			find_command(all);
	}
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdout_backup);
	return (0);
}

void	redir_heredoc_child(char *heredoc, int stdin_backup, t_all *all)
{
	wait(&(all->status));
	all->depth--;
	close(all->pipe[1]);
	stdin_backup = dup(STDIN_FILENO);
	dup2(all->pipe[0], STDIN_FILENO);
	close(all->pipe[0]);
	if (!redir_cleanup(all))
	{
		all->args_rd = NULL;
		parse_rd(all);
		if (all->args_rd)
			redirect_io(all, all->args_rd);
		else
			find_command(all);
	}
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	heredoc = free_safe(heredoc);
}

int		redir_heredoc(t_all *all)
{
	int		stdin_backup;
	char	*heredoc;
	char	*expand;
	pid_t	fk;

	if (read_heredoc(all->args_rd->next->content, &heredoc, 0, all))
		return (1);
	heredoc = heredoc ? expand_str(heredoc, 0, 1, all) : ft_strdup("");
	pipe(all->pipe);
	if ((fk = fork()) == -1)
		ft_printf("minishell: fork operation failed\n");
	else if (!fk)
	{
		all->depth++;
		close(all->pipe[0]);
		dup2(all->pipe[1], STDOUT_FILENO);
		close(all->pipe[1]);
		*heredoc ? ft_printf("%s\n", heredoc) : ft_printf("%s", heredoc);
		close(STDOUT_FILENO);
		exit(0);
	}
	else
		redir_heredoc_child(heredoc, stdin_backup, all);
	return (0);
}
