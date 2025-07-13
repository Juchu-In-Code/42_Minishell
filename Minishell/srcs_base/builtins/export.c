/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <viaremko@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 07:35:16 by viaremko          #+#    #+#             */
/*   Updated: 2025/06/16 17:39:57 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "z_minishell.h"

uint8_t check_line(char *line)
{
        uint8_t status;
        int index;
        int i;

        status = 1;             //VAL=KEY
        index = ft_strchr_index(line, '=');
        if(ft_isdigit(line[0]) || index == 0)
                return(0);      //ERROR
        if(line[index - 1] == '+')
        {
                status = 2;     //KEY+=VAL
                index--;        //to exclude + from verifying
        }
        else if(index == -1)
        {
                status = 3;     //KEY with no VAL
                index = ft_strlen(line);
        }
        i = -1;
        while(status && ++i < index)
        {
                if(!ft_isalpha(line[i]) && !ft_isdigit(line[i]) && line[i] != '_')
                        return(0);      //ERROR
        }
        return(status);
}

bool export_line(t_shell *shell, char *line)
{
        t_env   *entry;
        char    *sep;
        char    *key;
        char    *value;
        uint8_t state;
        if (!line)
                return (false);
        state = check_line(line);
        if(state == 0)
                return(false);
        if(state == 1 || state == 2)
                sep = ft_strchr(line, '=');
        if(state == 1 || state == 2)
                value = ft_strdup(sep + 1);
        else if (state == 3)
                value = ft_strdup("");
        key = ft_strunt(line, "+=");
        entry = get_env(shell->env, key);
        if(state == 1 && entry) 
                change_env_value(entry, value, state);
        else if(state == 2 && entry) //VAR+=KEY
                append_env_value(entry, value, state);
        else if(state == 3 && entry) 
                return(true);
        else 
        {
                entry = create_dict_entry(key, value, state);
                list_insert_tail(shell->env, entry);
        }
        return(true);
}

void    print_env_list(t_list *list, char *msg)
{
        t_item  *curr_node;
        t_env   *curr_env;

        curr_node = list->head;
        while (curr_node)
        {
                curr_env = curr_node->data;
                if(curr_env->state == 3)
                        printf("%s%s\n", msg,curr_env->dict[KEY]);
                else
                        printf("%s%s=\"%s\"\n", msg,curr_env->dict[KEY], curr_env->dict[VAL]);
                curr_node = curr_node->next;
        }
}

int export(char **av, t_shell *shell)
{
        int i;
        int ret_val;

        if(!av[0])
        {
                print_env_list(shell->env, "declare -x ");
                return(0);
        }
        ret_val = 0;
        i = -1;
        while(av[++i])
                ret_val += export_line(shell, av[i]);
        return(ret_val != 0);
}
