/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-s <dlopez-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 15:10:39 by crtorres          #+#    #+#             */
/*   Updated: 2023/11/03 14:45:41 by dlopez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int check_op(t_token *tokens)
{
	t_token	*aux_lst;
	int i = 0;

	aux_lst = tokens;
	while (aux_lst)
	{
		while (aux_lst->args[i])
		{
			if (aux_lst->type != CMD)
				return (1);
			i++;
		}
		aux_lst = aux_lst->next;
	}
	return (0);
}

static void	disable_ctrl_c_hotkey(void)
{
	int				rc;

	rc = tcgetattr(0, &g_var.termios);
	if (rc)
	{
		perror("tcgetattr");
		exit(1);
	}
	g_var.termios.c_lflag &= ~ECHOCTL;
	rc = tcsetattr(0, 0, &g_var.termios);
	if (rc)
	{
		perror("tcsetattr");
		exit(1);
	}
}


int	main(int argc, char **argv, char **envp)
{
	t_data	*data ;
	t_token	*tokens;
	int i;
	int len_mtx = ft_matrix_len(envp);
	char *line;
	(void) argc;
	(void) argv;

	tokens = NULL;
	line = ft_strdup("");	//inicializacion a lo guarro
	data = ft_calloc(1, sizeof(t_data));
	data->envi = envp;
	data->env_copy = ft_calloc(len_mtx + 1, sizeof(char *));
	i = -1;
	disable_ctrl_c_hotkey();
	handle_sign();
	while (line != NULL)
	{
		line = readline("\033[33m\u263B\033[36m > \033[0m");
		if (!line)
			return (0);
		while (!line[0])
			line = readline("\033[33m\u263B\033[36m > \033[0m");
		check_slash(line);
		add_history(line);
		if (ft_strchr(line, '$'))
			line = ft_expand(line, data);
		tokens = ft_parsing(line, tokens);
		handle_redirs(tokens);
		while (++i < len_mtx)
			data->env_copy[i] = ft_strdup(envp[i]);
		handle_sign();
		if (!ft_strchr(line, '|') && !ft_strchr(line, '>') && !ft_strchr(line, '<'))
		{
				if (ft_builtin(tokens, data) == -1)
					ft_execute(tokens, data);
		}
		else
			ft_execute(tokens, data);
		// printf("Line: %s\n", line);
		tcsetattr(0, 0, &g_var.termios);
	}
	return (0);
}

//TODO gestionar redirecciones desde el inicio
//! importante que add_history este situada antes de las expansiones para evitar que el historial guarde el parametro expandido
//? si no hay | en la linea de comandos entra en builtins.
//? si hay | entra en pipex.
//? si en pipex hay un comando de builtins, busca el comando y ejecuta por los builtins.
//TODO tener en cuenta funcion opendir para executer.
//TODO gestion mensajes de error varios como con las señales y el crtl+D