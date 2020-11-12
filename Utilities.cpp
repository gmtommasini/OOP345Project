// Name: Guilherme Matsumoto Tommasini
// Seneca Student ID: 167561182 
// Seneca email: gmatsumoto-tommasini@myseneca.ca
// Date of completion: 2020/11/11
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Utilities.h"

//initialize m_delimiter
char Utilities::m_delimiter = ',';

Utilities::~Utilities() {}
Utilities::Utilities() {}

void Utilities::setFieldWidth(size_t newWidth) { this->m_widthField = newWidth; }
size_t Utilities::getFieldWidth() const { return this->m_widthField; }
std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
	size_t pos = str.find(this->getDelimiter(), next_pos);
	more = false;
	std::string temp{};
	if (pos >= 0) { //extraction token
		temp = str.substr(next_pos, pos - next_pos);
		size_t len = util::trim(temp).length();
		next_pos = pos + 1;
		if (pos != std::string::npos)
			more = true;
		else
			more = false;
		if (len > 0) {
			if (len > this->m_widthField) {
				this->m_widthField = len;
			}
		}
		else {// 2 delimiters with no token between them.
			throw "ERROR: empty token!\n";
		}
	}
	return temp;
}
