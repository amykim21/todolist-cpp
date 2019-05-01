#pragma once
#include "CalendarComponent.h"	// **
using namespace std;

class DisplayableEvent : public CalendarComponent {
	friend class DisplayableDay;
	friend class ToDoList;
	friend class Task;
	friend class FullCalendarBuilder;
	friend class CalendarInterface;
	friend bool compareEvents(std::shared_ptr<DisplayableComponent> a, std::shared_ptr<DisplayableComponent> b);	//**
protected:
	std::string name;
public:
	DisplayableEvent(std::tm, std::shared_ptr<DisplayableComponent>, std::string n);
	virtual void display() override;
	// Event is leaf, no need to override addComponent()
	//virtual std::shared_ptr<DisplayableComponent> addComponent(std::shared_ptr<DisplayableComponent>);
};