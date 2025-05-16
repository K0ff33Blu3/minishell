NAME = libftprintf.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = ft_printf.c ft_putchar.c ft_putnbr.c ft_putnbr_hex.c ft_putnbr_unsigned.c ft_putstr.c ft_putptr.c

OBJS_DIR = obj
OBJS         := $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRCS))

all: $(NAME)

$(NAME) : $(OBJS)
	@ar rc $@ $?
	@echo -e "\033[32m\n$(NAME) created!\033[0m"

$(OBJS_DIR):
	@mkdir -p $@

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo -e "\033[90m$< compiled\033[0m"

clean:
	@rm -rf $(OBJS_DIR)
	@echo -e "\033[33mObjects removed.\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo -e "\033[31m$(NAME) wiped\033[0m"

re: fclean all

.PHONY: all clean fclean re