#include "../include/cub3d.h"

// void	draw_texture(t_recup *recup, int x, int y)
// {
// 	y = recup->ray.drawstart - 1;
// 	ft_init_texture(recup);
// 	recup->t.step = 1.0 * recup->texture[0].height / recup->ray.lineheight;
// 	recup->t.texx = (int)(recup->t.wallx * (double)recup->texture
// 			[recup->t.texdir].width);
// 	if (recup->ray.side == 0 && recup->ray.raydirx > 0)
// 		recup->t.texx = recup->texture[recup->t.texdir].width -
// 			recup->t.texx - 1;
// 	if (recup->ray.side == 1 && recup->ray.raydiry < 0)
// 		recup->t.texx = recup->texture[recup->t.texdir].width -
// 			recup->t.texx - 1;
// 	recup->t.texpos = (recup->ray.drawstart - recup->ry / 2 +
// 			recup->ray.lineheight / 2) * recup->t.step;
// 	while (++y <= recup->ray.drawend)
// 	{
// 		recup->t.texy = (int)recup->t.texpos &
// 			(recup->texture[recup->t.texdir].height - 1);
// 		recup->t.texpos += recup->t.step;
// 		if (y < recup->ry && x < recup->rx)
// 			recup->data.addr[y * recup->data.line_length / 4 + x] =
// 				recup->texture[recup->t.texdir].addr[recup->t.texy *
// 					recup->texture[recup->t.texdir].line_length /
// 					4 + recup->t.texx];
// 	}
// }