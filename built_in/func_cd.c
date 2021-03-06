/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejang <ejang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 21:04:07 by ejang             #+#    #+#             */
/*   Updated: 2022/06/26 15:17:59 by ejang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_pwd(void)
{
	char	*current_dir;

	current_dir = getcwd(NULL, 0);
	if (current_dir == NULL)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(1);
	}
	return (current_dir);
}

void	home_dir(char *str)
{
	char	*tmp1;

	tmp1 = ft_strdup("PWD=");
	if (chdir(str) < 0)
	{
		free(str);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(1);
	}
	tmp1 = ft_strjoin(tmp1, str);
	export_str(tmp1);
	free(tmp1);
	tmp1 = 0;
}

void	old_dir(void)
{
	char	*str1;
	char	*str2;
	char	*tmp;

	str1 = get_value("OLDPWD");
	str2 = get_value("PWD");
	if (chdir(str1) < 0)
	{
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		exit(1);
	}
	tmp = ft_strdup("PWD=");
	tmp = ft_strjoin(tmp, str1);
	export_str(tmp);
	free(tmp);
	tmp = ft_strdup("OLDPWD=");
	tmp = ft_strjoin(tmp, str2);
	export_str(tmp);
	free(tmp);
	tmp = 0;
}

static void	change_dir(char *str)
{
	char	*tmp;
	char	*ret;

	tmp = get_value("PWD");
	if (chdir(str) < 0)
	{
		free(tmp);
		printf("cd: no such file or directory: %s\n", str);
		exit(1);
	}
	else
	{
		ret = ft_strdup("PWD=");
		ret = ft_strjoin(ret, get_pwd());
		export_str(ret);
		free(ret);
		ret = ft_strdup("OLDPWD=");
		ret = ft_strjoin(ret, tmp);
		export_str(ret);
		free(ret);
		ret = 0;
	}
}

void	func_cd(t_cmd_node *head)
{
	t_cmd_node	*curr_node;
	int			ret;
	char		*str;

	curr_node = head->next;
	ret = 0;
	str = get_value("HOME");
	if (curr_node == NULL)
		home_dir(str);
	else if (ft_strcmp(curr_node->cmd, "~") == 0)
		home_dir(str);
	else if (ft_strcmp(curr_node->cmd, "-") == 0)
	{
		free(str);
		old_dir();
	}
	else
	{
		free(str);
		change_dir(curr_node->cmd);
	}
}
