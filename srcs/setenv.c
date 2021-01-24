/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   setenv.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vroth-di <vroth-di@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 16:31:38 by lumeyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 22:25:45 by vroth-di    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		add_env(t_env **env_list, char *varval, int exp, int i_eq)
{
	t_env	*lst;
	char	*var;
	char	*value;

	i_eq = ft_strlchr(varval, '=');
	var = ft_strdup(varval);
	var[i_eq] = 0;
	value = ft_strdup(varval + i_eq + 1);
	lst = *env_list;
	while (lst)
	{
		if (!ft_strcmp(lst->var, var))
		{
			lst->value = free_safe(lst->value);
			lst->value = value;
			lst->exp = exp;
			var = free_safe(var);
			return (0);
		}
		lst = lst->next;
	}
	env_lstaddb(env_list, var, value, exp);
	var = free_safe(var);
	value = free_safe(value);
	return (0);
}

int		error_unset(t_all *all)
{
	char *var;

	while (all->args && ft_strlchr(all->args->content, '=') > 0)
	{
		var = ft_strdupl(all->args->content,
		ft_strlchr(all->args->content, '='));
		unset_env(&(all->env_list), var);
		var = free_safe(var);
		next_args(&(all->args));
	}
	return (0);
}

void	ft_setenv_last(t_all *all, t_list *lst)
{
	if ((!ft_strcmp("&&", lst->content)
			|| !ft_strcmp("||", lst->content)) && lst->prd)
		return ;
	else
	{
		error_unset(all);
		find_command(all);
	}
}

void	ft_setenv_next(t_all *all, t_list *lst)
{
	if (lst && !ft_strcmp(lst->content, "env"))
	{
		error_unset(all);
		while (all->args && ft_strlchr(all->args->content, '=') > 0)
		{
			ft_printf("%s\n", all->args->content);
			next_args(&(all->args));
		}
		ft_env(all);
	}
	else if (!lst)
	{
		while (all->args && is_valid_assignment(all->args))
		{
			add_env(&(all->env_list), all->args->content, 0, 0);
			next_args(&(all->args));
		}
	}
	else
		ft_setenv_last(all, lst);
}

int		ft_setenv(t_all *all)
{
	t_list	*lst;

	lst = all->args;
	while (lst && is_valid_assignment(lst))
		lst = lst->next;
	if (lst && ft_strlchr(lst->content, '=') > 0)
	{
		error_unset(all);
		all->args = lst;
		return (0);
	}
	else if (lst && !ft_strcmp(lst->content, "|") && lst->prd)
	{
		error_unset(all);
		return (1);
	}
	else
		ft_setenv_next(all, lst);
	return (1);
}
