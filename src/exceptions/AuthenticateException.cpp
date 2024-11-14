/**
 *	@file   exceptions/AuthenticateException.cpp
 *	@brief  Exception class for arguments errors.
 *	@author Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

class AuthenticateException : public IMAPException {
public:

    AuthenticateException(const std::string& message)
        : IMAPException(message, 11) {}

};