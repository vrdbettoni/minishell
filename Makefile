NAME		=	minishell

CC			=	gcc
INCL		=	minishell.h
FLAG		=	-Wall -Wextra -Werror
LIB			=	./mylib

SRCS_PATH	=	srcs
OBJS_PATH	=	objs
INCL_PATH	=	includes

OBJ			=	$(addprefix $(OBJS_PATH)/, $(SRCS:.c=.o))
INCLS		=	$(addprefix $(INCL_PATH)/, $(INCL))
SRCS		=	main.c				autocompletion.c\
				escape_eq.c			exec.c\
				exit.c				expand.c\
				find_cmd.c			get_next_line_mod.c\
				get_unset_export.c	history_2.c\
				history.c			io_checks.c\
				key_choice.c		list_and_exec.c\
				list_funcs.c		move_term.c\
				ops.c				parse_loop.c\
				pipe.c				prd_reads.c\
				pwd_chdir.c			pwd_chdir_2.c\
				quotes.c			redir.c\
				setenv.c			syntax_check.c\
				termcaps.c			to_array.c\
				utils.c				utils_2.c\
				wildcard.c			utils_3.c

all:		$(NAME)

$(NAME): 	$(OBJ)
			@make -C ./mylib
			$(CC) $(CFLAGS) -o minishell -L $(LIB) -lncurses -lft $(OBJ)
			@echo "\033[32m > \033[1m$(NAME)\033[0;32m created !\033[0m"


$(OBJS_PATH)/%.o:	$(SRCS_PATH)/%.c
					@$(shell mkdir -p $(OBJS_PATH))
					@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@rm -rf $(OBJS_PATH)
			@make clean -C ./mylib
			@echo "\033[31m > \033[1m$(OBJS_PATH)/*\033[0;31m delete.\033[0m"

fclean:		clean
			@rm -rf $(NAME)
			@rm -rf ./*.dSYM
			@make fclean -C ./mylib
			@echo "\033[31m > \033[1m$(NAME)\033[0;31m delete.\033[0m"

re:			fclean all

.PHONY:		all clean fclean re
