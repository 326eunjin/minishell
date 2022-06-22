/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd_without_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejang <ejang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 18:55:31 by jeyoon            #+#    #+#             */
/*   Updated: 2022/06/22 22:44:10 by ejang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exe_cmd(t_cmd_line_list *cmd_line_list)
{
	if (cmd_line_list->size == 1)
		exe_without_pipe(cmd_line_list->cmd_heads[0]);
	else
		exe_with_pipe(cmd_line_list);
}

void	exe_without_pipe(t_cmd_node *node)
{
	pid_t	pid;
	int		status;

	if (node->type == BUILTIN)
		exe_builtin_single(node);
	else
	{
		pid = fork();
		if (pid < -1)
			g_state.exit_status = 1;
		if (pid == 0)
		{
			exec_single_cmd_without_pipe(node);
			g_state.exit_status = 1;
		}
		else
			waitpid(pid, &status, 0);
	}
}

void	exec_single_cmd_without_pipe(t_cmd_node *node)
{
	char		**arg;
	char		*tmp;
	t_cmd_node	*cmd_list;

	redir_in(node);
	redir_out(node);
	cmd_list = remove_redir(node);
	tmp = is_valid_cmd(node);
	arg = string_array(node);
	if (execve(tmp, arg, g_state.envp) == -1)
	{
		ft_putstr_fd("bash : ", STDERR_FILENO);
		ft_putstr_fd(node->cmd, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(1);
	}
}