## 5/22/20

After taking a lengthy break from this project due to various unforeseen circumstances,
we are back at it. Given that we still have yet to hit a single milestone, the current objective
must be changed. In schooling terms, the first milestone will be to shoot for a "passing grade";
simplify everything as much as possible, wherever possible, such that we can actually produce a result that actually does something.

This "passing grade" prototype will have the following:

- no UI; it will be strictly text-based. This means that everything will be in C++.
- parties will seat and excuse themselves; no Door, no Doorman.
- threads will be avoided as much as possible (for now).

#### General Flow

1. Party sits down at a Table; this action sends a signal to a Waiter.
2. said Waiter retrieves Order from Party and delivers it to the Kitchen.
   - we will still need to synchronize exchanges between Parties/Waiters,
     as well as Waiters/Cooks.
3. some Cook is notified of the new Order, which they begin preparing asynchronously
   via a timer. - when that timer expires, Cook places the cooked Order on the warming area, an
   action that notifies the appropriate Waiter.
4. Waiter retrieves the Order from the warming area and delivers it to the correct
   Table.
5. Party is notified via signal-slot that their Order has arrived, and begins "eating",
   which is nothing more than a timer. - when that timer expires, the Party leaves the Table and "exits the restaurant".
6. when a Party leaves, the corresponding Waiter is notified via signal-slot that they
   need to "clean the table", which is nothing more than a timer.

That's it.

Classes involved:

Restaurant
Table
Party
Worker
Waiter
Cook
Order
Menu
Kitchen
PartySpawner (?)

# 6/19/20

- The "passing-grade prototype" has been finished, though not exactly as it was initially stated. Once it was realized to be somewhat impossible (moreso, illogical) to avoid the use of threads, I dove headfirst and threaded all Simulation Actors: Parties, the Doorman, and Workers.
- In addition, I was able to implement proper threaded coordination between several Actors, such that Parties don't have to seat themselves; this is done by Waiters, with some help from the Doorman.

#### What's next...

The worst is behind us; mostly everything ahead involves using implementation strategies that I've already discovered and employed. Static accessor methods have turned out to be an absolute godsend in allowing relatively safe access to sensitive member data: Complete and utter encapsulation is not only undesirable, it is also virtually unattainable in most scenarios, particularly when several interacting entities are involved. Coupling is bound to occur between classes in some circumstances; the key is to clearly define what the boundaries of said coupling is, and to keep it that way with sound implementation strategies.

Next on the agenda is to carry through with Order submission, completion, and delivery. In order for this to be done, we will need to flesh out Bar and Bartender, as well as an additional static OrderService accessor that allows Waiters to forward OrderJobs to the Bar/Kitchen. In addition, we will also need to implement and integrate some kind of "status" enumeration, at the very least, to describe OrderJobs. These enums will likely be extended at a later date to describe other simulation entities, but for now, we actually sort of need it to implement Waiter's sound decision-making when it comes to handling OrderJobs.

#### ASIDE

It should be noted that I have somewhat let unit testing fall by the wayside. I was doing fairly well with the habit, until I hit threaded classes. I learned about unit testing several years ago, though it is not something that I have used extensively. Moreover, writing tests for an isolated object is far simpler than writing tests for a threaded class, which is simpler than writing tests for a threaded class that interacts with many other entities. Thus, I made the decision to set religious testing aside for the meantime, relying on print statements and programmer intuition to validate my code.
