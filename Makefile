NAME := ft_ping

INCS_DIR := ./includes

SRCS_DIR := ./srcs

OBJS_DIR := ./objs

SRCS := main.c map.c opt.c parsing.c socket.c

SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))

OBJS := $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

DEPS := $(OBJS:.o=.d)

CC := cc

CFLAGS := -Wall -Wextra -Werror -MMD -I$(INCS_DIR) -lm

CFLAGS += -fsanitize=address -g

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

-include $(DEPS)

.PHONY: all clean fclean re