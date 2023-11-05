#include "shell.h"

/**
 * slen - Computes the length of a string.
 * @s: The string to compute the length of.
 *
 * Return: The length of the string.
 */
int slen(const char *s)
{
	int length = 0;

	if (!s)
		return (-1);

	while (s[length])
		length++;

	return (length);
}

/**
 * scopy - Copies a string from source to destination.
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: The pointer to the destination string.
 */
char *scopy(char *dest, const char *src)
{
	int i = 0;

	while ((dest[i] = src[i]) != '\0')
		i++;

	return (dest);
}

/**
 * scncat - Concatenates two strings.
 * @dest: The destination string.
 * @src: The source string.
 *
 * Return: The concatenated string.
 */
char *scncat(char *dest, const char *src)
{
	int dest_len = slen(dest);
	int i = 0;

	while ((dest[dest_len + i] = src[i]) != '\0')
		i++;

	return (dest);
}

/**
 * scmp - Compares two strings.
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: The difference between the first pair of characters that differ.
 */
int scmp(const char *str1, const char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}

	return (*(const unsigned char *)str1 - *(const unsigned char *)str2);
}
