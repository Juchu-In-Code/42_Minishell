/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viaremko <viaremko@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:33:11 by viaremko          #+#    #+#             */
/*   Updated: 2026/06/25 13:19:45 by viaremko         ###   ########.fr       */
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
	uint8_t	status;
	int		index;
	int		i;

	status = 1;
	index = ft_strchr_index(line, '=');
	if (ft_isdigit(line[0]) || index == 0)
		return (0);
	if (index == -1)
	{
		status = 3;
		index = ft_strlen(line);
	}
	if (line[index - 1] == '+')
	{
		status = 2;
		index--;
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

static bool	parse_key_value(char *line, char **data)
{
	char	*sep;

	if (!line)
		return (false);
	sep = ft_strchr(line, '=');
	data[KEY] = ft_strunt(line, "+=");
	data[VAL] = ft_strdup(sep + 1);
	return (true);
}

static bool	export_line(t_shell *shell, char *line)
{
	t_env	*entry;
	char	*data[2];
	uint8_t	state;

	state = check_line(line);
	if (!state || state == 3)
		return (state);
	if (!parse_key_value(line, data))
		return (false);
	entry = get_env(shell->env, data[KEY]);
	if (entry)
		entry_helper(state, entry, data);
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
	int	err;

	if (ac == 1)
	{
		print_env_list(shell->env, "declare -x ");
		return (0);
	}
	ret_val = 0;
	err = 0;
	i = 0;
	while (av[++i])
	{
		ret_val = export_line(shell, av[i]);
		if (!ret_val)
			err = 1;
	}
	return (err);
}
