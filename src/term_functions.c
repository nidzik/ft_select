/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 10:35:27 by nidzik            #+#    #+#             */
/*   Updated: 2017/08/24 10:39:01 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/select.h"

/*
** print fct for tputs
*/

int			my_out(int i)
{
	int fd;

	fd = open("/dev/tty", O_RDWR);
	if (fd == -1)
	{
		write(2, "Open error\n", 11);
	}
	write(fd, &i, 1);
	close(fd);
	return (0);
}

/*
** get str code of keyboard
*/

int			ft_largest_word(char **av)
{
	int	i;
	int	max_size;

	max_size = (int)ft_strlen(av[1]);
	i = 2;
	while (av[i])
	{
		if ((int)ft_strlen(av[i]) > max_size)
			max_size = (int)ft_strlen(av[i]);
		i++;
	}
	return (max_size);
}
