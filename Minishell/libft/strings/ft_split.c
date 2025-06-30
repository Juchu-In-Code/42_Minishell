/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 16:41:48 by jgalizio          #+#    #+#             */
/*   Updated: 2024/11/18 16:35:46 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	count_tokens(char const *s, char c)
{
	size_t	counter;
	int		inside_token;

	counter = 0;
	inside_token = 0;
	while (*s)
	{
		if (*s != c && !inside_token)
		{
			inside_token = 1;
			counter++;
		}
		else if (*s == c)
			inside_token = 0;
		s++;
	}
	return (counter);
}

static char	**set_substrs(char const *s, char **str, char c, size_t token_count)
{
	size_t	current_str;
	size_t	subs_str_len;

	current_str = 0;
	while (*s && *s == c)
		s++;
	while (current_str < token_count && *s)
	{
		if (*s != c)
		{
			subs_str_len = 0;
			while (s[subs_str_len] && s[subs_str_len] != c)
				subs_str_len++;
			str[current_str] = ft_calloc(subs_str_len + 1, sizeof(char));
			if (!str[current_str])
				return (NULL);
			ft_strlcpy(str[current_str], s, subs_str_len + 1);
			s += subs_str_len;
			current_str++;
		}
		else
			s++;
	}
	str[current_str] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	size_t	how_many_tokens;
	char	**str_splitted;

	how_many_tokens = count_tokens(s, c);
	str_splitted = ft_calloc((how_many_tokens + 1), sizeof(char *));
	if (!str_splitted)
		return (NULL);
	if (!set_substrs(s, str_splitted, c, how_many_tokens))
	{
		ft_free_matrix((void **)str_splitted);
		return (NULL);
	}
	return (str_splitted);
}
/**/
/* int	main(void) */
/* { */
/* 	char	**str; */
/* 	int i = -1; */
/**/
/* 	str = ft_split("hola", 'o'); */
/* 	while (str[++i]) */
/* 		printf("%s\n", str[i]); */
/* 	ft_free_matrix((void **)str); */
/* } */
