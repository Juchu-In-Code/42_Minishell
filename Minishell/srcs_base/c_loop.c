/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_loop.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgalizio <jgalizio@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 07:35:16 by jgalizio          #+#    #+#             */
/*   Updated: 2025/06/16 17:39:57 by jgalizio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "z_minishell.h"

char *token_to_string(t_tok *token, char *raw_line)
{
	char	*token_str;
	token_str = ft_substr(raw_line, token->pos, token->size);
	return(token_str);
}

bool is_expandable(t_tok *token, char *line)
{
	char	*dollar_sign;
	char	*token_str;
	bool	output = false;

	token_str = ft_substr(line, token->pos, token->size);

	dollar_sign = ft_strchr(token_str, '$');
	if(dollar_sign == NULL)
		output = false;
	else if(dollar_sign[1] != '\0' && dollar_sign[1] == '?')
		output = true;
	else if(dollar_sign[1] != '\0' && ft_isalpha(dollar_sign[1]))
		output = true;
	
	free(token_str);
	return(output);
}

t_tok	*get_mock_token()
{
	t_tok *mock_token = malloc(sizeof(t_tok));
	if (!mock_token)
		return (NULL);

	mock_token->type = in;
	mock_token->pos = 0;
	mock_token->size = 11;

	return (mock_token);
}

void	loop(t_shell *shell)
{
	//mock t_tok
	t_tok	*mock_token;
	char	*input;
	char	*line;
	(void)line;

	input = NULL;
	while (shell->is_active && ft_readline(&input))
	{
		char **av = ft_split(input, ' ');
		int ac = ft_get_array_length(av);

		if(ac)
		{
			//it's a boolean function (true on detected builtin)	
			if(!exec_builtin(ac, av, shell))
			{
				//line is heap allocated
				//line = get_line_to_exec(av[0], shell->env);
				
				if(input)
				{
					mock_token = get_mock_token();
					printf("line: %s\n", input);

					bool result = is_expandable(mock_token, input);
					if(result == true)
						printf("The string is expandable\n");
					else
						printf("The string is not expandable\n");

					free(input);
					free(mock_token);
					shell->last_exit_code = 0;
				}
				else
				{
					ft_fprintf(2, "minishell: %s: No such file or directory\n", av[0]);
					shell->last_exit_code = 127;
				}
			}
		}
		
		ft_free_matrix((void *)av);
		//free(input);
		input = NULL;
	}
}
