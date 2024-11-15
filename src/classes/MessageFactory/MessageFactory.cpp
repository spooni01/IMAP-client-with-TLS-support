/**
 *	@file	Classes/Message/Message.cpp
 *	@brief	Message file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include "MessageFactory.hpp"


/**
 *  @brief	Default constructor for the MessageFactory class.
 */
MessageFactory::MessageFactory() {}


/**
 *  @brief	Add new message to listOfMessages
 * 
 *  @param  nonParsedPacket Non parsed packet.
 *  @param  directory A directory where new message will be store.
 */
void MessageFactory::addNewMessage(std::string nonParsedPacket, std::string directory)
{

    Message msg(nonParsedPacket);
    this->listOfMessages.push_back(Message(msg));


    // Ensure the directory exists.
    if (!std::filesystem::exists(directory)) {
        if (!std::filesystem::create_directory(directory)) {
            throw std::runtime_error("Failed to create directory: " + directory);
        }
    }

    // Define the file path.
    std::string filePath = directory + "/" + msg.getFileName() + ".txt";

    // Open the file and write the content.
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