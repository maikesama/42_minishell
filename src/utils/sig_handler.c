#include "./../../headers/main.h"


void	sig_handler(int signo)
{
    (void)signo;
    ft_printf("^C\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}