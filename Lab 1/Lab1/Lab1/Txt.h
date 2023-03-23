#pragma once

#include <iostream>

namespace l1 {
	class Txt
	{
	private:
		size_t lineNumber;
		char** text;

	public:
		// default constructor
		Txt();

		// constructor with 1 arg
		Txt(const char* filename);

		// copy constructor
		Txt(const Txt& other);

		// move constructor
		Txt(Txt&& other);

		// copy assignment operator
		Txt& operator= (const Txt& other);

		// move assignment operator
		Txt& operator= (Txt&& other);

		// function-member that returns size of lines
		size_t size() const;

		// destructor
		~Txt();
	};
}



