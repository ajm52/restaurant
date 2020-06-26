# This document is intended to describe, in respectable detail, the interaction(s) between restaurant entities.

## Note that these interactions are described in pseudocode, with comments where applicable.

### 1 - Party entering the Restaurant.

    /*
    Parties place themselves in the Restaurant's inbound queue.
    */
    party.enter()

    /*
    Following self-placement, Parties must gain access (using `std::lock_guard<std::mutex>`) to the Door's condition variable, notifying the Doorman via said CV.
    */
    party.notifyDoorman()

    /*
    Notifying the Doorman begins a chain reaction: the Doorman grabs the Party from the queue, pairs said Party with a clean Table and suitable Waiter, places the Party in Foyer's map using the Table ID as a key, constructs and queues a SeatingJob for the Waiter and notifies said Waiter that there is work to be done.

    The Waiter receives the notification, check their job queue within JobTable, retrieves the SeatingJob, uses the attached table ID to key into the Foyer and grab the waiting Party. Once the Waiter has assigned the Party's Table, Waiter, and Menu as member data variables, the Waiter notifies the Party that their "service has begun".
    */
    party.waitForService()

### 2 - Orders, from submission to completion.

    Suppose a Party has just submitted a vector of Menu selections to OrderService. That Order is used to construct an OrderJob, which is then queued to the appropriate Waiter's job queue. Following this, OrderService notifies the Waiter.

    Upon receiving the notification, the Waiter checks its queue and sees that there is work to be done. Suppose said Order is for a couple of beers. The Waiter grabs the OrderJob from JobTable and puts the exact same OrderJob into the job queue of a Bartender (with only one Bartender, this is easy, but with more than one, it would make sense to have a static asynchronous function that assigns an OrderJob to the "least busy Bartender"), notifying the Bartender.

    The Bartender receives this notification, checks their job queue in JobTable, retrieves the OrderJob, and fires an asynchronous callback function to simulate "preparing the drinks", which is nothing more than a timer. Once this timer expires, the Bartender places the completed OrderJob back into the Waiter's job queue and notifies the Waiter.

    The Waiter grabs the OrderJob from its job queue and delivers the associated Order to the correct Table.

###### ASIDE

    At this point, it would make perfect sense to have some kind of "status" variable that the Waiter would use to determine what to do with said OrderJob; if it "requires service", submit it to the Bar/Kitchen, and if it is "ready for consumption", deliver it to the associated Table.

### 3 - Party's dining experience.

    The Waiter has served a Party their food Order (which is done by setting an Order pointer variable within the Table) and has notified the Party that their food has arrived. Seeing that their Order is "on the table", the Party "begins eating", which is nothing more than a timer. Once this timer expires, the Party stands up from the Table and heads for the exit.

###### ASIDE

    While it makes sense for Parties to pay for their meals, implementing that feature is something to be considered once the program works without it.

### 4 - Party leaving the restaurant.

    Exiting the Restaurant is identical to entry, except for what happens after the Doorman is notified. After the Party has placed itself in the outgoing queue and notified the Doorman, the Doorman must grab the Party and place it "outside". I have yet to implement this, but I have a feeling it will likely involve static accessor methods in Simulation.

    Once the Party has been placed outside, the Doorman assigns a CleaningJob to the Waiter responsible for waiting on the Party that just left. Similar to other simulation tasks, cleaning the Table can be emulated simply using a callback timer.
