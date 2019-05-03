#include "stdafx.h"
#include "CalendarInterface.h"
#include "FullCalendarBuilder.h"
#include "DisplayableEvent.h" //**
#include "DisplayableDay.h" //**
#include "DisplayableMonth.h" //**
#include "DisplayableYear.h" //**
#include "Calendar.h"	//**
#include "ToDoList.h"	//**
#include "Task.h"	//**
#include "utilityfunctions.h"	//**
#include<iostream>
#include <fstream>	//**
#include <sstream>	//**

using namespace std;

CalendarInterface::CalendarInterface(std::string builderType, std::string calendarName, size_t years) : builder(nullptr),cal(nullptr),currentDisplay(nullptr) {
	if (builderType == "full") {
		builder = make_shared<FullCalendarBuilder>();
		cal = builder->buildCalendar(calendarName, years);
		currentDisplay = cal;
	}
}

void CalendarInterface::run() {
	// run until the user quits
	while (1) {
		// display the current display of the calendar
		currentDisplay->display();

		cout << "create new Event: create, search for Event: search, jump to specific date: jump" << endl;
		cout << "save calendar to file : save, restore calendar from file : restore" << endl;
		cout << "edit Event: edit, add To-Do List: todolist" << endl;
		// display options to the user and respond to user input accordingly
		cout << "zoom out: out, zoom in: in, quit: q" << endl << endl;
		string in;
		cin >> in;

		if (in == "create") {
			cout << "Enter name of the event:" << endl;
			string name;
			cin >> name;
			cout << "Enter the year:" << endl;
			std::tm date;
			date.tm_wday = 0;
			date.tm_sec = 0;
			date.tm_yday = 0;
			cin >> date.tm_year;
			cout << "Enter the month:" << endl;
			cal->children[date.tm_year]->display();
			cin >> date.tm_mon;

			cout << "Enter the date:" << endl;
			for (size_t i = 0; i < cal->children[date.tm_year]->children[date.tm_mon]->children.size(); ++i) {
				DisplayableDay* day = dynamic_cast<DisplayableDay*>(cal->children[date.tm_year]->children[date.tm_mon]->children[i].get());
				cout << to_string(i) << ": " << day->dateInfo.tm_mday << endl;
			}
			cin >> date.tm_mday;		
			cout << "Enter <hour> <minute>:" << endl;
			cin >> date.tm_hour >> date.tm_min;
			cout << "Enter <number of days between recurrences> <number of times the event recurs>" << endl;
			int recurEvery, recurFor;
			cin >> recurEvery >> recurFor;
			recurFor++;		// to account for original event
			for (size_t i = 0; i < recurFor; ++i) {
				cal->children[date.tm_year]->children[date.tm_mon]->children[date.tm_mday]->addComponent(builder->buildEvent(cal, name, date));
				currentDisplay = cal;
				date.tm_mday += recurEvery;		//**doesn't account for events that may recur outside of month, possible source of nullptr
			}
			//??how to use addDays
			//for (size_t i = 0; i < recurFor; ++i) {
			//	std::tm temp = dynamic_cast<DisplayableDay*>(cal->children[date.tm_year]->children[date.tm_mon]->children[date.tm_mday].get())->dateInfo;
			//	cal->children[temp.tm_year]->children[temp.tm_mon]->children[temp.tm_mday]->addComponent(builder->buildEvent(cal, name, temp));
			//	currentDisplay = cal;
			//	// tm addDays(tm current, int numDays)
			//	temp = addDays(temp, recurEvery);
			//	date.tm_mday += recurEvery;		//**doesn't account for events that may recur outside of month, possible source of nullptr
			//}			

		}
		else if (in == "search") {
			// multimap.find() returns multimap.end() if it can't find specified key
			cout << "What event would you like to search for?" << endl;
			string eventSearch;
			cin >> eventSearch;
			typedef multimap<std::string, std::shared_ptr<DisplayableComponent>>::iterator eventItr;// = CalendarComponent::eventMap.find(eventSearch);
			std::pair<eventItr, eventItr> range = cal->eventMap.equal_range(eventSearch);
			// if key doesn't exist
			int eventsFound = std::distance(range.first, range.second);
			if (eventsFound == 0) {
				cout << "The event does not exist." << endl;
			}
			else if (eventsFound == 1) {
				currentDisplay = range.first->second;
			}
			else {
				int i = 0;
				for (eventItr it = range.first; it != range.second; it++) {
					cout << to_string(i) << ": ";
					it->second->display();
					cout << endl;
					i++;
				}
				cout << "Choose one event: " << endl;
				cin >> i;
				eventItr userChoice = range.first;
				for (size_t k = 0; k < i; k++) {
					userChoice++;
				}
				currentDisplay = userChoice->second;
			}
		}
		else if (in == "jump") {
			cout << "Enter the year:" << endl;
			std::tm date;
			date.tm_wday = 0;
			date.tm_sec = 0;
			date.tm_yday = 0;
			cin >> date.tm_year;
			cout << "Enter the month:" << endl;
			// display year, which displays months
			cal->children[date.tm_year]->display();
			cin >> date.tm_mon;
			cout << "Enter the date:" << endl;
			for (size_t i = 0; i < cal->children[date.tm_year]->children[date.tm_mon]->children.size(); ++i) {
				DisplayableDay* day = dynamic_cast<DisplayableDay*>(cal->children[date.tm_year]->children[date.tm_mon]->children[i].get());
				cout << to_string(i) << ": " << day->dateInfo.tm_mday << endl;
			}
			cin >> date.tm_mday;
			cout << "Enter the granularity: year, month, or day" << endl;
			string granularity;
			cin >> granularity;
			if (builder->getComponentByDate(cal, date, granularity) == nullptr) {
				cout << "The date you specified does not exist." << endl;
			}
			else {
				currentDisplay = builder->getComponentByDate(cal, date, granularity);
			}
		}
		else if (in == "save") {
			ofstream ofs;
			ofs.open("Calendar.txt");
			if (ofs.is_open()) {
				ofs << cal->name << "\n" << cal->yearsToHold << "\n";// first line is name of calendar
																	// second line is number of years calendar contains
				// disregard builder type for now
				// all lines onward contain event information
				multimap<std::string, std::shared_ptr<DisplayableComponent>>::iterator eventItr;
				for (eventItr = cal->eventMap.begin(); eventItr != cal->eventMap.end(); eventItr++) {
					ofs << eventItr->first << "\n";
					DisplayableEvent* e = dynamic_cast<DisplayableEvent*>(eventItr->second.get());
					ofs << e->dateInfo.tm_year << "\n" << e->dateInfo.tm_mon << "\n" << e->dateInfo.tm_mday << "\n"
						<< e->dateInfo.tm_hour << "\n" << e->dateInfo.tm_min << "\n";

				}

			}
			ofs.close();
		}
		else if (in == "restore") {
			ifstream ifs;
			string calName;
			int y;
			std::tm date;
			date.tm_wday = 0;
			date.tm_sec = 0;
			date.tm_yday = 0;
			ifs.open("Calendar.txt");
			if (ifs.is_open()) {
				ifs >> calName;
				ifs >> y;
			}
			cal = builder->buildCalendar(calName, y);	//**buildCalendar only goes to buildDay()
			currentDisplay = cal;
			cal->eventMap.clear();	// clear multimap
			string eventName;
			while (ifs >> eventName >> date.tm_year >> date.tm_mon >> date.tm_mday >> date.tm_hour >> date.tm_min) {
				cal->children[date.tm_year]->children[date.tm_mon]->children[date.tm_mday]->addComponent(builder->buildEvent(cal, eventName, date));
			}
			currentDisplay = cal;
			ifs.close();
		}
		else if (in == "edit") {
			// **for local option use
			DisplayableEvent* e = dynamic_cast<DisplayableEvent*>(currentDisplay.get());
			
			if (e == nullptr) {
				cout << "You need to be in an Event to edit an event" << endl;
			}
			else {
				cout << "Delete: delete, Change date: change" << endl;
				string str;
				cin >> str;
				if (str == "delete") {
					shared_ptr<DisplayableComponent> temp = currentDisplay->getParent().lock();
					std::vector<std::shared_ptr<DisplayableComponent>>::iterator it = std::find(temp->children.begin(), temp->children.end(), currentDisplay);
					//cal->children[day->dateInfo.tm_year]->children[day->dateInfo.tm_mon]->children[day->dateInfo.tm_mday]->children[std::distance(temp->children.begin(), it)] = nullptr;
					//std::multimap<std::string, std::shared_ptr<DisplayableComponent>>::iterator erase;
					//for (std::multimap<std::string, shared_ptr<DisplayableComponent>>::iterator it = cal->eventMap.begin(); it != cal->eventMap.end(); ++it)
					//{
					//	if (it->second == currentDisplay) {
					//		//erase = it;
					//		printf("found\n");
					//		cal->eventMap.erase(it);
					//	}
					//}

					builder->removeEvent(cal, e, e->name, e->dateInfo);
					zoomOut();
				}
				else if (str == "change") {
					cout << "What date would you like to move this event to?" << endl;
				}
			}
			currentDisplay = cal;
		}
		else if (in == "todolist") {
			todolist();
			//currentDisplay = tdl;
		}

		else if (in == "in") {
			if (currentDisplay->children.size() > 0) {
				cout << "index? (0-" << currentDisplay->children.size() - 1 << ")" << endl;
				int index = 0;
				cin >> index;
				zoomIn(index);
			}
			else {
				cout << "Nothing to zoom in on" << endl;
			}
		}
		else if (in == "out") {
			zoomOut();
		}
		else if (in == "q") {
			break;
		}
	}
}

