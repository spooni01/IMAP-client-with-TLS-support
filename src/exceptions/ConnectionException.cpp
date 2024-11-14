/**
 *	@file   exceptions/ConnectionException.cpp
 *	@brief  Exception class for connection errors.
 *	@author Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

class ConnectionException : public IMAPException {
public:

    ConnectionException(const std::string& message)
        : IMAPException(message, 20) {}

};