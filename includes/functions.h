/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:56:31 by crtorres          #+#    #+#             */
/*   Updated: 2023/09/06 17:37:04 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

int		ft_parsing(char *line);
void	error_msg(char *msg);
int		ft_pwd(void);
int		ft_echo(char **argvs);
int		ft_unset(char **pointer, char **env);
int	    ft_exit(char *token, char **argv);

#endif