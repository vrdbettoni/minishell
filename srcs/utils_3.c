/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils_3.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vroth-di <vroth-di@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/29 16:39:58 by vroth-di     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 22:36:05 by vroth-di    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_cmd(t_list *args)
{
	t_list	*tmp;

	if (ft_strcmp("..", args->content))
		return ;
	free(args->content);
	args->content = ft_strdup("cd");
	tmp = ft_lstnew(ft_strdup(".."));
	tmp->subsh = 0;
	tmp->next = args->next;
	args->next = tmp;
}

int		len_to_pipe(t_list *lst)
{
	int		size;

	size = 0;
	if (lst == NULL)
		return (size);
	while (lst && !skip_args(lst))
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

int		return_error(t_all *all, char *token, int errcode)
{
	char	*str;

	str = strerror(errno);
	all->status = errcode;
	ft_putstr_fd("minishell: ", 2);
	if (token)
	{
		ft_putstr_fd(token, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	free(str);
	return (1);
}

void	ft_error(void)
{
	ft_printf("%s\n", strerror(errno));
}

int		match_n_match(char *s, char *type)
{
	while (*s && *type)
		if (*type != '*')
		{
			if (*s != *type)
				return (0);
			s++;
			type++;
		}
		else
		{
			while (*type == '*')
				type++;
			while (*s && *s != *type)
				s++;
		}
	if (*s != *type && *type != '*')
		return (0);
	return (1);
}
