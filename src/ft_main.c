/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 09:38:29 by nidzik            #+#    #+#             */
/*   Updated: 2017/08/24 18:28:36 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/select.h"

/*
** initialise terminos structure
** `vi` make cursor invisible
*/

int					init(struct termios *term)
{
	char			*term_buffer;
	char			*termtype;

	termtype = NULL;
	term_buffer = NULL;
	termtype = getenv("TERM");
	if (term == NULL)
		ft_exit("Specify a terminal type with `setenv TERM '.");
	if (tgetent(NULL, termtype) == -1)
		ft_exit("Could not access the termcap data base or is not\
								defined.");
	if (tcgetattr(0, term) == -1)
		ft_exit("Failed tcgetattr!");
	tputs(tgetstr("vi", NULL), 1, my_out);
	term->c_lflag &= (unsigned long)~(ICANON | ECHO);
	term->c_cc[VMIN] = 1;
	term->c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, term) == -1)
		ft_exit("Failed tcsetattr!");
	return (0);
}

/*
** Destruct(), permit to exit nicely ft_select execution
** where default setting are reset
** `te` undo `ti` option
** `ve` display cursor to normal
** `cd` position the cursor to last saved position
*/

void				destruct(struct termios *term)
{
	if (tcgetattr(0, term) == -1)
	{
		ft_putstr("Failed tcgetattr!\n");
	}
	tputs(tgetstr("te", NULL), 0, my_out);
	tputs(tgetstr("ve", NULL), 0, my_out);
	tputs(tgetstr("cd", NULL), 0, my_out);
	term->c_lflag = (ICANON | ECHO | ISIG);
	if (tcsetattr(0, 0, term) == -1)
	{
		ft_putstr("Failed tcsetattr\n");
	}
}

/*
** ft_add_elem(), take the av[][] tab of main,
** a chained list and add all argument to this list
*/

void				ft_add_elem(char **av, t_elem *elems)
{
	int				i;

	i = 1;
	while (av[i + 1])
	{
		elems->select = 0;
		if (i == 1)
			elems->current = 1;
		if (!av[i + 1])
			elems->next = NULL;
		else
		{
			elems->next = (t_elem *)malloc(sizeof(t_elem));
			elems->next->prev = elems;
			elems->next->name = av[i + 1];
			elems->next->number = i + 1;
			elems->next->next = NULL;
		}
		elems = elems->next;
		i++;
	}
}

/*
** inti struct t_elem
** all good.
*/

static t_elem		*ft_init_elems(t_elem *elems, char *av1)
{
	elems->name = av1;
	elems->current = 0;
	elems->number = 1;
	elems->prev = NULL;
	return (elems);
}

/*
** main() principal function, check if there is argument
** if yes, add all argument to a chained list and catch
** CTRL-C, CTRL-Z, ESC signals
*/

int					main(int ac, char **av)
{
	struct termios	term;
	t_elem			*elems;

	if (ac > 1)
	{
		elems = (t_elem *)malloc(sizeof(t_elem));
		elems = ft_init_elems(elems, av[1]);
		if (init(&term) == -1)
		{
			free(elems);
			return (-1);
		}
		ft_add_elem(av, elems);
		signal(SIGWINCH, resize);
		signal(SIGINT, ft_ctrl_c);
		signal(SIGTSTP, ft_ctrl_z);
		signal(SIGCONT, ft_fg);
		((t_select *)select_static())->s_elem = elems;
		((t_select *)select_static())->max_len = ft_largest_word(av);
		((t_select *)select_static())->term = term;
		ft_ini_input(&term, elems, ft_largest_word(av));
	}
	free(select_static());
	return (0);
}
