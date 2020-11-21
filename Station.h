// Name: Guilherme Matsumoto Tommasini
// Seneca Student ID: 167561182 
// Seneca email: gmatsumoto-tommasini@myseneca.ca
// Date of completion: 2020/11/11
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include "Utilities.h"


class Station {
	int id{};
	std::string itemName{};
	std::string description{};
	int serialNumber{};
	int quantity{};

	static size_t m_widthField;
	static size_t id_generator;

public:

	~Station();
	Station();
	Station(const std::string);
	const std::string& getItemName() const;
	unsigned int getNextSerialNumber();
	unsigned int getQuantity() const;
	void updateQuantity();
	void display(std::ostream& os, bool full) const;
};

