/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pipe.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 20:54:55 by lumeyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 21:02:17 by lumeyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_redirect(t_list *arg)
{
	if (!arg || !arg->content)
		return (0);
	if (!ft_strcmp(">", arg->content))
		return (1);
	if (!ft_strcmp("<", arg->content))
		return (2);
	if (!ft_strcmp(">>", arg->content))
		return (3);
	if (!ft_strcmp("<<", arg->content))
		return (4);
	return (0);
}

int		which_prd(t_list *arg)
{
	if (!arg || !arg->content)
		return (0);
	if (!ft_strcmp(">", arg->content))
		return (1);
	if (!ft_strcmp("<", arg->content))
		return (2);
	if (!ft_strcmp("|", arg->content))
		return (3);
	if (!ft_strcmp(">>", arg->content))
		return (4);
	if (!ft_strcmp("<<", arg->content))
		return (5);
	return (0);
}

int		setup_pipes_rd(t_all *all)
{
	int	piped;

	piped = 0;
	all->args_rd = NULL;
	all->args_pipe = NULL;
	if (parse_pipe(all))
		return (1);
	if (all->args_pipe)
	{
		piped = 1;
		redirect_io(all, all->args_pipe);
	}
	else
		parse_rd(all);
	if (all->args_rd)
		redirect_io(all, all->args_rd);
	else if (!piped)
		find_command(all);
	return (0);
}

void	pipe_stdout_child(t_all *all)
{
	int		bkp;

	wait(&(all->status));
	all->depth--;
	close(all->pipe[1]);
	bkp = dup(STDIN_FILENO);
	dup2(all->pipe[0], STDIN_FILENO);
	close(all->pipe[0]);
	all->args = all->args_pipe;
	setup_pipes_rd(all);
	dup2(bkp, STDIN_FILENO);
	all->status > 255 ? all->status /= 256 : 0;
}

int		pipe_stdout(t_all *all)
{
	pid_t fork1;
	pid_t fork2;

	all->args_pipe = all->args_pipe->next;
	if (pipe(all->pipe) < 0)
		return (print_n_set_error(all, "|", "operation failed", 1));
	fork1 = fork();
	if (fork1 < 0)
		return (print_n_set_error(all, "|", "operation failed", 1));
	else if (!fork1)
	{
		all->depth++;
		close(all->pipe[0]);
		dup2(all->pipe[1], STDOUT_FILENO);
		close(all->pipe[1]);
		parse_rd(all);
		all->args_rd ? redirect_io(all, all->args_rd) : find_command(all);
		exit(0);
	}
	else
		pipe_stdout_child(all);
	return (0);
}
