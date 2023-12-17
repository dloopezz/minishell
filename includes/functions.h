/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:56:31 by crtorres          #+#    #+#             */
/*   Updated: 2023/12/17 19:08:55 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "minishell.h"

typedef struct s_token	t_token;
typedef struct s_data	t_data;

//*PARSING
t_token	*ft_parsing(char *line, t_token *tokens);
int		select_type(char *line, int i);
t_token	*add_token(t_token *cmd_lst, char *cmd, int type);
t_token	*add_tokenfront(t_token *cmd_lst, char *cmd, int type);
bool	is_operator(char c);
void	read_list(t_token *cmd_lst);
int		check_close_quotes(char *cmd);
char	*ft_expand(t_data *data);
char	**split_cmd(t_token *tokens, char *cmd);
void	skip_spaces(char *str, int *i);
size_t	count_words(const char *str, char c);
int		select_mode(t_token *tokens, char *cmd, int *conts, int mode);
t_token	*get_last_node(t_token *tokens);
void	reorder_tokens(t_token **tokens);
void	set_redir(t_token *tokens); //quitar
t_token	*re_type_all(t_token *tokens);

//*REDIR
void	handle_redirs(t_token *tokens);
void	check_type(t_token *aux);
bool	is_redir(int type);
t_token	*add_file_token(t_token *tokens, int *i, char *line);

//*EXECUTE
// void	ft_execute(t_token *token, t_data *data);
int		ft_builtin(t_token *tokens, t_data *data);
bool	is_absolute_path(const char *path);
int		ft_cd(t_token *token, char **env);
char	*get_home(char **env);
void	free_cd(char *old_path, char *current_path, int i);
char	*ft_pwd_cd(void);
int		ft_listsize(t_token *lst);
int		ft_echo(t_token *token, int fd);
int		ft_env(t_data *data, t_token *tokens, int fd);
int		ft_export(t_token *token, t_data *data, int fd);
int		ft_pwd(int fd);
int		ft_unset(t_token *token, t_data *data);
int		ft_exit(char **args);
void	*ft_free_arrows(char **array, int number);
char	*search_var_in_env(char *variable, char **env);
int		get_posvar_in_env(char *variable, char **env);
char	**set_var_in_env(char *variable, char *str, char **env);
char	**setvar_cd(char *variable, char *str, char **env);
int		ft_matrix_len(char **str);
void	ft_swap_env(char **envio, int i, int j);
int		check_name(char *str);
char	**ft_new_env(int len, int index, char **env, char *variable);
char	**checkpath(char **envp, char **argv);
void	check_slash(char *line);
char	*search_shlvar_in_env(char *variable, char **env);
void	ft_check_cmd_path(t_token *token, t_data *data);
void	ft_executer(t_token *token, t_data *data, int fd_inf, int fd_outf);

//DANI
void	ft_execute(t_token *tokens, t_data *data);
void	process_cmd(t_token *tokens, t_data *data, int fdin, int fdout);
void	handle_redir(t_token *tokens, t_data *data, int fdin, int fdout);
int		open_file(char *file, int type);
int		builtin(char *cmd, t_token *tokens, t_data *data, int fd);

//ERRORS
void	error_msg(char *msg);
char	error_arg_msg(char *msg, int i);
void	err_cd_msg(int i);
int		error_syntax_msg(char *msg, int i);
void	exec_exit_error(int err, char *msg, int errnum);

//UTILS
void	handle_sign(void);
void	sig_child(void);
void	sig_heredoc(void);
void	sig_ignore(void);
void	sig_parent(void);
int		check_some_syntax(char *line);
void	count_heredocs(t_token *token, t_data *data);
void	ft_here_doc(t_token *token, t_data *data);
void	init_here_doc(t_token *token);
int		open_file(char *file, int type);
void	check_infile(t_token *token, int fd_inf);
void	check_outfile(t_token *token, int fd_outf);
int		ft_exec_pipes(t_token *token, t_data *data, int fd_out);
void	ft_exec(t_token *token, t_data *data);
int		ft_is_builtin(t_token *token);
char	*find_in_path(t_token *token, t_data *data);
int		error_found(char *str);
void	free_mtx(char **mtx);
void	free_data(t_data *data);
void	free_tokens(t_token *tokens);


//*EXPANSION
int		process_squotes(char *str, int *len);
int		process_dquotes(char *str, int *len, char **env);
int		doub_quotes(int *i, int *n_char, char *str_exp, t_data *data);
int		sing_quotes(int *i, int *n_char, char *str_exp, t_data *data);
int		check_init_dollar(char *str, int *len, char *string, char **env);
int		expandlen(char *str, char **env);
char	*virgula_expand(char *str_exp, int *n_char, t_data *env);
char	*quote_var(char *new);

#endif