#include "stdafx.h"
#include "DisplayableDay.h"
#include "DisplayableEvent.h"	//**
#include <iostream>


using namespace std;

DisplayableDay::DisplayableDay(std::tm d, std::shared_ptr<DisplayableComponent> p) : CalendarComponent(d, p) {}

bool compareEvents(std::shared_ptr<DisplayableComponent> a, std::shared_ptr<DisplayableComponent> b);
bool compareEvents(std::shared_ptr<DisplayableComponent> a, std::shared_ptr<DisplayableComponent> b) {
	bool a_before_b = false;
	// only need to look at hour and minute
	// if hour and minute is bigger, it goes later
	// cast a, b to DisplayableEvents
	DisplayableEvent* a_e = dynamic_cast<DisplayableEvent*>(a.get());
	DisplayableEvent* b_e = dynamic_cast<DisplayableEvent*>(b.get());
	if (b_e->dateInfo.tm_hour > a_e->dateInfo.tm_hour) {
		a_before_b = true;
	}
	else if (b_e->dateInfo.tm_hour == a_e->dateInfo.tm_hour) {
		if (b_e->dateInfo.tm_min > a_e->dateInfo.tm_min) {
			a_before_b = true;
		}
	}
	return a_before_b;
}


void DisplayableDay::display() {
	cout << daysoftheweek[dateInfo.tm_wday] << " ";
	cout << dateInfo.tm_mon + 1 << "/" << dateInfo.tm_mday << "/" << dateInfo.tm_year + CalendarComponent::BASEYEAR << endl;
	//**created event doesn't show up
	for (size_t i = 0; i < children.size(); ++i) {
		if (children[i] != nullptr) {
			DisplayableEvent* event = dynamic_cast<DisplayableEvent*>(children[i].get());
			cout << event->dateInfo.tm_hour << ":" << event->dateInfo.tm_min << " " << event->name << endl;
		}
	}

	//for (size_t i = 0; i < children.size(); ++i) {
	//	if (children[i] != nullptr) { // forward request to all children
	//		children[i]->display();
	//	}
	//}
}

// add event to day
std::shared_ptr<DisplayableComponent> DisplayableDay::addComponent(std::shared_ptr<DisplayableComponent> comp) {
	// try to dynamically cast comp to a pointer to a DisplayableEvent, will fail if the DisplayableComponent is not Event
	//vector<std::shared_ptr<DisplayableComponent> > children; (from DisplayableComponent class)
	DisplayableEvent* e = dynamic_cast<DisplayableEvent*>(comp.get());
	if (e == nullptr) {
		return nullptr;
	}
	// otherwise, add event to correct location
	children.push_back(comp);
	sort(children.begin(), children.end(), compareEvents);
	return comp;
}