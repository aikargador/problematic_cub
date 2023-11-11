#include "cub69d.h"

// void	map_init(t_able *table)
// {
// 	int	y;
// 	int	x;

// 	y = -1;
// 	table->map = calloc(24, sizeof(int *));
// 	for (int i = 0; i < 24; i++)
// 		table->map[i] = calloc(24, sizeof(int));
// 	while (++y < 24)
// 	{
// 		x = -1;
// 		while (++x < 24)
// 		{
// 			if (y == 0 || y == 24 - 1)
// 				table->map[y][x] = 1;
// 			else if (x == 0 || x == 24 -1)
// 				table->map[y][x] = 1;
// 			else
// 				table->map[y][x] = 0;
// 		}
// 	}
// 	//S = 83, N = 78, W = 87, E = 69
// 	table->map[13][3] = 1;
// 	table->map[6][5] = 1;
// 	table->map[3][9] = 1;
// 	table->map[12][12] = 1;
// 	table->map[20][20] = 1;
// 	// table->map[3][1] = 69;//e
// 	// table->map[3][1] = 87;//w
// 	// table->map[3][1] = 83;//s
// 	// table->map[3][1] = 78;//n
// }

// void	draw_map(t_able *table)
// {
// 	int i[2];

// 	i[0] = -1;
// 	while (++i[0] < 24) {
// 		i[1] = -1;
// 		while (++i[1] < 24)
// 			printf("%d, ", table->map[i[0]][i[1]]);
// 		printf("\n");
// 	}
// }

// void	*ft_calloc(size_t count, size_t size)
// {
// 	size_t	i;
// 	void	*str;

// 	i = 0;
// 	str = malloc(count * size);
// 	if (!str)
// 		return (0);
// 	while (i < (count * size))
// 		((char *)str)[i++] = '\0';
// 	return (str);
// }

// void	ft_memset(void *b, int c, size_t len)
// {
// 	size_t	i;

// 	i = 0;
// 	while (i < len)
// 	{
// 		((unsigned char *)b)[i] = c;
// 		i++;
// 	}
// }

// void	initialize_vars(t_able *table)
// {
// 	table
// }
// int	ft_strlen(const char *str)
// {
// 	int	i;

// 	i = -1;
// 	while (str[++i])
// 		;
// 	return (i);
// }

// char	*ft_strdup(const char *s1)
// {
// 	char	*str;
// 	int		i;

// 	i = ft_strlen(s1);
// 	str = ft_calloc((i + 1), sizeof(*str));
// 	if (!str)
// 			return (0);
// 	i = -1;
// 	while (s1[++i])
// 			str[i] = s1[i];
// 	return (str);
// }
/* 
	table->parse.swen_pth[3] = ft_strdup("./textures/wefuk/muha_ascend.xpm");
	table->parse.swen_pth[3] = ft_strdup("./textures/wefuk/muha_frozen.xpm");
	table->parse.swen_pth[3] = ft_strdup("./textures/wefuk/muha_highway.xpm");
	table->parse.swen_pth[0] = ft_strdup("./textures/wefuk/muha_lost.xpm"); //broke
	table->parse.swen_pth[2] = ft_strdup("./textures/wefuk/muha_lost_again.xpm");
	table->parse.swen_pth[3] = ft_strdup("./textures/wefuk/muha_tarzan_edition.xpm");
 */

void	magic_texture_init(t_able *table)
{
	table->swen_pth[0] = table->parse->so_text;
	table->swen_pth[1] = table->parse->we_text;//
	table->swen_pth[2] = table->parse->ea_text;
	table->swen_pth[3] = table->parse->no_text;//
	// table->parse.swen_pth[2] = ft_strdup("./textures/wefuk/muha_frozen.xpm");
	// table->parse.swen_pth[3] = ft_strdup("./textures/wefuk/fraz_muha.xpm");
	// table->parse.swen_pth[0] = ft_strdup("./textures/shahrukh/shahrukh_rand-144.xpm");//broke
	// table->parse.swen_pth[1] = ft_strdup("./textures/wefuk/alien_tymr.xpm");//broke
	// table->parse.swen_pth[2] = ft_strdup("./textures/wefuk/muha_for_the_streets.xpm");
	// table->parse.swen_pth[3] = ft_strdup("./textures/wefuk/tymr_glw.xpm");
	// table->parse.swen_pth[2] = ft_strdup("./textures/wefuk/tf_this1.xpm");
	// table->parse.swen_pth[0] = ft_strdup("./textures/wefuk/tf_this2.xpm"); //broke
	// table->parse.swen_pth[1] = ft_strdup("./textures/wefuk/tf_this3.xpm"); //broke
	// table->parse.swen_pth[0] = ft_strdup("./textures/opt/jinx256.xpm");
	// table->parse.swen_pth[1] = ft_strdup("./textures/opt/jinx256.xpm");
}

