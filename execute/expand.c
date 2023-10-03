/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crtorres <crtorres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:04:17 by crtorres          #+#    #+#             */
/*   Updated: 2023/10/03 12:03:46 by crtorres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	ft_expand(char *str, t_data *env)
{
	int		len;
	int		n_char;
	int		i;	
	char	*str_expand;

	len = expandlen(str, env);
	str = ft_calloc(len + 1, 1);
}

int	expandlen(char *str, t_data *env)
{
	int	i;
	int	len;
	
	i = 0;
	len = 0;
	
}
/**
 * The function counts the number of characters between single quotes in a given
 * string.
 * 
 * @param str A pointer to a character array (string) that contains the input
 * string.
 * @param i The parameter `i` is a pointer to an integer that represents the
 * current index position in the string `str`. It is used to keep track of the
 * current position while iterating through the string.
 * @param n The parameter `n` is a pointer to an integer. It is used to keep track
 * of the count of single quotes in the given string `str`.
 * 
 * @return either 1 or 0. If the condition `str[(*i)] == 39` is true, then 1 is
 * returned. Otherwise, 0 is returned.
 */
int	count_squote(char *str, int *i, int *n)
{
	if (str[(*i)] == 39)
	{
		(*n)++;
		(*i)++;
		while (str[(*i)] && str[(*i)] != 39)
		{
			(*n)++;
			(*i)++;
		}
		(*n)++;
		(*i)++;
		return (1);
	}
	return (0);
}

/**
 * The function `ft_expandsize` calculates the total size of a string after
 * expanding variables and quotes.
 * 
 * @param s A pointer to a character array (string) that represents the input
 * string.
 * @param env The `env` parameter is a pointer to an array of strings, where each
 * string represents an environment variable.
 * 
 * @return the total number of characters in the expanded string.
 */
int	ft_expandsize(char *s, char **env)
{
	int		i;
	int		total;

	total = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == '$')
			i += ft_checkdollar(&s[i], &total, NULL, env);
		if (s[i] == '\0')
			break ;
		/* This code block is checking if the current character `s[i]` is a single quote
		`'`. If it is, it increments the index `i` and the total count `total` by 1.
		Then, it enters a loop that continues until it reaches the end of the string
		or encounters another single quote. Inside the loop, it increments `i` and
		`total` by 1 for each character encountered. If the end of the string is
		reached before finding another single quote, the loop breaks. Finally, it
		increments `total` by 1 to account for the closing single quote and increments
		`i` by 1 to move to the next character. */
		if (s[i] && s[i] == '\'')
		{
			i++;
			total++;
			while (s[i] && s[i] != '\'')
			{
				i++;
				total++;
				if (s[i] == '\0')
					break ;
			}
			total++;
			i++;
		}
		if (s[i] && s[i] == DQUOTE)
		{
			total++;
			i++;
			while (s[i] && s[i] == '$')
				i += ft_checkdollar(&s[i], &total, NULL, env);
			if (s[i] == '\0')
				break ;
			while (s[i] && s[i] != DQUOTE)
			{
				while (s[i] && s[i] == '$')
					i += ft_checkdollar(&s[i], &total, NULL, env);
				if (s[i] == '\0')
					break ;
				total++;
				i++;
			}
			if (s[i] == '\0')
					break ;
			total++;
			i++;
		}
		if (s[i] == '\0')
			break ;
		total++;
		i++;
	}
	return (total);
}