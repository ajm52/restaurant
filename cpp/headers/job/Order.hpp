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
              selections_(),
              tableID_() {}

    /**
     * @description: main constructor.
     * @param id order id string.
     * @param selections attached selectinos.
     * @param tableID associated table ID.
     **/
    Order(const std::string id, const std::shared_ptr<std::vector<std::string>> selections, unsigned tableID)
        : orderId_(id),
          selections_(selections),
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
     * @description: accessor for this Order's selection set; each int represents a selection.
     * @returns a const reference to this Order's selection set
     */
    inline const std::vector<std::string> getSelections() const { return *selections_; }

    /**
     * @description: table ID accessor.
     * @returns the table ID associated with this order.
     */
    inline const unsigned getTableID() const { return tableID_; }

    /**
     * @description: order type accessor.
     */
    inline constexpr char getOrderType() const
    {
        assert(selections_->size() > 0 && (*selections_)[0].length() > 0);
        return (*selections_)[0][0];
    }

private:
    std::string orderId_;                                  ///< id string, unique to each order.
    std::shared_ptr<std::vector<std::string>> selections_; ///< menu selections.
    unsigned tableID_;                                     ///< the associated table id.
};

#endif // ORDER_HPP

/**
 * TODO think about whether Order should have move sems; would it offer us anything?
 */