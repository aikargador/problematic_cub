#ifndef	CUB69D_H
# define CUB69D_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdint.h>
# include <math.h>
# include "parse.h"

# define PIW 3.1415926536
# define PIE PIW * 2
# define PIN PIW / 2
# define PIS (3 * PIW) / 2

# define width 2250
# define height 1250
// # define width 1250
// # define height 750
# define TEX_DIM 256


# define DARK_BLUE 0x00000032
# define DARK_BROWN 0x00320000
# define DARK_PRL_PNK 0x006c2545
# define MATURE_GREEN 0x00afb7aa
# define MATURE_SKY 0x00324232

typedef struct s_cords {
	double	x;
	double	y;
}				t_cords;

// typedef struct s_icords {
// 	int	x;
// 	int	y;
// }			t_icords;

typedef struct	s_img {
	void	*img;
	int		*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		wdth;
	int		hght;
}				t_img;

typedef struct	s_mlx {
	void	*mlx;
	void	*win;
	t_img	*img;
	// t_img	*tmg;
}				t_mlx;

typedef struct s_plr {
	t_cords	pos;
	t_cords	dir;
	double	mv_spd;
	double	rt_spd;
}				t_plr;

typedef struct s_texture {
	int			id;
	t_icords	crd;
	size_t		color;
	double		pos;
	double		step;
	int			line_hgt;
	int			draw_start;
	int			draw_end;
	struct s_texture *poopy;
} t_rex;

typedef struct s_ray {
	t_cords		dir;
	t_cords		side_dist;
	t_cords		delta_dist;
	t_icords	map;
	t_icords	step;
	int			hit;
	int			side;
	double		perp_wall_dist;
}				t_ray;

// typedef struct	s_parse {
// 	// char	*no_path;
// 	// char	*so_path;
// 	// char	*ea_path;
// 	// char	*we_path;

// 	char	*swen_pth[4];
// }				t_parse;

typedef struct	s_frame {
	int		chnge;
	int		step;
	size_t	**frmes;
	char	*fpth[3];
}				t_frame;

// typedef struct	s_eggs {
// 	bool		keys[6];

// }			t_eggs;

typedef struct	s_table {
	// t_eggs		eggs
	bool		keys[6];
	bool		destroy;
	// size_t	*tex_buf;
	char	*swen_pth[4];
	// unsigned int	**swen_tx;
	size_t	**swen_tx;
	t_plr		plr;
	t_ray		ray;
	t_rex		tex;
	t_mlx		mlx;
	t_cords		plane;
	t_parse		*parse;
	t_frame		frame;
	t_icords	map_max;

	double		camx;
	// int			**map;
	int			col;
	///tmp map

}				t_able;

char	*ft_strdup(const char *s1);
int		main_loop(t_able *table);
void	annihilate_img(t_mlx *mlx_ptr);
int		key_press(int key, t_able *table);
// bool	create_new_image(t_img *img_ptr, t_mlx *mlx_ptr, bool destroy);
bool	create_new_image(t_mlx *mlx_ptr, bool destroy);
// t_img	*new_image(t_able *table);
t_img	*new_image(t_able *table, bool destroy);

// void	draw_column(t_able *table, int x, int y1, int y2, int color);
// void	draw_column(t_able *table, int x, int y1, int y2);
void	*ft_calloc(size_t count, size_t size);
void	fill_image(t_img *data, int x, int y, int color);
void	calc(t_able *table);

void	plyr_rt(t_able *table);
void	plyr_rrt(t_able *table);
void	plyr_mv_forward(t_able *table);
void	plyr_mv_backward(t_able *table);

void	init_texture(t_able *table);
void	texture(t_able *table);

int		handle_keyrelease(int keysym, t_able *table);
int		handle_keypress(int keysym, t_able *table);

// void	ft_memset(void *b, int c, size_t len);
void	draw_column(t_able *table);
void	fill_col_clr(t_able *table);

void	fill_frm_col(t_able *table);
bool	load_texture(t_able *table, size_t *tex, char *path);

void	strafe_left(t_able *table);
void	strafe_right(t_able *table);

// int		eggsecute(t_data *data);
int eggsecute(t_parse *parse);

# endif