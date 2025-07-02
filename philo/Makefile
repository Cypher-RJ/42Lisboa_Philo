NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS =	src/error.c \
		src/init.c \
		src/main.c \
		src/monitor.c \
		src/sim.c \
		src/syntax.c \
		src/utils.c \

OBJS = $(patsubst src/%.c,obj/%.o,$(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	@echo "\033[1;32mMaking ./philo executable.\033[0m"
	@ $(CC) $(CFLAGS) $(OBJS) -o $(NAME)

obj/%.o: src/%.c
	@mkdir -p $(@D)
	@ $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo "\033[1;31mCleaning object files.\033[0m"
	@rm -f -r obj/

fclean: clean
	@rm -f $(NAME)
	@echo "\033[1;31mCleaning ./philo executable.\033[0m"

re: fclean all

.PHONY: all clean fclean re