/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <viaremko@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 07:35:16 by viaremko          #+#    #+#             */
/*   Updated: 2025/06/16 17:39:57 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../z_minishell.h"

char	*token_to_string(t_tok *token, char *raw_line)
{
	char	*token_str;

	token_str = ft_substr(raw_line, token->pos, token->size);
	return (token_str);
}

bool	is_expandable(t_tok *token, char *line)
{
	char	*dollar_sign;
	char	*token_str;
	bool	output;

	output = false;
	token_str = ft_substr(line, token->pos, token->size);
	dollar_sign = ft_strchr(token_str, '$');
	if (dollar_sign == NULL)
		output = false;
	else if (dollar_sign[1] != '\0' && dollar_sign[1] == '?')
		output = true;
	else if (dollar_sign[1] != '\0' && ft_isalpha(dollar_sign[1]))
		output = true;
	ft_free((void *)&token_str);
	return (output);
}
