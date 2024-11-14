/**
 *	@file   exceptions/ArgumentsException.cpp
 *	@brief  Exception class for arguments errors.
 *	@author Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

class ArgumentsException : public IMAPException {
public:

    ArgumentsException(const std::string& message)
        : IMAPException(message, 4) {}

};