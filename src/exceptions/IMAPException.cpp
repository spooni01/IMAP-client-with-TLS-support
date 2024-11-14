/**
 *	@file   exceptions/IMAPException.cpp
 *	@brief  Main exception class.
 *	@author Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include <stdexcept>
#include <string>

class IMAPException : public std::exception {
public:

    explicit IMAPException(const std::string& message, int code = 2)
        : msg(message), errorCode(code) {}

    virtual const char* what() const noexcept override {
        return msg.c_str();
    }

    int code() const noexcept {
        return errorCode;
    }

private:

    std::string msg;
    int errorCode;

};