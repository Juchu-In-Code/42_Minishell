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