void CalendarInterface::zoomIn(unsigned int index) {
	shared_ptr<DisplayableComponent> temp = currentDisplay->getChild(index);
	// if the child exists, update the current display to the child. Otherwise, the current view remains the same
	if (temp != nullptr) {
		currentDisplay = temp;
	}
}
 
void CalendarInterface::zoomOut() {
    // if the current display has a parent, update current display to the parent
	if (currentDisplay->getParent().lock() != nullptr) {
		// create a shared_ptr from a weak_ptr, contributing to the objects reference count
		currentDisplay = currentDisplay->getParent().lock();
	}
}

void CalendarInterface::todolist() {
	cout << "TODO List:" << endl;
	std::shared_ptr<ToDoList> tdl = ToDoList::instance(cal->dateInfo, cal);
	tdl->display();
	cout << "add task: add, mark a task complete: complete, go back to calendar: calendar" << endl;
	string str = "";
	cin >> str;
	//while (str != "calendar") {
	//cout << "add task: add, mark a task complete: complete, go back to calendar: calendar" << endl;
	if (str == "add") {
		cout << "what is the name of the task you want to add?" << endl;
		string taskName;
		cin >> taskName;
		std::shared_ptr<DisplayableComponent> task = make_shared<Task>(cal->dateInfo, cal, taskName);
		tdl->addComponent(task);
	}
	else if (str == "complete") {
		cout << "which event would you like to mark complete?" << endl;
		int i;
		cin >> i;
		tdl->markComplete(i);
		//tdl->display();
		//typedef multimap<std::string, std::shared_ptr<DisplayableComponent>>::iterator eventItr;// = CalendarComponent::eventMap.find(eventSearch);
		////std::pair<eventItr, eventItr> range = CalendarComponent::eventMap.equal_range(eventSearch);
		////int eventsFound = std::distance(range.first, range.second);
		//eventItr userChoice = range.first;
		//for (size_t k = 0; k < i; k++) {
		//	userChoice++;
		//}
		//CalendarComponent::eventMap
		//currentDisplay = userChoice->second;


	}
	tdl->display();
	ToDoList::fini();
}