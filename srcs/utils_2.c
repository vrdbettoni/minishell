/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_2.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 20:03:58 by vroth-di     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/03 15:48:51 by vroth-di    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handler(int signo)
{
	if (signo == SIGINT)
	{
		kill(SIGINT, 0);
		ft_printf("\n");
		actual_path(2);
	}
}

void	print_name(void)
{
	ft_printf(
		"\n\033[0;31m____________________________________________________\n");
	ft_printf(
		"        ____ ___   (_)____   (_)_____ / /_   ___   / // /\n");
	ft_printf(
		"       / __ `__ \\ / // __ \\ / // ___// __ \\ / _ \\ / // / \n");
	ft_printf(
		"      / / / / / // // / / // /(__  )/ / / //  __// // /  \n");
	ft_printf(
		"     /_/ /_/ /_//_//_/ /_//_//____//_/ /_/ \\___//_//_/ \n");
	ft_printf("             _______________");
	ft_printf("_____________________________________\n\n\033[0m\n");
}

int		return_status(t_all *all, int errcode)
{
	if (errcode == 0)
		print_n_set_error(all, "syntax error near unexpected token", "'|'", 1);
	if (errcode == 1)
		print_n_set_error(all, "syntax error near unexpected token", "';'", 1);
	if (errcode == 2)
		print_n_set_error(all, "syntax error near unexpected token", "'('", 1);
	if (errcode == 3)
		print_n_set_error(all, "syntax error near unexpected token", "')'", 1);
	if (errcode == 4)
		print_n_set_error(all, "syntax error near unexpected token", "'&&'", 1);
	if (errcode == 5)
		print_n_set_error(all, "syntax error near unexpected token", "'||'", 1);
	if (errcode == 6)
		print_n_set_error(all, "syntax error", "number of parenthesis", 1);
	if (errcode == 7)
		print_n_set_error(all, "syntax error", "end of line", 1);
	return (0);
}

int		limite(char *s, int i, int cpt)
{
	while (i >= 0 && s[i] != ';' && s[i] != '(' && s[i] != '|')
	{
		if (s[i] == '&' && s[i + 1] == '&' && cpt == 0)
			return (0);
		if (s[i] == '|' && s[i + 1] == '|' && cpt == 0)
			return (0);
		if (ft_isalnum(s[i]))
			cpt++;
		i--;
	}
	return (cpt == 0 ? 0 : 1);
}
