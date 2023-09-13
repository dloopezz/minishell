/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:56:31 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/13 16:35:14 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

//PARSING
int		select_type(char *line, int i);
// t_token	*add_token(t_token *cmd_lst, char *cmd, int type);
bool		is_operator(char c);
// void	read_list(t_token *cmd_lst);

//UTILS
void	error_msg(char *msg);
char	error_arg_msg(char *msg, int i);

//EXECUTE
int		ft_pwd(void);
//int		ft_echo(char **argvs);
int		ft_unset(char **pointer, char **env);
int 	ft_export(char **token, char ***env);
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

#endif