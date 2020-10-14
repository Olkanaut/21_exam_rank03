#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_f
{
	int w;
	int h;
	char bchar;
}				t_f;

typedef struct s_f
{
	char	type;
	float	x;
	float	y;
	float	w;
	float	h;
	char	c;
}			t_f;

int		ft_strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}

int		str_error(const char *s, int res)
{
	write(1, s, ft_strlen((char*)s), 1);
	write(1, "\n", 1);
	return (res);
}

int		main(int argc, char **argv)
{
	FILE	*file;
	t_f		*f;
	char	*drawing;

	if (argc != 2)
		return (str_error("Error: argument", 1));
	if (!(file = fopen(argv[1], "r")))
		return (str_error("Error: Operation file corrupted", 1));
	if (!(read_field(file, f)))
		return (str_error("Error: argument", 1));
	// drawing = draw_back; ret
	// draw_shapes; ret

	// put_drawing;
	// clear_all;
	return (0);
}

// argc == 2
// fopen(argv[1], "r")
// read_field(file, &f)//close file, NULL
// drawing = draw_back(&f)//close file, NULL
// draw_shapes(file, &drawing, &f)//close file, free drawing
// put_drawing(drawing, &f)
// clear_all(file, drawing);
// return (0);