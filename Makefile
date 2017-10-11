
NAME = ft_select

# LIBFT
LFTPATH = ./libft
LFTFILE = $(LFTPATH)/libft.a

OBJPATH = obj
SRCPATH = src

INCLUDE = -I ./include

CC = gcc
BASEFLAGS = -Wall -Wextra -Wconversion
CFLAGS = $(BASEFLAGS) -Werror -O2 -g

FILES = ft_main.c \
		term_functions.c \
		ft_window.c \
		ft_move.c \
		ft_utils.c \
		ft_input.c \
		signal.c \
		ft_go_to.c \
		ft_norme.c

SRC = $(addprefix $(SRCPATH)/,$(FILES))
OBJECTS = $(SRC:$(SRCPATH)/%.c=$(OBJPATH)/%.o)

RM = rm -rf

# Yellow
Y = \033[0;33m
# Red
R = \033[0;31m
# Green
G = \033[0;32m
# No color
E = \033[39m

all: libft $(NAME)

$(NAME): $(OBJECTS)
	@echo "$(Y)[COMPILING FT_SELECT] $(G) $(CC) -o $@ $(CFLAGS) -g $(OBJECTS) $(INCLUDES) $(LFTFILE) $(E)"
	@$(CC) -o $@ $(CFLAGS)  $(OBJECTS) $(INCLUDE) $(LFTFILE) -ltermcap
	@echo "$(Y)[COMPILING FT_SELECT DONE]$(E)"

$(OBJECTS): $(OBJPATH)/%.o : $(SRCPATH)/%.c
	@mkdir -p $(dir $@)
	$(CC) -o $@ $(CFLAGS) $(INCLUDES) -c $<

clean:
	@echo "$(Y)[FT_SELECT]$(E)"
	@echo "$(R)[REMOVE OBJ DIR]$(E)"
	@$(RM) $(OBJPATH)
	@cd $(LFTPATH) && $(MAKE) -s clean

fclean: clean
	@$(RM) $(NAME)
	@cd $(LFTPATH) && $(MAKE) -s fclean

libft:
	@cd $(LFTPATH) && $(MAKE)

re: fclean all
