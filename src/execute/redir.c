/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:35:25 by dlopez-s          #+#    #+#             */
/*   Updated: 2024/01/28 03:04:34 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_great_redirs(t_token *tmp, t_data *data)
{
	int	file;
	
	file = 0;
	if ((tmp)->type == GT || (tmp)->type == GGT)
	{
		if ((tmp)->type == GT)
		{
			// data->gt = ft_calloc(sizeof(t_data), 1);
			data->gt = tmp->args[0];
			file = open_file(*(tmp)->next->args, 1);
		}
		else if ((tmp)->type == GGT)
		{
			// data->ggt = ft_calloc(sizeof(t_data), 1);
			data->ggt = tmp->args[0];
			file = open_file(*(tmp)->next->args, 2);
		}
		close(file);
	}
}

void	ft_less_redirs(t_token *tmp, t_data *data)
{
	if ((tmp)->type == LT || (tmp)->type == LLT)
	{
		if ((tmp)->type == LT)
		{
			//data->lt = ft_calloc(sizeof(t_data), 1);
			data->lt = tmp->args[0];
			if (tmp->next->type == INFILE)
				(data)->infile = (tmp)->next->args[0];
			if (access(data->infile, F_OK) == -1)
			{
				exec_exit_error(5, data->infile);
				data->infile = NULL;
			}
		}
		else if (tmp->type == LLT)
		{
			// data->llt = ft_calloc(sizeof(t_data), 1);
			data->llt = tmp->args[0];
			data->del = tmp->next->args;
		}
	}
}

void	ft_file_type(t_token *tmp, t_data *data)
{
	if (tmp->type == INFILE)
	{
		data->infile = ft_calloc(sizeof(t_data), 1);
		if (data->infile)
		{
			free(data->infile);
			data->infile = NULL;
			(data)->infile = (tmp)->args[0];
		}
	}
	if ((tmp)->type == OUTFILE)
	{
		(data)->outfile = ft_calloc(sizeof(t_data), 1);
		if (data->outfile)
		{
			free(data->outfile);
			data->outfile = NULL;
			(data)->outfile = (tmp)->args[0];
		}
	}
}

void	ft_check_redir(t_token *token, t_data *data)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (check_some_syntax(tmp) != 0)
			return ;
		if (is_redir((tmp)->type))
		{
			ft_great_redirs(tmp, data);
			ft_less_redirs(tmp, data);
		}
		ft_file_type(tmp, data);
		(tmp) = (tmp)->next;
	}
}
