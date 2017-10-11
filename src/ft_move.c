/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 09:43:33 by nidzik            #+#    #+#             */
/*   Updated: 2017/08/24 09:44:51 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/select.h"

/*
** ft_move_right(), permit to move cursor to the right
** change elems->current value
*/

void		ft_move_right(t_elem *fixed)
{
	t_elem	*elems;
	t_elem	*first;

	first = fixed;
	elems = fixed;
	while (elems != NULL)
	{
		if (elems->current == 1)
		{
			elems->current = 0;
			if (elems->next == NULL)
			{
				elems = first;
				elems->current = 1;
				break ;
			}
			elems = elems->next;
			elems->current = 1;
			break ;
		}
		else
			elems = elems->next;
	}
}

/*
** ft_move_right(), permit to move cursor to the right
** change elems->current value
*/

void		ft_move_left(t_elem *fixed)
{
	t_elem	*elems;
	t_elem	*last;

	last = fixed;
	while (last->next != NULL)
		last = last->next;
	elems = fixed;
	while (elems != NULL)
	{
		if (elems->current == 1)
		{
			elems->current = 0;
			if (elems->prev == NULL)
			{
				elems = last;
				elems->current = 1;
				break ;
			}
			elems = elems->prev;
			elems->current = 1;
			break ;
		}
		else
			elems = elems->next;
	}
}

/*
** ft_move_right(), permit to move cursor to the right
** change elems->current value
*/

void		ft_move_down(t_elem *fixed, int max)
{
	int		i;
	t_elem	*save;

	i = 0;
	while (fixed != NULL)
	{
		if (fixed->current == 1)
		{
			fixed->current = 0;
			save = fixed;
			while (i++ != ft_get_nb_col(max))
			{
				if (fixed->next == NULL)
				{
					save = go_to_first(save, max);
					break ;
				}
				fixed = fixed->next;
			}
			if (save->current == 0)
				fixed->current = 1;
			break ;
		}
		fixed = fixed->next;
	}
}

/*
** ft_move_up(), permit to move cursor upper and
** change elems->current value
*/

void		ft_move_up(t_elem *fixed, int max)
{
	int		i;
	t_elem	*save;

	i = 0;
	while (fixed != NULL)
	{
		if (fixed->current == 1)
		{
			fixed->current = 0;
			save = fixed;
			while (i++ != ft_get_nb_col(max))
			{
				if (fixed->prev == NULL)
				{
					save = go_to_last(save, max);
					break ;
				}
				fixed = fixed->prev;
			}
			if (save->current == 0)
				fixed->current = 1;
			break ;
		}
		fixed = fixed->next;
	}
}
