#include "Door.hpp"
#include <mutex>

Door::Door()
    : mIn_(),
      mOut_(),
      comingIn_(),
      goingOut_(),
      cv_() {}

Door::Door(const Door &d)
    : mIn_(),
      mOut_(),
      comingIn_(d.comingIn_),
      goingOut_(d.goingOut_),
      cv_(),
      outside_(d.outside_) {}

Door &Door::operator=(const Door &d)
{
    if (this == &d)
        return *this;
    std::queue<std::shared_ptr<Party>> swapper(d.comingIn_);
    comingIn_.swap(swapper);
    swapper = d.goingOut_;
    goingOut_.swap(swapper);
    outside_.assign(d.outside_.begin(), d.outside_.end());
    return *this;
}

Door::Door(Door &&d)
    : mIn_(), mOut_(), cv_()
{
    std::unique_lock<std::mutex> l1(d.mIn_, std::defer_lock);
    std::unique_lock<std::mutex> l2(d.mOut_, std::defer_lock);
    std::lock(l1, l2);
    comingIn_ = std::move(d.comingIn_);
    goingOut_ = std::move(d.goingOut_);
}

Door &Door::operator=(Door &&d)
{
    if (this != &d)
    {
        std::unique_lock<std::mutex> l1(d.mIn_, std::defer_lock);
        std::unique_lock<std::mutex> l2(d.mOut_, std::defer_lock);
        std::unique_lock<std::mutex> l3(this->mIn_, std::defer_lock);
        std::unique_lock<std::mutex> l4(this->mOut_, std::defer_lock);
        std::lock(l1, l2, l3, l4);
        comingIn_ = std::move(d.comingIn_);
        goingOut_ = std::move(d.goingOut_);
    }
    return *this;
}