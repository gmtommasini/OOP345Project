// Name: Guilherme Matsumoto Tommasini
// Seneca Student ID: 167561182 
// Seneca email: gmatsumoto-tommasini@myseneca.ca
// Date of completion: 2020/11/24
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "LineManager.h"
#include <algorithm>
#include <fstream>

using namespace std;

LineManager::~LineManager() {}
LineManager::LineManager() { initialStation = nullptr; }
LineManager::LineManager(const string& filename, vector<Workstation*>& workstations, vector<CustomerOrder>& orders) {
	std::ifstream file(filename);
	size_t pos = 0;
	bool more = true;
	Utilities ut;
	std::string current, next, line;
	if (!file) {
		throw std::string("Unable to open [") + filename + "] file.";
	}
	bool firstTime = true; //for first station in the line
	while (file) {		//if getline fails, it breaks the while loop
		std::getline(file, line);
		try {
			current = ut.extractToken(line, pos, more);
			if (more) {
				next = ut.extractToken(line, pos, more);
				for (auto station1 : workstations) {
					if (station1->getItemName() == current) {
						for (auto station2 : workstations) {
							if (station2->getItemName() == next) {
								station1->setNextStation(*station2);
								if (firstTime) {
									firstTime = false;
									initialStation = station1;
								}
								break; //break the inner for loop
							}
						}
					}
				}
			}
		}
		catch (...) {
			throw "Error reading stations order.";
		}
	}
	file.close();

	//Copy all the Workstation objects into the AssemblyLine container
	AssemblyLine = workstations;

	//Move all the CustomerOrder objects onto the back of the ToBeFilled queue
	std::for_each(
		orders.begin(),
		orders.end(),
		[&](CustomerOrder& ord) {
			ToBeFilled.push_back(move(ord));
			m_cntCustomerOrder++;
		}
	);
}

bool LineManager::run(std::ostream& os) {
	static size_t counter = 1;
	os << "Line Manager Iteration: " << counter++ << std::endl;
	if (!ToBeFilled.empty()) {
		*initialStation += move(ToBeFilled.front());
		ToBeFilled.pop_front();
	}
	for (auto station : AssemblyLine) {
		station->runProcess(os);
	}
	for (auto station : AssemblyLine) {
		station->moveOrder();
	}

	CustomerOrder temp;
	for (auto station : AssemblyLine) {
		if (station->getIfCompleted(temp)) {
			Completed.push_back(std::move(temp));
		}
	}
	return Completed.size() == m_cntCustomerOrder;
}

void LineManager::displayCompletedOrders(std::ostream& os) const {
	for (auto& order : Completed) {
		order.display(os);
	}
}

void LineManager::displayStations() const {
	for (auto station : AssemblyLine) {
		station->display(cout);
	}
}

void LineManager::displayStationsSorted() const {
	const Workstation* workStationPointer = initialStation;
	while (workStationPointer) { //the last station in the line has a nullptr
		workStationPointer->display(cout);
		workStationPointer = workStationPointer->getNextStation();
	}
}
