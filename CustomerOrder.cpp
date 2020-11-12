// Name: Guilherme Matsumoto Tommasini
// Seneca Student ID: 167561182 
// Seneca email: gmatsumoto-tommasini@myseneca.ca
// Date of completion: 2020/11/11
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "CustomerOrder.h"
#include <algorithm>

size_t CustomerOrder::m_widthField = 0;

CustomerOrder::~CustomerOrder() {
	if (this->m_lstItem) {
		for (size_t i = 0; i < this->m_cntItem; i++) {
			delete this->m_lstItem[i];
		}
		delete[] m_lstItem;
	}
	this->m_lstItem = nullptr;
}
CustomerOrder::CustomerOrder() {}
CustomerOrder::CustomerOrder(std::string& input) {
	if (input.length() > 0) {
		size_t pos = 0;
		bool more = true;
		Utilities ut;
		try {
			m_name = ut.extractToken(input, pos, more);
			m_product = ut.extractToken(input, pos, more);
			m_cntItem = std::count(input.begin(), input.end(), ut.getDelimiter()) - 1;
			this->m_lstItem = new Item * [m_cntItem];
			for (size_t i = 0; i < m_cntItem; i++) {
				Item* temp = new Item(ut.extractToken(input, pos, more));
				m_lstItem[i] = std::move(temp);
				temp = nullptr;
			};

			//update CustomerOrder::m_widthField if the value stored there is smaller than the value stored in Utilities::m_widthField
			if (CustomerOrder::m_widthField < ut.getFieldWidth()) {
				CustomerOrder::m_widthField = ut.getFieldWidth();
			}
		}
		catch (const std::string error) {
			std::cout << error;
		}
	}

}
CustomerOrder::CustomerOrder(CustomerOrder&) {
	throw "ERROR: Cannot make copies.";
}
CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
	*this = std::move(src);
}
CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept {
	if (this != &src) {
		try { 
			if (this->m_lstItem) {
				//deleting existing data
				for (size_t i = 0; i < this->m_cntItem; i++) {
					delete this->m_lstItem[i];
				}
				delete[] m_lstItem;
			}
			//copying 
			this->m_name = src.m_name;
			this->m_product = src.m_product;
			this->m_cntItem = src.m_cntItem;
			this->m_lstItem = src.m_lstItem;

			//emptying source
			src.m_name = "";
			src.m_product = "";
			src.m_cntItem = 0;
			src.m_lstItem = nullptr;
		}
		catch (...) {
			std::cout << "Error in move assignment operator." << std::endl;
		}
	}
	return *this;
}

bool CustomerOrder::isOrderFilled() const {
	for (size_t i = 0; i < this->m_cntItem; i++) {
		//if at least one is false, return false
		if (!(this->m_lstItem[i]->m_isFilled)) {
			return false;
		}
	}
	return true;
}
bool CustomerOrder::isItemFilled(const std::string& itemName) const {
	for (size_t i = 0; i < this->m_cntItem; i++) {
		if (this->m_lstItem[i]->m_itemName == itemName) {
			return this->m_lstItem[i]->m_isFilled;
		}
	}
	return true;
}
void CustomerOrder::fillItem(Station& station, std::ostream& os) {
	for (size_t i = 0; i < this->m_cntItem; i++) {
		if (this->m_lstItem[i]->m_itemName == station.getItemName()) {
			if (station.getQuantity() > 0) {
				station.updateQuantity();
				this->m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
				this->m_lstItem[i]->m_isFilled = true;
				os << "    Filled ";
			}
			else {
				os << "Unable to fill  ";
			}
			os << this->m_name << ", " << this->m_product << " [" << this->m_lstItem[i]->m_itemName << "]" << std::endl;
		}
		//else{//do nothing}
	}
}
void CustomerOrder::display(std::ostream& os) const {
	os << m_name << " - " << m_product << std::endl;
	for (size_t i = 0; i < m_cntItem; i++) {
		os << "[" << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber << "] "
			<< std::setw(m_widthField) << std::setfill(' ') << std::left << m_lstItem[i]->m_itemName
			<< " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "MISSING") << std::endl;
	}
}
