#ifndef ORDERSTATUS_H
#define ORDERSTATUS_H

#include <iostream>

/**
 * Order statuses for both food and drink.
 * Comments below indicate additional information
 * needed to generate an activity statement.
 * 
 * author: ajm
 * created: 1/29/20
 * last modified: 1/29/20
 **/
enum class OrderStatus
{
    Defaulted,     // indicates bad construction
    Initializing,  // indicates good construction
    TakenByWaiter, // waiter #
    Submitted,
    AssignedToWorker, // cook or bartender #
    BeingPrepared,    // cook or bartender #
    ReadyForConsumption,
    EnRouteToTable,   // table #
    DeliveredToTable, // table #
    BeingConsumed,    // party #
    Finished
};

std::ostream &operator<<(std::ostream &os, OrderStatus o)
{
    /**
     * extremely verbose, but this is what I found on cppreference
     * for overloading the << operator with enum classes. I will keep an eye 
     * out for a better method in the meantime.
     **/
    switch (o)
    {
    case OrderStatus::Defaulted:
        os << "Defaulted";
        break;
    case OrderStatus::Initializing:
        os << "Initializing";
        break;
    case OrderStatus::TakenByWaiter:
        os << "Taken by Waiter";
        break;
    case OrderStatus::Submitted:
        os << "Submitted";
        break;
    case OrderStatus::AssignedToWorker:
        os << "Assigned to Worker";
        break;
    case OrderStatus::BeingPrepared:
        os << "Being Prepared";
        break;
    case OrderStatus::ReadyForConsumption:
        os << "Ready for Consumption";
        break;
    case OrderStatus::EnRouteToTable:
        os << "En Route to Table";
        break;
    case OrderStatus::DeliveredToTable:
        os << "Delivered to Table";
        break;
    case OrderStatus::BeingConsumed:
        os << "Being Consumed";
        break;
    case OrderStatus::Finished:
        os << "Finished";
        break;
    default:
        os.setstate(std::ios_base::failbit);
    }
    return os;
}

#endif // ORDERSTATUS_H
