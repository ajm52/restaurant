# Restaurant Requirements (C++/Javascript)

**BACK-END**

- Employ metadata wherever possible to represent simulation data and constants.
  • This metadata will then be fed into the program on startup.
- All Workers should appropriately respond to a subset of concrete Job types.

- Prefer plain-text socket communication.

- Parties (groups of Guests) should be able to enter and leave the Restaurant by their own accord.

- Parties should be escorted to their Table by an assigned Waiter, chosen by the Doorman.

- Leaving and entering the Restaurant must be synchronized (i.e. two Parties may not enter simultaneously).

- Waiters must be able to aptly respond to a number of different scenarios at any given moment, including:
  • the assignment of a new Party by the Doorman.
  • a food/drink order request by a seated Party.
  • a completed order that is ready for Table delivery.
  • ...and potentially more.

- Parties that have enqueued themselves for entry must be placed in the Foyer by the Doorman.

- Successful placement of a Party in the Foyer should be followed by:
  • determination by the Doorman of a suitable Waiter.
  • a notification sent to said Waiter, notifying them of a Party requiring service.

- Preparing/consuming Orders can be emulated using a timer.

- Cooks/Bartenders should be able to work on multiple Orders at once.
  • When an Order is "ready", said Worker should somehow be notified (i.e. callback notify function?)

- Cooks/Bartenders must know how long each Order takes to prepare.
  • this will be done using a Factory pattern to instantiate Cooks/Bartenders based on metadata.
  • Cooks/Bartenders will have to store MenuEntry preparation times as member data.

- A "messenger" should be implemented to transfer state information from backend to frontend.

- Communication with the Messenger must be synchronized.

**FRONT-END**

- An informative frontend must be built in order to display state information of the following:
  • Parties
  • Workers (Waiters, Bartenders, Cooks)
  • Jobs (TableService/OrderService)
  • Orders (Food/Drink)
  • Tables (Clean/dirty, occupation status, and by whom)

- The frontend should also feature an ActivityFeed at the bottom to display incoming updates and their associated timestamps.
