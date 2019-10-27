This document will be used to describe, in respectable detail, the interaction(s) between entities of the restaurant.

interactions:

1 - Guest(s) enter restaurant

    party.enter()
    party.findTable()
    party.sitAtTable()
    /*
    when the party sits down at a table,
    a hidden service adds a "greet table" job to the
    tablespace job queue and server pool is notified.

    */

2 - Waiter greets table

    waiter.greet(table)

    /*
        during this, waiter provides menus for each
        guest and takes drink orders.
    */

3 - Waiter completes drink order

    example: one guest is sitting at a table and has just been greeted by their server.
    server sets the menu down, tallies the drink order onto it's own job queue, and goes
    to complete its next job.

    let's say next job is the drink order and it's water. Server can complete this job on their
    own by going to water dispenser, filling a cup, bringing it back to the correct table, and giving it to the correct guest.

4 - Waiter completes food order

    the single guest just got their water.
    after some period of time passes, the guest
    waves their server over. this inserts a "take order" job into server's job queue.

    let's say that job is next. To complete the food order,
    the waiter submits the order to the kitchen by placing
    the food order in the kitchen's incoming job queue and notifies the kitchen.

5 - Kitchen processes a food order

    a new food order has been placed in the incoming job queue
    and the server notified the kitchen, waking up a sleeping cook if there is one. If all cooks are not sleeping, one of them will check the queue and take the order, placing it in their own job queue.

    let's say that cook has just pulled the food order out of their job queue. They start "cooking the food" right away, which sets a timer, and goes to sleep. When the timer expires, the cook is notified and checks their current job status, which should read "Cooked". When that happens, the cook takes the food order, places the order in the outgoing job queue, and notifies the tablespace.

    when tablespace is notified, the correct server must go to the kitchen, take the food order, and deliver it to the correct guest and table. this job is now considered complete and can be discarded by the server.

6 - Guest's dining experience

    server has just delivered the guest their hamburger. This begins a meal timer.

    every so often, the guest may stop eating and either take a drink or pause momentarily to ponder life.

    whenever a guest takes a drink, a portion of the drink is reduced. When a guest's drink is empty, they can wave at their server, which places a "wait table" job in the server's job queue.

    when the guest has finished their food, the status of the table changes to "waiting for bill" and the guest flags their server down, which places a "tend to bill" job in the server's job queue.

    taking care of the bill takes a few minutes, after which the guest stands up from the now-dirty table and heads for the door. WHen the guest leaves, this notifies the server and places a "clean table" job in the server's job queue, which takes a couple minutes.

    when the server has finished cleaning the table, it is no longer occupied and the server is no longer serving that table.
