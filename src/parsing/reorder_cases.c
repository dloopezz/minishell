/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reorder_cases.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:04:48 by dlopez-s          #+#    #+#             */
/*   Updated: 2023/12/20 11:05:15 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	first_case(t_token *file, t_token *cmd)
{
	int		i;
	int		j;
	char	**new_args;

	new_args = (char **)ft_calloc(sizeof(char *),
			(ft_matrix_len(file->args) - 1) + ft_matrix_len(cmd->args) + 1);
	i = 0;
	while (cmd->args[i])
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	j = 0;
	while (file->args[++j])
	{
		new_args[i++] = file->args[j];
		file->args[j] = NULL;
		free(file->args[j]);
	}
	free(cmd->args);
	cmd->args = new_args;
}

char	*get_cmd(t_token **file)
{
	char	*cmd;
	char	*cmd_aux;
	int		i;

	i = 1;
	cmd = "";
	while ((*file)->args[i])
	{
		cmd_aux = ft_strjoin(cmd, " ");
		if (i != 1)
			free(cmd);
		cmd = ft_strjoin(cmd_aux, (*file)->args[i]);
		free (cmd_aux);
		cmd_aux = NULL;
		free((*file)->args[i]);
		(*file)->args[i] = NULL;
		i++;
	}
	return (cmd);
}

void	second_case(t_token **tokens, t_token *file, int is_first)
{
	int		i;
	char	*cmd;
	char	*first_cmd;
	char	**cmd_tab;

	i = 1;
	first_cmd = "";
	cmd = get_cmd(&file);
	if (is_first == 0)
		*tokens = add_tokenfront(*tokens, cmd, CMD);
	else
	{
		first_cmd = (*tokens)->args[0];
		cmd_tab = ft_split(cmd, ' ');
		i = 0;
		free((*tokens)->args);
		(*tokens)->args = NULL;
		(*tokens)->args = (char **)ft_calloc(sizeof(char *),
				ft_matrix_len(file->args) + ft_matrix_len(cmd_tab) + 1);
		(*tokens)->args[0] = first_cmd;
		while (cmd_tab[i])
			(*tokens)->args[ft_matrix_len((*tokens)->args)] = cmd_tab[i++];
		free(cmd_tab);
	}
	free(cmd);
}
