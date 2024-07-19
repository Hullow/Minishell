#define WORD 1
#define NEWLINE 2
#define REDIR 3
#define PIPE 4


struct token
{
	char *tok;
	int type;
	struct token *next;
};




ft_execution()
{
	if (ft_has_pipe)
	{

		list commands = ft_split_pipe();
		ft_execute_pipes(commands);
	}
	else
		{
			if (ft_has_redir())
				fd = ft_execute_redir(); // redir error handling ?
			ft_execute_command(commands);
		}

}

ft_has_redir(struct token *head)
{
	while (head)
	{
		if (head->type == REDIR)
			return (1);
		head = head->next;
	}
	return (0);
}