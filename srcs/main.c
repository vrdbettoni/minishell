/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 16:28:50 by vroth-di     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/03 15:49:12 by vroth-di    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	actual_path(int status)
{
	char		location[100];
	int			len;
	int			i;

	i = 0;
	if (status != 2)
	{
	getcwd(location, 100);
	len = ft_strlen(location);
	while (location[len - 1] && location[len - 1] != '/')
		len--;
	while (location[len])
		location[i++] = location[len++];
	location[i] = '\0';
	if (status != 0)
		ft_printf("\033[0;31m¤ \033[0m");
	else
		ft_printf("\033[0;32m¤ \033[0m");
	ft_printf("\033[34m\033[1m%s\033[0;34m $> \033[0m", location);
}}

void	main_loop(t_all *all)
{
	char		*command;

	print_name();
	command = NULL;
	while (1)
	{
		actual_path(all->status);
		all->depth = 0;
		all->full_command = &command;
		if (gnl(0, &command, 3, all) == -1)
			ft_exit(all);
		if (ft_strlen(command) > 0)
			ft_add_hist(all->history, ft_new_hist((char*)ft_strdup(command)));
		check_syntax(command, all) ?
		parse_args_to_lists(command, all, 0, 0) : free(command);
		command = NULL;
	}
}

int		run_script(t_all *all, char *script)
{
	int			fd;
	int			ret;
	char		*command;

	ret = 1;
	command = NULL;
	all->full_command = &command;
	if ((fd = open(script, O_RDONLY)) == -1)
	{
		ft_printf("Can't open the script.\n");
		all->depth = 0;
		ft_exit(all);
	}
	while (ret > 0)
	{
		ret = get_next_line(fd, &command, 1000);
		if (check_syntax(command, all))
			parse_args_to_lists(command, all, 0, 1);
		command = free_safe(command);
	}
	all->depth = 0;
	ft_exit(all);
	return (1);
}

int		main_init(t_all *all, int ac, char **av, char **environ)
{
	load_history(all->history);
	all->path_auto = save_path(all->env_list);
	ft_bzero(all->copy, 200);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	tputs(all->term->im, 1, ft_putchar);
	tputs(all->term->dm, 1, ft_putchar);
	all->status = 0;
	parse_args_to_lists(ft_strdup("clear"), all, 0, 0);
	ac == 1 ? main_loop(all) : run_script(all, av[1]);
	return (1);
}

int		main(int ac, char **av, char **environ)
{
	t_all		*all;
	t_termcap	term;
	t_termios	s_termios;
	t_termios	old_termios;

	if (!(all = malloc(sizeof(t_all)))
			|| !(all->history = malloc(sizeof(t_list*))))
		return (ft_printf("malloc error\n"));
	get_env(all, environ);
	if (tcgetattr(0, &old_termios) == -1)
		return (-1);
	all->old_term = &old_termios;
	if (tcgetattr(0, &s_termios) == -1)
		return (-1);
	s_termios.c_lflag &= ~(ICANON | ECHO);
	s_termios.c_cc[VMIN] = 1;
	s_termios.c_cc[VTIME] = 0;
	all->new_termios = &s_termios;
	if (tcsetattr(0, TCSANOW, &s_termios) == -1 || !init_termcap(&term, all, 0))
		return (-1);
	all->term = &term;
	main_init(all, ac, av, environ);
	return (1);
}
