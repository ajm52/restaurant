#ifndef GUEST_STATUS_H
#define GUEST_STATUS_H

/**
 * describes the current activity of a guest.
 * while this is not a necessary feature for 
 * this program to work, it is nice for the purpose 
 * of information/debugging.
 * */
enum guest_status
{
    OUTSIDE,            //guest has just spawned
    ENTERING,           //attempting to access door
    ENTERED,            //successfully entered restaurant
    WAITING_FOR_SERVER, //for initial greet
    SEATED,             //has been successfully seated by a waiter
    MAKING_ORDER,       //giving server orders
    WAITING_ORDER,      //waiting to receive orders
    EATING,             //eating
    LEAVING,            //attempting to leave via the door
    LEFT                //successfully left restaurant
}

#endif // GUEST_STATUS_H