/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopezz <lopezz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:56:31 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/12 11:58:59 by lopezz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

//PARSING
int		ft_parsing(char *line);
int		select_type(char *line, int i);
// t_token	*add_token(t_token *cmd_lst, char *cmd, int type);
bool		is_operator(char c);
// void	read_list(t_token *cmd_lst);

//UTILS
void	error_msg(char *msg);
char	error_arg_msg(char *msg, int i);

//EXECUTE
int		ft_pwd(void);
int		ft_echo(char **argvs);
int		ft_unset(char **pointer, char **env);
int	    ft_exit(char *token, char **argv);
void	*ft_free_arrows(char **array, int number);
char	*search_var_in_env(char *variable, char **env);
char	*set_var_in_env(char *variable, char *str, char **env);

#endif