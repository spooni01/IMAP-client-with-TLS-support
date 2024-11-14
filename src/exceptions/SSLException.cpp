/**
 *	@file   exceptions/SSLException.cpp
 *	@brief  Exception class for file errors.
 *	@author Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

class SSLException : public IMAPException {
public:

    SSLException(const std::string& message)
        : IMAPException(message, 6) {}

};