/**
 *	@file	Classes/Message/Message.hpp
 *	@brief	Message header file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#ifndef MESSAGE_HPP
#define MESSAGE_HPP

/**
 * @class Message
 * @brief A class to represent and parse an email message.
 */
class Message {
public:

    /**
     * @brief Constructor that initializes a Message object with raw email message data.
     *
     * @param rawMessage The raw email message in string format.
     */
    Message(const std::string& rawMessage);

    /**
     * @brief Get the formatted output of the parsed email message.
     *
     * @return A formatted string containing the email headers and body.
     */
    std::string getFormattedOutput() const;

    /**
     * @brief Get a filename derived from the Message-ID, which will be used for saving the message into folder.
     *
     * @return A string containing the message ID without angle brackets.
     */
    std::string getFileName() const;
    
    
    /**
     * @brief Extracts the UID from the raw message.
     *
     * @return A string containing the extracted UID.
     */
    std::string getExtractedUID() const { return extractUID(rawMessage); }

    /**
     * @brief Decodes a MIME-encoded string.
     *
     * @param text The MIME-encoded string to decode.
     * @return A string containing the decoded text.
     */
    std::string getDecodedMime(const std::string& text) const { return decodeMime(text); }

    /**
     * @brief Removes the last line from the given string.
     *
     * @param body The input string representing the message body.
     * @return A string with the last line removed.
     */
    std::string getLastLineRemoved(const std::string& body) const { return removeLastLine(body); }

    /**
     * @brief Retrieves the headers of the message.
     *
     * This method returns the map of headers parsed from the raw message. The headers typically include information
     * such as "From", "To", "Subject", and "Date".
     *
     * @return A constant reference to a map of headers (key-value pairs) extracted from the raw message.
     */
    const std::map<std::string, std::string>& getHeaders() const {
        return headers;
    }


private:

    /** 
     * @brief A string containing the unique identifier of the message.
     */
    std::string uid;

    /** 
     * @brief A string containing the "From" header value.
     */
    std::string from;

    /** 
     * @brief A string containing the "To" header value.
     */
    std::string to;

    /** 
     * @brief A string containing the "Subject" header value.
     */
    std::string subject;

    /** 
     * @brief A string containing the "Date" header value.
     */
    std::string date;

    /** 
     * @brief A string containing the "Content-Type" header value.
     */
    std::string contentType;

    /** 
     * @brief A string containing the "Message-ID" header value.
     */
    std::string messageID;

    /** 
     * @brief A map to store additional headers in key-value pairs.
     */
    std::map<std::string, std::string> headers;

    /** 
     * @brief A string containing the email body content.
     */
    std::string body;

    /**
     * @brief Parses the raw message and extracts the relevant headers and body.
     *
     * @param rawMessage The raw email message in string format.
     */
    void parseMessage(const std::string& rawMessage);

    /**
     * @brief Extracts the UID from the raw message string.
     * @param rawMessage The raw message from which the UID will be extracted.
     * @return A string containing the UID.
     */
    std::string extractUID(const std::string& rawMessage);

    /**
     * @brief Decodes MIME-encoded text.
     * 
     * @param text The MIME-encoded string to decode.
     * @return A string containing the decoded text.
     */
    std::string decodeMime(const std::string& text);

    /**
     * @brief Removes the last line from a given string.
     * 
     * @param input The input string from which the last line will be removed.
     * @return A new string without the last line.
     */
    std::string removeLastLine(const std::string& input);

};

#endif // MESSAGE_HPP