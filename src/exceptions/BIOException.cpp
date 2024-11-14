/**
 *	@file   exceptions/BIOException.cpp
 *	@brief  Exception class for bio errors.
 *	@author Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

class BIOException : public IMAPException {
public:

    BIOException(const std::string& message)
        : IMAPException(message, 22) {}

};
