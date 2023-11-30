/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:13:01 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/11/30 17:13:18 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_slash(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (ft_strncmp(&line[i], "\\", 1) == 0)
			error_arg_msg("Syntax error near unexpected token '\\'", 1);		
}
void	check_infile(t_token *token, t_data *data)
{
	if (token->type == LT)
		data->infile = open_file(*token->next->args, 0);
	else if (token->type == LLT)
		data->infile = open_file(*token->next->args, 0);
	dup2(data->infile, STDIN_FILENO);
	close(data->infile);
	if (data->infile != STDIN_FILENO)
	{
		dup2(data->infile, STDIN_FILENO);
		close(data->infile);
	}
}

void	check_outfile(t_token *token, t_data *data)
{
	if (token->type == GT)
		data->outfile = open_file(*token->next->args, 1);
	else if (token->type == GT)
		data->outfile = open_file(*token->next->args, 2);
	dup2(data->outfile, STDOUT_FILENO);
	close(data->outfile);
	if (data->outfile != STDOUT_FILENO)
	{
		dup2(data->outfile, STDOUT_FILENO);
		close(data->outfile);
	}
}
int	check_some_syntax(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (ft_strncmp(&line[0], ">", 1) == 0 && ft_strncmp(&line[1], ">", 1) == 0)
			return (error_syntax_msg("Syntax error near unexpected token `>'", 1), 258);
		else if (ft_strncmp(&line[0], ">", 1) == 0 && ft_strncmp(&line[2], ">", 1) == 0)
			return (error_syntax_msg("Syntax error near unexpected token `>'", 1), 258);
		else if (ft_strncmp(&line[0], "<", 1) == 0 && ft_strncmp(&line[1], "<", 1) == 0)
			return (error_syntax_msg("Syntax error near unexpected token `<'", 1), 258);
		else if (ft_strncmp(&line[0], ">", 1) == 0 || ft_strncmp(&line[0], "<", 1) == 0)
			return (error_syntax_msg("Syntax error near unexpected token `newline'", 1), 258);
	}
	return (1);
}