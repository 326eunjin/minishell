/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_bulitin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejang <ejang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:33:31 by ejang             #+#    #+#             */
/*   Updated: 2022/06/24 03:29:12 by ejang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exe_builtin(t_cmd_node	*node)
{
	if (ft_strcmp(node->cmd, "pwd") == 0)
		func_pwd();
	if (ft_strcmp(node->cmd, "env") == 0)
		func_env();
	if (ft_strcmp(node->cmd, "echo") == 0)
		func_echo(node);
	if (ft_strcmp(node->cmd, "export") == 0)
		func_export(node);
	if (ft_strcmp(node->cmd, "unset") == 0)
		func_unset(node);
	if (ft_strcmp(node->cmd, "cd") == 0)
		func_cd(node);
	if (ft_strcmp(node->cmd, "exit") == 0)
		func_exit(node);
	exit(0);
}

void	exe_builtin_single(t_cmd_node	*node)
{
	if (ft_strcmp(node->cmd, "pwd") == 0)
		func_pwd();
	if (ft_strcmp(node->cmd, "env") == 0)
		func_env();
	if (ft_strcmp(node->cmd, "echo") == 0)
		func_echo(node);
	if (ft_strcmp(node->cmd, "export") == 0)
		func_export_single_cmd(node);
	if (ft_strcmp(node->cmd, "unset") == 0)
		func_unset_single_cmd(node);
	if (ft_strcmp(node->cmd, "cd") == 0)
		func_cd_single_cmd(node);
	if (ft_strcmp(node->cmd, "exit") == 0)
		func_exit_single_cmd(node);
}
