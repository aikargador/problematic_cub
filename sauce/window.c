#include "cub69d.h"

void	annihilate_img(t_mlx *mlx_ptr)
{
	if (mlx_ptr->img)
	{
		if (mlx_ptr->img->img)
			mlx_destroy_image(mlx_ptr, mlx_ptr->img->img);
		free(mlx_ptr->img);
		mlx_ptr->img = NULL;
	}
}

t_img	*new_image(t_able *table, bool destroy)
{
	t_img	*img;

	if (destroy)
		annihilate_img(&table->mlx);
	img = calloc(1, sizeof(t_img));// change this to calloc when can!
	if (!img)
		return (NULL);
	img->img = mlx_new_image(&table->mlx, width, height);
	if (!img->img)
		return (NULL);
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bpp, \
			&img->line_len, &img->endian);
	if (!img->addr) {
		// printf("data addr\n");
		return (NULL);
	}
	return (img);
}
