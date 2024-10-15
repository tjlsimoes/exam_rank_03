
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
#endif

void	ft_memset(void *s, int c, size_t n)
{
	unsigned char *array;
	int	i;

	if (!s || !c || n <= 0)
		return ;
	i = 0;
	array = (unsigned char *)s;
	while (array[i])
	{
		array[i] = c;
		i++;
	}
}

int	lb_eof_idx(char *str)
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

int	ft_strcpy(char *s1, char *s2, int start)
{
	int	i;

	i = start;
	while (s2[i])
	{
		s1[i] = s2[i - start];
		i++; 
	}
	return (i);
}

char *ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		i;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	result = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!result)
		return (NULL);
	if (s1)
		i = ft_strcpy(result, s1, i);
	if (s2)
		i = ft_strcpy(result, s2, i);
	free(s1);
	result[i] = '\0';
	return (result);
}


char *get_substring(char *str, int b, int e, int remains)
{
	int		i;
	char 	*substring;

	if (!str || (b == 0 && remains))
		return (NULL);
	if (e == -1)
		e = ft_strlen(str) - 1;
	substring = (char *)malloc(e - b + 2);
	if (!substring)
		return (NULL);
	i = 0;
	while (b + i <= e && str[b + i])
	{
		substring[i] = str[b + i];
		i++; 
	}
	if (substring[0] == '\0')
	{
		free(substring);
		return (NULL);
	}
	substring[i] = '\0';
	return (substring);
}

char	*str_with_lb_eof(int fd, char *str)
{
	int	chars_read;
	char *buffer;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	chars_read = 5;
	while (lb_eof_idx(str) == - 1 && chars_read)
	{
		chars_read = read(fd, buffer, BUFFER_SIZE);
		if (chars_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		else if (chars_read == 0)
			break;
		buffer[chars_read] = '\0';
		if (!str)
			str = ft_strjoin(NULL, buffer);
		else
			str = ft_strjoin(str, buffer);
		if (!str)
		{
			free(buffer);
			return (NULL);
		}
		ft_memset(buffer, 0, sizeof(buffer));
	}
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*mem = NULL;
	char		*str_till_lb_eof;
	char		*remains;

	if (fd < 0 || fd > 4096 || BUFFER_SIZE < 1)
		return (NULL);
	mem = str_with_lb_eof(fd, mem);
	if (!mem)
		return (NULL);
	printf("%d\n", lb_eof_idx(mem));
	str_till_lb_eof = get_substring(mem, 0, lb_eof_idx(mem), 0);
	remains = get_substring(mem, lb_eof_idx(mem) + 1, ft_strlen(mem) - 1, 1);
	printf("%s\n", str_till_lb_eof);
	printf("%s\n", remains);
	free(mem);
	mem = remains;
	return (str_till_lb_eof);
}

int	main(void)
{
	char *mem = get_next_line(0);
	printf("%s\n", mem);
	free(mem);
	return (0);
}