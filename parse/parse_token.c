/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeyoon <jeyoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:37:09 by jeyoon            #+#    #+#             */
/*   Updated: 2022/06/09 18:46:40 by jeyoon           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

enum e_token_type	get_token_type(char *line, int idx)
{
	if (line[idx] == '"')
		return (DQUOTE);
	else if (line[idx] == '\'')
		return (QUOTE);
	else if (line[idx] == '|')
		return (PIPE);
	else if (line[idx] == '<')
	{
		if (line[idx + 1] != '\0' && line[idx + 1] == '<')
			return (TO_HEREDOC);
		return (TO_REDIRIN);
	}
	else if (line[idx] == '>')
	{
		if (line[idx + 1] != '\0' && line[idx + 1] == '>')
			return (TO_APPEND);
		return (TO_REDIROUT);
	}
	else
		return (TO_COMMON);
}

static void	add_token(t_token_node **token_head, t_token_node *new_node)
{
	t_token_node	*last_node;

	if (*token_head == NULL)
		*token_head = new_node;
	else
	{
		last_node = *token_head;
		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = new_node;
		new_node->prev = last_node;
	}
}

int	add_spacial_token(t_token_node **token_head, enum e_token_type type)
{
	t_token_node	*this_node;

	this_node = (t_token_node *)malloc(sizeof(t_token_node));
	if (this_node == NULL)
		return (FALSE);
	ft_memset(this_node, 0, sizeof(t_cmd_node));
	if (type == TO_REDIRIN)
		this_node->token = ft_strdup("<");
	else if (type == TO_REDIROUT)
		this_node->token = ft_strdup(">");
	else if (type == TO_HEREDOC)
		this_node->token = ft_strdup("<<");
	else if (type == TO_APPEND)
		this_node->token = ft_strdup(">>");
	else if (type == PIPE)
		this_node->token = ft_strdup("|");
	else if (type == DQUOTE)
		this_node->token = ft_strdup("\"");
	else if (type == QUOTE)
		this_node->token = ft_strdup("'");
	if (this_node->token == NULL)
		return (FALSE);
	this_node->type = type;
	add_token(token_head, this_node);
	return (TRUE);
}

int	add_common_token(t_token_node **token_head, char *line, \
	int *idx, enum e_token_type type)
{
	t_token_node	*this_node;
	int				start;

	this_node = (t_token_node *)malloc(sizeof(t_token_node));
	if (this_node == NULL)
		return (FALSE);
	ft_memset(this_node, 0, sizeof(t_cmd_node));
	start = *idx;
	while (line[*idx] != '\0' && !(line[*idx] == ' ' || \
		line[*idx] >= 9 && line[*idx] <= 13) && \
		(get_token_type(line, *idx) == TO_COMMON))
		(*idx)++;
	this_node->token = ft_substr(line, start, (*idx - start));
	if (this_node->token == NULL)
		return (FALSE);
	this_node->type = TO_COMMON;
	add_token(token_head, this_node);
	return (TRUE);
}

int	make_token_list(t_token_node **token_head, char *line)
{
	int					idx;
	enum e_token_type	type;

	idx = 0;
	while (line[idx] != '\0')
	{
		while (line[idx] != '\0' && (line[idx] == ' ' || \
			line[idx] >= 9 && line[idx] <= 13))
			idx++;
		if (line[idx] == '\0')
			return (FALSE);
		type = get_token_type(line, idx);
		if (type == TO_APPEND || type == TO_HEREDOC)
			idx++;
		if (type != TO_COMMON)
		{
			if (add_spacial_token(token_head, type) == FALSE)
				return (FALSE);
			idx++;
		}
		else
			if (add_common_token(token_head, line, &idx, type) == FALSE)
				return (FALSE);
	}
	return (TRUE);
}
