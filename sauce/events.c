#include "cub69d.h"

void	plyr_rt_and_mv(t_able *table, int rt, int mv)
{
	if (rt)
		plyr_rt(table);
	else
		plyr_rrt(table);
	if (mv)
		plyr_mv_forward(table);
	else
		plyr_mv_backward(table);
}

void	strafe_and_move(t_able *table, int mv, int strf)
{
	if (strf)
		strafe_right(table);
	else
		strafe_left(table);
	if (mv)
		plyr_mv_forward(table);
	else
		plyr_mv_backward(table);
}

void	handle_movements(t_able *table)
{
	if (table->keys[3] && table->keys[4]) // w a
		plyr_rt_and_mv(table, 0, 1);
	else if (table->keys[3] && table->keys[5]) // w d
		plyr_rt_and_mv(table, 1, 1);
	else if (table->keys[1] && table->keys[4]) // s a
		plyr_rt_and_mv(table, 0, 0);
	else if (table->keys[1] && table->keys[5]) // s d
		plyr_rt_and_mv(table, 1, 0);

	else if (table->keys[3] && table->keys[2])
		strafe_and_move(table, 1, 1);
	else if (table->keys[3] && table->keys[0])
		strafe_and_move(table, 1, 0);
	else if (table->keys[1] && table->keys[2])
		strafe_and_move(table, 0, 1);
	else if (table->keys[1] && table->keys[0])
		strafe_and_move(table, 0, 0);


	else if (table->keys[0]) // a
		strafe_left(table);
	else if (table->keys[2]) // d
		strafe_right(table);
	else if (table->keys[1]) // s
		plyr_mv_backward(table);
	else if (table->keys[5]) // <-
		plyr_rt(table);
	else if (table->keys[4]) // ->
		plyr_rrt(table);
	else if (table->keys[3]) // w
		plyr_mv_forward(table);
}

int	handle_keypress(int keysym, t_able *table)
{
	if (keysym == 53) {
		mlx_destroy_window(table->mlx.mlx, table->mlx.win);
		exit (0); //make sure to clear em memmo
	}
	else if (keysym == 0)
		table->keys[0] = true;
	else if (keysym == 1)
		table->keys[1] = true;
	else if (keysym == 2)
		table->keys[2] = true;
	else if (keysym == 13)
		table->keys[3] = true;
	else if (keysym == 123)
		table->keys[4] = true;
	else if (keysym == 124)
		table->keys[5] = true;
	return (0);
}

int	handle_keyrelease(int keysym, t_able *table)
{
	// printf("tangl %f\n", table->plr->angl);
	if (keysym == 0)
		table->keys[0] = false;
	else if (keysym == 1)
		table->keys[1] = false;
	else if (keysym == 2)
		table->keys[2] = false;
	else if (keysym == 13)
		table->keys[3] = false;
	else if (keysym == 123)
		table->keys[4] = false;
	else if (keysym == 124)
		table->keys[5] = false;
	return (0);
}

int	main_loop(t_able *table)
{
	// create_new_image(&table->mlx, true);
	// table->mlx.img = new_image(table, table->destroy);
	// if (!table->mlx.img)
	// 	return (printf("tf\n"));
	handle_movements(table);
	calc(table);
	// draw_column(table, table->col, table->tex.draw_start, table->tex.draw_end);
	mlx_put_image_to_window(table->mlx.mlx, table->mlx.win, table->mlx.img->img, 0, 0);
	// table->destroy = true;
	return (0);
}
