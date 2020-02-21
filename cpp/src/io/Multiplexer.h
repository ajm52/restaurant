#ifndef MULTIPLEXER_H
#define MULTIPLEXER_H

#include <vector>
#include <sys/select.h>
#include <stdio.h>

/**
 * @class Multiplexer
 * @description: Handles I/O operations on a set of file descriptors.
 * Mostly to be used for read operations.
 * @author ajm
 * @created: 2/17/20
 * @modified: 2/20/20
 * 
 * http://man7.org/linux/man-pages/man2/select.2.html#top_of_page
 * 
 * https://www.lowtek.com/sockets/select.html
 */
class Multiplexer
{
public:
    /**
     * @description: Default constructor.
     */
    Multiplexer()
        : nfds_(-1),
          readSockets_(),
          writeSockets_(),
          exceptSockets_() {}

    /**
     * @description: Destructor.
     */
    ~Multiplexer() {}

    /**
     * @description: Clears all file descriptor bit fields.
     */
    void resetFDs();

    /**
     * @description: pushes a read socket into readSockets_.
     * @param fd the socket.
     * @returns 0 on success; negative values indicate an error.
     * @note This method inserts a given file descriptor into
     * a running list of all file descriptors intended to be read, whereas 
     * "registering" a socket flips a bit using FD_SET, which 
     * is then checked when select() returns.
     */
    int addReadSocket(int);

    /**
     * @description: Registers a file descriptor for read activity.
     * @param fd fd to be registered.
     * @returns 0 on success; negative values indicate an error.
     */
    int registerReadSocket(int);

    /**
     * @description: Selects on the given FDs for activity.
     * When <code>select()</code> returns, the active FD is returned.
     * @note mainly to be used for read file descriptors.
     * @returns a set of active file descriptors, 
     * or an empty set in case of error.
     */
    std::vector<int> getNextActiveFDs();

private:
    int nfds_;                                                    ///< used in the select() function call.
    std::vector<int> readSockets_, writeSockets_, exceptSockets_; ///< sets of read/write/except sockets.
    fd_set readfds_, writefds_, exceptfds_;                       ///< file descriptor sets.
};

/**
 * TODO:
 * - write a method removeSocket(int).
 * - write an ErrorType enum class that Multiplexer clients can use.
 * - use a timeout constant in select() instead of nullptr.
 */

#endif // MULTIPLEXER_H