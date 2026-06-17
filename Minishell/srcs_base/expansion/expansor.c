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

static char *append_string(char *s1, char *s2)
{
	char	*new_str;
    
	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		return (s1);

	new_str = ft_strjoin(s1, s2);
	free(s1);
	return (new_str);
}

static char *append_char(char *s, char c)
{
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	return (append_string(s, str));
}

static char *process_dollar(char *str, int *i, t_shell *shell)
{
	int	start;
	int	len;
	char	*key;
	char	*val;

	//start will contain a char after $
	start = *i + 1;
	len = 0;

	//expands $?
	if (str[start] == '?')
	{
		*i += 1;
		return (ft_itoa(shell->last_exit_code));
	}

	//count the lenth of env variable to expand
	while (str[start + len])
	{
		if (!ft_isalnum(str[start + len]) && str[start + len] != '_')
			break;
		len++;
	}

	//only $ 
	if (len == 0)
		return (ft_strdup("$"));

	//substring the word after $
	key = ft_substr(str, start, len);

	//skip processed word
	*i += len;

	//get value
	val = get_env_val(shell->env, key);
	free(key);

	//to not acciedently get rid of original pointer
	if (val)
		return (ft_strdup(val));
    
	//no value for a key
	return (ft_strdup(""));
}

char *expand(char *str, t_shell *shell)
{
	char	*res;
	char	*tmp_val;
	int	i;

	if (!str)
		return (NULL);

	//str for the result of joins
	res = ft_strdup("");
	i = 0;

	while (str[i])
	{
		//caso de $
		if (str[i] == '$')
		{
			tmp_val = process_dollar(str, &i, shell);
			res = append_string(res, tmp_val);
			free(tmp_val);
		}//cualquier otro caracter
		else
			res = append_char(res, str[i]);
		i++;
	}
	return (res);
}
