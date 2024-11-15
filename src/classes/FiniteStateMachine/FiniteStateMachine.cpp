/**
 *	@file	src/classes/FiniteStateMachine/FiniteStateMachine.cpp
 *	@brief	FiniteStateMachine class file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include "FiniteStateMachine.hpp"


/**
 *  @brief	Function transfer State to INIT.
 */
void FiniteStateMachine::transitionToInit() {

    this->currentState = State::INIT;

}


/**
 *  @brief	Function transfer State to AUTH.
 */
void FiniteStateMachine::transitionToAuth() {

    this->currentState = State::AUTH;

}


/**
 *  @brief	Function transfer State to SELECT.
 */
void FiniteStateMachine::transitionToSelect() {

    this->currentState = State::SELECT;

}


/**
 *  @brief	Function transfer State to DOWNLOAD.
 */
void FiniteStateMachine::transitionToDownload()
{

    this->currentState = State::DOWNLOAD;

}


/**
 *  @brief	Function transfer State to QUIT.
 */
void FiniteStateMachine::transitionToQuit()
{

    this->currentState = State::QUIT;

}


/**
 *  @brief	Function return current state.
 */
FiniteStateMachine::State FiniteStateMachine::getState() const
{

    return this->currentState;

}