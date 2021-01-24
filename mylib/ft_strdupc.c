/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdupc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lumeyer <lumeyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/16 14:50:18 by lumeyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/31 21:11:56 by lumeyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdupc(char const *s1, char c)
{
	char	*copy;
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s1[len] && s1[len] != c)
		len++;
	if (!(copy = (char*)malloc(len + 1)))
		return (NULL);
	while (s1[i] && s1[i] != c)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
