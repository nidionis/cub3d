#include	"mlx_int.h"

int		mlx_get_screen_size(void *mlx_ptr, int *sizex, int *sizey)
{
	XWindowAttributes	xwAttr;
	Status				returned;
	t_xvar				*xvar;
	
	xvar = mlx_ptr;
	returned = XGetWindowAttributes(xvar->display, xvar->root, &xwAttr);
	(*sizex) = xwAttr.width;
	(*sizey) = xwAttr.height;
}
