/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_without_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeyoon <jeyoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:55:31 by jeyoon            #+#    #+#             */
/*   Updated: 2022/06/25 04:13:41 by jeyoon           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	exec_single_cmd_without_pipe(t_cmd_node *node)
{
	char		**arg;
	char		*tmp;
	t_cmd_node	*cmd_list;

	redir_in(node);
	redir_out(node);
	cmd_list = remove_redir(node);
	if (cmd_list->type == BUILTIN)
		exe_builtin(cmd_list);
	tmp = is_valid_cmd(cmd_list);
	arg = string_array(cmd_list);
	if (execve(tmp, arg, g_state.envp) == -1)
		execve_error(strerror(errno), cmd_list);
}

static void	exe_without_pipe(t_cmd_node *node)
{
	pid_t		pid;
	int			status;

	if ((node->type == BUILTIN) && (has_redir_in(node) \
	== NULL) && (has_redir_out(node) == NULL))
		exe_builtin_single(node);
	else
	{
		pid = fork();
		if (pid < -1)
			exit(1);
		if (pid == 0)
		{
			exec_single_cmd_without_pipe(node);
			exit(1);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (!WIFSIGNALED(status))
				g_state.exit_status = status / 256;
		}
	}
}

void	exe_cmd(t_cmd_line_list *cmd_line_list)
{
	if (cmd_line_list->size == 1)
		exe_without_pipe(cmd_line_list->cmd_heads[0]);
	else
		exe_with_pipe(cmd_line_list);
}
