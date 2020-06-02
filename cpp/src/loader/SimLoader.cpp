#include "SimLoader.h"
#include "Restaurant.h"
#include "Party.h"
#include "Waiter.h"
#include "Door.h"
#include "WorkerBulletin.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

void SimLoader::initDoorFD(Door *d)
{
    std::string doorConfigPath = "../../meta/door_io_data.md";
    std::shared_ptr<std::vector<int>> doorFD = dataLoader_.createFDs(doorConfigPath);
    /**
     * TODO: assert doorFD size == 1 and doorFD[0] >= 0
     */
}

void SimLoader::loadWaiterBulletin(WorkerBulletin &wb, const std::shared_ptr<std::vector<Waiter>> waiters)
{
    for (auto waiter : *(waiters.get()))
        wb.registerWorker(waiter);
}

std::shared_ptr<std::vector<Party>> SimLoader::createParties(Restaurant &r)
{
    std::string partyConfigPath = "../../meta/party_io_data.md";
    std::shared_ptr<std::vector<int>> fds = dataLoader_.createFDs(partyConfigPath);
    std::vector<Party> parties;
    int i = 0;
    while (i < fds.get()->size())
    {
        std::string id("P" + std::to_string(i));
        Party p(&r, nullptr, id);
        parties.push_back(p);
        i++;
    }
    return std::make_shared<std::vector<Party>>(std::move(parties));
}