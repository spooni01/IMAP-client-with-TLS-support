/**
 *	@file	Classes/Message/Message.hpp
 *	@brief	Message header file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#ifndef MESSAGE_HPP
#define MESSAGE_HPP


/**
 * @class EmailMessage
 * 
 * @brief Represents an email message, storing header information and the body.
 */
class Message {
public:
    
    /**
     * @brief Constructor for Message.
     */
    Message();

    // Getters for each field
    const std::string& getDate() const { return date; }
    const std::string& getFrom() const { return from; }
    const std::string& getTo() const { return to; }
    const std::string& getSubject() const { return subject; }
    const std::string& getMessageId() const { return messageId; }
    const std::string& getBody() const { return body; }

    /**
     * @brief Prints the email message detail.
     */
    void print() const;
    
private:

    std::string date;       // The date the email was sent.
    std::string from;       // The sender's email address.
    std::string to;         // The recipient's email address.
    std::string subject;    // The subject of the email.
    std::string messageId;  // The unique message identifier.
    std::string body;       // The body of the email message.

};


#endif // MESSAGE_HPP