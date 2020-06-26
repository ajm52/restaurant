# this doc briefly describes classes (i.e. intended functionality, data, related classes, etc)

## people package

##### Person:

- Intended to be used as a base class for Guests and Workers.
- Identified by a unique string.

##### Guest (not currently in use):

- A member of a Party.
- At this point, Guests don't have any place in the simulation, as we are working with empty Parties for the sake of testing.
- May delegate them the role of selecting menu options at some point.

##### Worker:

- A thread-based Restaurant employee (i.e. Bartender, Waiter, Cook).
- Equipped with standard run() and init() methods.
- Workers differ in how they handle specific jobs, which allows their generic workflow to be identical.
- Also comes equipped with a GlobalClock (timestamps are useful in threaded debugging), a JobTable (how Workers take on Jobs), a Menu, and a vector of current Jobs.
- Note that Workers keep their thread as a member variable, making them easy to join() when appropriate.

##### Party:

- A thread-based class that dines in the Restaurant. Intended to eventually contain Guests.
- Interacts directly with Waiters.
- In order for Parties to know where they are sitting, who their Waiter is, and what the Menu looks like, static setter methods are used to restrict Party member data access solely to Waiters. For this to work safely without threat of deadlock, Parties are also equipped with their own mutices, condition variables and service flags, all of which are used by Waiters in the servicing phase.
- Aside from a unique ID string, Parties are also equipped with references to the GlobalClock, Restaurant, and SimMonitor, all of which will be explained later.

##### Doorman:

- A dual thread-based class that plays a key role in getting Parties in and out of the Restaurant.
- The reason for having two threads is that we have two queues, inbound and outbound, each equipped with their own condition variable. When a Party enters the queue for entry/exit, it notifies the Doorman via the appropriate condition variable. While I could've made it work with one thread, using two seemed like a sensible decision.
- The Doorman has references to the Door (obviously), Foyer, JobTable, and GlobalClock.
- Note that the outgoing thread's run() method has yet to be implemented.

##### Waiter:

- A thread-based Worker whose main job is servicing Parties.
- Waiter Jobs include seating Parties, receiving/delivering their Orders, and cleaning newly vacated Tables.
- In addition to protected Worker data, Waiters also have access to the Foyer and restaurant Tables.

##### Bartender:

- A thread-based Worker that is solely responsible for preparing drink Orders.
- Contains no additional data to what Workers have access to.
- Note that while Bartenders (as well as Cooks) will have definitions for all job handlers methods, this is solely to satisfy pure virtuality; the only job handler method that will be used by these classes is to do with Orders. At some point in the near future, I will likely put in some kind of error handler there.

##### Cook (not yet implemented):

- Thread-based Worker, extremely similar to Bartender. We have yet to implement this, as we are still in the midst of working through getting the Order exchange down pat with Bartender.

##### PartyStatus (currently not in use):

- Intended to be used as an easy-to-communicate description of current Party activity. Statuses will come into play later when we are developing the front-end; the idea is to send plaintext status updates through the network, such that object status updates (not just Parties) can be viewed in realtime from a web browser.

## contain package (many of the classes here are not currently in use)

##### Table:

- Where Parties are seated in the Restaurant.
- Each Table comes equipped with an ID number, an occupation flag, and a raw pointer to a Party. We use a raw pointer as the nullptr value is indeed useful, as well as the fact that Tables do not own Parties; Parties are owned by the Simulation, which is where Parties should be created and destroyed.
- Note that this class also has a static accessor method that allows Waiters to seat Parties with relative encapsulation.
- In theory, two Waiters should never have a race condition when dealing with Table data, as SeatingJobs are assigned by the Doorman (no two Waiters can be assigned to the same Table).

##### Door:

- Allows Parties to enter and exit the Restaurant.
- Consists of two Party queues (ingoing/outgoing), two mutices, and a single condition variable. Both Doorman threads wait on this condition variable, so on either an entry or exit, both check their own queues for activity.
- Parties place themselves in the queue, while the Doorman retrieves the Party, picks a Waiter and Table for the Party, places the Party in the Foyer seating map using the Table's numeric ID as the key, and notifies the Waiter.
- There are undoubtable race conditions that can arise here between Parties and the Doorman, hence the need for mutices and a condition variable.

