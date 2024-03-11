/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:58:47 by nromito           #+#    #+#             */
/*   Updated: 2024/02/25 15:21:30 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*join_the_party(char *str, char *buf)
{
	char	*t;
	int		i;

	i = 0;
	if (str == NULL)
	{
		t = malloc(sizeof(char) * ft_strlen(buf) + 1);
		if (t == NULL)
			return (NULL);
		while (buf[i] != '\0')
		{
			t[i] = buf[i];
			i++;
		}
		t[i] = '\0';
		return (t);
	}
	t = ft_strjoin(str, buf);
	if (t == NULL)
		return (NULL);
	free (str);
	return (t);
}

char	*read_line(char *str, char *buf, int fd)
{
	int		check;

	check = 1;
	while (check > 0)
	{
		check = read(fd, buf, BUFFER_SIZE);
		if (check < 0)
			return (NULL);
		if (check == 0)
			break ;
		buf[check] = '\0';
		str = join_the_party(str, buf);
		if (ft_strchr(str, '\n') != NULL)
			break ;
	}
	return (str);
}

char	*clean_the_static_and_steal(char *str)
{
	int		j;
	int		k;
	char	*new_str;

	j = 0;
	if (str == NULL)
		return (NULL);
	while (str[j] != '\n' && str[j] != '\0')
		j++;
	if (str[j] == '\0')
	{
		free (str);
		return (NULL);
	}
	k = j + 1;
	while (str[k] != '\0')
		k++;
	new_str = ft_calloc(k - j + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	k = 0;
	while (str[j + 1] != '\0')
		new_str[k++] = str[(j++) + 1];
	free (str);
	return (new_str);
}

char	*steal_line(char *str)
{
	int		i;
	int		pass;
	char	*temp;

	i = 0;
	pass = 0;
	if (str == NULL || str[0] == '\0')
		return (NULL);
	while (str[pass] != '\n' && str[pass] != '\0')
		pass++;
	temp = ft_calloc(pass + 1 + '\n', sizeof(char));
	if (!temp)
		return (NULL);
	if (str[pass] == '\n')
		pass++;
	while (i < pass && str[i] != '\0')
	{
		temp[i] = str[i];
		i++;
	}
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buf;
	char		*out;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free (str);
		str = NULL;
		return (NULL);
	}
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	str = read_line(str, buf, fd);
	free (buf);
	buf = NULL;
	out = steal_line(str);
	str = clean_the_static_and_steal(str);
	return (out);
}

// int	main()
// {
// 	char *risultato;
// 	int	i = 0;
// 	int fd = open("text.txt", O_RDONLY);
// 	while (i < 133)
// 	{
// 		risultato = get_next_line(fd);
// 		printf("%s", risultato);
// 		free(risultato);
// 		i++;	
// 	}
// 	free (risultato);
// 	close (fd);
// 	return (0);
// }
