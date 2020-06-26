# restaurant.

compiled with clang++ 11.0.3 for MacOS Catalina 10.15.5

A Restaurant Simulation programmed in C++. Will eventually have a Javascript frontend. Using this to get practice with multithreaded programming.

This project was initially started back in November 2019; further development was curbed when I realized how much C++ knowledge I lacked and the amount of development idioms I was not considering.

After reading a few books (The Pragmatic Programmer, Effective C++), I began project development again from scratch. It would have probably been wise to keep old code, but I wanted a clean slate. Much of the prior code was poorly designed and heavily coupled.

This time around, development has been intentionally much slower with a heavy emphasis on intuitive class design/implementation, vigorous testing, and clean code. For a while, it was relatively straightforward to pair each class with a unit test. However, once I got into the threaded programming, unit testing became increasingly difficult to articulate, and I sort of gave it up (for the time being), using print statements and programmer intuition to verify code, inserting comments to remind myself what might need addressing at a later date.
