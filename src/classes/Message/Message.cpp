/**
 *	@file	Classes/Message/Message.cpp
 *	@brief	Message class file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include "Message.hpp"


/**
 * @brief Constructor that initializes a Message object with raw email message data.
 *
 * @param rawMessage The raw email message in string format.
 */
Message::Message(const std::string& rawMessage)
{

    parseMessage(rawMessage);

}


/**
 * @brief Parses the raw message and extracts the relevant headers and body.
 *
 * @param rawMessage The raw email message in string format.
 */
void Message::parseMessage(const std::string& rawMessage)
{

    // Remove the IMAP response part.
    std::string cleanedMessage = std::regex_replace(rawMessage, std::regex(R"(\)\s*A\d{3} .+)"), "");

    std::istringstream stream(cleanedMessage);
    std::string line;
    std::regex headerPattern(R"(^([A-Za-z\-]+):\s*(.*)$)");
    bool bodyStarted = false;
    std::stringstream bodyStream;

    while (std::getline(stream, line)) {

        // Trim the line to avoid any unwanted whitespace issues.
        line = std::regex_replace(line, std::regex("^\\s+|\\s+$"), "");

        // Check for the end of the headers.
        if (line.empty() && !bodyStarted) {
            bodyStarted = true;  // Body section starts after the first blank line.
            continue;
        }

        // If it is body, save it to bodyStream.
        if (bodyStarted) {
            bodyStream << line << "\n";
        } else {
            std::smatch match;
            if (std::regex_match(line, match, headerPattern)) {
                std::string key = match[1];
                std::string value = match[2];

                // Decode the value if it's MIME-encoded.
                headers[key] = decodeMime(value);
            }
        }
    }

    // Set fields from headers.
    uid = extractUID(cleanedMessage);
    subject = headers["Subject"];
    from = headers["From"];
    to = headers["To"];
    date = headers["Date"];
    contentType = headers["Content-Type"];
    messageID = headers["Message-ID"]; 
    body = removeLastLine(bodyStream.str()); // Remove blank line.
    body = removeLastLine(body); // Remove FETCH OK line.
    body = removeLastLine(body); // Remove blank line.

}


/**
 * @brief Extracts the UID from the raw message string.
 * @param rawMessage The raw message from which the UID will be extracted.
 * @return A string containing the UID.
 */
std::string Message::extractUID(const std::string& rawMessage)
{

    std::regex uidPattern(R"(\* \d+ FETCH \(UID (\d+))");
    std::smatch match;

    if (std::regex_search(rawMessage, match, uidPattern)) 
        return match[1];
    
    return {}; // Nothing found.

}


/**
 * @brief Get the formatted output of the parsed email message.
 *
 * @return A formatted string containing the email headers and body.
 */
std::string Message::getFormattedOutput() const
{

    std::ostringstream output;

    output << "Date: " << date << "\n";
    output << "From: " << from << "\n";
    output << "To: " << to << "\n";
    output << "Subject: " << subject << "\n";
    output << "Message-ID: " << messageID << "\n\n";

    output << body << "\n";

    return output.str();

}


/**
 * @brief Get a filename derived from the Message-ID, which will be used for saving the message into folder.
 *
 * @return A string containing the message ID without angle brackets.
 */
std::string Message::getFileName() const
{

    if (!messageID.empty() && messageID.front() == '<' && messageID.back() == '>')
        return subject + "_" + messageID.substr(1, messageID.size() - 2);

    return subject + "_" + messageID; 

}


/**
 * @brief Decodes MIME-encoded text.
 * 
 * ! IMPORTANT: This function was inspired from funcion in library
 * mimetic (https://www.codesink.org/mimetic_mime_library.html).
 * 
 * @param text The MIME-encoded string to decode.
 * @return A string containing the decoded text.
 */
std::string Message::decodeMime(const std::string& text)
{

    std::regex mimePattern(R"(\=\?([^\?]+)\?([BQ])\?([^\?]+)\?\=)");
    std::smatch match;
    std::string decoded = text;

    // MIME encoded format is found.
    while (std::regex_search(decoded, match, mimePattern)) {

        std::string charset = match[1];
        char encoding = match[2].str()[0];
        std::string encodedText = match[3];

        if (encoding == 'B' || encoding == 'b') { 
            return text;  // Skip.
        } else if (encoding == 'Q' || encoding == 'q') {  
            std::string newDecoded;
            for (size_t i = 0; i < encodedText.size(); ++i) {
                if (encodedText[i] == '_') {
                    newDecoded += ' '; 
                } else if (encodedText[i] == '=') {
                    int value;
                    std::istringstream hex(encodedText.substr(i + 1, 2));
                    if (hex >> std::hex >> value) {
                        newDecoded += static_cast<char>(value);
                        i += 2;
                    }
                } else {
                    newDecoded += encodedText[i];
                }
            }
            decoded.replace(match.position(0), match.length(0), newDecoded);
        }
    }
    return decoded;

}


/**
 * @brief Removes the last line from a given string.
 * 
 * @param input The input string from which the last line will be removed.
 * @return A new string without the last line.
 */
std::string Message::removeLastLine(const std::string& input)
{

    size_t pos = input.find_last_of("\n");

    if (pos != std::string::npos) {
        return input.substr(0, pos); 
    }
    return input;

}

