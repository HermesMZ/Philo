NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -pthread

SRC_DIR = src
LIB_DIR = lib
OBJ_DIR = obj

INCLUDES = include

SRC = \
	init.c \
	main.c \
	routine.c \
	utils.c \

LIB = \

SRC_ALL = \
	$(addprefix $(SRC_DIR)/, $(SRC)) \
	$(addprefix $(LIB_DIR)/, $(LIB)) \

OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o, $(SRC_ALL))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(LFLAGS) -I $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)🧼 Exécutable supprimé.$(RESET)"

re: fclean all

.PHONY: all clean fclean re