######### COLORS ########
GREEN := $(shell printf "\033[32m")
RED := $(shell printf "\033[31m")
RESET := $(shell printf "\033[0m")

######### FLAGS ########
CC = clang
CFLAGS = -Wall -Wextra -Werror -g3 -pthread
SANITIZE_FLAGS = -fsanitize=thread -fno-omit-frame-pointer

######### DIRECTORIES ########
SRC_DIR = srcs
OBJ_DIR = objs
INCLUDE_DIR = includes
# Add all include directories here
INCLUDE_DIRS = -I$(INCLUDE_DIR)

######### FILES ########
# Update these with your actual source files

SRC_FILES = $(SRC_DIR)/main.c \
			$(SRC_DIR)/parsing.c \
			$(SRC_DIR)/init.c \
			$(SRC_DIR)/philo_utils.c \
			$(SRC_DIR)/str_utils.c \
			$(SRC_DIR)/fork_utils.c \
			$(SRC_DIR)/monitoring.c \
			$(SRC_DIR)/actions.c \
			$(SRC_DIR)/mutex.c \

OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
OBJ_FILES_ASAN = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/asan/%.o,$(SRC_FILES))

######### NAME ########
NAME = philo
NAME_ASAN = asan_philo

######### COMMANDS ########
all: $(NAME)

$(NAME): $(OBJ_FILES)
	@printf "$(GREEN)Compiling $(NAME)...$(RESET)\n"
	@$(CC) $(CFLAGS) -o $@ $^
	@printf "$(GREEN)✓ $(NAME) successfully compiled!$(RESET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c -o $@ $<
	@printf "$(GREEN)█$(RESET)"

asan: $(NAME_ASAN)

$(NAME_ASAN): $(OBJ_FILES_ASAN)
	@printf "$(GREEN)Compiling $(NAME) with AddressSanitizer...$(RESET)\n"
	@$(CC) $(CFLAGS) $(SANITIZE_FLAGS) -o $@ $^
	@printf "$(GREEN)✓ $(NAME) with ASAN successfully compiled!$(RESET)\n"
	@printf "$(GREEN)→ Run with: ASAN_OPTIONS=abort_on_error=1:halt_on_error=1 ./$(NAME_ASAN)$(RESET)"

$(OBJ_DIR)/asan/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(SANITIZE_FLAGS) $(INCLUDE_DIRS) -c -o $@ $<
	@printf "$(GREEN)█$(RESET)"

clean:
	@printf "$(RED)Cleaning object files...$(RESET)\n"
	@rm -rf $(OBJ_DIR)
	@printf "$(RED)✓ Object files cleaned!$(RESET)\n"

fclean: clean
	@printf "$(RED)Removing executable...$(RESET)\n"
	@rm -f $(NAME) $(NAME_ASAN)
	@printf "$(RED)✓ Executable removed!$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re asan
