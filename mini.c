#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

float OVAL = 1.00000000;

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
	float	r;
	char	c;
}				t_shape;

int	clear_all(FILE *file, char *s)
{
	fclose(file);
	if (s)
		free(s);
	return (1);
}

int	ft_strlen(char *s)
{
	int i = 0;

	while (*s)
	{
		s++;
		i++;
	}
	return (i);
}

int	str_err(const char *s, int res)
{
	write(1, s, ft_strlen((char *)s));
	write(1, "\n", 1);//
	return (res);
}

int		in_shape(float x, float y, t_shape *shape)
{
	float	dist;

	// dist = sqrtf(powf(x - shape->x, 2.) + powf(y - shape->y, 2.));
	dist = sqrtf(powf(x - shape->x, 2.) + powf(y - shape->y, 2.));

	if (dist <= shape->r)
	{
		if (shape->r - dist < OVAL)
			return (2);
		return (1);
	}
	return (0);
}

void	draw_shape(char **s, t_shape *shape, t_f *f)
{
	int i = 0;
	int j;

	while (i < f->h)
	{
		j = 0;
		while (j < f->w)
		{
			if ((shape->type == 'c' && in_shape(j, i, shape) == 2) || (shape->type == 'C' && in_shape(j, i, shape)))
				(*s)[i * f->w + j] = shape->c;
			j++;
		}
		i++;
	}
}

int 	draw_shapes(FILE *file, char **s, t_f *f)
{
	int	res;
	t_shape	temp;

	while (res = fscanf(file, "%c %f %f %f %c\n", &temp.type, &temp.x, &temp.y, &temp.r, &temp.c) == 5)
	{
		if (!(temp.r > 0.0 && (temp.type == 'c' || temp.type == 'C')))
			return (0);
		draw_shape(s, &temp, f);
	}
	if (res == -1)
		return (0);
	return (1);
}

char	*fill_back(FILE *file, t_f *f)
{
	char	*s;
	int i;
	int len;

	len = f->h * f->w;
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

int read_f(FILE *file, t_f *f)
{
	if (fscanf(file, "%d %d %c\n", &f->w, &f->h, &f->bchar) != 3)
		return (0);
	if (!(f->w > 0 && f->h > 0 && f->w <= 300 && f->h <= 300))
		return (0);
	return (1);
}

void	put_drawing(char *s, t_f *f)
{
	int i = 0;

	while (i < f->h)
	{
		write(1, s + i * f->w, f->w);
		write(1, "\n", 1);
		i++;
	}
}

int	main(int argc, char **argv)
{
	FILE	*file;
	t_f		f;
	char	*drawing;

	f.w = 0;
	f.h = 0;
	f.bchar = 0;
	drawing = NULL;

	if (argc != 2)
		return (str_err("Error: argument", 1));
	if (!(file = fopen(argv[1], "r")))
		return (str_err("Error: Operation file corrupted", 1));
	if (!read_f(file, &f))
		return (str_err("Error: Operation file corrupted", 1));
	if (!(drawing = fill_back(file, &f)))
		return (clear_all(file, NULL) && str_err("Error: memory", 1));
	if (!draw_shapes(file, &drawing, &f))
		return (clear_all(file, drawing) && str_err("Error: memory", 1));
	put_drawing(drawing, &f);
	clear_all(file, drawing);
	return (0);
}