##### Foyer:

- Following entry, Parties are placed here by the Doorman, where they wait to be seated at their Table.
- Data members include a table count, a queue of numeric IDs of Tables that are clean, a map of Parties waiting to be seated that is keyed on Table IDs, and a mutex.
- In retrospect, it seems to make more sense that the Doorman is responsible for handling clean Table IDs. This will likely be changed soon.

##### JobTable:

- The communication medium between job assigners and Workers.
- This class contains a vector of Job queues, where each queue is indexed on a Worker's numeric ID, two maps containing condition variables and mutices that are keyed on Worker numeric IDs, a vector of job flags (one for each Worker), and tallies to track the current number of cooks, waiters, and bartenders.
- A Worker's actual ID is not solely numeric (i.e. a Waiter's ID could be "W-0" or "W-5", a Bartender's ID could be "B-0"). I could have used strings, but I decided to use unsigned integers.
- Worker indices are managed in the following manner: Suppose we have 3 Waiters, 2 Cooks, and 1 Bartender. The Waiters' indices would be [0-2], the Cooks' [3-4], and the Bartender's [5]. In other words, Waiters are indexed first, followed by Cooks, then Bartenders.
- After a Job is assigned to a queue indexed by a specific Worker, that Worker is notified via it's condition variable. At the point of wakeup, Workers check their job queue for Jobs. Flags are used as an extra layer of protection against spurious wakeups and similar mishaps.
- Perhaps we could do away with Worker tallies and key on strings instead. This would reduce information duplication, as Worker tallies are also kept in other classes (i.e. Restaurant, Simulation).

##### Bar (will be implemented soon):

- Contains the restaurant Bartenders.
- As the next item of development is assigning OrderJobs to Bartenders, implementing Bar will happen very soon.

##### Restaurant:

- The main container that houses almost all Simulation activity.
- Includes mostly everything that is necessary to make the program run: the JobTable, Foyer, Door, Menu, Tables, restaurant Workers, a GlobalClock reference, and Worker tallies.
- As previously mentioned, I may look into stripping either this class (or Simulation) of Worker tallies to reduce information duplication. Either way, JobTable should definitely not have to manage those variables.

##### WorkerNode (currently not in use):

- Intended for use as representation of Worker data, consisting of a Worker ID and an active job tally.
- Equipped with several operator overloads for modifying/testing Worker job tallies, as well as printing WorkerNode information.
- May eventually see use in WorkerBulletin, which we will get into later.

##### MinHeap (currently not in use):

- A generic minheap data structure.
- This class will eventually see use in WorkerBulletin, as we will be managing a heap of WorkerNodes.
- While templated data structures are generally most applicable for cases with several possible data inputs (and my use case really only involves WorkerNodes), I wanted to implement MinHeap generically for the sake of getting practice with templates, as I find generic programming to be pretty cool (even though I know very little about it).
- As a result of implementing MinHeap, I also realized that templated structs/classes don't compile unless the source code is written in the header (I'm not sure why this is the case, this is just what I've read on StackOverflow).

##### WorkerBulletin (currently not in use):

- Intended to be used as a way of identifying the "Least Busy Worker" in constant time. It should be noted that this class is a result of premature optimization, hence why it is currently not in use.
- In a busy Restaurant, Party assignments are constantly being made. Assigning all Parties to a single Waiter while all other Waiters do nothing surely does not make sense. How does one assign work such that all Workers are kept busy? WorkerBulletin is the answer to that problem.
- WorkerNodes are heapified on two keys (first on active job count, then on Worker ID). Thus, the Worker with the lowest active job count will be at the top of the heap, allowing for fast and efficient Job assignment. Of course, WorkerBulletin must be heapified whenever the "least busy Worker" is requested; to heapify whenever a change is made (i.e. a Job is finished) would result in unnecessary work, as WorkerBulletin need only be in proper form when a Job assignment occurs.

##### Queue (currently not in use):

