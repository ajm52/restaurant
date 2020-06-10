#ifndef MESSAGEBLOCK_HPP
#define MESSAGEBLOCK_HPP

#include <string>

/**
 * @struct <code>MessageBlock</code>
 * @description: Holds a plaintext message and an associated FD.
 * @author ajm
 * @created: 2/20/20
 * @modified: 2/20/20
 */
struct MessageBlock
{
    int fd_;          ///< associated file descriptor.
    std::string msg_; ///< a plaintext message.

    /**
     * @description: default constructor.
     */
    MessageBlock(int fd, std::string msg) : fd_(fd), msg_(msg) {}

    /**
     * @description: copy constructor.
     * @param mb <code>MessageBlock</code> to be copied.
     */
    MessageBlock(const MessageBlock &mb) : fd_(mb.fd_), msg_(mb.msg_) {}

    /**
     * @description: copy assignment operator.
     * @param mb <code>MessageBlock</code> to be copied.
     * @returns <code>this</code> with mb's parameters.
     */
    MessageBlock &operator=(const MessageBlock &mb)
    {
        if (this == &mb)
            return *this;
        this->fd_ = mb.fd_;
        this->msg_ = mb.msg_;
        return *this;
    }

    /**
     * @description: destructor.
     */
    ~MessageBlock() {}
};

#endif // MESSAGEBLOCK_HPP