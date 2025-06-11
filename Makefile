# Nome degli eseguibili
NAME         = minishell
# BONUS_NAME   = pipex_bonus

# Compilatore e flags
CC           := cc
CFLAGS       := -Wall -Wextra -Werror -g

# Directory
LIBFT_DIR    := libft
OBJS_DIR     := obj

# Libreria
LIBFT_LIB    := $(LIBFT_DIR)/libft.a

# Sorgenti
SRCS         := main.c build_in_cmd.c parsing.c signal.c token.c token_utils.c expand.c redirections.c utils.c find_cmd_path.c

# Oggetti (con prefisso obj/)
OBJS         := $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRCS))

# Regola di default
all: $(NAME)

# --- 1) Creazione dell’executable base ---
# Assicuriamoci che obj/ esista, poi linkiamo
$(NAME): $(OBJS) $(LIBFT_LIB) | $(OBJS_DIR)
	@$(CC) $(CFLAGS) $^ -o $(NAME) -L$(LIBFT_DIR) -lreadline -lft
	@echo -e "\033[32m$(NAME) created!\033[0m"

# --- 3) Rule per creare la cartella obj/
$(OBJS_DIR):
	@mkdir -p $@

# --- 4) Regola pattern per compilare ogni .c in obj/*.o
#     $< = file .c di input, $@ = obj/foo.o
$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo -e "\033[90m$< compiled\033[0m"

# --- 5) Compilazione della libft ---
$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

# --- 6) Pulizia oggetti ---
clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJS_DIR)
	@echo -e "\033[33mObjects removed.\033[0m"

# --- 7) Pulizia completa (oggetti + binari) ---
fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME) $(BONUS_NAME)
	@echo -e "\033[31mBinaries wiped\033[0m"

# --- 8) Rebuild ---
re: fclean all

.PHONY: all bonus clean fclean re