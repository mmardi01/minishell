/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmardi <mmardi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:03:45 by mmardi            #+#    #+#             */
/*   Updated: 2022/07/07 12:51:20 by mmardi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define CTL_D "\033[A\033[11Cexit\n"

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>

int	g_status;

typedef struct t_fd
{
	int	pfd[2];
	int	pfd2[2];
	int	fd[2];
	int	k;
}	t_fd;

char	**ft_split(const char *s, char c);
int		ft_strlen(const char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_echo(char **str, int fd);
int		ft_check_command(char **str, char **env, int fd);
char	*ft_strtrim(const char *s1, char const *set);
char	**mysplit(char *str);
char	*get_next_line(int fd);
char	*ft_strchr(char *str, char c);
char	*ft_strjoin(char *s1, char *s2);
int		get_history(void);
int		executable(char **commands, char **env);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	ft_ctrlc(int sig);
int		get_globale(int i);
int		get_globale_3(int i);
void	save_history(char *str, int fd);
int		ft_is_str(char *line, char *str);
int		ft_cd(char **line, char **env);
int		ft_pwd(int fd);
void	ft_clt_d(void);
int		ft_skip2(char *str, int *count, int *j);
char	*get_word2(char *str, char c, int *j);
int		check_redirections(char	**str);
int		ft_check_exit(char **s);
int		get_glo_2(int n);
void	redirect_output(char **spath, char **command, char **env, int *fd);
int		exec(char **spath, char **commands, char **env);
char	**only_commands(char **commands);
void	redirect(char **commands, char **env);
void	ft_free(char **array);
void	ft_putstr_fd(char *s, int fd);
char	**add_to_path(char **spath, char *command);
int		check_next_red(char **str, char c);
int		check_permession(char **commands);
char	*ft_strdup(const char *str);
int		get_fd2(char **commands);
void	ft_unlink(char	**command);
void	handledollar(char **s, int *tab, char **env);
int		get_glo_3(int n);
char	**cmd_btw_pipes(char **str);
void	mypipe(char **commands, char **env, t_fd *fd);
void	redirect2(char **commands, char **env, t_fd *fd);
void	ft_aficher(char **str, int i, int fd);
void	ft_exp_cmd(char *arg, char **env);
int		check_arg(char *cmd);
int		ft_unset(char **arg, char **env);
int		ft_env(char **env);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_check_n(char **str, int *i);
int		ft_export(char **cmd, char **env, int fd);
int		ft_export_h(char *cmd, char **env);
void	handle_commands(char *str, char **env);
int		*handle_quotes(char **s);
int		quotes_number(char *str);
void	ft_exit(char **str);
long	ft_atoi(const char *str);
int		ft_print_env(char **env, int fd);
int		ft_export_h(char *cmd, char **env);
void	add_ne(char *arg, char **env);
char	*ft_itoa(int j);
char	*ft_strrchr(char *s, int c);
char	*ft_itoa(int j);
int		check_arg(char *cmd);
char	*get_env(char *str, char **env);
void	print_n(char *a, int ich, int k, long n);
int		n_al(long n);
int		ft_is_alphanum(char s);
int		ft_is_alpha(char s);

#endif
