#include "cub69d.h"

void	ray_dir(t_able *table);
void	chk_wall_cnt(t_able *table);
void	draw_ray(t_able *table);

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	int	*dst;

	dst = (int *)data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void	fill_col(t_able *table);

void	calc(t_able *table)
{
	table->col = 0;
	while (table->col < width)
	{
		table->camx = 2 * table->col / (double)width - 1;
		table->ray.dir.x = table->plr.dir.x + table->plane.x * table->camx;
		table->ray.dir.y = table->plr.dir.y + table->plane.y * table->camx;
		table->ray.map.x = (int)table->plr.pos.x;
		table->ray.map.y = (int)table->plr.pos.y;
		table->ray.delta_dist.x = fabs(1 / table->ray.dir.x);
		table->ray.delta_dist.y = fabs(1 / table->ray.dir.y);
		table->ray.hit = 0;
		ray_dir(table);
		chk_wall_cnt(table);
		draw_ray(table);
		texture(table);
		if (table->frame.chnge < 0 || table->frame.chnge >= 120000)
		{
			if (table->frame.chnge >= 120000)
				table->frame.chnge = 39999;
			else
				table->frame.chnge = 20000;
			table->frame.step *= -1;
		}
		table->frame.chnge += table->frame.step;
		table->col++;
	}
}

void	ray_dir(t_able *table)
{
	if (table->ray.dir.x < 0)
	{
		table->ray.step.x = -1;
		table->ray.side_dist.x = (table->plr.pos.x - table->ray.map.x) * table->ray.delta_dist.x;
	}
	else
	{
		table->ray.step.x = 1;
		table->ray.side_dist.x = (table->ray.map.x + 1.0 - table->plr.pos.x) * table->ray.delta_dist.x;
	}
	if (table->ray.dir.y < 0)
	{
		table->ray.step.y = -1;
		table->ray.side_dist.y = (table->plr.pos.y - table->ray.map.y) * table->ray.delta_dist.y;
	}
	else
	{
		table->ray.step.y = 1;
		table->ray.side_dist.y = (table->ray.map.y + 1.0 - table->plr.pos.y) * table->ray.delta_dist.y;
	}
}

void	chk_wall_cnt(t_able *table)
{
	while (!table->ray.hit)
	{
		if (table->ray.side_dist.x < table->ray.side_dist.y)
		{
			table->ray.side_dist.x += table->ray.delta_dist.x;
			table->ray.map.x += table->ray.step.x;
			if (table->ray.dir.x < 0)
				table->ray.side = 0;
			else
				table->ray.side = 2;
		}
		else
		{
			table->ray.side_dist.y += table->ray.delta_dist.y;//
			table->ray.map.y += table->ray.step.y;
			if (table->ray.dir.y < 0)
				table->ray.side = 1;
			else
				table->ray.side = 3;
		}
		if (table->parse->map[table->ray.map.y][table->ray.map.x] == '1')
			table->ray.hit = 1;
	}
}

// Process 23976 stopped
// * thread #1, queue = 'com.apple.main-thread', stop reason = step over
//     frame #0: 0x0000000100001be1 cub69d`main at main.c:160:21
//    157           mlx_loop_hook(table.mlx.mlx, &main_loop, &table);
//    158           // mlx_key_hook(table.mlx.win, &key_press, &table);
//    159           // mlx_hook(table.win, X_EVENT_KEY_PRESS, 0, &key_press, &table);
// -> 160           mlx_loop(table.mlx.mlx);
//    161   }
//    162   
//    163   // int main() {
// Target 0: (cub69d) stopped.
// (lldb) 
// Process 23976 stopped
// * thread #1, queue = 'com.apple.main-thread', stop reason = EXC_BAD_ACCESS (code=1, address=0x1)
//     frame #0: 0x0000000100002d00 cub69d`chk_wall_cnt(table=0x00007ffeefbff4b8) at ray_cast.c:84:54
//    81                            else
//    82                                    table->ray.side = 3;
//    83                    }
// -> 84                    if (table->map[table->ray.map.x][table->ray.map.y] == 1)
//    85                            table->ray.hit = 1;
//    86            }
//    87    }
// Target 0: (cub69d) stopped.
void	draw_ray(t_able *table)
{
	// if (table->ray.side == 0 || table->ray.side == 2) //need fix!
	// 	table->ray.perp_wall_dist = (table->ray.map.x - table->plr.pos.x
	// 			+ (1 - table->ray.step.x) / 2) / table->ray.dir.x;
	// else
	// 	table->ray.perp_wall_dist = (table->ray.map.y - table->plr.pos.y + (1
	// 				- table->ray.step.y) / 2) / table->ray.dir.y;
	if (!table->ray.side || table->ray.side == 2)
		table->ray.perp_wall_dist = table->ray.side_dist.x - table->ray.delta_dist.x;
	else
		table->ray.perp_wall_dist = table->ray.side_dist.y - table->ray.delta_dist.y;
	// if(side == 0) perpWallDist = (sideDistX - deltaDistX);
    //   else          perpWallDist = (sideDistY - deltaDistY);
	// table->ray.perp_wall_dist = (table->ray.map.y - table->plr.pos.y + (1 - table->ray.step.y) / 2) / table->ray.dir.y;
	//Calculate height of line to draw on screen
	// printf("%f\n", table->ray.perp_wall_dist);
	if (table->ray.perp_wall_dist <= 0)//fixfixifxixifixifixifixif
		table->ray.perp_wall_dist = 1;
	table->tex.line_hgt = (int)(height / table->ray.perp_wall_dist);
	//calculate lowest and highest pixel to fill in current stripe
	table->tex.draw_start = (height / 2) - (table->tex.line_hgt / 2);
	if(table->tex.draw_start < 0)
		table->tex.draw_start = 0;
	table->tex.draw_end = (height / 2) + (table->tex.line_hgt / 2);
	if(table->tex.draw_end >= height)
		table->tex.draw_end = height - 1;
}

	// if (!table->ray.side/*  || table->ray.side == 2 */)
	// 	table->ray.perp_wall_dist = (table->ray.map.x - table->plr.pos.x + (1 - table->ray.step.x) / 2) / table->ray.dir.x;
	// else
	// 	table->ray.perp_wall_dist = (table->ray.map.y - table->plr.pos.y + (1 - table->ray.step.y) / 2) / table->ray.dir.y;
	// //Calculate height of line to draw on screen
	// table->tex.line_hgt = (int)(height / table->ray.perp_wall_dist);

	// //calculate lowest and highest pixel to fill in current stripe
	// table->tex.draw_start = -table->tex.line_hgt / 2 + height / 2;
	// if(table->tex.draw_start < 0)
	// 	table->tex.draw_start = 0;
	// table->tex.draw_end = table->tex.line_hgt / 2 + height / 2;
	// if(table->tex.draw_end >= height)
	// 	table->tex.draw_end = height - 1;
	// int	color = 0xFFFF00;
	// if (table->ray.side == 1)
		// color = color / 2;

