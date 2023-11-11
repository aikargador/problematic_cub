/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aikram <aikram@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 20:21:30 by aikram            #+#    #+#             */
/*   Updated: 2023/11/10 15:02:09 by aikram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub69d.h"

bool	load_texture(t_able *table, size_t *tex, char *path)
{
	t_img	tmp;
	int		txhw;
	int		yx[2];

	txhw = TEX_DIM;
	ft_memset(yx, -1, sizeof(int) * 2);
	tmp.img = mlx_xpm_file_to_image(table->mlx.mlx, path, &txhw, &txhw);
	if (!tmp.img)
		return (false);
	tmp.addr = (int *)mlx_get_data_addr(tmp.img, &tmp.bpp, &tmp.line_len, &tmp.endian);
	if (!tmp.addr)
		return (false);
	while (++yx[0] < TEX_DIM)
	{
		yx[1] = -1;
		while (++yx[1] < TEX_DIM)
			tex[(TEX_DIM * yx[0]) + yx[1]] = tmp.addr[(TEX_DIM * yx[0]) + yx[1]];
	}
	mlx_destroy_image(table->mlx.mlx, tmp.img);
	return (true);
}

void	init_texture(t_able *table)
{
	int	i;

	i = -1;
	table->swen_tx = malloc(4 * sizeof(size_t *));
	if (!table->swen_tx)
		return ;//change this to appropriate eggor mono sodium glutamate!
	while (++i < 4)
	{
		table->swen_tx[i] = malloc((TEX_DIM * TEX_DIM) * sizeof(size_t));
		if (!table->swen_tx[i])
			return ;//again fex thes shet!
		if (!load_texture(table, table->swen_tx[i], table->swen_pth[i]))
			return ;//chkk and update to approp ret val!
	}
}

void	fill_col_clr(t_able *table)
{
	int	i;

	i = -1;
	while (++i < table->tex.draw_start - 1)
		table->mlx.img->addr[(i * width) + table->col] = 0x00DFDAD2;
	while (++i < table->tex.draw_end)
	{
		table->tex.crd.y = (int)table->tex.pos & (TEX_DIM - 1);
		table->tex.pos += table->tex.step;
		table->mlx.img->addr[(i * width) + table->col] = 0x008c7e90; //seggs spotted
	}
	i--;
	while (++i < height)
		table->mlx.img->addr[((i * width) + table->col) % 2812500] = 0x00324232;
}

void	fill_frm_col(t_able *table)
{
	int	i;

	i = -1;
	while (++i < table->tex.draw_start - 1)// draw start has issues!
		table->mlx.img->addr[(i * width) + table->col] = table->parse->ceil_color;
	while (++i < table->tex.draw_end)
	{
		table->tex.crd.y = (int)table->tex.pos & (TEX_DIM - 1);
		table->tex.pos += table->tex.step;
		if (!table->ray.side)
		{
			// if (table->frame.chnge < 0 || table->frame.chnge >= 90000)
			// {
			// 	if (table->frame.chnge >= 90000)
			// 		table->frame.chnge = 59999;
			// 	else
			// 		table->frame.chnge = 30000;
			// 	table->frame.step *= -1;
			// }
			if (table->frame.chnge >= 0 && table->frame.chnge < 20000)
				table->mlx.img->addr[(i * width) + table->col] = table->frame.frmes[0][(TEX_DIM * table->tex.crd.y) + table->tex.crd.x]; //seggs spotted
			else if (table->frame.chnge >= 20000 && table->frame.chnge < 40000)
				table->mlx.img->addr[(i * width) + table->col] = table->frame.frmes[1][(TEX_DIM * table->tex.crd.y) + table->tex.crd.x]; //seggs spotted
			else if (table->frame.chnge >= 40000 && table->frame.chnge < 120000)
				table->mlx.img->addr[(i * width) + table->col] = table->frame.frmes[2][(TEX_DIM * table->tex.crd.y) + table->tex.crd.x]; //seggs spotted
			// table->frame.chnge += table->frame.step;
		}
		else
			table->mlx.img->addr[(i * width) + table->col] = table->swen_tx[table->ray.side][(TEX_DIM * table->tex.crd.y) + table->tex.crd.x]; //seggs spotted
	}
	i--;
	while (++i < height)
			table->mlx.img->addr[((i * width) + table->col) % 2812500] = table->parse->floor_color;
			// table->mlx.img->addr[2812500] = DARK_BLUE;
}

void	fill_col(t_able *table)
{
	int	i;

	i = -1;
	while (++i < table->tex.draw_start - 1 && table->tex.draw_start < 1250)
		table->mlx.img->addr[(i * width) + table->col] = table->parse->ceil_color;
	// printf("start %d\n", table->tex.draw_start);
	// printf("end   %d\n", table->tex.draw_end);
	while (i < table->tex.draw_end)
	{
		table->tex.crd.y = (int)table->tex.pos & (TEX_DIM - 1);
		table->tex.pos += table->tex.step;
		table->mlx.img->addr[(i * width) + table->col] = table->swen_tx[table->ray.side][(TEX_DIM * table->tex.crd.y) + table->tex.crd.x]; //seggs spotted
		i++;
	}
	while (++i < height)
		table->mlx.img->addr[((i * width) + table->col) % 2812500] = table->parse->floor_color;
}

void	texture(t_able *table)
{
	double	wallx;

	if (!table->ray.side || table->ray.side == 2)
		wallx = table->plr.pos.y + table->ray.perp_wall_dist \
		* table->ray.dir.y;
	else
		wallx = table->plr.pos.x + table->ray.perp_wall_dist \
		* table->ray.dir.x;
	wallx -= floor((wallx));
	table->tex.crd.x = wallx * (double)TEX_DIM;
	table->tex.step = 1.0 * TEX_DIM / table->tex.line_hgt;
	table->tex.pos = (table->tex.draw_start - height / 2 + table->tex.line_hgt \
	/ 2) * table->tex.step;
	// fill_col(table);
	fill_frm_col(table);
}
