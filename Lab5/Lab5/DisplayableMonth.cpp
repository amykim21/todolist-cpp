#include "stdafx.h"
#include "DisplayableMonth.h"
#include "DisplayableDay.h"
#include <iostream>
#include <iomanip>

using namespace std;

DisplayableMonth::DisplayableMonth(std::tm d, std::shared_ptr<DisplayableComponent> p, string monthname, unsigned int numdays) 
	: CalendarComponent(d, p), name(monthname), numberOfDays(numdays) {
	// initialize children vector, one spot for each day
	for (size_t i = 0; i < numberOfDays; ++i) {
		children.push_back(nullptr);
	}
}

void DisplayableMonth::display() {
	cout << name << ":" << endl;
	cout << std::left << setw(11) << "Sunday"  << setw(11) << "Monday" << setw(11) << "Tuesday" << setw(11) << "Wednesday" << setw(11) <<
		"Thursday" << setw(11) << "Friday" << setw(11) << "Saturday" << endl;
	for (size_t i = 0; i < children.size(); ++i) {
		if (children[i] != nullptr) {
			DisplayableDay* day = dynamic_cast<DisplayableDay*>(children[i].get());
			if (i == 0) {
				for (int t = 0; t < day->dateInfo.tm_wday; ++t) {
					cout << setw(11) << " ";
				}
			}
			string str = to_string(day->dateInfo.tm_mday);
			//cout << setw(11) << day->dateInfo.tm_mday;
			for (int p = 0; p < day->children.size(); ++p) {
				str = str + "*";
			}
			cout << setw(11) << str;
			if (day->dateInfo.tm_wday == 6) {
				cout << endl;
			}
		}
	}
	cout << endl;

	//for (size_t i = 0; i < children.size(); ++i) {
	//	if (children[i] != nullptr) { // forward request to all children
	//		children[i]->display();
	//	}
	//}
}

shared_ptr<DisplayableComponent> DisplayableMonth::addComponent(shared_ptr<DisplayableComponent> comp) {
	// try to dynamically cast comp to a pointer to a DisplayableDay, will fail if the DisplayableComponent is not a day
	DisplayableDay* d = dynamic_cast<DisplayableDay *>(comp.get()); // can only cast regular pointers, not shared_ptrs
	if (d == nullptr) { // the cast failed
		return nullptr;
	}
	// otherwise, add the day to the correct location
	int dayOfMonth = d->dateInfo.tm_mday - 1;
	if (children[dayOfMonth] == nullptr) { // day does not already exist
		children[dayOfMonth] = comp;
		return comp;
	}
	else {  // day already exist, return existing day
		return children[dayOfMonth];
	}
}