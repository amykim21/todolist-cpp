#pragma once
#include "CalendarComponent.h"
#include "CalendarInterface.h"
#include <string>

using namespace std;

class ToDoList : public CalendarComponent {
public:
	static shared_ptr<ToDoList> instance(std::tm d, std::shared_ptr<DisplayableComponent> p);
	static void fini();
	void display() override;
	void markComplete(unsigned int i);
	std::shared_ptr<DisplayableComponent> addComponent(std::shared_ptr<DisplayableComponent>) override;
protected:
private:
	static ToDoList* inst;
	ToDoList(std::tm d, std::shared_ptr<DisplayableComponent> p);
	//virtual ~ToDoList();

};

