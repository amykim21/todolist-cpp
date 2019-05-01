#include "stdafx.h"
#include "DisplayableDay.h"
#include <iostream>

using namespace std;

DisplayableDay::DisplayableDay(std::tm d, std::shared_ptr<DisplayableComponent> p) : CalendarComponent(d, p) { }

void DisplayableDay::display() {
	cout << "\t\t\t" << daysoftheweek[dateInfo.tm_wday] << " ";
	cout << dateInfo.tm_mon + 1 << "/" << dateInfo.tm_mday << "/" << dateInfo.tm_year + CalendarComponent::BASEYEAR << endl;
}

std::shared_ptr<DisplayableComponent> DisplayableDay::addComponent(std::shared_ptr<DisplayableComponent> comp) {

}
