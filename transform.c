#include "shell.h"
#include <limits.h>
#include <stdlib.h>

/**
 * mk_asctoint - Convert ASCII string to integer.
 * @s: Pointer to the string to convert.
 *
 * Description: Converts a string of ASCII digits to an integer,
 *              while checking for overflows.
 * Return: The integer value, INT_MAX or INT_MIN on overflow, or -1 on error.
 */
int mk_asctoint(const char *s)
{
	int result = 0;
	int i = 0;

	while (s[i] != '\0')
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1); /* Non-numeric character detected */
		if ((result > INT_MAX / 10) ||
			((result == INT_MAX / 10) && (s[i] - '0' > INT_MAX % 10)))
			return (INT_MAX); /* Overflow detected */

		result = result * 10 + (s[i] - '0');
		i++;
	}
	return (result);
}

/**
 * mk_cnvrt - Convert integer to string and print it.
 * @num: The integer to convert.
 *
 * Description: Converts an integer to a string and prints it
 *              character by character.
 */
void mk_cnvrt(int num)
{
	char *buffer;
	int index = 0;
	int isNegative = num < 0 ? 1 : 0;

	buffer = malloc(sizeof(char) * 12); /* +1 for negative numbers */
	if (buffer == NULL)
		return; /* Allocation failed */

	if (num == 0)
	{
		cpchar('0'); /* Just print zero if the number is zero */
		free(buffer);
		return;
	}

	if (isNegative)
		num = -num; /* Make the number positive for conversion */

	while (num != 0)
	{
		buffer[index++] = '0' + (num % 10);
		num /= 10;
	}

	if (isNegative)
		buffer[index++] = '-'; /* Add negative sign */

	/* Print the number in reverse order */
	while (--index >= 0)
		cpchar(buffer[index]);

	free(buffer);
}
