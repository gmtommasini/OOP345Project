#pragma once
#include <string>
#include "util.h"

//namespace sdds {
	class Utilities	{
		size_t m_widthField{ 1 };
		static char m_delimiter;

	public:
		~Utilities();
		Utilities();

		void setFieldWidth(size_t newWidth);
		size_t getFieldWidth() const;
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

		static void setDelimiter(char newDelimiter){
			m_delimiter = newDelimiter;
		}
		static char getDelimiter(){
			return m_delimiter;
		}
	};


	
//}