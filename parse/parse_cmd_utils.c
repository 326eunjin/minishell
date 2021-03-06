/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeyoon <jeyoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:22:53 by jeyoon            #+#    #+#             */
/*   Updated: 2022/06/25 23:59:56 by jeyoon           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	get_end_index(t_token_node **curr)
{
	int	end;

	if ((*curr)->next == NULL)
		end = (*curr)->idx + ft_strlen((*curr)->token);
	else
		end = (*curr)->next->idx;
	return (end);
}

char	*replace_dollar(char *str, int idx, char *line)
{
	char	**split;
	char	*ret;
	char	*name;
	int		envp_idx;

	if (idx < 1 || line[idx - 1] != '$')
		return (ft_strdup("$"));
	if (ft_strcmp(str, "\"") == 0)
		return (ft_strdup("$"));
	if (ft_strcmp(str, "?") == 0)
		return (ft_itoa(g_state.exit_status));
	envp_idx = is_in_envp(str);
	if (envp_idx == -1)
		return (ft_strdup(""));
	split = ft_split(g_state.envp[envp_idx], '=');
	if (split == 0)
		return (0);
	ret = ft_strdup(split[1]);
	free_split(split);
	return (ret);
}

static void	dquote_dollar(char **new_str, char *key)
{
	int		envp_idx;
	char	**split;
	char	*ret;

	if (ft_strcmp(key, "?") == 0)
	{
		*new_str = ft_strjoin(*new_str, ft_itoa(g_state.exit_status));
		return ;
	}
	envp_idx = is_in_envp(key);
	if (envp_idx == -1)
		return ;
	split = ft_split(g_state.envp[envp_idx], '=');
	if (split == 0)
		exit(1);
	ret = ft_strdup(split[1]);
	free_split(split);
	*new_str = ft_strjoin(*new_str, ret);
}

static void	make_new_dollar_string(int \
	*idx, t_token_node **curr, char **new_str)
{
	char	*tmp_str;
	int		tmp_idx;

	tmp_idx = ++(*idx);
	while (((*curr)->token[*idx] != '\0') && ((*curr)->token[*idx] != '$') && \
		(is_white_space((*curr)->token[*idx]) == FALSE))
		(*idx)++;
	tmp_str = ft_substr((*curr)->token, tmp_idx, *idx - tmp_idx);
	if (ft_strcmp(tmp_str, "") != 0)
		dquote_dollar(new_str, tmp_str);
	else
		*new_str = ft_strjoin(*new_str, ft_strdup("$"));
	free(tmp_str);
}

void	make_new_str(char **new_str, t_token_node **curr, char *line)
{
	int	idx;
	int	len;

	idx = 0;
	len = ft_strlen((*curr)->token);
	if (len == 0)
		return ;
	while (idx < len)
	{
		if ((*curr)->token[idx] == '$')
			make_new_dollar_string(&idx, curr, new_str);
		else
		{
			*new_str = ft_strjoin(*new_str, \
				char_to_string((*curr)->token[idx]));
			idx++;
		}
	}
}
