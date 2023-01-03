/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaulino <dpaulino@student.42mulhouse.fr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 11:51:45 by dpaulino          #+#    #+#             */
/*   Updated: 2023/01/03 12:25:49 by dpaulino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	g_color;

void	test(t_point *img, t_img_data *img1, t_img_data *img2, t_point *pos)
{
	if (img2->address[img->y * img2->width + img->x] == -16777216)
	{
		img->x++;
		pos->x++;
	}
	else
	{
		if (g_color != -1)
		{
			if (img2->address[img->y * img2->width + img->x] != 0)
				img1->address[pos->y * img1->line_len / 4 + pos->x] = g_color;
		}
		else
			img1->address[pos->y * img1->line_len / 4 + pos->x] = \
			img2->address[img->y * img2->width + img->x];
		img->x++;
		pos->x++;
	}
}

void	draw_image(t_img_data *img1, t_img_data *img2, t_point pos, int color)
{
	t_point	img;
	int		tmp_x;

	g_color = color;
	tmp_x = pos.x;
	img.x = 0;
	img.y = 0;
	if (pos.x < 0 || pos.x + img2->width > img1->width || \
	pos.y < 0 || pos.y + img2->height > img1->height)
		return ;
	while (img.y < img2->height)
	{
		while (img.x < img2->width)
		{
			test(&img, img1, img2, &pos);
		}
		pos.y++;
		img.y++;
		pos.x = tmp_x;
		img.x = 0;
	}
}
