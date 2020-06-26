#include "Worker.hpp"
#include "Job.hpp"
#include <thread>
#include <mutex>
#include <memory>
#include <vector>
#include <chrono>
#include <iostream>
#include <boost/algorithm/string.hpp>

Worker::Worker(Worker &&w)
    : Person(w.id_),
      gc_(w.gc_),
      jt_(w.jt_),
      menu_(std::move(w.menu_)),
      jobs_(std::move(w.jobs_)),
      t_(std::move(w.t_)) {}

Worker &Worker::operator=(Worker &&w)
{
    if (this == &w)
        return *this;
    id_ = w.id_;
    gc_ = w.gc_;
    jt_ = w.jt_;
    menu_ = std::move(w.menu_);
    jobs_ = std::move(w.jobs_);
    t_ = std::move(w.t_);
    return *this;
}

void Worker::init()
{
    std::thread t(&Worker::run, std::ref(*this));
    t_ = std::move(t);
}

void Worker::run()
{
    std::cout << getClock() << " " << getId() << " is awake.\n";
    while (true)
    {

        std::unique_lock<std::mutex> ul(*getJobTable().getMutex(getIDNumber())); //begin critical section

        while (!getJobTable().workToBeDone(getIDNumber())) //waits here until there is work to be done.
        {
            getJobTable().getCV(getIDNumber())->wait(ul);
        }

        std::cout << getClock() << " " << getId() << ": Work to be done. Acquiring jobs...\n";
        std::shared_ptr<std::vector<std::shared_ptr<Job>>> jobs = this->getJobTable().acquireAllJobs(this->getIDNumber(), true);

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        std::cout << getClock() << " " << getId() << ": Jobs acquired. Pushing to local job list... ";
        for (int i = 0; i < jobs.get()->size(); ++i)
            jobs_.push_back(jobs.get()->at(i));

        std::cout << " done.\n";
        ul.unlock(); // end critical section

        std::this_thread::sleep_for(std::chrono::milliseconds(750));
        for (int i = 0; i < jobs_.size(); ++i)
        {
            //TODO add an ID string to Job.
            std::cout << getClock() << " " << getId() << ": Beginning Job#" << std::to_string(i) << ".\n";

            jobs_[i]->accept(*this); // complete the job.

            std::cout << getClock() << " " << getId() << ": Job#" << std::to_string(i) << " done.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

        jobs_.clear();

        std::cout << getClock() << " " << getId() << ": Local job wave completed.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));

    } // end main while loop
}

const int Worker::getIDNumber() const
{
    std::vector<std::string> tokens;
    boost::algorithm::split(tokens, this->getId(), boost::algorithm::is_any_of("-"));
    if (tokens.size() >= 2)
    {
        return std::stoi(tokens[1]);
    }
    else
    {
        return -1;
    }
}