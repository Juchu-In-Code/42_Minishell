char **list_to_ptr(t_list *env)
{
    char	**result;
    t_item	*curr;
    t_env	*curr_env;
    int		i = 0;
    size_t  	len_key;
    size_t	len_val;

    if (!env || env->size == 0)
        return (NULL);
    result = malloc(sizeof(char *) * (env->size + 1));
    if (!result)
        return (NULL);
    curr = env->head;
    while (curr)
    {
        curr_env = (t_env *)curr->data;
        len_key = ft_strlen(curr_env->dict[KEY]);
        len_val = ft_strlen(curr_env->dict[VALUE]);
	result[i] = malloc(len_key + len_val + 2); //+2 for null and =
	if (!result[i])
	{
		while (--i >= 0)
			free(result[i]);
		free(result);
		return NULL;
	}
	ft_strjoinv(curr_env->dict[KEY],"/",curr_env->dict[VALUE], NULL);
        i++;
        curr = curr->next;
    }
    result[i] = NULL;
    return result;
}
