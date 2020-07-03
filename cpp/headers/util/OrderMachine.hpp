#ifndef ORDERMACHINE_HPP
#define ORDERMACHINE_HPP

#include "Order.hpp"
#include "JobTable.hpp"
#include <memory>
#include <vector>
#include <string>
#include <mutex>

class Party;

/**
 * @class OrderMachine
 * @author ajm
 * @description: Made available to Parties to help them submit Orders.
 * Employs the Adapter Pattern: Catches order submissions made by Parties
 * and turns them into OrderJobs to be picked up by Waiters.
 */
class OrderMachine
{
public:
    OrderMachine(JobTable &jt) : jt_(jt), numOrders_(), m_() {}
    ~OrderMachine() = default;
    /**
         * @description: intended for use by Parties to have their menu selections
         * made into an Order, which is then forwarded on to the correct Waiter.
         * @param selections menu selections made by Party
         * @param p party making the order
         */
    void submitOrder(const std::shared_ptr<std::vector<std::string>>, const std::shared_ptr<Party>);

    /**
     * @description: computes and returns the next Order ID string.
     * @returns next order ID string
     */
    inline const std::string getNextOrderID() const { return "O" + std::to_string(numOrders_); }

    /**
     * @description: self-explanatory.
     */
    inline void incrOrderCount() { numOrders_++; }

    OrderMachine(const OrderMachine &) = delete; ///< made uncopyable/unmovable to avoid unwarranted operations
    OrderMachine &operator=(const OrderMachine &) = delete;
    OrderMachine(OrderMachine &&) = delete;
    OrderMachine &operator=(OrderMachine &&) = delete;

private:
    JobTable &jt_; ///< used to submit OrderJobs.
    unsigned numOrders_;
    mutable std::mutex m_;
};
#endif // ORDERMACHINE_HPP

/**
 * TODO think about what other data members this class should have.
 */