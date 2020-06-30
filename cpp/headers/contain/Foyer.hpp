#ifndef FOYER_HPP
#define FOYER_HPP

#include <map>
#include <mutex>
#include <memory>

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
     * @description: destructor.
     */
    ~Foyer() = default;

    /**
     * @description: place a party in the foyer.
     * @param id table # where the party should be seated.
     * @param pPtr a pointer to the party to be seated.
     * @returns true if the Party was placed successfully, false otherwise.
     */
    void putParty(unsigned, std::shared_ptr<Party>);

    /**
     * @description: remove and return a party from the foyer.
     * @param id table # for a corresponding party to be seated.
     * @returns a pointer to the corresponding party, or nullptr if 
     * no such mapping exists.
     */
    std::shared_ptr<Party> removeParty(unsigned);

    std::map<unsigned, std::shared_ptr<Party>> toBeSeated_; ///< map of <Table #, Party*> pairs
    mutable std::mutex m_;                                  ///< foyer mutex.

    Foyer(const Foyer &) = delete; ///< Foyer is neither copyable nor movable.
    Foyer &operator=(const Foyer &) = delete;
    Foyer(Foyer &&) = delete;
    Foyer &operator=(Foyer &&) = delete;
};

#endif // FOYER_HPP