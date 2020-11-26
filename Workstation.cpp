// Name: Guilherme Matsumoto Tommasini
// Seneca Student ID: 167561182 
// Seneca email: gmatsumoto-tommasini@myseneca.ca
// Date of completion: 2020/11/26
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Workstation.h"
using namespace std;

Workstation::~Workstation() {}
Workstation::Workstation() {
	m_pNextStation = nullptr;
}
Workstation::Workstation(const string& input) : Station(input), m_pNextStation{ nullptr } {}

void Workstation::runProcess(std::ostream& os) {
	if (!m_orders.empty()) {
		m_orders.front().fillItem(*this, os);
	}
}

bool Workstation::moveOrder() {
	bool moved = false;
	if (!m_orders.empty()) {
		if (m_pNextStation != nullptr &&
			m_orders.front().isItemFilled(this->getItemName())) {
			//*(Workstation*)m_pNextStation += std::move(m_orders.front());
			*static_cast<Workstation*>(m_pNextStation) += std::move(m_orders.front());
			m_orders.pop_front();
			moved = true;
		}
	}
	return moved;
}

void Workstation::setNextStation(Station& station) {
	if (station.getQuantity() > 0) {
		m_pNextStation = &station; //casting station to workstation*
	}
}

const Workstation* Workstation::getNextStation() const {
	return static_cast<Workstation*>(m_pNextStation);
}

bool Workstation::getIfCompleted(CustomerOrder& order) {
	bool complete = false;
	if (!m_orders.empty() && m_orders.front().isOrderFilled()) {
		order = std::move(m_orders.front());
		m_orders.pop_front();
		complete = true;
	}
	return complete;
}

void Workstation::display(std::ostream& os) const {
	os << getItemName() << " --> " <<
		(m_pNextStation != nullptr ? m_pNextStation->getItemName() : "END OF LINE")
		<< std::endl;
}

Workstation& Workstation::operator+=(CustomerOrder&& order) {
	m_orders.push_back(move(order));
	return *this;
}


