#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

# define INFILE 0
# define OUTFILE 1

typedef struct s_token t_token;

//void	pipex(t_token *tokens, char *env[]);
void	exec_cmd(t_token *tokens, char **env);
int		find_path_pos(char **env);
char	*find_path(char *cmd, char **env);
int		error_found(char *str);
void	free_mtx(char **mtx);
int		ft_open(char *file, int check);

#endif