/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   key_choice.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vroth-di <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 16:25:42 by vroth-di     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 16:26:15 by vroth-di    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		key_choice(t_all *all, char **buffer, char **res, int len)
{
	if ((*buffer)[0] == 1 || (*buffer)[0] == 19)
	{
		(*buffer)[0] == 1 ? previous_word(all, res, len) : 0;
		(*buffer)[0] == 19 ? next_word(all, res, len) : 0;
		return (0);
	}
	if ((*buffer)[0] == 11 || (*buffer)[0] == 12)
	{
		(*buffer)[0] == 11 ? ft_copy(all, res) : 0;
		(*buffer)[0] == 12 ? ft_paste(all, res, len) : 0;
		return (0);
	}
	if ((*buffer)[0] == 9)
	{
		autocompletion(all, res);
		return (0);
	}
	return (ft_isprint((*buffer)[0]) || (*buffer)[0] == 10 ? 1 : 0);
}

int		retour_termcap(t_all *all, char **buffer, char **res)
{
	int		len;

	len = ft_strlen(*res);
	if ((*buffer)[0] == 127 && res[0] != '\0')
		return (len > 0 ? delete(all, buffer, res, len) : 0);
	if ((*buffer)[0] == 4 || (*buffer)[0] == 28)
	{
		(*buffer)[0] == 4 ? ft_printf("exit\n") : 0;
		return (0);
	}
	if ((*buffer)[0] == 27 && (*buffer)[1] == 91)
	{
		(*buffer)[2] == 72 ? s_e_line(all, 0, len) : 0;
		(*buffer)[2] == 70 ? s_e_line(all, 1, len) : 0;
		(*buffer)[2] == 70 ? next_word(all, res, len) : 0;
		(*buffer)[2] == 65 ? previous_history(all, res) : 0;
		(*buffer)[2] == 66 ? next_history(all, res) : 0;
		if ((*buffer)[2] == 67 || (*buffer)[2] == 68)
			prompt(all, buffer, res, len);
		return (0);
	}
	return (key_choice(all, buffer, res, len));
}
