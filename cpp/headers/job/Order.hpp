#ifndef ORDER_HPP
#define ORDER_HPP

#include <string>
#include <memory>
#include <vector>

class Party;
class Waiter;
class Bartender;
class OrderMachine;

/**
 * @enum OrderStatus
 * @description: used to describe the status of an order.
 * @author ajm
 */
enum class OrderStatus
{
    Created,
    QueuedForSubmission,
    QueuedForPrep,
    ReceivedForPrep,
    BeingPrepared,
    ReadyToDeliver,
    QueuedForDelivery,
    EnRouteForDelivery,
    Delivered,
    DeliveryAcknowledged,
    ConsumptionUnderway,
    Consumed
};

/**
 * @class Order
 * @description: Represents a set of either drink or food orders from a given table.
 * @author ajm
 **/
class Order
{
public:
    class OrderAccess
    {
        static inline void setStatus(std::shared_ptr<Order> o, OrderStatus os)
        {
            o->status_ = os;
        }
        friend class Party;
        friend class Waiter;
        friend class Bartender;
        friend class OrderMachine;
    };

    /**
     * @description: constructor.
     * Data members are defaulted initialized.
     **/
    Order() : orderId_("DEFAULT_OID"),
              selections_(),
              tableID_(),
              status_(OrderStatus::Created) {}

    /**
     * @description: main constructor.
     * @param id order id string.
     * @param selections attached selectinos.
     * @param tableID associated table ID.
     **/
    Order(const std::string id, const std::string wid, const std::shared_ptr<std::vector<std::string>> selections, unsigned tableID)
        : orderId_(id),
          wID_(wid),
          selections_(selections),
          tableID_(tableID),
          status_(OrderStatus::Created) {}

    /**
     * @description: copy constructor.
     * @param order to be copied from.
     */
    Order(const Order &);

    /**
     * @description: copy assignment operator.
     * @param order to be copied from.
     * @returns a reference to this order.
     */
    Order &operator=(const Order &);

    /**
     * @description: destructor.
     */
    ~Order() = default;

    inline const std::string &getOrderId() const { return orderId_; }

    inline const std::string getWID() const { return wID_; }

    inline const std::vector<std::string> getSelections() const { return *selections_; }

    inline const unsigned getTableID() const { return tableID_; }

    inline const OrderStatus getOrderStatus() const { return status_; }

    /**
     * @description: order type accessor.
     */
    inline constexpr char getOrderType() const
    {
        assert(selections_->size() > 0 && (*selections_)[0].length() > 0);
        return (*selections_)[0][0];
    }

private:
    std::string orderId_;
    std::string wID_;
    std::shared_ptr<std::vector<std::string>> selections_;
    unsigned tableID_;
    OrderStatus status_;
};

#endif // ORDER_HPP

/**
 * TODO think about whether Order should have move sems; would it offer us anything?
 */