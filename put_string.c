#include "shell.h"

/**
 * pchar - Prints a character to stdout.
 * @c: The character to print.
 */
void pchar(char c)
{
	write(1, &c, 1);
}

/**
 * ps - Prints a string to stdout.
 * @s: The string to print.
 */
void ps(char *s)
{
	if (!s)
		return;

	while (*s)
		pchar(*s++);
}

/**
 * cpchar - Prints a character to stderr.
 * @c: The character to print.
 */
void cpchar(char c)
{
	write(2, &c, 1);
}

/**
 * sps - Prints a string to stderr.
 * @s: The string to print.
 */
void sps(char *s)
{
	if (!s)
		return;

	while (*s)
		cpchar(*s++);
}
