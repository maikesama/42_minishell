#include "./../../headers/main.h"


void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		int	len;
		char	*str;

		len = ft_strlen(rl_line_buffer + 2);
		str = (char *) malloc (len);
		ft_strlcpy(rl_line_buffer, str, len);
		str[len + 1] = ' ';
		str[len + 2] = ' ';


		//se commento le il rl_on_new_line(); ft_printf(RL_S"\e[95m"RL_E "MiniShell>>>" RL_S"\e[0m"RL_E"\n", rl_on_new_line);
		//non abbiamo piu il problema quando chiudiamo un programma in esecuzione (prova grep m e quando è in loop cntrl C)
		//scrive tre volte minishell.
		//Ho visto che però commentandolo non funziona bene il cntrl C quando non è stato dato nessun comando a minishell
		rl_on_new_line();
		//ft_printf(RL_S"\e[95m"RL_E "MiniShell>>>" RL_S"\e[0m"RL_E"\n",
		//	rl_on_new_line);
	//	write (1, "\e[95mMiniShell>>>\e[0m\n", 23);
	//	write (1, rl_line_buffer, ft_strlen(rl_line_buffer));
	//	write (1, "  \b\b\n", 5);
		rl_replace_line(str, 1);
		rl_redisplay();
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		free(str);
		// rl_on_new_line();
		// ft_printf("MiniShell>>>", rl_on_new_line);
		// rl_on_new_line();
		// rl_replace_line("", 1);
		// rl_redisplay();
	}
}