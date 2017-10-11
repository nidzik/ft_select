/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 09:45:20 by nidzik            #+#    #+#             */
/*   Updated: 2017/08/24 18:24:23 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/select.h"

/*
** ft_exit(), permit to exit with message
*/

void		ft_exit(char *str)
{
	ft_putendl(str);
	exit(1);
}

/*
** ft_get_win_x(), return current width of window
*/

int			ft_get_win_x(void)
{
	struct winsize	sz;
	int				win_x;

	ioctl(0, TIOCGWINSZ, &sz);
	win_x = sz.ws_col;
	return (win_x);
}

/*
** ft_get_win_y(), return current height of window
*/

int			ft_get_win_y(void)
{
	struct winsize	sz;
	int				win_y;

	ioctl(0, TIOCGWINSZ, &sz);
	win_y = sz.ws_row;
	return (win_y);
}

/*
** ft_get_cursor_y(), return y position of cursor
*/

int			ft_get_cursor_y(void)
{
	char	*ansi;
	char	*buff;
	char	*tmp;
	int		y;

	y = 0;
	ansi = ft_strnew(1);
	buff = ft_strnew(10);
	write(0, "\E[6n", 4);
	while (ft_strchr(buff, 'R') == NULL)
	{
		ft_bzero(buff, 10);
		read(0, buff, 10);
		tmp = ansi;
		ansi = ft_strjoin(tmp, buff);
		ft_strdel(&tmp);
	}
	y = ft_atoi(&ansi[2]);
	ft_strdel(&buff);
	ft_strdel(&ansi);
	return (y);
}

/*
** ft_move_up_line(), permit when there is no much line left in bottom
** of window, to scroll ("sf") and move cursors to up ("up")
*/

void		ft_move_up_line(t_elem *fixed, int curr_line, int max)
{
	int		nb_lines;
	t_elem	*elem;
	int		last_line;
	int		scroll_up;
	int		save;

	elem = fixed;
	scroll_up = 0;
	while (elem->next != NULL)
		elem = elem->next;
	nb_lines = elem->number / ft_get_nb_col(max);
	if (elem->number % ft_get_nb_col(max) != 0)
		nb_lines++;
	last_line = (nb_lines + curr_line);
	if (last_line < ft_get_win_y() || (nb_lines > ft_get_win_y()))
		return ;
	save = 0;
	ft_norme1(curr_line, save, last_line, nb_lines);
}
