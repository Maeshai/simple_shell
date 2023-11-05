#include "shell.h"

/**
 * tknize - Tokenizes a string into an array of strings.
 * @strng: The string to tokenize.
 *
 * Return: A pointer to an array of strings.
 */
/*char **tknize(char *strng)
{
	char *token, **tokens = NULL, delims[] = " \n\t";
	int index = 0;

	if (!strng)
		return (NULL);

	token = strtok(strng, delims);
	if (!token)
	{
		free(strng);
		return (NULL);
	}

	tokens = malloc(sizeof(char *) * 1024);
	if (!tokens)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	while (token)
	{
		tokens[index++] = token;
		token = strtok(NULL, delims);
	}
	tokens[index] = NULL;

	return (tokens);
}*/

/**
 * g_evr - Gets the environment variable's value.
 * @env_lbl: The name of the environment variable.
 *
 * Return: The value of the environment variable or NULL if not found.
 */
/* char *g_evr(char *env_lbl)
{
	int index = 0, char_count, name_len;

	name_len = slen(env_lbl);
	while (environ[index])
	{
		for (char_count = 0;
			environ[index][char_count] && char_count < name_len;
			char_count++)
		{
			if (environ[index][char_count] != env_lbl[char_count])
				break;
		}

		if (char_count == name_len && environ[index][char_count] == '=')
			return (environ[index] + name_len + 1);

		index++;
	}

	return (NULL);
} */
/* Additional functions g_comnd, tkn_free, and ext_sh remain unchanged */
