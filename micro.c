#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

float ZVAL = 0.00000000;
float UVAL = 1.00000000;

typedef struct	s_f
{
	int		w;
	int		h;
	char	bchar;
}				t_f;

typedef struct	s_shape
{
	char	type;
	float	x;
	float	y;
	float	w;
	float	h;
	char	color;
	// struct s_shape	*next;
}				t_shape;

int		clear_all(FILE *file, char *s)
{
	fclose(file);
	if (s)
		free(s);
	return (1);
}

int		ft_strlen(char *s)
{
	int i = 0;

	while (*s)
	{
		s++;
		i++;
	}
	return (i);
}

int		str_error(char const *s, int res)//const
{
	write(1, s, ft_strlen((char *)s));
	// write(1, "\n", 1);////
	return (res);
}

void	draw_drawing(char *s, t_f *f)
{
	int i = 0;

	while (i < f->h)
	{
		write(1, s + i * f->w, f->w);
		write(1, "\n", 1);
		i++;
	}
}

int		in_shape(float x, float y, t_shape *sh)
{
	if (x < sh->x || x > sh->x + sh->w || y < sh->y || y > sh->y + sh->h)
		return (0);
	if (x - sh->x < UVAL || sh->x + sh->w - x < UVAL || y - sh->y < UVAL || sh->y + sh->h - y < UVAL)
		return (2);
	return (1);
}

void	draw_shape(char **s, t_shape *shape, t_f *f)
{
	int i;
	int j;
	int res;

	i = 0;
	while (i < f->h)
	{
		j = 0;
		while (j < f->w)
		{
			res = in_shape(j, i, shape);
			if ((shape->type == 'r' && res == 2) || (shape->type == 'R' && res))
				(*s)[i * f->w + j] = shape->color;
			j++;
		}
		i++;
	}
}

int		draw_shapes(FILE *file, char **s, t_f *f)
{
	t_shape	temp;
	int		res;

	while (res = fscanf(file, "%c %f %f %f %f %c\n", &temp.type, &temp.x, &temp.y, &temp.w, &temp.h, &temp.color) == 6)
	{
		if (!(temp.w > ZVAL && temp.h > ZVAL && (temp.type == 'r' || temp.type == 'R')))//check
			return (0);
		draw_shape(s, &temp, f);
	}
	if (res == -1)///
		return (0);
	return (1);
}

char	*paint_back(t_f *f)
{
	char	*s;
	int		len;
	int		i;

	len = f->w * f->h;
	if (!(s = (char*)malloc(sizeof(char) * len)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		s[i] = f->bchar;
		i++;
	}
	return (s);
}

int		get_f(FILE *file, t_f *f)
{
	int		res;

	if ((res = fscanf(file, "%d %d %c\n", &f->w, &f->h, &f->bchar)) != 3)
		return (0);
	if (!(f->w > 0 && f->w <= 300 && f->h > 0 && f->h <= 300))//check
		return (0);
	if (res == -1)
		return (0);
	return (1);
}

int		main(int argc, char **argv)
{
	FILE	*file;
	t_f	f;
	char	*drawing;

	f.w = 0;
	f.h = 0;
	f.bchar = 0;

	if (argc != 2)
		return (str_error("Error: argument\n", 1));
	if (!(file = fopen(argv[1], "r")))
		return (str_error("Error: Operation file corrupted\n", 1));
	if (!get_f(file, &f))
		return (clear_all(file, NULL) && str_error("Error: Operation file corrupted\n", 1));
	if (!(drawing = paint_back(&f)))
		return (clear_all(file, NULL) && str_error("Error: memory\n", 1));
	if (!draw_shapes(file, &drawing, &f))
		return (clear_all(file, drawing) && str_error("Error: Operation file corrupted\n", 1));
	draw_drawing(drawing, &f);
	clear_all(file, drawing);
	// write(1, "\n", 1);//
	return (0);
}