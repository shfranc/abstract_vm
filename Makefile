NAME = avm
FLAGS = -Wall -Wextra -Werror -g
CC = clang++

PATH_SRCS = srcs
PATH_INCS = incs
PATH_OBJS = objs

SRCS = $(addprefix $(PATH_SRCS)/, main.cpp \
		Avm.cpp \
		Reader.cpp \
		Lexer.cpp \
		Token.cpp \
		Parser.cpp \
		Factory.cpp \
		Int8.cpp \
		ParsingException.cpp )
OBJS = $(SRCS:$(PATH_SRCS)/%.cpp=$(PATH_OBJS)/%.o)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $@ $^

$(PATH_OBJS)/%.o: $(PATH_SRCS)/%.cpp
	@test -d $(PATH_OBJS) || mkdir $(PATH_OBJS)
	$(CC) $(FLAGS) -c $< -o $@ -I $(PATH_INCS)

clean:
	rm -rf $(OBJS)
	@rm -rf $(PATH_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re
