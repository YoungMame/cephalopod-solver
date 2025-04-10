NAME = cephalopod

SRCS_DIR = ./
SRCS = main.cpp board_hash.cpp
OBJS_DIR = ./.obj/
OBJS = $(patsubst %.cpp, $(OBJS_DIR)%.o, $(SRCS))
INCLUDES_DIR = ./
INCLUDES = board_hash.hpp

IFLAGS = -I $(INCLUDES_DIR)
CFLAGS = -Werror -Wextra -Wall -std=c++20 -g
FLAGS = $(IFLAGS) $(CFLAGS)

all: $(NAME)

$(NAME): $(OBJS)
	c++ $(FLAGS) $(OBJS) $(GCHS) -o $(NAME)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.cpp
	mkdir -p $(OBJS_DIR)
	c++ $(FLAGS) -c $< -o $@

clean: 
	rm -rf $(OBJS_DIR)*.gch $(OBJS_DIR)*.o
	rmdir -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME)

re : clean $(NAME)