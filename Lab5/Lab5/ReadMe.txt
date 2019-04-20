========================================================================
    CONSOLE APPLICATION : Lab5 Project Overview
========================================================================

Lab 5 Readme.

Group members: None


// answer the following questions
1. Part 2.1: Adding events to the calendar
Think about the separation of concerns in the project. 
What class/classes is responsible for the user interface of the Calendar?


What class/classes is responsible for managing the representation and construction of the Calendar?


Which class should handle collecting information from the user about an event?


Which class should handle constructing and adding the event to the Calendar?




2. Part 2.2 Make the calendar interactive
How did you decide to efficiently search for an event by name?



Which object in the project understands the structure of the Calendar? Which object should be responsible for jumping to a specific object in the Calendar?



How did you design saving/restoring the calendar to/from a file? What information needs to be saved about a Calendar to successfully restore it?





3. Part 2.3 Updating the display
How a particular component in the calendar should be displayed depends on what the current display of the calendar is.
How did you implement this functionality? 







Did you make any changes to the interfaces provided in the starter code? If so, how easy was it to 
refactor the code to match this change? 





How does your implementation maintain flexibility and extensibility of the project? Compare this with other designs you considered.







Part 3 (only answer the questions pertaining to the functionality you chose to implement)
3.1: Merging calendars
Describe the benefits of the Decorator pattern? If you used the decorator pattern, how was it applied to 
support merging calendars?






If you chose not to use the decorator pattern, how does your design compare with it when 
considering flexibility and extensibility of the design? 







3.2 ToDo List
Describe your implementation? How does it support easy extensibility of the project in the future?
How is the singleton pattern used to enforce only a sigle TODO list instance?








3.3 Incremental Builder
What challenges did you run into while implementing this? Were any changes to the builder interface required? 
How does using the builder pattern contribute to easily being able to change how an object(calendar in this case)
is represented?

/////////////////////////////////////////////////////////////////////////////
