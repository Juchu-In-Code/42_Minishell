
#include "../z_minishell.h"

t_redir	*create_red(t_tok source, t_tok target)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->redir_type = source.type;
	redir->target.pos = target.pos;
	redir->target.size = target.size;
	redir->target.type = target.type;
	redir->target.state = target.state;
	return (redir);

}

void	create_cmd_lists(t_cmd	*cmd)
{
	cmd->redirs = list_create(NULL);
	cmd->args = list_create(NULL);
	cmd->ac = 0;
}

bool	assemble_cmds(t_shell *shell)
{
	t_item	*current_item;
	t_tok	*current_token;
	t_item	*next_item;
	t_tok	*next_tok;
	int		cmd;

	shell->cmds = ft_calloc(shell->pipe_count + 1, sizeof(t_cmd));
	if (!shell->cmds)
		return (false);

	cmd = 0;
	create_cmd_lists(&shell->cmds[cmd]);
	current_item = shell->tokens->head;
	while (current_item)
	{
		current_token = current_item->data;
		if (is_redir(current_token->type))
		{
			next_item = current_item->next;
			next_tok = next_item->data;
			if(next_tok->type == id_space)
			{
				next_item = next_item->next;
				next_tok = next_item->data;
			}
			list_insert_tail(shell->cmds[cmd].redirs, create_red(*current_token, *next_tok));
			current_item = next_item->next;
			continue;
		}
		if (is_quoted(current_token->type)
			|| current_token->type == id_string
			|| current_token->type == id_space)
			list_insert_tail(shell->cmds[cmd].args, current_token);
		if (current_token->type == id_pipe)
		{
			cmd++;
			create_cmd_lists(&shell->cmds[cmd]);
		}
		current_item = current_item->next;
	}
	return (true);
}
