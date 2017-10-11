/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 09:36:35 by nidzik            #+#    #+#             */
/*   Updated: 2017/08/24 18:27:46 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#./include "./include/select.h"

/*
** ft_ini_input() function initialise ft_input parameter
** in a struct (struct s_input)
*/

void			ft_ini_input(struct termios *term, t_elem *elems, \
							int max_len_word)
{
	t_input *input;

	input = (t_input *)malloc(sizeof(t_input));
	input->fd = open("/dev/tty", O_RDWR);
	ioctl(0, TIOCGWINSZ, &input->sz);
	input->size_win = input->sz.ws_col;
	ft_input(term, elems, max_len_word, input);
}

/*
** ft_size_win(), function permit to change size_win var if
** size of windows have change while executing
*/

void			ft_size_win(t_input *input, int get_num, t_elem *elems,
							int max_len_word)
{
	if (input->size_win != get_num)
	{
		input->size_win = get_num;
		ft_print(elems, max_len_word);
	}
}

/*
** close /dev/tty - free all struct
** exept select
*/

void			ft_free(struct termios *term, t_elem *elems, t_input *input)
{
	t_elem		*el;

	(void)input;
	(void)term;
	(void)elems;
	while (elems != NULL)
	{
		el = elems;
		elems = elems->next;
		free(el);
	}
	close(input->fd);
	free(input);
}

/*
** return the term and print the reseult
** yeah.
*/

void			ft_return(t_elem *elems, struct termios *term, t_input *input)
{
	(void)input;
	destruct(term);
	while (elems)
	{
		if (elems->select == 1)
		{
			ft_putstr(elems->name);
			ft_putstr(" ");
		}
		elems = elems->next;
	}
	ft_free(term, elems, input);
}

/*
** ft_add_elem() function, add elem on t_elem chained list
** elem->name : argument name
** elem->select : 1 selected, 0 not selected
*/

void			ft_input(struct termios *term, t_elem *elems, int m,\
						t_input *input)
{
	tputs(tgetstr("sc", NULL), 0, my_out);
	ft_print(elems, m);
	while (42)
	{
		ft_bzero(input->buf, 3);
		(read(0, input->buf, 3));
		{
			input->size_win = input->sz.ws_col;
			if (UP || DOWN || LEFT || RIGHT)
				ft_norme2(m, input, elems);
			else if (input->buf[0] == '\n')
			{
				ft_return(elems, term, input);
				break ;
			}
			else if (ESC)
			{
				destruct(term);
				break ;
			}
			else if (SPACE)
				ft_key_space(elems);
			ft_print(elems, m);
		}
		tputs(tgetstr("rc", NULL), 0, my_out);
	}
}
