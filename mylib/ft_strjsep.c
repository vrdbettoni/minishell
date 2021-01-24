/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjsep.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/31 21:12:49 by lumeyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 21:12:51 by lumeyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjsep(char const *s1, char const *s2, char c)
{
	char	*res;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j++])
		i++;
	if (!(res = malloc(sizeof(char) * (i + 2))))
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		res[i] = s1[i];
	res[i++] = c;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}
