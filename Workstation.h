// Name: Guilherme Matsumoto Tommasini
// Seneca Student ID: 167561182 
// Seneca email: gmatsumoto-tommasini@myseneca.ca
// Date of completion: 2020/11/21
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once

#include "Station.h"
#include "CustomerOrder.h"
#include <queue>
//#include <memory>

using namespace std;

class Workstation : public Station{
	deque<CustomerOrder> m_orders;
	Station* m_pNextStation;//Workstation
public:
	~Workstation();
	Workstation();
	Workstation(const string&);
	Workstation(Workstation&) = delete;
	Workstation(Workstation&&) = delete;
	Workstation& operator=(Workstation&) = delete;
	Workstation& operator=(Workstation&&) = delete;

	void runProcess(std::ostream&);
	bool moveOrder();
	void setNextStation(Station& station);
	const Workstation* getNextStation() const;
	bool getIfCompleted(CustomerOrder& order);
	void display(std::ostream&) const;
	Workstation& operator+=(CustomerOrder&&);
};
