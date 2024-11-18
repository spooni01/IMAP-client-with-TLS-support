/**
 *	@file	Classes/MessageFactory/MessageFactory.hpp
 *	@brief	MessageFactory header file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#ifndef MESSAGEFACTORY_HPP
#define MESSAGEFACTORY_HPP


/**
 * @class MessageFactory
 * 
 *  This class is responsible for creating and managing a collection of messages
 *  (represented by Message objects).
 */
class MessageFactory {
private:

	/**
	 *  @brief	List of all messages stored in the factory.
	 *
	 *  This vector holds all the messages managed by the MessageFactory class.
	 *  Each message is represented as a Message object. The Message class is
	 *  assumed to contain all the necessary data related to a single message.
	 */
	std::vector<Message> listOfMessages;


	/**
	 *  @brief The directory of output files.
	 */
	std::string outputDirectory;


	using UIDList = std::vector<int>;
    using DataStorage = std::map<std::string, UIDList>;
	DataStorage data_;

public:

	/**
	 *  @brief	Default constructor for the MessageFactory class.
	 *  
	 *  @param  directory A directory where messages are storen.
	 */
	MessageFactory(std::string directory);

	/**
	 *  @brief	Destructor for the MessageFactory class.
	 */
	~MessageFactory();

	/**
 	 *  @brief	Add new message to listOfMessages
	 * 
	 *  @param  nonParsedPacket Non parsed packet.
	 *  @param  directory A directory where new message will be store.
	 */
	void addNewMessage(std::string nonParsedPacket, std::string directory);

	/**
	 *  @brief	Load messages from file into listOfMessages
	 * 
	 *  @param  directory A directory where new message will be store.
	 */
	void loadMessagesFromFile(const std::string& directory);

	/**
	 *  @brief	Checks if message exists.
	 * 
	 *  @param  messageID ID of message to find.
	 * 
	 *  @return true when message exists.
	 */
	bool messageExists(std::string messageID);

	/**
	 *  @brief	Find message in listOfMessages.
	 * 
	 *  @param  messageID ID of message to find.
	 * 
	 *  @return pointer on message.
	 */
	Message* findMessage(std::string messageID);

	/**
	 *  @brief	Adds a new UID to the data storage for a given server.
	 *
	 * @param server The server name.
	 * @param uid The UID to add.
	 */
	void addToDataStorage(const std::string& server, int uid);

	/**
	 *  @brief	Checks if a given server and UID exist in the data storage.
	 *
	 * @param server The server name.
	 * @param uid The UID to check.
	 * 
	 * @return `true` if the server and UID exist, `false` otherwise.
	 */
	bool existsInDataStorage(const std::string& server, int uid) const;

	/**
	 *  @brief	Saves the data storage to a file.
	 */
	void saveDataStorageToFile();

	/**
	 *  @brief	Loads the data storage from a file.
	 */
	void loadDataStorageFromFile();

};

#endif // MESSAGEFACTORY_HPP