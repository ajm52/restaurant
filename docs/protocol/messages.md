# this doc states and describes the various messages that will be implemented

# messages collectively form the communication protocol used between I/O entities on the BE.

**MESSAGES**

Messages sent by Parties:

- GreetingMessage<string> ("Greetings, <Waiter>!")
- OrderRequestMessage<string> ("Hey <Waiter>, service please!")
- NewOrderMessage<string...> ("<O1> <O2> ...")
- ThankYouMessage<string> ("Thanks, <Waiter>!")

Messages sent by Doorman:

- NewPartyMessage<string,string,string> ("Hey <Waiter>, seat <Party> at <Approachable>.")
- CleaningMessage<string,string> ("Hey <Waiter>, clean <Approachable>.")

Messages sent by Waiter:

- GreetingMessage<string> ("Greetings, <Party>!")
- OrderQueryMessage<string> ("What would you like, <Party>?")
- RequestReceivedMessage<string> ("Coming right up!")
- OrderDoneMessage<string> ("Heads up <Party>, incoming order!")
- CurteousMessage<string> ("My pleasure, <Party>.")

Messages sent by Bartender:

- OrderDoneMessage<string,string> ("Hey <Waiter>, <Order> is done.")

Messages sent by HeadCook:

- NewOrderMessage<string,string> ("Hey <Cook>, prepare <Order>.")

Messages sent by Cook:

- OrderReceivedMessage<string> ("Yes, Chef!")
- OrderDoneMessage<string,string> ("Hey <Waiter>, <Order> is done.")
