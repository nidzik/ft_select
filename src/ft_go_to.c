/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_go_to.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 09:33:01 by nidzik            #+#    #+#             */
/*   Updated: 2017/08/24 10:45:31 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#./include "./include/select.h"

/*
** Go to last element of t_elem linked list
*/

t_elem			*go_to_last(t_elem *fixed, int max)
{
	int			i;
	int			nb_col;
	t_elem		*save;

	save = fixed;
	i = 0;
	nb_col = ft_get_nb_col(max);
	while (fixed != NULL)
	{
		fixed->current = 0;
		while (i++ != nb_col)
		{
			if (fixed == NULL)
				break ;
			fixed = fixed->next;
		}
		if (fixed == NULL)
		{
			save->current = 1;
			break ;
		}
		save = fixed;
		i = 0;
	}
	return (save);
}

/*
** Go to first element of t_elem linked list
*/

t_elem			*go_to_first(t_elem *fixed, int max)
{
	int			i;
	int			nb_col;
	t_elem		*save;

	save = fixed;
	i = 0;
	nb_col = ft_get_nb_col(max);
	while (fixed != NULL)
	{
		fixed->current = 0;
		while (i++ != nb_col)
		{
			if (fixed == NULL)
				break ;
			fixed = fixed->prev;
		}
		if (fixed == NULL)
		{
			save->current = 1;
			break ;
		}
		save = fixed;
		i = 0;
	}
	return (save);
}

/*
** function call in ft_print(), handle case when
** current = 1 or select = 1
*/

void			ft_special_case(t_elem *elems)
{
	if (elems->current == 1 && elems->select == 1)
	{
		tputs(tgetstr("us", NULL), 1, my_out);
		tputs(tgetstr("mr", NULL), 1, my_out);
		tputs(elems->name, 1, my_out);
	}
	else if (elems->current == 1)
	{
		tputs(tgetstr("us", NULL), 1, my_out);
		tputs(elems->name, 1, my_out);
	}
	else if (elems->select == 1)
	{
		tputs(tgetstr("mr", NULL), 1, my_out);
		tputs(elems->name, 1, my_out);
	}
	else
		tputs(elems->name, 1, my_out);
}

/*
** ft_init_print(), call ft_print function
*/

void			ft_init_print(t_select *sel)
{
	ft_print(sel->s_elem, sel->max_len);
}
