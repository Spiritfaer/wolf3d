# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: istalevs <istalevs@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/08 16:11:41 by istalevs          #+#    #+#              #
#    Updated: 2018/05/07 23:07:58 by istalevs         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= wolf3d

# src / obj files
SRC		= checks.c \
		event_mix.c \
		list.c \
		pars.c \
		sprite.c \
		drawing.c \
		floor.c \
		main.c \
		raycast.c \
		weapon.c \
		event.c \
		foo.c \
		maker.c \
		renderer.c \
		event_control.c \
		init.c \
		map.c \
		set_struct.c

OBJ		= $(addprefix $(OBJDIR),$(SRC:.c=.o))

# compiler
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

# mlx library
# MLX_LNK	= -l mlx -framework OpenGL -framework AppKit

# ft library
FT		= ./libft/
FT_LIB	= $(addprefix $(FT),libft.a)
FT_INC	= -I ./libft
FT_LNK	= -L ./libft -l ft

# ft SDL2
SDL		= ./sdl/sdl2/2.0.8/lib/
SDL_LIB	= $(addprefix $(FT),libSDL2.a)
SDL_INC	= -I ./sdl/sdl2/2.0.8/include/SDL2/
SDL_LNK	= -L ./sdl/sdl2/2.0.8/lib/ -l SDL2

# ft SDL2_image
SDL_IMG	= ./sdl/sdl2_image/2.0.3/lib/
IMG_LIB	= $(addprefix $(FT),libSDL2_image.a)
IMG_INC	= -I ./sdl/sdl2_image/2.0.3/include/SDL2/
IMG_LNK	= -L ./sdl/sdl2_image/2.0.3/lib/ -l SDL2_image

# ft SDL2_mixer
SDL_MIX	= ./sdl/sdl2_mixer/2.0.2_3/lib/
MIX_LIB	= $(addprefix $(FT),libSDL2_mixer.a)
MIX_INC	= -I ./sdl/sdl2_mixer/2.0.2_3/include/SDL2/
MIX_LNK	= -L ./sdl/sdl2_mixer/2.0.2_3/lib/ -l SDL2_mixer

# ft SDL2_ttf
SDL_TTF	= ./sdl/sdl2_ttf/2.0.14/lib/
TTF_LIB	= $(addprefix $(FT),libSDL2_mixer.a)
TTF_INC	= -I ./sdl/sdl2_ttf/2.0.14/include/SDL2/
TTF_LNK	= -L ./sdl/sdl2_ttf/2.0.14/lib/ -l SDL2_ttf

# directories
SRCDIR	= ./src/
INCDIR	= ./includes/
OBJDIR	= ./obj/

all: obj $(FT_LIB) $(NAME)

obj:
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o:$(SRCDIR)%.c
	@$(CC) $(CFLAGS) $(FT_INC) $(SDL_INC) $(IMG_INC) $(MIX_INC) $(TTF_INC) -I $(INCDIR) -o $@ -c $<

$(FT_LIB):
	@make -C $(FT)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(SDL_LNK) $(IMG_LNK) $(MIX_LNK) $(TTF_LNK) $(FT_LNK) -lm -o $(NAME)
	@say -v Karen "You're the best! All is done!"
	@echo "You're the best! All is done!"

clean:
	@rm -rf $(OBJDIR)
	@make -C $(FT) clean
	@say -v Karen "Objects files was deleted"
	@echo "Objects files was deleted"

fclean: clean
	@rm -fr .DS*
	@rm -rf $(NAME)
	@make -C $(FT) fclean
	@say -v Karen "All is clear!"
	@echo "All is clear!"

re: fclean all