void	init_frame(t_able *table)
{
	int	i;

	i = -1;
	table->frame.frmes = malloc(3 * sizeof(size_t *));
	if (!table->frame.frmes)
		return ;//change this to appropriate eggor mono sodium glutamate!
	while (++i < 3)
	{
		table->frame.frmes[i] = malloc((TEX_DIM * TEX_DIM) * sizeof(size_t));
		if (!table->frame.frmes[i])
			return ;//again fex thes shet!
		if (!load_texture(table, table->frame.frmes[i], table->frame.fpth[i]))
			return ;//chkk and update to approp ret val!
	}
}

void	magic_frame_init(t_able *table)
{
	table->frame.fpth[0] = ft_strdup("./textures/wefuk/tf_this1.xpm");
	table->frame.fpth[1] = ft_strdup("./textures/wefuk/tf_this2.xpm");
	table->frame.fpth[2] = ft_strdup("./textures/wefuk/tf_this3.xpm");
}

void	player_init(t_able *table)
{
	printf("%d\n", table->parse->pos.x);
	printf("%d\n", table->parse->pos.y);
	table->plr.pos.x = table->parse->pos.x;
	table->plr.pos.y = table->parse->pos.y;
	table->plr.dir.x = 0;
	table->plr.dir.y = 0;
	if (table->parse->pdir == 'N')
		table->plr.dir.y = -1;
	else if (table->parse->pdir == 'S')
		table->plr.dir.y = 1;
	else if (table->parse->pdir == 'E')
		table->plr.dir.x = 1;
	else
		table->plr.dir.x = -1;
	table->plane.x = 0;
	table->plane.y = 0.75;
	table->plr.mv_spd = 0.05;
	table->plr.rt_spd = 0.10;
}

int eggsecute(t_parse *parse)
{
	t_able table;

	// printf("no_texture = %s\n", parse->no_text);
	ft_memset(&table, 0, sizeof(t_able));
	table.parse = parse;
	table.frame.chnge = 0;
	table.frame.step = 1;
	magic_texture_init(&table);
	table.mlx.img = calloc(1, sizeof(t_img));
	if (!table.mlx.img)
		return 69;
	table.mlx.mlx = mlx_init();
	player_init(&table);
	// table.plr.rt_spd = 0.05;
	// map_init(&table);
	// draw_map(&table); 
	table.mlx.win = mlx_new_window(table.mlx.mlx, width, height, "mlx");
	if (!table.mlx.win)
	{
		free(table.mlx.win);
		return (1);
	}
	table.mlx.img = new_image(&table, false);
	magic_frame_init(&table);
	init_texture(&table);
	init_frame(&table);
	if (!table.mlx.img)
		return (printf("tf\n"));
	mlx_hook(table.mlx.win, 03, 1L<<1, &handle_keyrelease, &table);
	mlx_hook(table.mlx.win, 02, 1L<<0, &handle_keypress, &table);
	mlx_loop_hook(table.mlx.mlx, &main_loop, &table);
	// mlx_key_hook(table.mlx.win, &key_press, &table);
	// mlx_hook(table.win, X_EVENT_KEY_PRESS, 0, &key_press, &table);
	mlx_loop(table.mlx.mlx);
	return (0);
}

// int	eggsecute(t_data *data)
// {
// 	t_eggs	eggs;

// 	ft_bzero(&table, sizeof(t_able));
// 	table.mlx.mlx = mlx_init();
// 	if (!table.mlx.mlx)
// 		return (1);
	

// }