#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

/* Usage :
**   ./gnl_test fichier.txt    lit le fichier
**   ./gnl_test                lit l'entree standard (clavier ou pipe)
*/
int	main(int argc, char **argv)
{
	int		fd;
	int		n;
	char	*line;

	fd = 0;
	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
		{
			printf("Impossible d'ouvrir %s\n", argv[1]);
			return (1);
		}
	}
	n = 1;
	line = get_next_line(fd);
	while (line)
	{
		printf("[%d] \"%s\"\n", n, line);
		free(line);
		line = get_next_line(fd);
		n++;
	}
	printf("[%d] NULL\n", n);
	if (fd > 0)
		close(fd);
	return (0);
}