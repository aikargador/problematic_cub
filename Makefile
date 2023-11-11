NAME = cub69d

# Determine the OS using the 'uname' command
UNAME := $(shell uname)

# Compiler and flags
CC := cc
CFLAGS := -Wall -Wextra -Werror -g -I includes


# Set compiler flags based on the detected OS
ifeq ($(UNAME), Darwin) # macOS 
	CFLAGS += -Imlx
	CXXFLAGS = -Lmlx -lmlx -Lparse/libft -lft -framework OpenGL -framework AppKit -lm
else ifeq ($(UNAME), Linux)
	CFLAGS += -Imlx_linux
	CXXFLAGS = -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
else
	$(error Unsupported OS: $(UNAME))
endif

# Targets and dependencies
# all: your_program

# your_program: main.c
#     $(CC) $(CFLAGS) -o $@ $^

# clean:
#     rm -f your_program


# CXXFLAGS = -Wall -Werror -Wextra -g
# CFLAGS = -Imlx -I includes ${CXXFLAGS}

UTILS = ${addprefix utils/, }
PARSE = ${addprefix parse/, ft_error p_check p_cpy_map p_init p_map \
		p_map_utilis p_parse p_text_utilis p_texture p_wall p_wall_utilis parsing_utils}
SAUCE = ${addprefix sauce/, ${addsuffix .c, execution movement ray_cast \
		events window texture ${UTILS} ${PARSE}}} main.c
OBJS = ${SAUCE:c=o}

#-fsanitize=address -O2
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# # linux obj files
# %.o: %.c
# 	$(CC) -Wall -Wextra -Werror -I include -Imlx_linux -03 -c $< -o $@

# # linux executable!
# $(NAME): $(OBJ)
# 	$(CC) $(OBJ) -Lmlx_linux -lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

# ${NAME}: ${OBJS}
# 	${CC} ${OBJS} -Lmlx -lmlx -framework OpenGL -framework AppKit -lm -o ${NAME}
${NAME}: ${OBJS}
	${CC} ${OBJS} $(CXXFLAGS) -o ${NAME}

all: ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re

# does not check for empty xpm files!
# 

