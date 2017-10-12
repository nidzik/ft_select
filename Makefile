
NAME = ft_select

# LIBFT
LFTPATH = libft/
LFTIPATH = -I $(LFTPATH)
LFT = -L $(LFTPATH) -lft
LFTCALL = all
LFTCL = fclean

#TERMCAPS
TERM = -ltermcap


OBJPATH = obj
SRCPATH = src
INCLUDE = -I ./include/


CC = gcc
BASEFLAGS = -Wall -Wextra -Wconversion
CFLAGS = $(BASEFLAGS) -Werror -O2 -g

LIBS = $(LFT) $(TERM)
INCLUDES = $(INCLUDE) $(LFTIPATH)

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

all: l $(NAME)

$(NAME): $(OBJECTS)
	@echo "$(Y)[COMPILING FT_SELECT] $(G) $(CC) -o $@ $(CFLAGS) objs.o $(LIBS) $(E)"
	@$(CC) -o $@ $(CFLAGS)  $(OBJECTS) $(INCLUDES) $(LIBS) 
	@echo "$(Y)[COMPILING FT_SELECT DONE]$(E)"

$(OBJECTS): $(OBJPATH)/%.o : $(SRCPATH)/%.c
	@mkdir -p $(dir $@)
	$(CC) -o $@ $(CFLAGS) $(INCLUDES)  -c $<

clean:
	@echo "$(R)[REMOVE OBJ DIR]$(E)\n$(RM) $(OBJPATH)"
	@$(RM) $(OBJPATH)
	@echo "$(G)[DONE.] $(E)"

fclean: clean
	@echo "$(R)[REMOVE FT_SELECT]$(E)\n$(RM) $(NAME)"
	@$(RM) $(NAME)
	@echo "$(G)[DONE.] $(E)"
lfclean:
	@echo "$(Y)[RM LIBFT] $(E)"
	@make -C $(LFTPATH) $(LFTCL)
	@echo "$(G)[DONE.] $(E)"

cl: lfclean fclean

l:
	@echo "$(Y)[COMPILING LIBFT]\n$(G) make -C $(LFTPATH) $(LFTCALL) $(E)"
	@make -C $(LFTPATH) $(LFTCALL)
	@echo "$(Y)[COMPILING LIBFT DONE]$(E)"

re: fclean all
