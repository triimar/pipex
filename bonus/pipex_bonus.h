/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:49:45 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/23 15:25:31 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h> 
# include <stdio.h> 
# include <string.h> 
# include <stdlib.h> 
# include <sys/wait.h>
# include <unistd.h> 
# include "libft.h"

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		forks;
	int		pipe1[2];
	int		pipe2[2];
	int		here_doc;
	int		*pids;
	char	**envp_pths;
	t_cmd	*s_cmd_lst;
}	t_pipex;

typedef struct s_wait
{
	int		wstatus;
	int		status_code;
}	t_wait;

/* pipex_bonus.c */
int		pipex(t_pipex *s_pipex, char *envp[]);
/* pipex_initiate_bonus.c*/
void	open_files(t_pipex *s_pipex, char *infile, char *outfile);
int		pipex_init(t_pipex *s_pipex, char **argv, char **envp);
/* parser_bonus.c */
int		all_paths(t_pipex *s_pipex, char **envp);
int		ft_get_cmd(t_cmd *s_cmd, char *argv);
char	*get_right_path(char *command, char **paths);
/* here_doc_bonus.c */
void	here_doc(t_pipex *s_pipex);
/* pipex_utils_bonus.c */
int		make_pipes(int pipe1[2], int pipe2[2], int child_nr);
void	redirect(int in_fd, int out_fd);
void	close_all(t_pipex *s_pipex);
void	used_pipes(t_pipex *s_pipex, int child_nr);
t_cmd	*get_node(t_cmd *list, int child_nr);
void	ft_waiting(int *pids, int nr_of_forks);
/* pipex_utils2_bonus.c */
char	*ft_pathjoin(char const *s1, char const *s2);
int		ft_str_same(const char *s1, const char *s2, size_t len_s1);
/* errors_bonus.c */
void	path_error(t_pipex *s_pipex, int exit_code, char *command);
void	execve_error(t_pipex *s_pipex);
int		fork_pipe_error(int return_val);
/*pipex_free_bonus.c */
void	pipex_free(t_pipex *s_pipex);

#endif