
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
	t_item	*curr;
	t_tok	*token;
	t_tok	*nxt;
	int		cmd;

	shell->cmds = ft_calloc(shell->pipe_count + 1, sizeof(t_cmd));
	if (!shell->cmds)
		return (false);

	cmd = 0;
	create_cmd_lists(&shell->cmds[cmd]);
	curr = shell->tokens->head;
	while (curr)
	{
		token = curr->data;
		if (is_redir(token->type))
		{
			nxt = curr->next->data;
			list_insert_tail(shell->cmds[cmd].redirs, create_red(*token, *nxt));
			curr = curr->next;
		}
		if (is_quoted(token->type) || token->type == id_string)
		{
			list_insert_tail(shell->cmds[cmd].args, token);
			shell->cmds[cmd].ac++;
		}
		if (token->type == id_pipe)
		{
			cmd++;
			create_cmd_lists(&shell->cmds[cmd]);
		}
		curr = curr->next;
	}
	return (true);
}
