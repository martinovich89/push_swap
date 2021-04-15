NAME		=	push_swap

NAME_CHK	=	checker	

LIB			=	-L./libft -lft

INC			=	-I./includes

SRC_PATH	=	./srcs/

#SRC			=	$(CONSTRUCTION) $(DESTRUCTION) $(ERRORS) $(SORTING ALGORITHM) $(UTILS)

SRC			=	push_swap.c utils.c

SRC_CHK		=	checker.c utils.c get_next_line.c get_next_line_utils.c \
				get_next_line_utils2.c

SRCS		=	$(addprefix $(SRC_PATH), $(SRC))

SRCS_CHK	=	$(addprefix $(SRC_PATH), $(SRC_CHK))

FLAGSD		=	-Wall -Wextra -Werror #-fsanitize=address -g3

FLAGS		=	-Wall -Wextra -Werror

OBJS		=	$(SRCS:.c=.o)

OBJS_CHK	=	$(SRCS_CHK:.c=.o)

CC			=	@clang

RM			=	@rm -f

all:	$(NAME) $(NAME_CHK)

$(NAME):$(OBJS)
		@make -C libft
		$(CC) $(FLAGSD) $(INC) -o $(NAME) $(OBJS) $(LIB)
		@echo "$(NAME) created"

$(NAME_CHK):$(OBJS_CHK)
		@make -C libft
		$(CC) $(FLAGSD) $(INC) -o $(NAME_CHK) $(OBJS_CHK) $(LIB)
		@echo "$(NAME_CHK) created"

%.o: %.c
	$(CC) $(FLAGS) $(INC) -o $@ -c $<

clean:
		@make $@ -C libft
		$(RM) $(OBJS) $(OBJS_CHK)
		@echo "$(OBJS) $(OBJS_CHK) deleted"

fclean: clean
		@make $@ -C libft
		$(RM) $(NAME) $(NAME_CHK)
		@echo "$(NAME) $(NAME_CHK) deleted"

re:		fclean all

.PHONY: all clean fclean re
