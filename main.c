#include "shell.h"

/**
 * main - entry point
 * @arc: argument count
 * @arv: argument vector
 * @env: environment variables
 * Return: 0 on success
 */

int main(int arc __attribute__((unused)), char **arv, char **env)
{
	char **tk, *bfr;
	int sts, idn, rs = 1, scde = 0;

	bfr = NULL;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(1, "$ ", 2);
		tk = g_tkn(&bfr, scde);
		if (!tk || !tk[0])
		{
			rs++;
			free(tk);
			continue;
		}
		ext_sh(tk, arv, rs, scde, bfr);
		if (c_evr(tk, env, bfr) == -1)
			continue;
		idn = fork();
		if (idn == 0)
			return (exe_comnd(tk, arv, rs, env));
		wait(&sts);
		if (WIFEXITED(sts))
			scde = WEXITSTATUS(sts);
		free(tk);
		free(bfr);
		rs++;
	}
	return (0);
}
