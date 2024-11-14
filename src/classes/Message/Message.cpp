/**
 *	@file	Classes/Message/Message.cpp
 *	@brief	Message file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include "Message.hpp"


/**
 * @brief Constructor for Message.
 */
Message::Message()
{

    // TODO parsing of message

}


/**
 * @brief Prints the email message detail.
 */
void Message::print() const
{

    std::cout << "Date: " << date << "\n"
              << "From: " << from << "\n"
              << "To: " << to << "\n"
              << "Subject: " << subject << "\n"
              << "Message-ID: " << messageId << "\n\n"
              << body << "\n";

}