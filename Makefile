# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmthimun <hmthimun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/15 23:43:08 by hmthimun          #+#    #+#              #
#    Updated: 2018/07/30 09:13:53 by hmthimun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	avm

CC = g++ -o

SRC =	 main.cpp \
	        ArgReader.cpp \
	        Exceptions.cpp \
			Split.cpp \
			Factory.cpp \

OBJ =	$(SRC:.cpp=.o)

CPPFLAGS += -Werror -Wall -Werror

all:	$(NAME)

$(NAME): $(OBJ)
	 $(CC) $(NAME) $(OBJ) $(CPPFLAGS)

clean:
	rm -f $(OBJ)


fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
