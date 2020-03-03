# this doc states and describes the various updates that will be implemented.

# updates are used to communicate simulation info from BE to FE via the Messenger.

**UPDATES**

Updates sent by Parties:

- SpawnUpdate<string> ("<Party> has spawned outside.")
- ApproachingUpdate<string,string> ("<Party> is approaching <Approachable>.")
- EnteringUpdate<string,string> ("<Party> is entering <Approachable>.")
- EnteredUpdate<string,string> ("<Party> has entered <Approachable>.")
- WaitingFoyerUpdate<string> ("<Party> is waiting to be seated.")
- GreetingUpdate<string,string> ("<Party> is greeting <Waiter>.")
- MenuUpdate<string> ("<Party> is reading the menu.")
- NewOrderUpdate<string> ("<Party> is requesting a new order.")
- OrderSubmittingUpdate<string,string> ("<Party> is submitting an order to <Waiter>.")
- OrderSubmittedUpdate<string> ("<Party>'s order has been submitted.")
- WaitingOrderUpdate<string> ("<Party> is waiting for their order.")
- ReceivingOrderUpdate<string> ("<Party> is receiving an order.")
- EnjoyingMealUpdate<string> ("<Party> is enjoying their meal.")
- MealFinishedUpdate<string> ("<Party> has finished their meal.")
- LeavingTableUpdate<string,string> ("<Party> has left <Approachable>.")
- ExitingUpdate<string,string> ("<Party> is leaving <Approachable>.")
- ExitUpdate<string,string> ("<Party> has left <Approachable> and is headed for home.")

Updates sent by Door(man):

- FoyerUpdate<string,int> ("<Party> is in the foyer, waiting to be seated at table <ID>.")
- EntryUpdate<string> ("<Party> has entered.")
- AssignmentUpdate<string,string,string> ("<Doorman> is assigning <Waiter> to serve <Party>.")
- MessagingUpdate<string> ("<Doorman> is contacting <Waiter>...")
- MessageSuccessUpdate<string> ("<Waiter> has been contacted by <Doorman>.")
- ExitUpdate<string> ("<Party> has left.")
- AssignmentUpdate<string,string,string> ("<Doorman> is assigning <Waiter> to clean <Approachable>.")

Updates sent by Waiter:

- IdleUpdate<string> ("<Waiter> is idle.")
- NewMessageUpdate<string,string> ("<Waiter> has a new message from <Sender>.")
- FetchingUpdate<string,string> ("<Waiter> is fetching <Party> from foyer.")
- SeatingUpdate<string,string,int> ("<Waiter> is seating <Party> at table <ID>.")
- GreetingUpdate<string,string> ("<Waiter> is greeting <Party>.")
- ApproachingUpdate<string,string> ("<Waiter> is approaching <Approachable>.")
- OrderQueryUpdate<string,string> ("<Waiter> is asking <Party> for their order.")
- OrderReceivedUpdate<string,string,string> ("<Waiter> has received <Party>'s order, <Order>.")
- OrderSubmittingUpdate<string,string,string> ("<Waiter> is submitting <Order> to <Approachable>.")
- OrderSubmittedUpdate<string,string> ("<Order> has been submitted by <Waiter>.")
- FetchingOrderUpdate<string,string,string> ("<Waiter> is fetching <Order> from <Approachable>.")
- FetchedOrderUpdate<string,string> ("<Order> has been fetched by <Waiter>.")
- DeliveringOrderUpdate<string,string,string> ("<Waiter> is delivering <Order> to <Approachable>.")
- OrderDeliveredUpdate<string,string,string,string> ("<Waiter> has delivered <Order> to <Party> at <Approachable>.")
- CleaningUpdate<string,string> ("<Waiter> is cleaning <Approachable>.")

Updates sent by Bartender:

- IdleUpdate<string> ("<Bartender> is idle.")
- NewOrderUpdate<string,string> ("<Order> has come in for <Bartender>.")
- FetchingOrderUpdate<string,string> ("<Bartender> is fetching <Order>.")
- FetchedOrderUpdate<string,string> ("<Bartender> has fetched <Order>.")
- OrderStartedUpdate<string,string> ("<Bartender> has started <Order>.")
- OrderCompletedUpdate<string,string> ("<Bartender> has completed <Order>.")
- TablingOrderUpdate<string,string> ("<Bartender> is tabling <Order> for delivery.")
- TabledOrderUpdate<string,string> ("<Bartender> has tabled <Order> for delivery.")
- NotifyingWaiterUpdate<string,string,string> ("<Bartender> is notifying <Waiter> that <Order> is done.")
- NotifiedWaiterUpdate<string,string> ("<Bartender> has notified <Waiter>.")

Updates sent by HeadCook:

- IdleUpdate<string> ("<HeadCook> is idle.")
- NewOrderUpdate<string,string> ("<Order> has come in for <HeadCook>.")
- FetchingOrderUpdate<string,string> ("<HeadCook> is fetching <Order>.")
- FetchedOrderUpdate<string,string> ("<HeadCook> has fetched <Order>.")
- AssignmentUpdate<string,bool,string> ("<HeadCook> is assigning <Worker> to prepare <Order>.")

Updates sent by Cook:

- IdleUpdate<string> ("<Cook> is idle.")
- NewAssignmentUpdate<string,string> ("<Cook> has received an assignment from <HeadCook>.")
- OrderStartedUpdate<string,string> ("<Cook> has started <Order>.")
- OrderCompletedUpdate<string,string> ("<Cook> has completed <Order>.")
- TablingOrderUpdate<string,string> ("<Cook> is tabling <Order> for delivery.")
- TabledOrderUpdate<string,string> ("<Cook> has tabled <Order> for delivery.")
- NotifyingWaiterUpdate<string,string,string> ("<Cook> is notifying <Waiter> that <Order> is done.")
- NotifiedWaiterUpdate<string,string> ("<Cook> has notified <Waiter>.")
