#include "shell.h"

static void free_resources(char **tkn, char *bufr);

/**
 * tknize - Tokenizes a string.
 * @str: String to tokenize.
 *
 * Return: Pointer to an array of strings (tokens).
 */
char **tknize(char *str)
{
	char *token, **tokens = NULL;
	char delims[] = " \n\t";
	int i = 0;

	if (!str)
		return (NULL);

	token = strtok(str, delims);
	if (!token)
	{
		free(str);
		return (NULL);
	}

	tokens = malloc(sizeof(char *) * 1024);
	if (!tokens)
	{
		perror("Error: Allocation failed");
		free(str);
		exit(EXIT_FAILURE);
	}

	while (token)
	{
		tokens[i++] = token;
		token = strtok(NULL, delims);
	}
	tokens[i] = NULL;

	return (tokens);
}

/**
 * g_evr - Fetches the environment variable's value by its label.
 * @env_lbl: Label of the environment variable.
 *
 * Return: Value of the environment variable or NULL if not found.
 */
char *g_evr(char *env_lbl)
{
	int i = 0, j, lbl_len;

	lbl_len = strlen(env_lbl);
	while (environ[i])
	{
		for (j = 0; environ[i][j] && j < lbl_len; j++)
			if (environ[i][j] != env_lbl[j])
				break;

		if (j == lbl_len && environ[i][j] == '=')
			return (environ[i] + lbl_len + 1);

		i++;
	}

	return (NULL);
}

/**
 * ext_sh - Exits the shell program.
 * @tokens: Array of tokens (strings).
 * @argv: Argument vector.
 * @shell_no: Shell iteration number.
 * @status: Exit status.
 * @buffer: Input buffer.
 */
void ext_sh(char **tokens, char **argv, int shell_no, int status, char *buffer)
{
	int exit_code;

	if (tokens && strcmp(tokens[0], "exit") == 0)
	{
		if (tokens[1])
		{
			exit_code = atoi(tokens[1]);
			if (exit_code < 0)
			{
				fprintf(stderr, "%s: %d: exit: Illegal number: %s\n",
						argv[0], shell_no, tokens[1]);
				free_resources(tokens, buffer);
				exit(EXIT_FAILURE);
			}
			free_resources(tokens, buffer);
			exit(exit_code <= 255 ? exit_code : 232);
		}
		free_resources(tokens, buffer);
		exit(status);
	}
}

/**
 * g_comnd - Checks if a command exists in the PATH.
 * @cmd: Command to find.
 *
 * Return: Full path of the command if found, or NULL.
 */
char *g_comnd(char *cmd)
{
	char *path, *token, *full_cmd;
	struct stat st;

	if (stat(cmd, &st) == 0)
		return (cmd);

	path = g_evr("PATH");
	token = strtok(path, ":");
	while (token)
	{
		full_cmd = malloc((strlen(token) + strlen(cmd) + 2) * sizeof(char));
		if (!full_cmd)
		{
			perror("Error: Allocation failed");
			return (NULL);
		}

		strcpy(full_cmd, token);
		strcat(full_cmd, "/");
		strcat(full_cmd, cmd);

		if (stat(full_cmd, &st) == 0)
			return (full_cmd);

		free(full_cmd);
		token = strtok(NULL, ":");
	}

	return (NULL);
}

/**
 * free_resources - Frees allocated memory for tokens and buffer.
 * @tokens: Array of tokens to free.
 * @buffer: Input buffer to free.
 */
static void free_resources(char **tokens, char *buffer)
{
	free(buffer);
	if (tokens)
	{
		free(tokens[0]); /* If the buffer was allocated as a block,
				 * free the first element
				 */
		free(tokens);
	}
}
