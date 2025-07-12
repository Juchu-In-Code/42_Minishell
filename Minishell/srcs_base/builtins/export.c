/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <lodyiaremko@proton.me>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:05:03 by viaremko          #+#    #+#             */
/*   Updated: 2025/07/03 14:36:00 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../z_minishell.h"

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
        if(state == 2 && entry) //VAR+=KEY
                append_env_value(entry, value);
        else if( (state == 1 || state == 3) && entry) 
                change_env_value(entry, value);
        else 
        {
                entry = create_dict_entry(key, value, state);
                list_insert_tail(shell->env, entry);
        }
        return(true);
}

int export(char **av, t_shell *shell)
{
        int i;
        int ret_val;

        if(!av[0])
        {
                print_env(shell->env);
                return(0);
        }
        ret_val = 0;
        i = -1;
        while(av[++i])
                ret_val += export_line(shell, av[i]);
        return(ret_val != 0);
}
