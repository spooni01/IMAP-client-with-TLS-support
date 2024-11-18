/**
 *	@file	Classes/Message/Message.cpp
 *	@brief	Message file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include "MessageFactory.hpp"


/**
 *  @brief	Default constructor for the MessageFactory class.
 *  
 *  @param  directory A directory where messages are storen.
 */
MessageFactory::MessageFactory(std::string directory)
{

    this->outputDirectory = directory;
    this->loadDataStorageFromFile();

}


/**
 *  @brief	Destructor for the MessageFactory class.
 */
MessageFactory::~MessageFactory()
{

    this->saveDataStorageToFile();

}


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


/**
 *  @brief	Load messages from file into listOfMessages
 * 
 *  @param  directory A directory where new message will be store.
 */
void MessageFactory::loadMessagesFromFile(const std::string& directory) 
{

    // Check if folder exists.
    if (!std::filesystem::exists(directory))
        return;
    
    // Loop through files and save message ID`s.
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            std::ifstream file(entry.path());
            std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            Message msg(content);

            // Check if Message-ID exists.
            if (msg.headers.find("Message-ID") == msg.headers.end()) 
                throw FileException("Some email in file fo not have message ID");
            
            // Extract and set message ID.
            std::string messageID = msg.headers["Message-ID"];

            // Remove angle brackets from message ID.
            msg.setMessageID(messageID);

            this->listOfMessages.push_back(msg);
        }
    }

}


/**
 *  @brief	Checks if message exists.
 * 
 *  @param  messageID ID of message to find.
 * 
 *  @return true when message exists.
 */
bool MessageFactory::messageExists(std::string messageID) {

	return std::any_of(listOfMessages.begin(), listOfMessages.end(),
		[messageID](const Message& message) {
			return message.messageID == messageID;
		});

}


/**
 *  @brief	Find message in listOfMessages.
 * 
 *  @param  messageID ID of message to find.
 * 
 *  @return pointer on message.
 */
Message* MessageFactory::findMessage(std::string messageID) {

  	auto found = std::find_if(listOfMessages.begin(), listOfMessages.end(),
    	[messageID](const Message& message) {
        	return message.messageID == messageID;
    });

  	if (found != listOfMessages.end()) 
    	return &(*found);
	else 
    	return nullptr;

}


/**
 * @brief	Adds a new UID to the data storage for a given server.
 *
 * @param server The server name.
 * @param uid The UID to add.
 */
void MessageFactory::addToDataStorage(const std::string& server, int uid)
{

    auto it = data_.find(server);
    if (it != data_.end()) 
        it->second.push_back(uid);
    else 
        data_.insert({server, {uid}});

}


/**
 *  @brief	Checks if a given server and UID exist in the data storage.
 *
 * @param server The server name.
 * @param uid The UID to check.
 * 
 * @return `true` if the server and UID exist, `false` otherwise.
 */
bool MessageFactory::existsInDataStorage(const std::string& server, int uid) const
{
        
    auto it = data_.find(server);
    if (it != data_.end()) {
        return std::find(it->second.begin(), it->second.end(), uid) != it->second.end();
    }
    return false;
}


/**
 *  @brief	Saves the data storage to a file.
 */
void MessageFactory::saveDataStorageToFile()
{

    std::ofstream file(outputDirectory + "/imapcl.log");
    if (file.is_open()) {
        for (const auto& pair : data_) {
            file << pair.first << ":";
            for (size_t i = 0; i < pair.second.size(); ++i) {
                file << " " << pair.second[i];
                if (i < pair.second.size() - 1) {
                    file << ",";
                }
            }
            file << std::endl;
        }
        file.close();
    } else {
        throw FileException("Error opening storage file");
    }
}


/**
 *  @brief	Loads the data storage from a file.
 */
void MessageFactory::loadDataStorageFromFile()
{
    
    std::string filename = outputDirectory + "/imapcl.log";

    // Check if file exists.
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::ofstream outfile(filename);
        if (!outfile.is_open()) {
            throw FileException("Error creating data storage file");
        }
        outfile.close();
    } else {
        file.close(); 
    }

    // Open the file for reading.
    file.open(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t pos = line.find(':');
            if (pos != std::string::npos) {
                std::string server = line.substr(0, pos);
                std::string uids = line.substr(pos + 1);

                // Split uids by comma.
                std::vector<std::string> uidStrings;
                std::istringstream iss(uids);
                std::string uidStr;
                while (std::getline(iss, uidStr, ',')) {
                    uidStrings.push_back(uidStr);
                }

                // Convert strings to integers and add to data storage.
                for (const std::string& uidStr : uidStrings) {
                    int uid;
                    std::istringstream uidIss(uidStr);
                    if (uidIss >> uid) {
                        addToDataStorage(server, uid);
                    } else {
                        throw FileException("Invalid uid format in storage file");
                    }
                }
            } else {
                throw FileException("Invalid line in storage file");
            }
        }
        file.close();
    } else {
        throw FileException("Error opening data storage file");
    }

}
