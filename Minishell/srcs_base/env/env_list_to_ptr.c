/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_ptr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <viaremko@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:51:04 by viaremko          #+#    #+#             */
/*   Updated: 2025/06/08 21:12:03 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../z_minishell.h"

static char	**alloc_env_array(size_t size)
{
        char **result;

        result = malloc(sizeof(char *) * (size + 1));
        if (result)
                result[size] = NULL;
        return (result);
}

static char *make_env_entry(t_env *env)
{
    if (!env || !env->dict[KEY] || !env->dict[VAL])
        return (NULL);
    return (strjoinv(env->dict[KEY], "=", env->dict[VAL], NULL));
}

static bool	fill_env_array(char **result, t_list *env)
{
        t_item  *curr;
        t_env   *curr_env;
        int     i;

        i = 0;
        curr = env->head;
        while (curr)
        {
                curr_env = (t_env *)curr->data;
                result[i] = make_env_entry(curr_env);
                if (!result[i])
                        return (false);
                i++;
                curr = curr->next;
        }
        return (true);
}

char	**env_list_to_ptr(t_list *env)
{
        char    **result;

        if (!env || env->size == 0)
                return (NULL);
        result = alloc_env_array(env->size);
        if (!result)
                return (NULL);
        if (!fill_env_array(result, env))
        {
                ft_free_matrix((void **)result);
                return (NULL);
        }
        return (result);
}
