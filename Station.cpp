#include "Station.h"


size_t Station::m_widthField = 0;
size_t Station::id_generator = 1;

Station::~Station() {}
Station::Station() {}

Station::Station(const std::string input) {
	size_t pos = 0;
	bool more = true;
	Utilities ut;
	std::string token;
	try {
		id = id_generator++;
		token = ut.extractToken(input, pos, more);
		itemName = token;
		token = ut.extractToken(input, pos, more);
		serialNumber = stoi(token);
		token = ut.extractToken(input, pos, more);
		quantity = stoi(token);
		if (Station::m_widthField < ut.getFieldWidth()) {
			Station::m_widthField = ut.getFieldWidth();
		}
		token = ut.extractToken(input, pos, more);
		description = token;
	}
	catch (const std::string error) {
		std::cout << error;
	}
}
const std::string& Station::getItemName() const {
	return itemName;
}
unsigned int Station::getNextSerialNumber() {
	return serialNumber++;
}
unsigned int Station::getQuantity() const {
	return quantity;
}
void Station::updateQuantity() {
	if (quantity > 0) {
		quantity--;
	}
}
void Station::display(std::ostream& os, bool full) const {
	os << "[" << std::right << std::setw(3) << std::setfill('0') << id
		<< "] Item: " << std::left << std::setw(Station::m_widthField) << std::setfill(' ') << itemName
		<< " [" << std::right << std::setw(6) << std::setfill('0') << serialNumber << "]";
	if (full) {
		os << std::left << " Quantity: " << std::setw(Station::m_widthField) << std::setfill(' ') << quantity
			<< " Description: " << description;
	}
	os << std::endl;
}