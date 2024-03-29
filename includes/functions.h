/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:05:27 by dlopez-s          #+#    #+#             */
/*   Updated: 2024/02/02 10:48:24 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "minishell.h"

typedef struct s_token		t_token;
typedef struct s_data		t_data;
typedef struct s_heredoc	t_heredoc;

//PARSING
t_token	*ft_parsing(char *line, t_data *data, t_token *tokens);
int		select_type(char *line, int i);
t_token	*add_token(t_token *cmd_lst, char *cmd, int type, int quotes);
t_token	*add_tokenfront(t_token *cmd_lst, char *cmd, int type);
bool	is_operator(char c);
char	**split_cmd(t_token *tokens, char *cmd);
void	skip_spaces(char *str, int *i);
size_t	count_words(const char *str, char c);
int		select_mode(t_token *tokens, char *cmd, int *conts, int mode);
void	reorder_tokens(t_token **tokens);
t_token	*re_type_all(t_token *tokens);
void	first_case(t_token *file, t_token *cmd);
void	second_case(t_token **tokens, t_token *file, int is_first);
void	check_op(t_token *tokens, char *cmd);
void	re_parse(t_token **tokens, char *cmd);
t_data	*reset_data(t_data *data);
int		check_unclosed_quotes(t_data *data, int flag);
// void	read_list(t_token *cmd_lst);

//REDIR
void	set_redir(t_token *tokens);
void	ft_great_redirs(t_token *tmp, t_data *data);
void	ft_less_redirs(t_token *tmp, t_data *data);
void	ft_file_type(t_token *tmp, t_data *data);
void	ft_check_redir(t_token *token, t_data *data);
bool	is_redir(int type);
void	ft_here_doc(t_token *token, t_data *data);
void	count_heredocs(t_token *token, t_data *data);
int		open_file(char *file, int type);
void	check_infile(t_token *token, t_data *data, int fd_inf);
void	check_outfile(t_token *token, t_data *data, int fd_outf);

//BUILTINS
bool	is_absolute_path(const char *path);
int		ft_cd(t_token *token, char **env);
int		check_and_free_path(char *cur_path);
char	*get_home(char **env);
char	*substring_before_last_slash(const char *path);
void	free_cd(char *old_path, char *current_path, int i);
char	*ft_pwd_cd(void);
int		ft_listsize(t_token *lst);
int		ft_echo(t_token *token, int fd);
int		ft_env(t_data *data, t_token *tokens, int fd);
int		ft_export(t_token *token, t_data *data, int fd);
int		ft_pwd(int fd);
int		ft_unset(t_token *token, t_data *data);
int		ft_exit(char **args);
char	*search_var_in_env(char *variable, char **env);
int		get_posvar_in_env(char *variable, char **env);
char	**set_var_in_env(char *variable, char *str, char **env);
int		ft_matrix_len(char **str);
void	ft_swap_env(char **envio, int i, int j);
int		check_name(char *str);
char	**ft_new_env(char **env, char *variable);

//EXECUTE
void	ft_executer(t_token *token, t_data *data, int fd_inf, int fd_outf);
void	ft_exec(t_token *token, t_data *data);
int		ft_check_cmd_path(t_token *token, t_data *data);
int		check_slash(char *token);
int		prueba_builtin(t_token *token, t_data *data);
pid_t	ft_fork(void);
int		ft_exec_pipes(t_token *token, t_data *data, int fd_out);
int		get_pipes(t_token *tokens);
int		builtin(char *cmd, t_token *tokens, t_data *data, int fd);
int		ft_is_builtin(t_token *token, t_data *data);
int		ft_is_builtin2(t_token *token);
void	no_path(t_token **token, t_token **tmp);
int		check_no_path(t_data **data, t_token **token, t_token **tmp);
int		init_rl(t_data **data);
int		open_file(char *file, int type);
t_token	*copy_without_pipe(t_token *token);

//EXPANDER
char	*ft_expand(t_data *data, char *str);
int		process_squotes(char *str, int *len);
int		process_dquotes(char *str, int *len, char **env);
int		doub_quotes(int *i, int *n_char, char *str_exp, t_data *data);
int		sing_quotes(int *i, int *n_char, char *str_exp, t_data *data);
int		check_init_dollar(char *str, int *len, char *string, char **env);
int		expandlen(char *str, char **env, int str_len);
char	*virgula_expand(char *str_exp, int *n_char, t_data *env);
char	*quote_var(char *new);
char	*get_env(char *str, char **env);
void	create_new_string(char *string, char *s, int *len, char *new);

//ERRORS
char	error_msg(char *msg, int i);
char	error_arg_msg(char *msg, int i);
void	err_cd_msg(char *msg, int i);
int		err_syntax(char *msg, int i);
void	exec_exit_error(int err, char *msg);

//SIGNALS
void	handle_sign(void);
void	sig_child(void);
void	sig_heredoc(void);
void	sig_ignore(void);
void	sig_parent(void);
void	disable_ctrl_c_hotkey(t_data *data);

//UTILS
int		check_some_syntax(t_token *token);
void	free_struct(t_heredoc *hd, int nb_hd);
char	*find_in_path(t_token *token, t_data *data);
void	free_data(t_data *data);
void	free_tokens(t_token *tokens);
void	free_mtx(char **mtx);
void	free_tokens_no_mtx(t_token *tokens);
char	*search_shlvar_in_env(char *variable, char **env);
void	shell_level(t_data **data);

#endif