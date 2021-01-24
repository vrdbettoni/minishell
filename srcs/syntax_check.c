/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   syntax_check.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vroth-di <vroth-di@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 16:13:59 by vroth-di     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/01 00:21:29 by vroth-di    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		parenthesis_left(char *s, int i, int cpt)
{
	int		quo;
	int		d_quo;

	quo = 0;
	d_quo = 0;
	while (s[i] && s[i] != ')')
	{
		if (s[i] == '\'' && d_quo == 0)
			quo = quo == 1 ? 0 : 1;
		if (s[i] == '"' && quo == 0)
			d_quo = d_quo == 1 ? 0 : 1;
		ft_isalnum(s[i]) && quo == 0 && d_quo == 0 ? cpt++ : 0;
		i++;
	}
	!s[i] ? cpt = 0 : 0;
	return (cpt == 0 ? 0 : 1);
}

int		parenthesis_right(char *s, int i, int cpt)
{
	int		quo;
	int		d_quo;

	quo = 0;
	d_quo = 0;
	while (i >= 0 && s[i] != '(')
	{
		if (s[i] == '\'' && d_quo == 0)
			quo = quo == 1 ? 0 : 1;
		if (s[i] == '"' && quo == 0)
			d_quo = d_quo == 1 ? 0 : 1;
		if ((s[i] == ';' || s[i] == '|') && cpt == 0)
			return (0);
		ft_isalnum(s[i]) && quo == 0 && d_quo == 0 ? cpt++ : 0;
		i--;
	}
	return (cpt == 0 ? 0 : 1);
}

int		number_parenthis(char *s, int left, int right)
{
	int		quo;
	int		d_quo;
	int		i;

	i = 0;
	quo = 0;
	d_quo = 0;
	while (s[i])
	{
		if (s[i] == '\'' && d_quo == 0)
			quo = quo == 1 ? 0 : 1;
		if (s[i] == '"' && quo == 0)
			d_quo = d_quo == 1 ? 0 : 1;
		s[i] == '(' && d_quo == 0 && quo == 0
				&& !(i >= 1 && s[i - 1] == '\\') ? left++ : 0;
		s[i] == ')' && d_quo == 0 && quo == 0
				&& !(i >= 1 && s[i - 1] == '\\') ? right++ : 0;
		i++;
	}
	return (left == right ? 1 : 0);
}

int		loop_check_syntax(char *s, t_all *all, int i)
{
	if ((s[i] == ';') && !limite(s, i - 1, 0))
		return (return_status(all, 1));
	else if (s[i] == '|' && s[i + 1] && s[i + 1] == '|')
	{
		if (!limite(s, i - 1, 0))
			return (return_status(all, 5));
		i++;
	}
	else if ((s[i] == '|') && !limite(s, i - 1, 0))
		return (return_status(all, 0));
	else if ((s[i] == '(') && !parenthesis_left(s, i, 0))
		return (return_status(all, 2));
	else if ((s[i] == ')') && !parenthesis_right(s, i, 0))
		return (return_status(all, 3));
	else if ((s[i] == '&' && s[i + 1] == '&') && !limite(s, i - 1, 0))
		return (return_status(all, 4));
	return (1);
}

int		check_syntax(char *s, t_all *all)
{
	int		i;
	int		quo;
	int		d_quo;

	quo = 0;
	d_quo = 0;
	i = -1;
	if (!number_parenthis(s, 0, 0))
		return (return_status(all, 6));
	while (s[++i])
	{
		if (s[i] == '\'' && d_quo == 0)
			quo = quo == 1 ? 0 : 1;
		if (s[i] == '"' && quo == 0)
			d_quo = d_quo == 1 ? 0 : 1;
		if (quo == 0 && d_quo == 0 && !(i >= 1 && s[i - 1] == '\\'))
			if (!loop_check_syntax(s, all, i))
				return (0);
	}
	return (1);
}
