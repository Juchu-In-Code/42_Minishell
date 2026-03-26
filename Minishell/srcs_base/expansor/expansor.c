void    expand(t_item *item, t_list *env)
{
    //i assume token->str is heap allocated char* 
    
    t_token *token;
    token = (t_token *)item->data; 

    //get_env_val may return NULL;
    //in that case the variable is not fond.
    //so the node has to be deleted 
    //to not accidently mess with that garbage value in the future. 
    char *val = get_env_val(env_list, token->str);
    if(!val)
    {
       //delete item
       item->prev = item->next;
       free(t_token->str);
       free(t_token); 
       free(t_item); 
       return;
    }

    char *expanded_str = ft_strdup(val);
    if(!expanded_str)
        return;

    //free the old value;
    free(token->str);
    token->str = expanded_str;
}

void expansor(t_list *tokens, t_list *env)
{
    t_item	*current;
	t_item	*next;

	current = tokens->head;
	if (!tokens)
		return;
	while (current)
	{
		next = current->next;
		if (current->expansion)
            expand(current, env);
		current = next;
	}
}