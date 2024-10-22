#include "get_next_line.h"

char	*ft_strdup(char *line, int i)
{
	int		k;
	char	*result;

	k = 0;
	result = (char *)malloc(i + 1);
	if (!result)
		return (NULL);
	while (line[k])
	{
		result[k] = line[k];
		k++;
	}
	result[k] = '\0';
	return (result);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t				i;
	unsigned char 	*str;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
		str[i++] = c;
	return (s);
}

char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE];
	char			line[70000];
	static int		buffer_read;
	static int		buffer_pos;
	int				i;

	ft_memset(line, 0, sizeof(line));

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while(1)
	{
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read(fd, buffer, BUFFER_SIZE);
			buffer_pos = 0;
			if (buffer_read <= 0)
				break ;
		}
		if (line[i] == '\n')
			break ;
		line[i] = buffer[buffer_pos++];
		i++;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line, i));
}

#include <stdio.h>
int main(void)
{
	char	*output;

	output = get_next_line(0);
	printf("%s", output);
	free(output);
	return (0);
}