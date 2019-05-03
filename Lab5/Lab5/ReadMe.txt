========================================================================
    CONSOLE APPLICATION : Lab5 Project Overview
========================================================================

Lab 5 Readme.

Group members: None


// answer the following questions
1. Part 2.1: Adding events to the calendar
Think about the separation of concerns in the project. 
What class/classes is responsible for the user interface of the Calendar?
CalendarInterface

What class/classes is responsible for managing the representation and construction of the Calendar?
CalendarBuilder declares the interface, and FullCalendarBuilder is a concrete class defining that interface.

Which class should handle collecting information from the user about an event?
CalendarInterface

Which class should handle constructing and adding the event to the Calendar?
FullCalendarBuilder



2. Part 2.2 Make the calendar interactive
How did you decide to efficiently search for an event by name?
I made a multimap called eventMap in CalendarComponent.  Every time I build an event, I add it into eventMap.  Since multimaps can
contain multiple pairs of the same key, eventMap can contain events with the same name; thus eventMap supports recurring events.
I used multimap's equal_range function to find all the pairs in multimap whose key matched the name the user searched for.
Then I prompted the user to choose which of the matches she wanted to scope into.

Which object in the project understands the structure of the Calendar? Which object should be responsible for jumping to a specific object in the Calendar?
currentDisplay, which is a shared pointer to DisplayableComponent, is responsible for jumping to a specific object in the Calendar.
It is possible to set currentDisplay equal to any of the classes that inherit from DisplayableComponent, which lets us
easily keep track of the display the user is looking at.


How did you design saving/restoring the calendar to/from a file? What information needs to be saved about a Calendar to successfully restore it?
I saved the calendar name, number of years, and the name/year index/month index/day index/hour/minute of each event.
They are the parameters needed for builder to replicate the Calendar the user saved.
The first input I take in from the txt file are saved as information about the calendar, and then I take in event input until 
there are no lines left.


3. Part 2.3 Updating the display
How a particular component in the calendar should be displayed depends on what the current display of the calendar is.
How did you implement this functionality? 
I wrote overriden functions for each DisplayableComponent which called display() on its children of its choice.  For example,
DisplayableYear calls display() on its events that are way down the hierarchy using the children vector.
If currentDisplay is a year, I call DisplayableYear::display() on it and it displays accordingly.



Did you make any changes to the interfaces provided in the starter code? If so, how easy was it to 
refactor the code to match this change? 
I made some classes friends of DisplayableComponent and imported every Displayable  Year/Month/Day/Event into CalendarInterface.cpp.
Otherwise, I didn't stray much from the starter code, so it was easy to refactor the code to match my changes.
I also made a stand-alone function called compareEvents to use to sort my vector of events.  I made it a friend of various classes
so that it could access information such as dateInfo.



How does your implementation maintain flexibility and extensibility of the project? Compare this with other designs you considered.
My implementation can add more DisplayableComponents (for example, DisplayableTime) by making it inherit from DisplayableComponent
and be a child of DisplayableEvent.  This composite pattern is different from a hierarchical pattern in which DisplayableEvent
inherits from DisplayableDay, DisplayableDay inherits from DisplayableMonth, etc.  The former pattern is more flexible because
I can maintain a single variable currentDisplay which can switch back and forth between DisplayableComponents.




Part 3 (only answer the questions pertaining to the functionality you chose to implement)
3.1: Merging calendars
Describe the benefits of the Decorator pattern? If you used the decorator pattern, how was it applied to 
support merging calendars?
x





If you chose not to use the decorator pattern, how does your design compare with it when 
considering flexibility and extensibility of the design? 
x





3.2 ** ToDo List ** (I only implemented the ToDo List)
Describe your implementation? How does it support easy extensibility of the project in the future?
How is the singleton pattern used to enforce only a sigle TODO list instance?

I have a Task class and a ToDoList class, both of which inherit from CalendarComponent.  In this way, my Todolist and task can access
dates saved in dateInfo.  I also wrote overriden display() for Todolist, which calls the overriden display() for task.
If I wanted to add something to my Todolist, for example a Memo, I can just make it inherit from ToDoList and write a
display() function for it.  Then I would make Todolist's display() call Memo's display().  
I have an inst variable and an instance() method which constructs the object only if inst = 0.  Once the object is constructed, inst is set
to something else.  I also have a fini() which destructs the object and sets inst to 0.  This ensures that there is only one
ToDoList object constructed.







3.3 Incremental Builder
What challenges did you run into while implementing this? Were any changes to the builder interface required? 
How does using the builder pattern contribute to easily being able to change how an object(calendar in this case)
is represented?
x
/////////////////////////////////////////////////////////////////////////////
