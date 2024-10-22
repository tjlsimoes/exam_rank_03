// #ifndef BUFFER_SIZE
// # define BUFFER_SIZE 42
// #endif
// #include <unistd.h>
// #include <stdlib.h>

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	idx_lb(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == 10)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_strcpy(char *result, char *str, int start)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		result[start + i] = str[i];
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*result;

	i = 0;
	result = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
	if (s1)
		i = ft_strcpy(result, s1, i);
	if (s2)
		ft_strcpy(result, s2, i);
	result[i + ft_strlen(s2)] = '\0';
	free(s1);
	return (result);
}

char	*str_with_lb_eof(int fd, char *str)
{
	char	*buffer;
	int		chars_read;

	chars_read = 5;
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (idx_lb(str) == -1 && chars_read > 0)
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (!chars_read)
			break ;
		else if (chars_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[chars_read] = '\0';
		if (!str)
			str = ft_strjoin(NULL, buffer);
		else
			str = ft_strjoin(str, buffer);
		if (!str)
			return (NULL);
	}
	free(buffer);
	return (str);
}

char	*get_substring(char *str, int b, int e, int remains)
{
	int		i;
	char	*substring;

	if (!str || (b == 0 && remains))
		return (NULL);
	substring = (char *)malloc(e - b + 2);
	if (!substring)
		return (NULL);
	i = 0;
	while (i + b <= e && str[i + b])
	{
		substring[i] = str[i + b];
		i++;
	}
	substring[i] = '\0';
	if (substring[0] == '\0')
	{
		free(substring);
		return (NULL);
	}
	return (substring);
}

char	*get_next_line(int fd)
{
	static char	*mem = NULL;
	char		*str_til_lb_eof;
	char		*remains;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	mem = str_with_lb_eof(fd, (char *)mem);
	if (!mem)
		return (NULL);
	str_til_lb_eof = get_substring(mem, 0, idx_lb(mem), 0);
	remains = get_substring(mem, idx_lb(mem) + 1, ft_strlen(mem) - 1, 1);
	free(mem);
	mem = remains;
	return (str_til_lb_eof);
}

// #include <stdio.h>
// #include <fcntl.h>

// int	main(void)
// {
// 	char 	*output;
// 	int		fd;

// 	fd = open("foo_c.txt", O_RDONLY);
// 	if (!fd)
// 	{
// 		printf("Error opening file.\n");
// 		return (1);
// 	}
// 	output = get_next_line(fd);
// 	printf("%s", output);
// 	free(output);
// 	close(fd);
// 	return (0);
// }