#include "stdafx.h"
#include "DisplayableYear.h"
#include <iostream>
#include "DisplayableMonth.h"
#include "DisplayableDay.h"  // **
#include "DisplayableEvent.h"  // **

using namespace std;

DisplayableYear::DisplayableYear(std::tm d, std::shared_ptr<DisplayableComponent> p, bool l) : CalendarComponent(d, p), leap(l) {
	for (size_t i = 0; i < CalendarComponent::MONTHS; ++i) {
		children.push_back(nullptr);
	}
}

void DisplayableYear::display() {
	cout << "Year " << dateInfo.tm_year + CalendarComponent::BASEYEAR << ":" << endl;
	for (size_t i = 0; i < children.size(); ++i) {
		if (children[i] != nullptr) {
			DisplayableMonth* month = dynamic_cast<DisplayableMonth*>(children[i].get());
			cout << "\t" << to_string(i) << ": " << months[month->dateInfo.tm_mon] << endl;
			// forward request to event in month
			for (size_t j = 0; j < month->children.size(); ++j) {
				if (month->children[j] != nullptr) {
					DisplayableDay* day = dynamic_cast<DisplayableDay*>(month->children[j].get());
					for (size_t k = 0; k < day->children.size(); ++k) {
						if (day->children[k] != nullptr) {
							DisplayableEvent* event = dynamic_cast<DisplayableEvent*>(day->children[k].get());
							event->display();
						}
					}
				}
			}
		}
	}
	//**
	//for (size_t i = 0; i < children.size(); ++i) { // forward request to all children
	//	if (children[i] != nullptr) {
	//		children[i]->display();
	//	}
	//}
}

shared_ptr<DisplayableComponent> DisplayableYear::addComponent(shared_ptr<DisplayableComponent> comp) {
	// try to dynamically cast comp to a pointer to a DisplayableMonth
	DisplayableMonth * m = dynamic_cast<DisplayableMonth *>(comp.get());
	if (m == nullptr) { // if the cast fails, return nullptr
		return nullptr;
	}
	// otherwise, add the month to the correct location
	int monthOfYear = m->dateInfo.tm_mon;
	if (children[monthOfYear] == nullptr) { // month does not already exist
		children[monthOfYear] = comp;
		return comp;
	}
	else {  // month already exist, return existing month
		return children[monthOfYear];
	}
}
