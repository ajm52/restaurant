#ifndef STATUS_H
#define STATUS_H

/**
 * A set of enum classes, intended to allow
 * for easy real-time activity analysis.
 * 
 * These will be used by factory methods to generate
 * Activity statements, which may either be printed
 * to console or sent to the front-end for visualization.
 * 
 * Activity statements are generated using a provided Status,
 * as well as 0 or more inputs (i.e. table #). Statuses requiring
 * inputs are indicated by comments below.
 * 
 * author: ajm
 * created: 1/21/20
 * last modified: 1/21/20
 **/
namespace Status
{
/**
 * NOTE: Guests will be fully controlled by their
 * respective Party. Autonomy may be granted later
 * if significant progress is first achieved.
 **/
enum class Party
{
    Outside,
    EnteringRestaurant,
    LeavingRestaurant,
    WaitingInFoyer,
    BeingEscortedToTable,   // table #
    Seated,                 // table #
    ExchangingPleasantries, // waiter #
    AwaitingService,
    SubmittingOrder, // order #, waiter #
    AwaitingOrder,   // order #
    PerusingFoodOptions,
    EnjoyingMeal,
    StandingUp,
    HeadedForExit,
    /**
     * the following three won't be used until a solid working
     * prototype is established (guests will initially dine for free).
     **/
    AwaitingBill,
    AcceptingBill,
    PayingBill
};

/**
 * Table statuses
 **/
enum class Table
{
    Clean,
    Occupied, // party #
    Dirty
};

namespace Worker
{

enum class Common
{
    Idling //Waiters, Cooks, and Bartenders may all idle
};

/**
 * Used by Waiters.
 **/
enum class TableService
{
    SeatingParty,            // party #, table #
    GreetingParty,           // party #
    RetrievingOrder,         //order #, party #
    SubmittingNewOrder,      //order #
    DeliveringFinishedOrder, // order #, table #
    CleaningTable            // table #
};

/**
 * Used by Cooks and Bartenders.
 **/
enum class ConsumableService
{
    //all of these require an order #.
    PullingOrder,
    StartingOrder,
    FinishingOrder,
    SubmittingFinishedOrder
};

} // namespace Worker
} // namespace Status

#endif // STATUS_H

/**
 * NOTE: In the presence of more than one Cook,
 * we will need a mechanism to designate new orders 
 * to an appropriate Cook. 
 * This could be done in many ways, 
 * but I am likely to choose one of the following:
 * 
 * - Designate a HeadCook that assigns incoming Orders.
 * - Implement a hook that observes the Order queue, notifying
 * the least busy Cook accordingly.
 **/