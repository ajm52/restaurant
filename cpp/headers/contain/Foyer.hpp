#ifndef FOYER_HPP
#define FOYER_HPP

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
    Foyer() : toBeSeated_(), m_() {}

    /**
     * @description: move constructor.
     * @param f foyer we're moving.
     */
    Foyer(Foyer &&);

    /**
     * @description: move assignment operator.
     * @param f foyer we're moving.
     * @returns this foyer after assignment.
     */
    Foyer &operator=(Foyer &&);

    /**
     * @description: destructor.
     */
    ~Foyer() = default;

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

    std::map<unsigned, Party *> toBeSeated_; ///< map of <Table #, Party*> pairs
    mutable std::mutex m_;                   ///< foyer mutex.

private:
    Foyer(const Foyer &) = delete; ///< Foyer is uncopyable.
    Foyer &operator=(const Foyer &) = delete;
};

#endif // FOYER_HPP