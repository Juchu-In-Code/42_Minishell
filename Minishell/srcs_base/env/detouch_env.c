t_item	*get_list_item(t_list *list, char *key)
{
        t_item  *curr_node;
        t_env   *curr_env;

        curr_node = list->head;
        while (curr_node)
        {
                curr_env = curr_node->data;
                if (!ft_strcmp(curr_env->dict[KEY], key))
                        return (curr_node);
                curr_node = curr_node->next;
        }
        return (NULL);
}

void detouch_env(t_list *list, t_item *item)
{
    if (!list || !item)
        return;
    if (item->prev)
        item->prev->next = item->next;
    else
        list->head = item->next;
    if (item->next)
        item->next->prev = item->prev;
    else
        list->tail = item->prev;
    env->size--;
    free(item->data);
    free(item);
}
