/*
Author: Jon Shidal
Purpose: Define full calendar builder class, responsible for building and managing the structure of the calendar
*/
#include "stdafx.h"
#include "FullCalendarBuilder.h"
#include "CalendarComponent.h"
#include "DisplayableEvent.h"	// **
#include "DisplayableDay.h"
#include "DisplayableMonth.h"
#include "DisplayableYear.h"
#include <algorithm>		//**

using namespace std;
//std::multimap<std::string, std::shared_ptr<DisplayableComponent>> DisplayableComponent::eventMap;

void test(std::shared_ptr<DisplayableComponent> cal);
void test(std::shared_ptr<DisplayableComponent> cal) {
	cout << "children of calendar: " << endl;
	for (size_t i = 0; i < cal->children.size(); i++) {
		DisplayableYear* year = dynamic_cast<DisplayableYear*>(cal->children[i].get());
		cout << year->dateInfo.tm_year << endl;
	}
	//cout << "size of year vector: " << cal->children.size() << endl;
	cout << "children of year at index 0: " << endl;
	for (size_t i = 0; i < cal->children[0]->children.size(); i++) {
		DisplayableMonth* month = dynamic_cast<DisplayableMonth*>(cal->children[0]->children[i].get());
		cout << month->dateInfo.tm_mon << endl;
	}
	cout << "children of month at index 0: " << endl;
	for (size_t i = 0; i < cal->children[0]->children[0]->children.size(); i++) {
		DisplayableDay* day = dynamic_cast<DisplayableDay*>(cal->children[0]->children[0]->children[i].get());
		cout << day->dateInfo.tm_mon << " " << day->dateInfo.tm_mday << endl;
	}
}

// you may decide to define this.**
shared_ptr<DisplayableComponent> FullCalendarBuilder::getComponentByDate(shared_ptr<DisplayableComponent> cal, tm d, string granularity) {

	shared_ptr<DisplayableComponent> comp = nullptr;
	if (granularity == "year") {
		comp = cal->children[d.tm_year];
	}
	else if (granularity == "month") {
		comp = cal->children[d.tm_year]->children[d.tm_mon];
	}
	else if (granularity == "day") {
		comp = cal->children[d.tm_year]->children[d.tm_mon]->children[d.tm_mday];
	}
	return comp;
}

shared_ptr<Calendar> FullCalendarBuilder::buildCalendar(string name, size_t years) {
	currentCalendar = make_shared<Calendar>(name, years);
	// construct each year in a recursive way, add each year as a child of the calendar
	for (unsigned int i = 0; i < years; ++i) {
		tm y = currentCalendar->dateInfo;
		y.tm_year += i;
		y.tm_wday = (y.tm_wday + CalendarComponent::DAYSINAYEAR * i) % CalendarComponent::DAYSINAWEEK; // calculate day of the week for first day of the year
		currentCalendar->addComponent(buildYear(y, currentCalendar));
	}
	return currentCalendar;
}

shared_ptr<DisplayableComponent> FullCalendarBuilder::buildYear(std::tm d, std::shared_ptr<DisplayableComponent> p) {
	shared_ptr<DisplayableComponent> y = make_shared<DisplayableYear>(d, p, false);
	// construct each month and add it as a child of the year
	for (unsigned int i = 0; i < CalendarComponent::MONTHS; ++i) {
		d.tm_mon = i;
		y->addComponent(buildMonth(d, y));
		// set week day of first day of the next month
		d.tm_wday = (d.tm_wday + CalendarComponent::days[i]) % CalendarComponent::DAYSINAWEEK;
	}
	return y;
}

shared_ptr<DisplayableComponent> FullCalendarBuilder::buildMonth(std::tm d, std::shared_ptr<DisplayableComponent> p) {
	int index = d.tm_mon;
	shared_ptr<DisplayableComponent> m = make_shared<DisplayableMonth>(d, p, CalendarComponent::months[index], CalendarComponent::days[index]);
	for (int i = 0; i < CalendarComponent::days[index]; ++i) { // for each day in the month
		m->addComponent(buildDay(d, m)); // construct day and add as a child of the month
		++(d.tm_mday); // increment day of the month
		d.tm_wday = (d.tm_wday + 1) % CalendarComponent::DAYSINAWEEK; // increment weekday, reset to 0 if needed
	}
	return m;
}

shared_ptr<DisplayableComponent> FullCalendarBuilder::buildDay(std::tm d, std::shared_ptr<DisplayableComponent> p) {
	shared_ptr<DisplayableComponent> day = make_shared<DisplayableDay>(d, p);
	//CalendarComponent::eventMap;
	//day->addComponent(buildEvent(p, "", d));
	//?? how will this function get the event's name?
	return day;
}

// you may decide to define this.**
// an event that recurs every 7 days and recurs 3 times starting on 1/1/2019 would occur on
// 1/1/2019(original event), 1/8/2019(1st recurrence), 1/15/2019(2nd recurrence), and on 1/22/2019(3rd recurrence).
shared_ptr<DisplayableComponent> FullCalendarBuilder::buildEvent(shared_ptr<DisplayableComponent> cal, string name, tm when/*, int recurrEvery, int recurrFor*/) {
	// CalendarComponent::CalendarComponent(std::tm d, std::shared_ptr<DisplayableComponent> p) : DisplayableComponent(p), dateInfo(d){}
	shared_ptr<DisplayableComponent> e = make_shared<DisplayableEvent>(when, cal, name);
	// add to eventMap
	cal->eventMap.insert(std::pair <std::string, std::shared_ptr<DisplayableComponent>>(name, e));	// previous unresolved external error, solved
	return e;
}

//std::shared_ptr<DisplayableComponent> removeEvent();	//**
std::shared_ptr<DisplayableComponent> FullCalendarBuilder::removeEvent(std::shared_ptr<DisplayableComponent> p, DisplayableEvent* e, std::string name, tm when) {
	typedef multimap<std::string, std::shared_ptr<DisplayableComponent>>::iterator eventItr;
	std::pair<eventItr, eventItr> range = p->eventMap.equal_range(name);
	for (eventItr it = range.first; it != range.second; it++) {
		if (it->second.get() == e) {
			p->eventMap.erase(it);
			break;
		}
	}

	for (size_t i = 0; i < p->children[when.tm_year]->children[when.tm_mon]->children[when.tm_mday]->children.size(); ++i) {
		if (e == p->children[when.tm_year]->children[when.tm_mon]->children[when.tm_mday]->children[i].get()) {
			p->children[when.tm_year]->children[when.tm_mon]->children[when.tm_mday]->children[i] = nullptr;
		}
	}
	return nullptr;
}


