#include "stdafx.h"
#include "Task.h"

Task::Task(std::tm d, std::shared_ptr<DisplayableComponent> p, std::string name) : CalendarComponent(d, p) {
	complete = false;
	taskName = name;
	taskInfo = d;
}

void Task::setComplete() {
	complete = true;
}

void Task::display() {
	cout << "\t" << taskName << " " << taskInfo.tm_mon + 1 << "/" << taskInfo.tm_mday + 1 << "/" << taskInfo.tm_year + 119 + CalendarComponent::BASEYEAR
		<< " " << taskInfo.tm_hour << ":" << taskInfo.tm_min;
	if (complete) {
		cout << " COMPLETE" << endl;
	}
	else {
		cout << " TODO" << endl;
	}
}
