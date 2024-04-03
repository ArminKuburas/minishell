/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 09:56:31 by akuburas          #+#    #+#             */
/*   Updated: 2024/04/03 14:56:45 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(char *path, char *path_name, char **env)
{
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		path = ft_substr(env[i], 0, j);
		if (path == NULL)
			return(NO_MEMORY);
		if (ft_strcmp(path, path_name) == 0)
		{
			return (SUCCESS);
		}
		free(path);
		i++;
	}
	return (FAILURE);
}


/*The goal of this function is to remove certain quotes and also expanding dollar signs inside "" and on their own but not when inside 'single quotes'
Also not inside double quotes if said quotes are inside single quotes. We also shouldnt remove quotes within quotes from the strings
So for example ec"ho" should become echo. $EXAMPLE should try to find EXAMPLE inside the env and remove $EXAMPLE from the string and add in what it finds in the env. If it cant find anything it just removes the $EXAMPLE
We won't handle $$ like bash does. Instead it will try to find $ inside the env, probably wont find it and just remove the $$. if a $ is on its own like "hello $ goodbye" it should leave the dollar sign alone.*/

int	split_cleaner(t_shelldata *data, char **env)
{
	int		i;
	char	*quote;
	int		j;
	int		x;
	char	*env_path;

	while (data->split_input[i] != NULL)
	{
		quote = ft_strchr(data->split_input[i], '\'');
		if (quote == NULL)
			quote = ft_strchr(data->split_input[i], '"');
		if (quote != NULL)
		{
			if (*quote == '"')
			{
				j = 0;
				while (data->split_input[i][j] && data->split_input[i][j] != *quote)
					j++;
				while (data->split_input[i][j] && data->split_input[i][j] != '$')
					j++;
				if (data->split_input[i][j] == '$')
				{
					if (ft_strchr("\t ", data->split_input[i][j + 1]) == NULL)
					{
						get_path();
					}
				}
			}
		}
	}
	return (SUCCESS);
}
