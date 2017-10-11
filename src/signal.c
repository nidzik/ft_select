/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 10:11:21 by nidzik            #+#    #+#             */
/*   Updated: 2017/08/24 12:01:48 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/select.h"

/*
** select_static(),  init of struct select
*/

void			*select_static(void)
{
	static t_select *sel = NULL;

	if (sel == NULL)
		sel = (t_select *)malloc(sizeof(t_select));
	return (sel);
}

/*
** resize(), called when resizing windows
** then get back t_select struct and call ft_init_print
*/

void			resize(int i)
{
	t_select	*select;

	(void)i;
	select = (t_select *)select_static();
	ft_init_print(select);
}

/*
** ft_crlt_c(), call destruct function, reset all original
** terminal settings
*/

void			ft_ctrl_c(int i)
{
	t_select	*select;

	(void)i;
	select = (t_select *)select_static();
	destruct(&select->term);
}

/*
** ft_ctrl_z(), suspend process, reset original terminal
** settings
*/

void			ft_ctrl_z(int i)
{
	t_select	*select;
	char		arg[2];

	select = (t_select *)select_static();
	arg[0] = (char)select->term.c_cc[VSUSP];
	arg[1] = '\0';
	(void)i;
	select->term.c_lflag = (cc_t)(ICANON | ECHO | ISIG);
	signal(SIGTSTP, SIG_DFL);
	ioctl(1, TIOCSTI, arg);
	tputs(tgetstr("ke", NULL), 0, my_out);
	tputs(tgetstr("te", NULL), 0, my_out);
	tputs(tgetstr("ve", NULL), 0, my_out);
	tputs(tgetstr("cd", NULL), 0, my_out);
	fflush(stdout);
}

/*
** ft_fg(), reset terminal parameter to needed
** and detach ft_select to background
*/

void			ft_fg(int i)
{
	t_select	*select;

	select = (t_select *)select_static();
	(void)i;
	init(&select->term);
	signal(SIGTSTP, ft_ctrl_z);
	fflush(stdout);
	ft_print(select->s_elem, select->max_len);
}
