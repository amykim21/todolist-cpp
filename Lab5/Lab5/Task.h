#pragma once
#include "CalendarComponent.h"
using namespace std;

// ToDoList maintains children of Tasks
class Task : public CalendarComponent {
public:
	//std::shared_ptr<DisplayableComponent> addComponent(std::shared_ptr<DisplayableComponent>) override;	// leaf class, no need to override
	Task(std::tm d, std::shared_ptr<DisplayableComponent> p, std::string name);
	//string name;
	void display() override;
	//void display();
	void setComplete();
protected:
	bool complete;
	string taskName;
	std::tm taskInfo;
private:

};