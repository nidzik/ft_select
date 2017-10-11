/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_norme.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 10:35:27 by nidzik            #+#    #+#             */
/*   Updated: 2017/08/24 10:39:01 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/select.h"

void	ft_norme1(int curr_line, int save, int last_line, \
				int nb_lines)
{
	int scroll_up;

	scroll_up = 0;
	if (curr_line == ft_get_win_y())
	{
		scroll_up = last_line - ft_get_win_y();
		save = scroll_up;
		while (save-- > 0)
			tputs((tgetstr("sf", NULL)), 1, my_out);
		while (scroll_up-- > 0)
			tputs((tgetstr("up", NULL)), 1, my_out);
	}
	else
	{
		scroll_up = nb_lines;
		save = scroll_up;
		while (save-- > 0)
			tputs((tgetstr("sf", NULL)), 1, my_out);
		while (scroll_up-- > 0)
			tputs((tgetstr("up", NULL)), 1, my_out);
	}
}

void	ft_norme2(int m, t_input *input, t_elem *elems)
{
	if (UP)
		ft_move_up(elems, m);
	else if (DOWN)
		ft_move_down(elems, m);
	else if (LEFT)
		ft_move_left(elems);
	else if (RIGHT)
		ft_move_right(elems);
}
