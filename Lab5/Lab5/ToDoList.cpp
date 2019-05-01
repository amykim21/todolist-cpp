#include "stdafx.h"
#include "ToDoList.h"
#include "Task.h"



ToDoList* ToDoList::inst = 0;
ToDoList::ToDoList(std::tm d, std::shared_ptr<DisplayableComponent> p): CalendarComponent(d, p) {}

shared_ptr<ToDoList> ToDoList::instance(std::tm d, std::shared_ptr<DisplayableComponent> p) {
	if (inst == 0) {
		//std::tm empty;
		inst = new ToDoList(d, p);	//?? how to make DisplayableComponent to pass into constructor?
		// push all events into children
		//for (multimap<std::string, std::shared_ptr<DisplayableComponent>>::iterator it = eventMap.begin(); it != eventMap.end(); ++it) {
		//	inst->children.push_back(it->second);
		//}
		shared_ptr<ToDoList> tdl(inst);
		return tdl;
	}
	return nullptr;
}

void ToDoList::display() {
	multimap<std::string, std::shared_ptr<DisplayableComponent>>::iterator eventItr;
	int i = 0;
	for (eventItr = CalendarComponent::eventMap.begin(); eventItr != CalendarComponent::eventMap.end(); eventItr++) {
		//cout << eventItr->first;
		DisplayableEvent* e = dynamic_cast<DisplayableEvent*>(eventItr->second.get());
		Task* t = new Task(e->dateInfo, nullptr, e->name);
		cout << to_string(i) << ": ";
		t->display();
		i++;
		//ofs << e->dateInfo.tm_year << "\n" << e->dateInfo.tm_mon << "\n" << e->dateInfo.tm_mday << "\n"
		//	<< e->dateInfo.tm_hour << "\n" << e->dateInfo.tm_min << "\n";
	}
	//CalendarComponent::eventMap;
}

std::shared_ptr<DisplayableComponent> ToDoList::addComponent(std::shared_ptr<DisplayableComponent> comp) {
	DisplayableEvent* e = dynamic_cast<DisplayableEvent*>(comp.get());
	if (e != nullptr) {
		shared_ptr<DisplayableComponent> t = make_shared<Task>(e->dateInfo, nullptr, e->name);
		children.push_back(t);
		// sort this children vector of tasks
		return t;
	}
	return nullptr;
}

void ToDoList::prioritizeComponent(unsigned int i) {

}

void ToDoList::markComplete(unsigned int i) {

}

void ToDoList::fini() {
	delete inst;
	inst = 0;
}
//ToDoList::~ToDoList() {
//
//}
//
//DisplayableComponentDecorator::DisplayableComponentDecorator(std::shared_ptr<DisplayableComponent> c): CalendarComponent(c), comp(c) {
//	//comp = c;
//}
//
////std::shared_ptr<DisplayableComponent> DisplayableComponentDecorator::addComponent(std::shared_ptr<DisplayableComponent> c) {
////	comp->addComponent(c);
////}
//
//CompleteDecorator::CompleteDecorator(std::shared_ptr<DisplayableComponent> dc) : DisplayableComponentDecorator(dc) {}
//
//void CompleteDecorator::display() {
//	comp->display();
//	cout << "  COMPLETE" << endl;
//}
//
//PriorityDecorator::PriorityDecorator(std::shared_ptr<DisplayableComponent> dc) : DisplayableComponentDecorator(dc) {}
//
//void PriorityDecorator::display() {
//	comp->display();
//	cout << "  TODO" << endl;
//}
//
