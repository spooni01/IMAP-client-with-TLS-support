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

public:

	/**
	 *  @brief	Default constructor for the MessageFactory class.
	 */
	MessageFactory();

	/**
 	 *  @brief	Add new message to listOfMessages
	 * 
	 *  @param  nonParsedPacket Non parsed packet.
	 *  @param  directory A directory where new message will be store.
	 */
	void addNewMessage(std::string nonParsedPacket, std::string directory);

};

#endif // MESSAGEFACTORY_HPP