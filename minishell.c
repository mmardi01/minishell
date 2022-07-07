/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 20:16:52 by mmardi            #+#    #+#             */
/*   Updated: 2022/07/07 12:51:11 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*str;

	(void)ac;
	(void)av;
	rl_catch_signals = 0;
	signal (SIGINT, ft_ctrlc);
	signal (SIGQUIT, SIG_IGN);
	ft_env(env);
	while (1)
	{
		get_globale(0);
		str = readline("minishell$ ");
		if (str && str[0])
			add_history(str);
		if (!str)
			ft_clt_d();
		if (quotes_number(str) == 0)
			handle_commands(str, env);
		else
		{
			g_status = 258;
			ft_putstr_fd("syntax error\n", 2);
		}
		free (str);
	}
}
