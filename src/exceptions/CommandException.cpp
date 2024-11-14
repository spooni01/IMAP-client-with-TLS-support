/**
 *	@file   exceptions/CommandException.cpp
 *	@brief  Exception class for command errors.
 *	@author Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

class CommandException : public IMAPException {
public:

    CommandException(const std::string& message)
        : IMAPException(message, 23) {}

};