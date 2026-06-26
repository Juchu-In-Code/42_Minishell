/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <viaremko@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:06:12 by viaremko          #+#    #+#             */
/*   Updated: 2026/06/26 11:34:22 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../z_minishell.h"

char	*expand_token(t_tok *tok, char *raw_input, t_shell *shell)
{
	char	*str;
	char	*expanded;

	if (tok->type == id_qsin || tok->type == id_qdob)
		str = ft_substr(raw_input, tok->pos + 1, tok->size - 2);
	else
		str = ft_substr(raw_input, tok->pos, tok->size);
	if (tok->type == id_qsin)
		return (str);
	expanded = expand(str, shell);
	ft_free((void **)&str);
	return (expanded);
}

int	count_cmds_args(t_list *args)
{
	t_item	*curr;
	t_tok	*tok;
	int		count;
	bool	has_content;

	if (!args || !args->head)
		return (0);
	count = 0;
	has_content = false;
	curr = args->head;
	while (curr != NULL)
	{
		tok = (t_tok *)curr->data;
		if (tok->type == id_space)
		{
			if (has_content == true && ++count)
				has_content = false;
		}
		else
			has_content = true;
		curr = curr->next;
	}
	if (has_content == true)
		count++;
	return (count);
}
