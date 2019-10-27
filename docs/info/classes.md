restaurant:

- the main object of the entire simulation.
- in the simulation, guests may enter and leave the restaurant.
- the restaurant consists of a tablespace, kitchen, and bar.

tablespace:

- the dining area of the restaurant.
- consists of tables, servers, and two counters, where each table may or may not be occupied. The counters provide a two-way job channel to the kitchen and bar.
- really a container class for the restaurant's tables and servers.

kitchen:

- where food is prepared.
- consists of cooks and a counter (food is "cooked" using a timer).
- food orders may be submitted to the kitchen via the counter, which is also used to send back cooked food.

bar:

- where drinks are prepared, besides water.
- consists of a bartender and a counter (drinks are "made" using a timer).
- drink orders may be submitted to the bar via the counter, which is also used to send back drinks that are ready.

table:

- where guests enjoy their meals.
- has an id, occupied flag, capacity, and guest array.
- the id is used to map a server to the table they are serving.

counter:

- used as a order channel between restaurant sections.
- orders may be submitted and sent out.
- consists of two thread-safe queues.

person:

- could be a guest, cook, server, or bartender.
- guests are controlled by their party thread, while the others have their own.

guest:

- a restaurant customer.
- sits at a table, dines, then leaves.

party:

- a collection of guests and a master thread that controls them.
- may sit at a table or leave when finished eating.

cook:

- works in the kitchen.
- pulls and submits jobs to and from the tablespace via the counter.
- has a job table to track current jobs.

server:

- works in the tablespace.
- attends to guests that they are currently serving.
- has a job table and serving table to track jobs and current tables being served.

bartender:

- works behind the bar.
- submits and pulls drink jobs to and from the tablespace via the counter.
- has a job table to track drink jobs.

food:

- prepared by cooks, eaten by guests.
- produced when a food order is completed.

food_type:

- food enum.
- hamburger, cheeseburger, nachos, wings.

drink:

- prepared by the bartender (or server if it is water).
- produced when a drink order is completed.

drink_type:

- drink enum.
- water, beer, soda, tea.

menu:

- consists of two lists, food and drink.
- server provides these to guests when greeting a table and takes them away when food order is complete.

order:

- taken from a table by a server and delivered as a job to either the kitchen or bar.
- consists of a table and guest id.

food_order:

- consists of some food (will be null if not completed).

drink_order:

- consists of a drink (will be null if not completed).

job:

- could be a greet_job, order_job, or cleaning_job.
- used by the restaurant's workers.
