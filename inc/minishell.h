/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeyoon <jeyoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 16:20:55 by jeyoon            #+#    #+#             */
/*   Updated: 2022/06/09 17:33:10 by jeyoon           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include "../libft/libft.h"

# define FALSE 0
# define TRUE 1

enum	e_token_type
{
	TO_COMMON,
	TO_REDIRIN,
	TO_REDIROUT,
	TO_HEREDOC,
	TO_APPEND,
	PIPE,
	DQUOTE,
	QUOTE
};

enum	e_cmd_type
{
	COMMON,
	REDIRIN,
	REDIROUT,
	HEREDOC,
	APPEND,
	BUILTIN,
	OPTION
};

typedef struct s_token_node	t_token_node;
typedef struct s_cmd_node	t_cmd_node;
typedef struct s_cmd_line_list	t_cmd_line_list;
typedef struct s_state		t_state;

struct s_token_node	//	공백과 특수문자를 기준으로 잘린 부분 하나하나의 정보
{
	enum e_token_type	type;	//	토큰의 종류
	char				*token;	//	토큰 내용
	t_token_node		*next;	//	연결리스트 연결부 (다음)
};

struct s_cmd_node	//	실행에서 사용되는 가장 작은 단위.
{
	enum e_cmd_type	type;	//	종류
	char			*cmd;	//	실제 내용
	t_cmd_node		*prev;	//	연결리스트 연결부 (이전)
	t_cmd_node		*next;	//	연결리스트 연결부 (다음)
};

struct s_cmd_line_list	//	t_cmd_node 연결리스트 배열의 정보
{
	int			size;	//	연결리스트 배열의 개수 (파이프로 잘린 영역의 개수)
	t_cmd_node	**list;	//	연결리스트 배열. 하나의 인자가 하나의 파이프에서 실행되는 단위이다.
};

struct s_state//전역변수로 쓸 구조체
{
	char			**envp;//환경변수
	int				exit_status;//종료 코드
	//추가 예정
};

t_state				g_state;

/*
	*** parse ***
*/

int parse_cmd(t_cmd_line **cmd_line);
int  token_list(t_cmd_line *cmd_line, char *line);
int  token_cnt(t_cmd_line *cmd_line, char *line);
void token_analyze(t_cmd_line *cmd_line);


/*
	*** utils ***
*/
int	ft_strcmp(char *s1, char *s2);
char **copy_envp(char **envp);

/*
	*** execute commands ***
*/
void    exe_cmd(t_cmd_line *cmd_line);

/*
	built-in
*/
void	func_pwd(t_cmd_line *cmd_line);




#endif