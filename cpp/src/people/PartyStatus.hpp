#ifndef PARTYSTATUS_HPP
#define PARTYSTATUS_HPP

/**
 * @enum PartyStatus
 * @description: Succinctly describes 
 * a party's current state in the simulation.
 * @author ajm
 * @created: 3/4/20
 * @modified: 3/4/20
 */
enum class PartyStatus
{
    DEFAULTED,        ///< fallback.
    OUTSIDE,          ///< outside restaurant.
    APPROACHING,      ///< approaching restaurant.
    ENTERING,         ///< entering restaurant.
    ENTERED,          ///< entered restaurant.
    WAITING_FOYER,    ///< in foyer, waiting to be seated.
    GREETINGS,        ///< greeting waiter.
    READING_MENU,     ///< reading the menu.
    ORDER_REQUEST,    ///< ready to order.
    SUBMITTING_ORDER, ///< passing order to waiter.
    ORDER_SUBMITTED,  ///< order submitted.
    WAITING_ORDER,    ///< waiting for order.
    RECEIVING_ORDER,  ///< receiving order from waiter.
    ENJOYING_MEAL,    ///< enjoying meal(s).
    MEAL_COMPLETE,    ///< meal(s) is/are finished.
    LEAVING_TABLE,    ///< leaving table.
    EXITING,          ///< leaving restaurant.
    PARTY_DONE        ///< successfully left restaurant; run() complete.
};
#endif // PARTYSTATUS_HPP