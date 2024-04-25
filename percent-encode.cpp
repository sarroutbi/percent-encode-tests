#include <stddef.h>
#include <stdio.h>
#include "percent-encode.h"

unsigned char
p11_is_percent_format_reserved_char(char c)
{
	switch (c) {
	case ' ':
	case '!':
	case '"':
	case '#':
	case '$':
	case '%':
	case '&':
	case '\'':
	case '(':
	case ')':
	case '*':
	case '+':
	case ',':
	case '/':
	case ':':
	case ';':
	case '=':
	case '?':
	case '@':
	case '[':
	case ']':
		return 1;
	}
	return 0;
}

char
p11_percent_format_first(char c)
{
	switch (c) {
	case ' ':
	case '!':
	case '"':
	case '#':
	case '$':
	case '%':
	case '&':
	case '\'':
	case '(':
	case ')':
	case '*':
	case '+':
	case ',':
	case '/':
		return '2';
	case ':':
	case ';':
	case '=':
	case '?':
		return '3';
	case '@':
		return '4';
	case '[':
	case ']':
		return '5';
	}
	return c;
}

char
p11_percent_format_second(char c)
{
	switch (c) {
	case ' ':
		return '0';
	case '!':
		return '1';
	case '"':
		return '2';
	case '#':
		return '3';
	case '$':
		return '4';
	case '%':
		return '5';
	case '&':
		return '6';
	case '\'':
		return '7';
	case '(':
		return '8';
	case ')':
		return '9';
	case '*':
		return 'A';
	case '+':
		return 'B';
	case ',':
		return 'C';
	case '/':
		return 'F';
	case ':':
		return 'A';
	case ';':
		return 'B';
	case '=':
		return 'D';
	case '?':
		return 'F';
	case '@':
		return '0';
	case '[':
		return 'B';
	case ']':
		return 'D';
	}
	return c;
}

const char *
percent_encode(const char *string, size_t len)
{
	static char buffer[1024];
	size_t output_index, input_index;

	while (len && string[len - 1] == ' ')
		len--;

	for (output_index = input_index = 0; output_index < sizeof(buffer) - 3;
			output_index++) {
		if (input_index >= len) {
			break;
		}
		if (p11_is_percent_format_reserved_char(string[input_index])) {
			buffer[output_index++] = '%';
			buffer[output_index++] = p11_percent_format_first(string[input_index]);
			buffer[output_index] = p11_percent_format_second(string[input_index]);
		} else {
			buffer[output_index] = string[input_index];
		}
		input_index++;
	}
	buffer[output_index] = '\0';
	return buffer;
}

const char *
printf_percent_encode(const char *string, size_t len)
{
	static char buffer[1024];
	size_t output_index, input_index;

	while (len && string[len - 1] == ' ')
		len--;

	for (output_index = input_index = 0; output_index < sizeof(buffer) - 3;
			output_index++) {
		if (input_index >= len) {
			break;
		}
		if (p11_is_percent_format_reserved_char(string[input_index])) {
                        snprintf(&buffer[output_index], 4, "%%%x", string[input_index]);
                        output_index += 2;
		} else {
			buffer[output_index] = string[input_index];
		}
		input_index++;
	}
	buffer[output_index] = '\0';
	return buffer;
}

