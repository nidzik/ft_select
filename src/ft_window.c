/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 09:33:30 by nidzik            #+#    #+#             */
/*   Updated: 2017/08/24 17:58:22 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/select.h"

/*
** ft_get_nb_col(), with maximum word lenght in argument
** this function return the number of columns
*/

int			ft_get_nb_col(int max)
{
	int		nb_col;
	int		win_x;

	win_x = ft_get_win_x();
	nb_col = (int)(win_x / (max + 1));
	if (nb_col < 1)
		nb_col = 1;
	return (nb_col);
}

/*
** ft_rest(), calcul rest of division, like % operator
*/

static int	ft_rest(const int nb, const int col)
{
	int		rest;
	int		mul;

	mul = nb / col;
	rest = nb - (col * (int)mul);
	return (rest);
}

/*
** ft_print_space(), print needed space for correctly
** fill line. it take the size of largest word, a string and
** possition of the string in t_elem list
*/

static void	ft_print_space(int max, char *name, int number)
{
	int		diff;
	int		nb_col;
	int		win_x;

	win_x = ft_get_win_x();
	nb_col = ft_get_nb_col(max);
	diff = max - (int)ft_strlen(name) + 1;
	if (nb_col <= 1)
		diff = win_x - (int)ft_strlen(name);
	else if (nb_col > 1)
	{
		if (number % nb_col == 0)
			diff += (win_x % (max + 1));
	}
	if (ft_rest(number, nb_col) == 0)
		tputs("\n", 1, my_out);
	else
	{
		while (diff-- > 0)
			tputs(" ", 1, my_out);
	}
}

/*
** ft_print(), display all element in terminal and
** call ft_print_space to fill blanck place
*/

void		ft_print(t_elem *fixed, int max)
{
	t_elem	*elems;
	int		number;

	number = 1;
	elems = fixed;
	ft_move_up_line(fixed, ft_get_cursor_y(), max);
	tputs((tgetstr("sc", NULL)), 1, my_out);
	tputs((tgetstr("cd", NULL)), 1, my_out);
	while (elems != NULL)
	{
		ft_special_case(elems);
		tputs(tgetstr("ue", NULL), 1, my_out);
		tputs(tgetstr("me", NULL), 1, my_out);
		ft_print_space(max, elems->name, number);
		number++;
		elems = elems->next;
	}
	tputs((tgetstr("rc", NULL)), 1, my_out);
}

/*
** ft_key_space(), when space is pressed, this function permit
** to save element
*/

void		ft_key_space(t_elem *fixed)
{
	t_elem	*elems;
	t_elem	*save;

	save = fixed;
	elems = fixed;
	while (elems != NULL)
	{
		if (elems->current == 1)
		{
			if (elems->select == 1)
				elems->select = 0;
			else
				elems->select = 1;
			ft_move_right(save);
			break ;
		}
		elems = elems->next;
	}
}
