/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejang <ejang@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 16:06:07 by ejang             #+#    #+#             */
/*   Updated: 2022/06/15 13:22:08 by ejang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
// #include "libft/libft.h"

char **copy_envp(char **envp)
{
	int i = -1;
	int cnt = 0;
	char **ret;
	while(envp[++i])
		cnt++;
	ret = (char **)malloc(sizeof(char *) * (cnt + 1));
	i = -1;
	while(envp[++i])
		ret[i] = ft_strdup(envp[i]);
	ret[cnt] = NULL;
	return (ret);
}
