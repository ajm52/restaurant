#ifndef FOYER_HPP
#define FOYER_HPP

#include <vector>
#include <queue>
#include <map>
#include <mutex>

class Party;

/**
 * @struct Foyer
 * @description: Where parties wait to be seated.
 * @author ajm
 **/
struct Foyer
{
    /**
     * @description: default constructor.
     */
    Foyer();

    /**
     * @description: constructor.
     * @param tableCount # of tables in the restaurant.
     */
    explicit Foyer(unsigned);

    /**
     * @description: copy constructor.
     * @param f foyer we're copying from.
     */
    Foyer(const Foyer &);

    /**
     * @description: copy assignment operator.
     * @param f foyer we're copying from.
     * @returns this foyer.
     */
    Foyer &operator=(const Foyer &);

    /**
     * @description: destructor.
     */
    ~Foyer();

    /**
     * @description: removes and returns the ID of the next Table
     * to have a Party.
     * @returns the ID of the Table.
     */
    unsigned getNextTableID();

    /**
     * @description: place a party in the foyer.
     * @param id table # where the party should be seated.
     * @param pPtr a pointer to the party to be seated.
     * @returns true if the Party was placed successfully, false otherwise.
     */
    void putParty(unsigned, Party *);

    /**
     * @description: remove and return a party from the foyer.
     * @param id table # for a corresponding party to be seated.
     * @returns a pointer to the corresponding party, or nullptr if 
     * no such mapping exists.
     */
    Party *removeParty(unsigned);

    unsigned tableCount_; ///< # of restaurant tables.

    //TODO move nextTableIDs to Doorman.
    std::queue<unsigned> nextTableIDs_;      ///< table indices that are ready to be used.
    std::map<unsigned, Party *> toBeSeated_; ///< map of <Table #, Party*> pairs
    mutable std::mutex m_;                   ///< foyer mutex.

private:
    /**
     * @description: builds the table ID queue.
     * should only be called once when Foyer is first created.
     */
    void prepSeatingQueue();
};

#endif // FOYER_HPP

/**
 * TODO research 'explicit' keyword and proper usage.
 * TODO make Foyer uncopyable, yet moveable.
 */