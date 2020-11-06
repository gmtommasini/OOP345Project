/*
Guilherme Matsumoto Tommasini
167561182
gmatsumoto-tommasini
gmatsumoto-tommasini@mysenca.ca
2020/11/03

I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/

#pragma once
#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>

namespace util {
#define CharsToTrim "\t\n\v\f\r "

	inline std::string& ltrim(std::string& src) {
		src.erase(0, src.find_first_not_of(CharsToTrim));
		return src;
	};
	inline std::string& rtrim(std::string& src) {
		src.erase(src.find_last_not_of(CharsToTrim) + 1);
		return src;
	};
	inline std::string& trim(std::string& str) {
		//return ltrim(rtrim(str));
		return str.erase(str.erase(0, str.find_first_not_of(CharsToTrim)).find_last_not_of(CharsToTrim) + 1);
	};

	inline std::string substring(std::string& src, const char C) {
		int pos = src.find(C);
		pos = pos > 0 ? pos : src.length();
		std::string temp = src.substr(0, pos);
		trim(temp);
		src.erase(0, pos + 1);
		return temp;
	}
	inline std::istream& listrim(std::istream& in) { //left trim the stream
		do {
			if (in.peek() == ' ' || in.peek() == '\t' || in.peek() == '\v' || in.peek() == '\f') {
				in.get();
			}
			else {
				return in;
			}
		} while (true);
	}
}

#endif // !UTIL_H