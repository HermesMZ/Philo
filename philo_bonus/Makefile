NAME = philo_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -pthread

SRC_DIR = src
LIB_DIR = lib
OBJ_DIR = obj

INCLUDES = include

SRC = \
	checks_bonus.c \
	forks_bonus.c \
	init_bonus.c \
	main_bonus.c \
	routine_bonus.c \
	simulation_bonus.c \
	utils_bonus.c \

LIB = \
	ft_atoi.c \
	ft_atol.c \

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

re: fclean all

.PHONY: all clean fclean re