/**
 *	@file	Classes/Message/Message.cpp
 *	@brief	Message file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include "MessageFactory.hpp"


/**
 *  @brief	Default constructor for the MessageFactory class.
 */
MessageFactory::MessageFactory()
{

    // TODO Message factory

}


/**
 *  @brief	Add new message to listOfMessages
 * 
 *  @param  nonParsedPacket Non parsed packet.
 */
void MessageFactory::addNewMessage(std::string nonParsedPacket)
{

    // Parse
    Message msg(nonParsedPacket);

    // Ensure the directory 'maildir' exists
    std::string directory = "maildir";
    if (!std::filesystem::exists(directory)) {
        if (!std::filesystem::create_directory(directory)) {
            throw std::runtime_error("Failed to create directory: " + directory);
        }
    }

    // Define the file path
    std::string filePath = directory + "/" + msg.getFileName() + ".txt";

    // Open the file and write the content
    std::ofstream outFile(filePath);
    if (!outFile) {
        throw std::runtime_error("Failed to open file for writing: " + filePath);
    }

    outFile << msg.getFormattedOutput();
    if (!outFile.good()) {
        throw std::runtime_error("Failed to write to file: " + filePath);
    }

    outFile.close();

}