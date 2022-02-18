#include "../../inc/minishell.h"

int	is_w_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r'
			|| c == '\n' || c == '\v' || c == '\f')
		return (1);
	return (0);
}

int print_sep_error(char sep)
{
	write(1, "parse error near '", 18);
	write(1, &sep, 1);
	write(1, "'\n", 2);
	return (1);
}

int	is_sep(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

int	print_quote_err(void)
{
	write(1, "Error : found an unclosed quote or double quotes\n", 49);
	return (1);
}

int	count_arr(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
