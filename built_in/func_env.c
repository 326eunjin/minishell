/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejang <ejang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:19:35 by ejang             #+#    #+#             */
/*   Updated: 2022/06/08 14:49:57 by ejang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void func_envp(void)//envp는 환경변수! 전역 변수로 설정하는게 좋을듯 하다,,
{
	int i = 0;
	while (g_state.envp[i])
	{
		printf("%s\n",g_state.envp[i]);
		i++;
	}
}