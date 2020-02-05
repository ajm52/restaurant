# Restaurant Requirements (C++/Javascript)

author: ajm
created: 2/4/20
last modified: 2/4/20

**NOTE**

This document, subject to change, will most likely undergo many modifications and additions throughout development.

These requirements are fairly technical and may be, at times, overly specific. I have done this to get the entirety
of how I visualize the application on paper, which should simplify the process of implementation,
and hopefully mitigate refactoring.

.
.
.

Requirements:

**BACK-END**

- A Restaurant-wide messaging protocol must be established.

- Employ metadata wherever possible to represent simulation data and constants.
  • This metadata may then be fed into the program on startup.
- All Workers will appropriately respond to a subset of MessageTypes established in the protocol.

- Prefer plain-text socket communication, though certain objects may need to be Serializable to properly emulate a Restaurant.

- Parties (groups of Guests) should be able to enter and leave the Restaurant by their own accord.

- Parties should be escorted to their Table by an assigned Waiter, chosen by the Doorman.

- Leaving and entering the Restaurant must be synchronized (i.e. two Parties may not enter simultaneously).

- Waiters must be able to aptly respond to a number of different scenarios/messages at any given moment, including:
  • the assignment of a new Party by the Doorman.
  • a food/drink order request by a seated Party.
  • a completed order that is ready for Table delivery.
  • ...and potentially more.

- Parties that have enqueued themselves for entry must be placed in the Foyer by the Doorman (i.e. a thread or signal hook).

- Successful placement of a Party in the Foyer should be followed by:
  • determination by the Doorman of the least busy Waiter.
  • a message sent to said Waiter, notifying them of a new Party requiring service.

- "Preparing an order" shall be emulated simply using a timer.

- Cooks/Bartenders should be able to "work on" multiple Orders at once.
  • When an Order is "ready", said Worker should somehow be notified (i.e. callback notify function?)

- Cooks/Bartenders must "know" how long each Order takes to prepare.
  • this will be done using a Factory pattern to instantiate Cooks/Bartenders based on metadata.
  • Cooks/Bartenders will have to store Order preparation times as member data.

- A Messenger should be implemented to transfer state information from backend to frontend.

- Communication with the Messenger must be synchronized.

**FRONT-END**

- An informative frontend must be built in order to display state information of the following:
  • Parties
  • Workers (Waiters, Bartenders, Cooks)
  • Jobs (TableService/OrderService)
  • Orders (Food/Drink)
  • Tables (Clean/dirty, Occupied (and by whom))

- The frontend should also feature an ActivityFeed at the bottom to display incoming updates and their associated timestamps.
