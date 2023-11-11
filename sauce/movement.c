#include "cub69d.h"

void	plyr_rt(t_able *table)
{
	double	old_dirx;
	double	old_planex;
	
	old_dirx = table->plr.dir.x;
	table->plr.dir.x = table->plr.dir.x * cos(-table->plr.rt_spd) - table->plr.dir.y * sin(-table->plr.rt_spd);
	table->plr.dir.y = old_dirx * sin(-table->plr.rt_spd) + table->plr.dir.y * cos(-table->plr.rt_spd);
	old_planex = table->plane.x;
	table->plane.x = table->plane.x * cos(-table->plr.rt_spd) - table->plane.y * sin(-table->plr.rt_spd);
	table->plane.y = old_planex * sin(-table->plr.rt_spd) + table->plane.y * cos(-table->plr.rt_spd);
}

void	plyr_rrt(t_able *table)
{
	double	old_dirx;
	double	old_planex;
	
	old_dirx = table->plr.dir.x;
	table->plr.dir.x = table->plr.dir.x * cos(table->plr.rt_spd) - table->plr.dir.y * sin(table->plr.rt_spd);
	table->plr.dir.y = old_dirx * sin(table->plr.rt_spd) + table->plr.dir.y * cos(table->plr.rt_spd);
	old_planex = table->plane.x;
	table->plane.x = table->plane.x * cos(table->plr.rt_spd) - table->plane.y * sin(table->plr.rt_spd);
	table->plane.y = old_planex * sin(table->plr.rt_spd) + table->plane.y * cos(table->plr.rt_spd);
}

void	plyr_mv_forward(t_able *table)
{
	if (table->parse->map[(int)(table->plr.pos.x + table->plr.dir.x * table->plr.mv_spd)][(int)(table->plr.pos.y)] == '0')
		table->plr.pos.x += table->plr.dir.x * table->plr.mv_spd;
	if (table->parse->map[(int)(table->plr.pos.x)][(int)(table->plr.pos.y + table->plr.dir.y * table->plr.mv_spd)] == '0')
		table->plr.pos.y += table->plr.dir.y * table->plr.mv_spd;
}

void	plyr_mv_backward(t_able *table)
{
	if (table->parse->map[(int)(table->plr.pos.x - table->plr.dir.x * table->plr.mv_spd)][(int)(table->plr.pos.y)] == '0')
		table->plr.pos.x -= table->plr.dir.x * table->plr.mv_spd;
	if (table->parse->map[(int)(table->plr.pos.x)][(int)(table->plr.pos.y - table->plr.dir.y * table->plr.mv_spd)] == '0')
		table->plr.pos.y -= table->plr.dir.y * table->plr.mv_spd;
}

void	strafe_right(t_able *table)
{
	if (table->parse->map[(int)(table->plr.pos.y - table->plr.dir.x * table->plr.mv_spd)][(int)(table->plr.pos.x)] == '0')
		table->plr.pos.y -= table->plr.dir.x * table->plr.mv_spd;
	if (table->parse->map[(int)(table->plr.pos.y)][(int)(table->plr.pos.x + table->plr.dir.y * table->plr.mv_spd)] == '0')
		table->plr.pos.x += table->plr.dir.y * table->plr.mv_spd;
}

void	strafe_left(t_able *table)
{
	// t_icords	axis;

	// if ((int)(table->plr.pos.y + table->plr.dir.x * table->plr.mv_spd) < table->plr.pos.y + table->plr.dir.x * table->plr.mv_spd)
	// 	axis.y = (int)(table->plr.pos.y + table->plr.dir.x * table->plr.mv_spd) + 1;
	if (table->parse->map[(int)(table->plr.pos.y + table->plr.dir.x * table->plr.mv_spd)][(int)(table->plr.pos.x)] == '0')
		table->plr.pos.y += table->plr.dir.x * table->plr.mv_spd;


	// if ((int)(table->plr.pos.x - table->plr.dir.y * table->plr.mv_spd) < table->plr.pos.x - table->plr.dir.y * table->plr.mv_spd)
	// 	axis.x = table->plr.pos.x - table->plr.dir.y * table->plr.mv_spd + 1;
	if (table->parse->map[(int)(table->plr.pos.y)][(int)(table->plr.pos.x - table->plr.dir.y * table->plr.mv_spd)] == '0')
		table->plr.pos.x -= table->plr.dir.y * table->plr.mv_spd;


}


// static void	move_left_right(t_info *info)
// {
	// if (info->move.move_right == 1)
	// {
	// 	if (info->map.tab_map[(int)(info->pos.y - info->raycast.dir.x * \
	// 			info->raycast.speed)][(int)(info->pos.x)] == '0')
	// 		info->pos.y -= info->raycast.dir.x * info->raycast.speed;
	// 	if (info->map.tab_map[(int)(info->pos.y)][(int)(info->pos.x
	// 		+ info->raycast.dir.y * info->raycast.speed)] == '0')
	// 		info->pos.x += info->raycast.dir.y * info->raycast.speed;
	// }
	// if (info->move.move_left == 1)
	// {
	// 	if (table->parse->map[(int)(table->plr.pos.y + table->plr.dir.x * table->plr.mv_spd)][(int)(table->plr.pos.x)] == '0')
	// 	if (info->map.tab_map[(int)(info->pos.y + info->raycast.dir.x * info->raycast.speed)][(int)(info->pos.x)] == '0')
	// 		info->pos.y -= -info->raycast.dir.x * info->raycast.speed;
	// 	if (info->map.tab_map[(int)(info->pos.y)][(int)(info->pos.x - info->raycast.dir.y * info->raycast.speed)] == '0')
	// 		info->pos.x -= info->raycast.dir.y * info->raycast.speed;
	// }
// }

// void plyr_mv_left(t_able *table) {
//     double old_dirx = table->plr.dir.x;
//     table->plr.dir.x = table->plr.dir.x * cos(-M_PI_2) - table->plr.dir.y * sin(-M_PI_2);
//     table->plr.dir.y = old_dirx * sin(-M_PI_2) + table->plr.dir.y * cos(-M_PI_2);

//     double oldPlanex = table->plane.x;
//     table->plane.x = table->plane.x * cos(-M_PI_2) - table->plane.y * sin(-M_PI_2);
//     table->plane.y = oldPlanex * sin(-M_PI_2) + table->plane.y * cos(-M_PI_2);
// }


/* 

to dos!!!!
void	plyr_mv_left(t_able *table) {}

void	plyr_mv_right(t_able *table)
{}

*/