NAME= ft_select
CC= gcc
PARAMS= -Wall -Wextra -Werror -g

INC_PATH= inc/
SRC_PATH= src/
OBJ_PATH= obj/

INC_NAME= ft_select.h
SRC_NAME= main.c list.c display.c term_init.c signals.c move.c
OBJ_NAME= $(SRC_NAME:.c=.o)

INC= -I inc/ -I libft/
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))

DEF= \033[0m
RED= \033[31;1m
GRN= \033[32;1m
YEL= \033[33;1m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@gcc $(PARAMS) -o $(NAME) $(OBJ) $(INC) -L libft/ -lft -ltermcap
	@echo "$(RED)[ft_select] : $(DEF)Compilation             $(GRN)[OK]$(DEF)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@echo "$(RED)[ft_select] :$(DEF) Compiling $@"
	@$(CC) $(PARAMS) $(INC) -o $@ -c $<

clean:
	@make -C libft clean
	@rm -rf $(OBJ_PATH)
	@echo "$(RED)[ft_select] : $(DEF)Cleaning                $(GRN)[OK]$(DEF)"

fclean: clean
	@make -C libft execlean
	@rm -rf $(NAME)
	@echo "$(RED)[ft_select] : $(DEF)Full Cleaning           $(GRN)[OK]$(DEF)"

re: fclean all
