/*
	Semester 05
	System Programming
	Assignment 01 - 
	Lexical Analysis

	Name:	Balse Shantanu Yogesh
	Branch: Third Year CST
	Batch:	B1
*/
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

//// Definitions ////

int stringLength(const char *str)
{
	// returns the length of the string.
	// Note: String MUST contain a '\0'
	const char *orig = str;
	int len = 0;
	while (1)
	{
		len++;
		str++;
		if (*str == 0)
			break;
	}
	if (orig[0] == 0)
		len = 0;
	return len;
}

bool equalStrings(const char *a, const char *b)
{
	// Returns true if both strings are the same else returns false
	while (*a && *b && (*a == *b)) { ++a; ++b; }
	if (*a == 0 && *b == 0)
		return true;
	return false;
}

char *returnLastWord(char *str)
{
	// Returns the last word from the string
	int len = stringLength(str);
	int i = len - 1;
	int k = 0;

	while (i >= 0 && str[i] != ' ')
		i--;

	static char lastWord[50];
	for (int j = i + 1; j < len; j++)
		lastWord[k++] = str[j];

	lastWord[k] = 0;
	return lastWord;
}

bool isKeyword(char *buffer)
{
	// Returns true if keyword is found else returns false
	char keywords[5][10] = { "int", "float", "char", "long", "double" };
	bool flag = false;
	for (int i = 0; i < 6; ++i)
	{
		if (equalStrings(buffer, keywords[i]))
		{
			flag = true;
			break;
		}
	}
	return flag;
}

bool isNumOrAlpha(char c)
{
	// Returns true if c is an alphabet(either lower case or upper case), or a number
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= 48 && c <= 57))
		return true;
	return false;
}

bool isAlpha(char c)
{
	// Returns true if c is an alphabet(either lower or upper case)
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return true;
	return false;
}

bool isNum(char c)
{
	// Returns true if c is a number
	if (c >= 48 && c <= 57)
		return true;
	return false;
}

bool isDelimiter(char ch)
{
	// Returns true if ch is a delimiter
	if (ch == ' ' || ch == ',' || ch == ';' || ch == '\n' || ch == '[' || ch == ']' || ch == '=')
		return true;
	return false;
}

void printKeywords(char *str)
{
	char buffer[15], ch;
	int i = 0, j = 0;

	while (str[i])
	{
		ch = str[i];

		if (isNumOrAlpha(ch))
			buffer[j++] = ch;

		if (isDelimiter(ch) && j != 0)
		{
			buffer[j] = 0;
			j = 0;

			if (isKeyword(buffer))
				cout << buffer << ", ";
		}

		i++;
	}
}

void printIdentifiers(char *str)
{
	char buffer[15], ch;
	int i = 0, j = 0;

	while (str[i])
	{
		ch = str[i];

		if (isAlpha(ch) || (isNum(ch) && j != 0))
			buffer[j++] = ch;

		if (isDelimiter(ch) && j != 0)
		{
			buffer[j] = 0;
			j = 0;

			if (!isKeyword(buffer) && !isNum(buffer[0]))
				cout << buffer << ", ";
		}

		i++;
	}
}

void printOperators(char *str)
{
	char operators[] = "+-=*/%", ch;
	int i = 0;
	while (str[i])
	{
		ch = str[i];

		for (int i = 0; i < 7; i++)
		{
			if (operators[i] == ch)
			{
				cout << ch << ", ";
				break;
			}
		}

		i++;
	}
}

void printArraySizes(char *str)
{
	char buffer[50], ch, size[10];
	int i = 0, j = 0, tabFlag = 0;

	while (str[i])
	{
		ch = str[i];

		if (isNumOrAlpha(ch) || ch == ' ')
			buffer[j++] = ch;

		if (ch == '[')
		{
			buffer[j] = 0;
			char *v = returnLastWord(buffer);
			i++;
			ch = str[i];
			int k = 0;
			while (ch != ']')
			{
				size[k] = ch;
				k++;
				i++;
				ch = str[i];
			}
			size[k] = 0;
			if (!tabFlag)
			{
				cout << "size of " << v << " is " << size << ", " << endl;
				tabFlag = 1;
			}
			else if (tabFlag)
				cout << "\t\t: size of " << v << " is " << size << ", " << endl;
		}

		i++;
	}
}

int main()
{
	char input[80];

	fgets(input, sizeof(input), stdin);
	cout << endl;

	cout << "Keywords\t: ";
	printKeywords(input);
	cout << endl;

	cout << "Identifiers\t: ";
	printIdentifiers(input);
	cout << endl;

	cout << "Operators\t: ";
	printOperators(input);
	cout << endl;

	cout << "Arrays\t\t: ";
	printArraySizes(input);
	cout << endl;

	cin.get();

	return 0;
}

////