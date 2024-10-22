#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	idx_lb(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strcpy(char *result, char *str, int start)
{
	int	i;
	
	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		result[start + i] = str[i];
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		i;

	i = 0;
	result = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
	if (s1)
		i = ft_strcpy(result, s1, i);
	if (s2)
		i += ft_strcpy(result, s2, i);
	result[i] = '\0';
	free(s1);
	return (result);
}

char	*str_with_lb_eof(int fd, char *str)
{
	char	*buffer;
	int		chars_read;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	chars_read = 5;
	while (idx_lb(str) == -1 && chars_read)
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (!chars_read)
			break;
		if (chars_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[chars_read] = '\0';
		str = ft_strjoin(str, buffer);
		if (!str)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (str);
}

char	*get_substring(char *str, int b, int e, int remains)
{
	int		i;
	char	*substring;

	i = 0;
	if ((b == 0 && remains) || !str)
		return (NULL);
	substring = (char *)malloc(e - b + 2);
	if (!substring)
		return (NULL);
	while (b + i <= e && str[b + i])
	{
		substring[i] = str[b + i];
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
	static char	*mem;
	char		*remains;
	char		*str_til_lb_eof;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	mem = str_with_lb_eof(fd, mem);
	if (!mem)
		return (NULL);
	// printf("Initial mem %s|\n|", mem);
	// printf("Initial remains %s|\n|", remains);
	// printf("Initial str_til_lb %s|\n|", str_til_lb_eof);
	str_til_lb_eof = get_substring(mem, 0, idx_lb(mem), 0);
	remains = get_substring(mem, idx_lb(mem) + 1, ft_strlen(mem) - 1,1);
	free(mem);
	mem = remains;
	return (str_til_lb_eof);
}

int	main(void)
{
	char	*str;
	str = get_next_line(0);
	printf("Final return %s|\n|", str);
	printf("%s", str);
	free(str);
	return (0);
}