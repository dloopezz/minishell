/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:56:31 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/19 19:48:30 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "minishell.h"

typedef struct s_token t_token;
typedef struct s_data t_data;

//PARSING
t_token	*ft_parsing(char *line, t_token *tokens);
int		select_type(char *line, int i);
t_token	*add_token(t_token *cmd_lst, char *cmd, int type);
bool		is_operator(char c);
void	read_list(t_token *cmd_lst);

//EXECUTE
void 	ft_execute(t_token *tokens, t_data *data);
int	    ft_builtin(t_token *tokens, t_data *data);
int 	ft_cd(t_token *token, char **env);
int 	ft_listsize(t_token *lst);
int		ft_echo(t_token *token);
int		ft_env(t_data *data, t_token *tokens);
int 	ft_export(t_token *token, t_data *data);
int		ft_pwd(void);
int		ft_unset(char **pointer, char **env);
int	    ft_exit(char **args);
void	*ft_free_arrows(char **array, int number);
char	*search_var_in_env(char *variable, char **env);
int 	get_posvar_in_env(char *variable, char **env);
char	*set_var_in_env(char *variable, char *str, char **env);
int		ft_matrix_len(char **str);
void	ft_swap_env(char **envio, int i, int j);
int		check_name(char *str);
char	**ft_new_env(int len, int index, char **env);
char	**checkpath(char **envp, char **argv);

//UTILS
void	error_msg(char *msg);
char	error_arg_msg(char *msg, int i);
//!void	handle_sign(void);  DA ERROR POR EL PUTO READLINE

#endif