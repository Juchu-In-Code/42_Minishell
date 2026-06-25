/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <viaremko@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:06:12 by viaremko          #+#    #+#             */
/*   Updated: 2025/07/26 14:13:33 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../z_minishell.h"

static char	*append_string(char *s1, char *s2)
{
	char	*new_str;

	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		return (s1);
	new_str = ft_strjoin(s1, s2);
	ft_free((void **)&s1);
	return (new_str);
}

static char	*append_char(char *s, char c)
{
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	return (append_string(s, str));
}

static char	*process_dollar(char *str, int *i, t_shell *shell)
{
	int		start;
	int		len;
	char	*key;
	char	*val;

	start = *i + 1;
	len = 0;
	if (str[start] == '?')
		*i += 1;
	if (str[start] == '?')
		return (ft_itoa(shell->last_exit_code));
	while (str[start + len] && (ft_isalnum(str[start + len]) || str[start
				+ len] == '_'))
		len++;
	if (len == 0)
		return (ft_strdup("$"));
	key = ft_substr(str, start, len);
	*i += len;
	val = get_env_val(shell->env, key);
	ft_free((void **)&key);
	if (val)
		return (ft_strdup(val));
	return (ft_strdup(""));
}

char	*expand(char *str, t_shell *shell)
{
	char	*res;
	char	*tmp_val;
	int		i;

	if (!str)
		return (NULL);
	res = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			tmp_val = process_dollar(str, &i, shell);
			res = append_string(res, tmp_val);
			ft_free((void **)&tmp_val);
		}
		else
			res = append_char(res, str[i]);
		i++;
	}
	return (res);
}
