
#include <iostream>
#include <iomanip>
#include <cassert>
#include <cstring>
#include "Text.h"

Text::Text(const char* charSeq)
{
	bufferSize = strlen(charSeq) + 1;
	buffer = new char[bufferSize];
	strcpy(buffer, charSeq);

}

Text::Text(const Text& other)
{
	bufferSize = other.bufferSize;
	buffer = new char[bufferSize];
	int counter = 0;
	while (counter < bufferSize) {
		buffer[counter] = other.buffer[counter];
		counter++;
	}
}

void Text::operator = (const Text& other)
{
	if (other.bufferSize > bufferSize) {
		delete[] buffer;
		buffer = new char[other.bufferSize];
	}
	int counter = 0;
	while (counter < other.bufferSize) {
		buffer[counter] = other.buffer[counter];
		counter++;
	}

}

Text::~Text()
{
	delete[] buffer;
}

int Text::getLength() const
{
	int temp = strlen(buffer);
	return temp;
}

char Text::operator [] (int n) const
{
	if (n > bufferSize) {
		return '\0';
	}
	else
		return buffer[n];
}

void Text::clear()
{
	int counter = 0;
	while (counter < bufferSize) {
		buffer[counter] = NULL;
		counter++;
	}
}

void Text::showStructure() const

// Outputs the characters in a string. This operation is intended for
// testing/debugging purposes only.

{
	int j;   // Loop counter

	for (j = 0; j < bufferSize; j++)
		cout << j << "\t";
	cout << endl;
	for (j = 0; buffer[j] != '\0'; j++)
		cout << buffer[j] << "\t";
	cout << "\\0" << endl;
}

Text Text::toUpper() const
{
	Text temp(buffer);
	int counter = 0;
	while (counter < temp.bufferSize) {
		temp.buffer[counter] = toupper(buffer[counter]);
		counter++;
	}
	return temp;
}

Text Text::toLower() const
{
	Text temp(buffer);
	int counter = 0;
	while (counter < temp.bufferSize) {
		temp.buffer[counter] = tolower(buffer[counter]);
		counter++;
	}
	return temp;
}

bool Text::operator == (const Text& other) const
{
	return (strcmp(buffer, other.buffer) == 0);
}

bool Text::operator <  (const Text& other) const
{
	return (strcmp(buffer, other.buffer) < 0);
}

bool Text::operator >  (const Text& other) const
{
	return (strcmp(buffer, other.buffer) > 0);
}
