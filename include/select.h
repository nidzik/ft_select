/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidzik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 09:53:17 by nidzik            #+#    #+#             */
/*   Updated: 2017/08/24 11:52:25 by nidzik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SELECT_H
# define SELECT_H

# include <curses.h>
# include <term.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <termios.h>
# include <sys/ioctl.h>
# include "../libft/libft.h"
# include <signal.h>

# define BUFF0		input->buf[0] == 27
# define BUFF32		input->buf[0] == 32
# define LEFT		(BUFF0 && input->buf[1] == 91 && input->buf[2] == 68)
# define UP			(BUFF0 && input->buf[1] == 91 && input->buf[2] == 65)
# define DOWN		(BUFF0 && input->buf[1] == 91 && input->buf[2] == 66)
# define RIGHT		(BUFF0 && input->buf[1] == 91 && input->buf[2] == 67)
# define ESC		(BUFF0 && input->buf[1] == 0 && input->buf[2] == 0)
# define SPACE		(BUFF32 && input->buf[1] == 0 && input->buf[2] == 0)
# define BUFFADDR	&buffer

/*
** t_elems truct for stock all elements
** given to ft_select
*/

typedef struct		s_elem
{
	char			*name;
	int				current;
	int				select;
	struct s_elem	*next;
	struct s_elem	*prev;
	int				number;
}					t_elem;

typedef struct		s_select
{
	t_elem			*s_elem;
	struct termios	term;
	int				max_len;
}					t_select;

typedef struct		s_input
{
	char			buf[3];
	int				size_win;
	int				fd;
	struct winsize	sz;
}					t_input;

void				ft_ini_input(struct termios *term, t_elem *elems, \
															int max_len_word);
void				ft_size_win(t_input *input, int get_num, t_elem *elem, \
															int max_len_word);
void				ft_input(struct termios *term, t_elem *elems, int m, \
																t_input *input);

void				destruct(struct termios *term);
void				ft_add_elem(char **av, t_elem *elems);
int					init(struct termios *term);

void				ft_test(t_elem *elems, int max_size);
void				ft_move_right(t_elem *fixed);
void				ft_move_left(t_elem *fixed);
void				ft_move_down(t_elem *fixed, int max);
void				ft_move_up(t_elem *fixed, int max);

void				ft_print(t_elem *elems, int max);
void				ft_key_space(t_elem *fixed);

int					ft_get_nb_col(int max);
void				ft_get_input(struct termios *term, t_elem *elems,\
															int max_len_word);
void				ft_print_elems(t_elem *elems);
void				ft_move_up_line(t_elem *fixed, int curr_line, int max);

void				*select_static(void);
void				resize(int i);
void				ft_ctrl_c(int i);
void				ft_ctrl_z(int i);
void				ft_fg(int i);

void				get_screen_size(void);
int					my_out(int i);
int					ft_largest_word(char **av);

int					ft_get_win_x(void);
int					ft_get_win_y(void);
void				ft_exit(char *str);
int					ft_get_cursor_y(void);

t_elem				*go_to_first(t_elem *fixed, int max);
t_elem				*go_to_last(t_elem *fixed, int max);
void				ft_special_case(t_elem *elem);
void				ft_init_print(t_select *sel);

void				ft_norme1(int curr_line, int save, int last_line, \
								int nb_lines);
void		   		ft_norme2(int m, t_input *input, t_elem *elems);
#endif