- A generic queue data structure.
- Initially I thought it would be fun to implement my own LinkedList-style queue and use that throughout the program. While that sounds fine and dandy, it makes more sense to take advantage of the Standard Library instead of trying to re-create the wheel.
- While I would certainly learn a thing or two by implementing this and integrating it into the program, the central objective must take priority, which is to practice C++ multithreading while minimizing development time.

## job package

##### Order:

- Represents either a drink or food order from the Menu.
- Orders are tagged with a unique Order ID string, an associated table ID, and a vector of MenuEntryKeys in string form that represent Menu selections.
- Menu selections are submitted to OrderService by Parties. From there, OrderService constructs an Order and an associated OrderJob, assigning the Job to the Waiter responsible for that Table.
- This class doesn't exactly belong in the job package; I suppose it should probably go in the menu package.

##### Job:

- An abstract struct that represents work to be done.
- This struct consists solely of a single pure virtual method, `accept(Worker&)`, which is implemented by all Job subclasses. It exists for the sake of implementing the Visitor pattern, or in other words, "double dispatch", a design pattern that conveniently allows multiple types of Entities to perform multiple types of Actions. Worker and Job are both abstract, so this is perfect.

##### SeatingJob:

- A type of Job that is assigned by the Doorman and done by Waiters.
- Contains a single data member, an unsigned integer that identifies a Table at which the waiting Party should be seated.
- As aforementioned, the table ID also allows Waiters to key into the Foyer and grab the corresponding Party requiring service.
- May change the name of this struct to WaitJob, as "waiting a table of guests" is more than simply seating a Party at their Table. If this change would be made, integrating WorkerBulletin would be much more natural, at least for Waiters.

##### OrderJob:

- A type of Job that is assigned to Waiters, Cooks, and Bartenders.
- Consists of a single data member, the associated Order.
- When assigned to a Waiter, the Waiter must deliver said OrderJob to a Cook or Bartender to be properly handled; Bartenders and Cooks are the ones responsible for preparing Orders, notifying the corresponding Waiter via the JobTable when said Order is ready to be served.

## menu package

##### Menu:

- Used by Parties to decide what they should order.
- Consists of a map of MenuEntries keyed on MenuEntryKeys, managed by a custom comparator.

##### MenuEntry:

- A Menu entry. Pretty self-explanatory.
- Each MenuEntry consists of a name and a preparation time; "preparing" an Order is simulated using an asynchronous callback timer.

##### MenuEntryKey:

- Identifies a specific MenuEntry.
- Each MenuEntry has a type (i.e. Food -> 'F', Drink -> 'D') and an unsigned ID number.

##### MenuEntryKeyComparator:

- A custom comparator used by Menu's internal map.
- Exists solely for the purpose of using custom keys (i.e. MenuEntryKey) in the Standard Library's map.

## util package

##### GlobalClock:

- Used exclusively for the sake of generating timestamps for thread-based actions.
- The existence of this class makes threaded console output much more legible, allowing for simpler debugging. Aside from this, it makes perfect sense for a simulation program to be equipped with its own internal clock.
- Timestamps are generated using the overloaded `<< operator`.

##### SimMonitor:

- Can be thought of as the Simulation overseer.
- For now, it's sole purpose is to track Order history and generate Order ID strings. Down the line, SimMonitor could easily be extended to observe Restaurant entities, pushing updates to the front-end when status updates occur.

##### OrderService:

- This class can be thought of as a collection static helper methods intended to ease along program flow.
- For now, the only method in use is `forwardOrder(Order, std::shared_ptr<Waiter>)`. As one could imagine, this method literally forwards a Party's Order onto their respective Waiter.
- While I could've granted Party access to the JobTable such that Parties place their OrderJob directly into the JobTable and notify their Waiter, I feel as though this would be a poor breach of encapsulation: Parties should not have access to the JobTable, nor should they assign Jobs. Thus, we have OrderService, which employs somewhat of an Adapter pattern to coordinate action between two incompatible Actors.

## sim package

##### Simulation:

- The central program container. This object is created, initialized and ran from `main.cpp`.
- Aside from initializing data structures from metadata and creating the Restaurant, Simulation is also responsible for creating and managing all existing Parties, both inside and outside the Restaurant.
- This class also contains the GlobalClock to which all other classes refer, as well as the SimMonitor.
