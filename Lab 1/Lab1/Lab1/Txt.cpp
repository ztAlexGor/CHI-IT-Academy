#include "Txt.h"
#include <fstream>


l1::Txt::Txt() : lineNumber(0), text(nullptr)
{
}

l1::Txt::Txt(const char* filename) : Txt()
{
	std::ifstream file(filename, std::ios::in);

	if (!file)
	{
		return;
	}

	// count lines in file
	char buffer[1000];

	while (!file.eof())
	{
		lineNumber++;
		file.getline(buffer, 1000);
	}

	// returning to beginning of file
	file.clear();
	file.seekg(0);

	// trying to allocate memory for n lines 
	// and copy text from file
	try
	{
		text = new char* [lineNumber];

		for (int i = 0; i < lineNumber; ++i)
		{
			file.getline(buffer, 1000);
			
			size_t len = strlen(buffer);
			text[i] = new char[len + 1];
			memcpy(text[i], buffer, len);
			text[i][len] = '\0';
		}
	}
	catch (std::bad_alloc ex)
	{
		std::cout << ex.what() << std::endl;
	}
	file.close();
}

l1::Txt::Txt(const Txt& other) : lineNumber(other.lineNumber)
{
	text = new char* [lineNumber];

	for (int i = 0; i < lineNumber; ++i)
	{
		text[i] = new char[strlen(other.text[i]) + 1];
		memcpy(text[i], other.text[i], strlen(other.text[i]));
	}
}

l1::Txt::Txt(Txt&& other) : lineNumber(other.lineNumber), text(std::move(other.text))
{
	other.text = nullptr;
	other.lineNumber = 0;
}

// copy-and-swap 
l1::Txt& l1::Txt::operator=(const Txt& other)
{
	Txt newTxt = other;

	std::swap(this->lineNumber, newTxt.lineNumber);
	std::swap(this->text, newTxt.text);

	return *this;
}

l1::Txt& l1::Txt::operator=(Txt&& other)
{
	lineNumber = other.lineNumber;
	text = std::move(other.text);
	
	other.lineNumber = 0;
	other.text = nullptr;

	return *this;
}

size_t l1::Txt::size() const
{
	return lineNumber;
}

l1::Txt::~Txt()
{
	for (size_t i = 0; i < lineNumber; i++)
	{
		delete[] text[i];
	}
	delete[] text;
}
