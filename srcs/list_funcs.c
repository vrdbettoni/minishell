/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   list_funcs.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vroth-di <vroth-di@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 16:28:26 by lumeyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 22:25:45 by vroth-di    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		print_env(t_env *lst)
{
	while (lst)
	{
		if (lst->exp)
		{
			ft_printf("%s=", lst->var);
			ft_printf("%s\n", lst->value);
		}
		lst = lst->next;
	}
	return (0);
}

int		env_lstlen(t_env *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

t_env	*env_new(char *var, char *value, int exp)
{
	t_env	*new;

	if (!(new = (t_env*)malloc(sizeof(t_env))))
		exit_err();
	new->var = ft_strdup(var);
	new->value = ft_strdup(value);
	new->exp = exp;
	new->next = NULL;
	return (new);
}

void	env_lstaddb(t_env **alst, char *var, char *value, int exp)
{
	t_env *current;

	if (alst == NULL)
		return ;
	if (!(*alst))
	{
		*alst = env_new(var, value, exp);
		return ;
	}
	current = *alst;
	while (current->next)
		current = current->next;
	current->next = env_new(var, value, exp);
}
