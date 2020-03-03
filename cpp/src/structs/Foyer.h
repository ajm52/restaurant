#ifndef FOYER_H
#define FOYER_H

#include <map>

class Party;

/**
 * @struct <code>Foyer</code>
 * @description: Where parties wait to be seated.
 * @author ajm
 * @created: 2/6/20
 * @modified: 3/2/20
 **/
struct Foyer
{
    std::map<int, Party *> table_; ///< map of <Table #, Party*> pairs

    /**
     * @description: place a party in the foyer.
     * @param id table # where the party should be seated.
     * @param pPtr a pointer to the party to be seated.
     */
    bool putParty(int id, Party *pPtr);

    /**
     * @description: remove and return a party from the foyer.
     * @param id table # for a corresponding party to be seated.
     * @returns a pointer to the corresponding party, or nullptr if 
     * no such mapping exists.
     */
    Party *removeParty(int id);
};

#endif // FOYER_H

/**
 * TODO: make Foyer threadsafe with mutex.
 */