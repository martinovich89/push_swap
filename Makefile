NAME		=	push_swap

LIB			=	-L./libft -lft #-L/libs/mlx -lm -lbsd -lX11 -lXext ./libs/mlx/libmlx.a

INC			=	-I./includes #-I./libs/mlx

SRC_PATH	=	./

SRC			=	main.c

SRCS		=	$(addprefix $(SRC_PATH), $(SRC))

FLAGSD		=	-Wall -Wextra -Werror -fsanitize=address -g3

FLAGS		=	-Wall -Wextra -Werror

OBJS		=	$(SRCS:.c=.o)

CC			=	@clang

RM			=	@rm -f

all:	$(NAME)
$(NAME):$(OBJS)
		@make -C libft
#		@make -C libs/mlx
		$(CC) $(FLAGSD) $(INC) -o $(NAME) $(OBJS) $(LIB)
		@echo "$(NAME) created"

%.o: %.c
	$(CC) $(FLAGS) $(INC) -o $@ -c $<

clean:
		@make $@ -C libft
#		@make $@ -C libs/mlx
		$(RM) $(OBJS)
		@echo "$(OBJS) deleted"

fclean: clean
		@make $@ -C libft
		$(RM) $(NAME)
		@echo "$(NAME) deleted"

re:		fclean all

.PHONY: all clean fclean re