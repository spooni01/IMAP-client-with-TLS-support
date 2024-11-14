/**
 *	@file   exceptions/FileException.cpp
 *	@brief  Exception class for file errors.
 *	@author Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

class FileException : public IMAPException {
public:

    FileException(const std::string& message)
        : IMAPException(message, 6) {}

};