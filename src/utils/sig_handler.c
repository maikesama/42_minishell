#include "./../../headers/main.h"


void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		rl_on_new_line();
		ft_printf(RL_S"\e[95m"RL_E "MiniShell>>>" RL_S"\e[0m"RL_E"\n",
			rl_on_new_line);
	//	write (1, "\e[95mMiniShell>>>\e[0m\n", 23);
	//	write (1, rl_line_buffer, ft_strlen(rl_line_buffer));
	//	write (1, "  \b\b\n", 5);
		rl_replace_line("", 1);
		rl_redisplay();
		// rl_on_new_line();
		// ft_printf("MiniShell>>>", rl_on_new_line);
		// rl_on_new_line();
		// rl_replace_line("", 1);
		// rl_redisplay();
	}
}