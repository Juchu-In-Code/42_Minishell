/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <viaremko@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:33:11 by viaremko          #+#    #+#             */
/*   Updated: 2025/07/18 17:33:26 by viaremko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../z_minishell.h"
/*NOTE: 
 *	status = 0 -> ERROR;
 *	status = 1 -> VAL=KEY;
 *	status = 2 -> VAL+=KEY;
 *	status = 3 -> VAL;
 */
static uint8_t	check_line(char *line)
{
	uint8_t			status;
	int				index;
	int				i;

	status = 1;
	index = ft_strchr_index(line, '=');
	if (ft_isdigit(line[0]) || index == 0)
		return (0);
	if (line[index - 1] == '+')
	{
		status = 2;
		index--;
	}
	else if (index == -1)
	{
		status = 3;
		index = ft_strlen(line);
	}
	i = -1;
	while (++i < index)
	{
		if (!ft_isalnum(line[i]) && line[i] != '_')
			return (0);
	}
	return (status);
}

static void	print_env_list(t_list *list, char *msg)
{
	t_item	*curr_node;
	t_env	*curr_env;

	curr_node = list->head;
	while (curr_node)
	{
		curr_env = curr_node->data;
		if (curr_env->state == 3)
			printf("%s%s\n", msg, curr_env->dict[KEY]);
		else
			printf("%s%s=\"%s\"\n", msg, curr_env->dict[KEY],
				curr_env->dict[VAL]);
		curr_node = curr_node->next;
	}
}

static bool	parse_key_value(char *line, uint8_t state, char **data)
{
	char	*sep;

	if (!line)
		return (false);
	if (state == 0)
		return (false);
	if (state == 1 || state == 2)
		sep = ft_strchr(line, '=');
	if (state == 1 || state == 2)
		data[VAL] = ft_strdup(sep + 1);
	else if (state == 3)
		data[VAL] = ft_strdup("");
	data[KEY] = ft_strunt(line, "+=");
	return (true);
}

static bool	export_line(t_shell *shell, char *line)
{
	t_env	*entry;
	char	*data[2];
	uint8_t	state;

	state = check_line(line);
	if (!parse_key_value(line, state, data))
		return (false);
	entry = get_env(shell->env, data[KEY]);
	if (state == 0)
		return false;
	if (state == 1 && entry)
		change_env_value(entry, data[VAL], state);
	else if (state == 2 && entry)
		append_env_value(entry, data[VAL], state);
	else if (state == 3 && entry)
		return (true);
	else
	{
		entry = create_dict_entry(data[KEY], data[VAL], state);
		list_insert_tail(shell->env, entry);
	}
	return (true);
}

int	ft_export(int ac, char **av, t_shell *shell)
{
	int	i;
	int	ret_val;
	
	if (ac == 1)
	{
		print_env_list(shell->env, "declare -x ");
		return (0);
	}
	ret_val = 0;
	i = 0;
	while (av[++i])
		ret_val += export_line(shell, av[i]);
	return (ret_val == 0);
}
