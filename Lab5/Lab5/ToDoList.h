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
	void prioritizeComponent(unsigned int i);
	void markComplete(unsigned int i);
	std::shared_ptr<DisplayableComponent> addComponent(std::shared_ptr<DisplayableComponent>) override;
protected:
private:
	static ToDoList* inst;
	ToDoList(std::tm d, std::shared_ptr<DisplayableComponent> p);
	//virtual ~ToDoList();

};



//class CompleteTask : public Task {
//public:
//	CompleteDecorator(std::shared_ptr<DisplayableComponent> dc);
//	void display() override;
//};
//
//class PriorityTask : public Task {
//public:
//	PriorityDecorator(std::shared_ptr<DisplayableComponent> dc);
//	void display() override;
//
//};


//class ToDoList : public CalendarComponent {
//	friend class CalendarInterface;
//public:
//	static shared_ptr<ToDoList> instance(std::tm d, std::shared_ptr<DisplayableComponent> p);
//	static void fini();
//	void display() override;
//	void prioritizeComponent(unsigned int i);
//	void markComplete(unsigned int i);
//	std::shared_ptr<DisplayableComponent> addComponent(std::shared_ptr<DisplayableComponent>) override;
//protected:
//	//string name;
//private:
//	static ToDoList* inst;
//	ToDoList(std::tm d, std::shared_ptr<DisplayableComponent> p);
//	//virtual ~ToDoList();
//
//};
//
//class DisplayableComponentDecorator : public CalendarComponent {
//protected:
//	std::shared_ptr<DisplayableComponent> comp;		// component: holds address of obj being decorated
//public:
//	DisplayableComponentDecorator(std::shared_ptr<DisplayableComponent> c);
//	std::shared_ptr<DisplayableComponent> addComponent(std::shared_ptr<DisplayableComponent>) override;
//	std::shared_ptr<DisplayableComponent> getChild(unsigned int) override;
//};
//
//class CompleteDecorator : public DisplayableComponentDecorator {
//public:
//	CompleteDecorator(std::shared_ptr<DisplayableComponent> dc);
//	void display() override;
//};
//
//class PriorityDecorator : public DisplayableComponentDecorator {
//public:
//	PriorityDecorator(std::shared_ptr<DisplayableComponent> dc);
//	void display() override;
//
//};
