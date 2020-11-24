// Name: Guilherme Matsumoto Tommasini
// Seneca Student ID: 167561182 
// Seneca email: gmatsumoto-tommasini@myseneca.ca
// Date of completion: 2020/11/23
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once

#include <vector>
#include <deque>
#include "Workstation.h"

using namespace std;

class LineManager {
	vector<Workstation*> AssemblyLine;// – A container containing all the references of the Workstation objects on the assembly line
	deque<CustomerOrder> ToBeFilled;//– A queue of customer orders to be filled
	deque<CustomerOrder> Completed;// – A queue of customer orders completed
	unsigned int m_cntCustomerOrder{ 0 };// – The number of CustomerOrder objects the assembly line started with.

	Workstation* initialStation = nullptr; // A pointer to the first station in the line (NOT AssemblyLine[0])

public:
	~LineManager();
	LineManager();
	LineManager(const string&, vector<Workstation*>&, vector<CustomerOrder>&);
	
	bool run(std::ostream& os);
	void displayCompletedOrders(std::ostream& os) const;
	void displayStations() const;
	void displayStationsSorted() const;



};
