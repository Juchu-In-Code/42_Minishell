char **list_to_ptr(t_list *env)
{
    char	**result;
    t_item	*curr;
    t_env	*curr_env;
    int		i;
    size_t  	len[2];

    if (!env || env->size == 0)
        return (NULL);
    result = malloc(sizeof(char *) * (env->size + 1));
    if (!result)
        return (NULL);
    curr = env->head;
    i = 0;
    while (curr)
    {
        curr_env = (t_env *)curr->data;
        len[KEY] = ft_strlen(curr_env->dict[KEY]);
        len[VAL] = ft_strlen(curr_env->dict[VALUE]);
	result[i] = malloc(len[KEY] + len[VAL] + 2); //+2 for null and =
	if (!result[i])
	{
		free_mtx(result);
		return(NULL);
	}
	result[i] = ft_strjoinv(curr_env->dict[KEY],"/",curr_env->dict[VALUE], NULL);
        i++;
        curr = curr->next;
    }
    result[i] = NULL;
    return result;
}
