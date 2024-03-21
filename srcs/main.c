#include <readline/readline.h>

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	(void) env;

	readline(NULL);
	
	return (1);
}