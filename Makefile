.PHONY: clean all re fclean
CC = c++
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address -std=c++98 
NAME = irc
SRC = main.cpp server.cpp socket.cpp Channel.cpp  ./command/kick.cpp ./command/pass.cpp ./command/user.cpp ./command/nick.cpp client.cpp ./command/join.cpp ./command/privmsg.cpp ./command/mode.cpp ./command/hexchat.cpp ./command/topic.cpp ./command/invite.cpp
OBJ = $(SRC:.cpp=.o)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
