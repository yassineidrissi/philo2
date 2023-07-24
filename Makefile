SRCS = philo.c srcs/ft_parsing.c srcs/errors.c srcs/lib_src.c srcs/utils.c srcs/time.c srcs/print.c

OBJS			= $(SRCS:.c=.o)
CC				= cc
RM				= rm -f
CFLAGS			= -g -Wall -Wextra -Werror -I -fsanitize=thread
NAME			= philo
PRINTF = printf

DEFAULT = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

%.o : %.c
		@$(CC) $(CFLAGS) -c $< -o $@

all:		1337_logo	$(NAME) 

$(NAME):	1337_logo	$(OBJS)
			@$(CC) $(OBJS) -o $(NAME)
			@echo "\033[92m✅PHILO GENERATED YOU CAN STARTED✅\033[0m"
			@$(PRINTF) "\r%100s\r$(GREEN)$(NAME) is up to date!$(DEFAULT)\n"

clean:				
				@$(RM) $(OBJS) 
				@echo "\033[31m Delete object files🗑\033[31m"
			
fclean:			clean
				@$(RM) $(NAME)
				@echo "\033[31m Delete exucted file🗑\033[31m"

re:				fclean $(NAME)

1337_logo:

	@echo "\033[92m░░███╗░░██████╗░██████╗░███████╗\033[0m███╗░░░███╗███████╗██████╗░"
	@echo "\033[92m░████║░░╚════██╗╚════██╗╚════██║\033[0m████╗░████║██╔════╝██╔══██╗"
	@echo "\033[92m██╔██║░░░█████╔╝░█████╔╝░░░░██╔╝\033[0m██╔████╔██║█████╗░░██║░░██║"
	@echo "\033[92m╚═╝██║░░░╚═══██╗░╚═══██╗░░░██╔╝░\033[0m██║╚██╔╝██║██╔══╝░░██║░░██║"
	@echo "\033[92m███████╗██████╔╝██████╔╝░░██╔╝░░\033[0m██║░╚═╝░██║███████╗██████╔╝"
	@echo "\033[92m╚══════╝╚═════╝░╚═════╝░░░╚═╝░░░\033[0m╚═╝░░░░░╚═╝╚══════╝╚═════╝░"
	@echo "\033[92mCREATING .O FILES AND exuctubel of philo ⌛\033[0m"

.PHONY: all fclean clean re 1337_logo