/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:58:12 by nromito           #+#    #+#             */
/*   Updated: 2023/11/14 18:57:04 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_all(char **matrix, int r)
{
	while (--r >= 0)
		free (matrix[r]);
	free(matrix);
	return (NULL);
}

char	**fill_matrix(char **matrix, int words, const char *s, const char c)
{
	int	r;
	int	len;
	int	i;

	r = 0;
	len = 0;
	i = 0;
	while (r < words)
	{
		while (*s == c)
			s++;
		while (s[len] != c && s[len] != 0)
			len++;
		matrix[r] = malloc (sizeof(char) * (len + 1));
		if (matrix[r] == NULL)
			return (free_all(matrix, r));
		matrix[r][len++] = '\0';
		i = len - 1;
		while (--len > 0)
			matrix[r][len - 1] = s[len - 1];
		s += i;
		r++;
	}
	return (matrix);
}

char	**ft_split(char const *s, char const c)
{
	int		i;
	int		words;
	char	**matrix;

	if (s == NULL || *s == '\0')
	{
		matrix = ft_calloc(sizeof(char *), 1);
		if (matrix == NULL)
			return (NULL);
		return (matrix);
	}
	i = -1;
	words = 0;
	if (s[0] != c && s[0] != 0)
		words ++;
	while (s[++i + 1] != 0)
		if (s[i] == c && s[i + 1] != c && s[i + 1] != 0)
			words++;
	matrix = malloc(sizeof(char *) * (words + 1));
	if (!matrix)
		return (NULL);
	matrix[words] = NULL;
	return (fill_matrix(matrix, words, s, c));
}

// int main(void)
// {
// 	char a = "w";
// 	char b[20] = "wCiaowcome staiw";
	
// }