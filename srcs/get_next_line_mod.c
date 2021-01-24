/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line_mod.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vroth-di <vroth-di@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/30 14:14:32 by vroth-di     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/29 16:22:09 by vroth-di    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_read_suite(int i, char **res, char *buffer, int ret)
{
	int		j;

	j = 0;
	buffer[0] != 4 ? ft_printf("\n") : 0;
	(i != -1) ? (*res)[i] = '\0' : 0;
	if (ret > 0 && i != -1)
	{
		i = ft_strchr_mod(buffer);
		while (buffer[i])
			buffer[j++] = buffer[1 + i++];
		buffer[j] = '\0';
	}
	return (buffer[0] == 4 ? -1 : ret);
}

int		ft_read(t_all *all, char **res, char *buffer, int buffer_size)
{
	int		i;
	int		ret;

	ret = 1;
	all->index = 0;
	all->current = *(all->history);
	all->free_command = 1;
	while (((i = ft_strchr_mod(*res)) == -1) && ret > 0)
	{
		ft_bzero(buffer, 3);
		ret = read(0, buffer, buffer_size);
		buffer[ret] = '\0';
		(buffer[0] == 4) ? (ret = -1) : 0;
		if (retour_termcap(all, &buffer, res) != 0 && buffer[0] != 127)
			res = set_line(all, res, buffer, &ret);
		if (ft_isprint(buffer[0]) == 1)
		{
			ft_printf("%s", buffer);
			all->index++;
		}
	}
	return (ft_read_suite(i, res, buffer, ret));
}

int		ft_rest(t_all *all, char *res, char *buffer)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	res[i] = '\0';
	while (i-- > 0)
		res[i] = buffer[i];
	i = ft_strchr_mod(buffer);
	if (i != -1)
	{
		(buffer[i] == '\n') ? i++ : 0;
		while (buffer[i])
			buffer[j++] = buffer[i++];
		buffer[j] = '\0';
		return (1);
	}
	return (0);
}

int		gnl(int fd, char **line, int buffer_size, t_all *all)
{
	static char		*buffer;
	char			*res;
	int				i;

	i = 1;
	if (!line || read(fd, 0, 0) ||
							!(res = malloc(sizeof(char) * (buffer_size + 1))))
		return (-1);
	ft_bzero(res, buffer_size + 1);
	if (!buffer)
	{
		if (!(buffer = (char*)malloc(sizeof(char) * (buffer_size + 1))))
			return (-1);
		i = ft_read(all, &res, buffer, buffer_size);
	}
	else
		ft_rest(all, res, buffer) == 0 ?
			i = ft_read(all, &res, buffer, buffer_size) : 0;
	*line = res;
	if (i > 0)
		return (1);
	free(buffer);
	buffer = NULL;
	return (i == 0 ? 0 : -1);
}
