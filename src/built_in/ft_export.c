// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_export.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: efirmino <efirmino@student.42nice.fr>      +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/02/09 11:01:22 by efirmino          #+#    #+#             */
// /*   Updated: 2023/02/11 08:40:50 by efirmino         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../include/minishell.h"

// static void	ft_check_n_add(char *str)
// {
// 	char	*key;
// 	char	*value;
// 	int		i;
// 	// int		j;
// 	char	**splitted;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '=')
// 		{
// 			value = ft_strdup(str + (i + 1));
// 			splitted = ft_split(str, '=');
// 			key = splitted[0];
// 			// if (ft_is_alphanum(value))
// 			ft_add_env_element(key, value);
// 		}
// 		i++;
// 	}
// 	free(value);
// 	ft_freesplit(splitted);
// }

// void	ft_export(t_cmd *command)
// {
// 	pid_t	child;
// 	char	**cmd;
// 	// char	**to_export;
// 	int		i;
// 	// int		j;

// 	child = fork();
// 	cmd = command->cmd;
// 	if (child == 0)
// 	{
// 		i = 1;
// 		while (cmd[i])
// 		{
// 			ft_check_n_add(cmd[i]);
// 			i++;
// 		}
// 	}
// 	waitpid(child, 0, 0);
// }