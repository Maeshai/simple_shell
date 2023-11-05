#include "shell.h"
#include <stdio.h>
#include <string.h>

/**
 * outpt_env - Prints all the environment variables
 * @env: The environment variables array
 *
 * Return: void
 */
void outpt_env(char **env)
{
	int i = 0;

	if (env == NULL)
	{
	return;
	}
	while (env[i])
	{
	write(STDOUT_FILENO, env[i], strlen(env[i]));
	write(STDOUT_FILENO, "\n", 1);
	i++;
	}
}

/**
 * c_evr - check if a command is env
 * @tkn: tokenized input
 * @env: environment variables
 * @bufr: input buffer
 * Return: -1 on success, 0 otherwise
 */
int c_evr(char **tkn, char **env, char *bufr)
{
	if (scmp(tkn[0], "env") == 0)
	{
		outpt_env(env);
		free(tkn);
		free(bufr);
		return (-1);
	}
	return (0);
}

/**
 * g_tkn - get tokenized input
 * @bufr: input buffer
 * @stats: status
 * Return: tokenized input
 */
char **g_tkn(char **bufr, int stats)
{
	size_t sB = 0;
	int lc;

	lc = getline(bufr, &sB, stdin);
	if (lc == -1)
	{
		free(*bufr);
		exit(stats);
	}
	return (tknize(*bufr));
}
/**
 * error_perm - Prints a permission error message.
 * @arv: The name of the shell executable (argv[0]).
 * @dsh: The command count.
 * @comnd: The command that caused the permission error.
 */
void error_perm(char *arv, int dsh, char *comnd)
{
	char *error_message = "Permission denied";

	if (arv && comnd)
	{
	fprintf(stderr, "%s: %d: %s: %s\n", arv, dsh, comnd, error_message);
	}
}

/**
 * cant_find - Prints an error message when a command is not found.
 * @arv: The name of the shell executable (argv[0]).
 * @dsh: The command count.
 * @comnd: The command that was not found.
 */
void cant_find(char *arv, int dsh, char *comnd)
{
	fprintf(stderr, "%s: %d: %s: not found\n", arv, dsh, comnd);
}

/**
 * exe_comnd - execute command
 * @tkn: tokenized input
 * @arv: argument vector
 * @dsh: shell instance number
 * @env: environment variables
 * Return: error number
 */
int exe_comnd(char **tkn, char **arv, int dsh, char **env)
{
	char *cm;

	cm = g_comnd(tkn[0]);
	if (execve(cm, tkn, env) == -1)
	{
		if (errno == EACCES)
		{
			error_perm(arv[0], dsh, tkn[0]);
		}
		else
		{
			cant_find(arv[0], dsh, tkn[0]);
		}
		if (cm)
		{
		free(cm);
		cm = NULL;
		}
		if (tkn)
		{
			int i;

			for (i = 0; tkn[i] != NULL; i++)
			{
				free(tkn[i]);
			}
			free(tkn);
			tkn = NULL;
		}
		perror("Error");
		return (errno);
	}
	if (cm)
		free(cm);
	return (0);
}
