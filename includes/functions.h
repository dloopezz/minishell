/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:56:31 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/08 12:39:22 by dlopez-s         ###   ########.fr       */
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

//EXECUTE
int		ft_pwd(void);
int		ft_echo(char **argvs);
int		ft_unset(char **pointer, char **env);
int	    ft_exit(char *token, char **argv);

#endif