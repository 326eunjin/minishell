/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejang <ejang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:33:03 by jeyoon            #+#    #+#             */
/*   Updated: 2022/06/06 11:02:25 by ejang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_cmd_line *cmd_line;
    //환경 변수 불러오기
    while (1)
    {
        if (parse_cmd(cmd_line) == FALSE)
        {
            //return_error(cmd_line);
            continue;
        }
        // 커맨드라인 유효성 검증 부분
        // 실행부분
    }
    return (0);
}