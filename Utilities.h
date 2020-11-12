// Name: Guilherme Matsumoto Tommasini
// Seneca Student ID: 167561182 
// Seneca email: gmatsumoto-tommasini@myseneca.ca
// Date of completion: 2020/11/11
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once
#include <string>
#include "util.h"

class Utilities {
	size_t m_widthField{ 1 };
	static char m_delimiter;

public:
	~Utilities();
	Utilities();

	void setFieldWidth(size_t newWidth);
	size_t getFieldWidth() const;
	std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

	static void setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}
	static char getDelimiter() {
		return m_delimiter;
	}
};

