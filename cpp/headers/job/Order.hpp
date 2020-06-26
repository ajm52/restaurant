#ifndef ORDER_HPP
#define ORDER_HPP

#include <string>
#include <vector>

/**
 * @class Order
 * @description: Represents a set of either drink or food orders from a given table.
 * @author ajm
 **/
class Order
{
public:
    /**
     * @description: constructor.
     * Data members are defaulted initialized.
     **/
    Order() : orderId_("DEFAULT_OID"),
              orders_(),
              tableID_() {}

    /**
     * @description: main constructor.
     * @param id order id string.
     * @param orders attached orders.
     **/
    Order(std::string id, std::vector<std::string> &orders, unsigned tableID) : orderId_(id),
                                                                                orders_(orders),
                                                                                tableID_(tableID) {}

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

    /**
     * @description: accessor for the order's id string.
     * @returns this order's id string.
     */
    inline const std::string &getOrderId() const { return orderId_; }

    /**
     * @description: accessor for this Order's order set; each int represents a selection.
     * @returns a const reference to this Order's order set
     */
    inline const std::vector<std::string> &getOrders() const { return orders_; }

    /**
     * @description: table ID accessor.
     * @returns the table ID associated with this order.
     */
    inline const unsigned getTableID() const { return tableID_; }

private:
    std::string orderId_;             ///< id string, unique to each order.
    std::vector<std::string> orders_; ///< menu selections.
    unsigned tableID_;                ///< the associated table id.
};

#endif // ORDER_HPP

/**
 * TODO change getOrders() to getSelections(), as it just makes more sense.
 */