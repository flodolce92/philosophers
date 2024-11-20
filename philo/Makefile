# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/16 18:05:10 by flo-dolc          #+#    #+#              #
#    Updated: 2024/11/13 14:55:36 by flo-dolc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
GREEN		=	\033[0;32m
YELLOW		=	\033[0;33m
RED			=	\033[0;31m
BLUE		=	\033[0;34m
RESET		=	\033[0m

SRCS_DIR	=	src/

SRC			=	main.c \
				utils.c \
				init.c \
				threads.c \
				actions.c \
				actions_utils.c \

SRCS		=	$(addprefix $(SRCS_DIR), $(SRC))

OBJS_DIR	=	obj/

OBJS		=	$(addprefix $(OBJS_DIR), $(SRC:.c=.o))

NAME		=	philo

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

INCLUDES	=

all:			$(NAME)

$(OBJS_DIR):
				@echo "$(YELLOW)Creating object directory...$(RESET)"
				@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c | $(OBJS_DIR)
				@echo "$(BLUE)Compiling $<...$(RESET)"
				@$(CC) $(CFLAGS) -c -g $< -o $@ $(INCLUDES)

$(NAME):		$(OBJS_DIR) $(OBJS)
				@echo "$(GREEN)Linking objects and creating $(NAME)...$(RESET)"
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
				@echo "$(RED)Cleaning object files...$(RESET)"
				@$(RM) $(OBJS)
				@$(RM) -r $(OBJS_DIR)

fclean:			clean
				@echo "$(RED)Removing executable...$(RESET)"
				@$(RM) $(NAME)

re:				fclean all

norm:
				@echo "$(BLUE)Running norminette...$(RESET)"
				@norminette $(SRCS) $(SRCS_DIR)philo.h

.PHONY:			all clean fclean re norm
