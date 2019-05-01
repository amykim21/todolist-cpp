#include "stdafx.h"
#include "DisplayableEvent.h"

DisplayableEvent::DisplayableEvent(std::tm d, std::shared_ptr<DisplayableComponent> p, string n)
	: CalendarComponent(d, p), name(n) {}

void DisplayableEvent::display() {
	//** need revision
	//cout << "\t" << dateInfo.tm_hour << " at " << dateInfo.tm_min << ": " << name << endl;
	//cout << dateInfo.tm_mon + 1 << "/" << dateInfo.tm_mday << "/" << dateInfo.tm_year + CalendarComponent::BASEYEAR << endl;
	cout << "\t\t" << daysoftheweek[dateInfo.tm_wday] << " " << dateInfo.tm_mon + 1 << "/" << dateInfo.tm_mday + 1 << "/" << dateInfo.tm_year + 119 + CalendarComponent::BASEYEAR << endl;
	cout << "\t\t" << dateInfo.tm_hour << ":" << dateInfo.tm_min << " " << name << endl;

}
