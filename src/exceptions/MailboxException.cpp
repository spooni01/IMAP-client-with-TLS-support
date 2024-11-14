/**
 *	@file   exceptions/MailboxException.cpp
 *	@brief  Exception class for mail errors.
 *	@author Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

class MailboxException : public IMAPException {
public:

    MailboxException(const std::string& message)
        : IMAPException(message, 30) {}

};
