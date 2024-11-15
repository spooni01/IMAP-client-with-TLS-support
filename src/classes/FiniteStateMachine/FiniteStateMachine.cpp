/**
 *	@file	src/classes/FiniteStateMachine/FiniteStateMachine.cpp
 *	@brief	FiniteStateMachine class file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */

#include "FiniteStateMachine.hpp"


/**
 *  @brief	Function transfer State to INIT.
 */
void FiniteStateMachine::transitionToInit()
{

    DEBUG_PRINT(ANSI_COLOR_GRAY, "FiniteStateMachine::transitionToInit() -> State is now INIT");
    this->currentState = State::INIT;

}


/**
 *  @brief	Function transfer State to AUTH.
 */
void FiniteStateMachine::transitionToAuth()
{

    DEBUG_PRINT(ANSI_COLOR_GRAY, "FiniteStateMachine::transitionToAuth() -> State is now AUTH");
    this->currentState = State::AUTH;

}


/**
 *  @brief	Function transfer State to SELECT.
 */
void FiniteStateMachine::transitionToSelect()
{

    DEBUG_PRINT(ANSI_COLOR_GRAY, "FiniteStateMachine::transitionToSelect() -> State is now SELECT");
    this->currentState = State::SELECT;

}


/**
 *  @brief	Function transfer State to DOWNLOAD.
 */
void FiniteStateMachine::transitionToDownload()
{

    DEBUG_PRINT(ANSI_COLOR_GRAY, "FiniteStateMachine::transitionToDownload() -> State is now DOWNLOAD");
    this->currentState = State::DOWNLOAD;

}


/**
 *  @brief	Function transfer State to QUIT.
 */
void FiniteStateMachine::transitionToQuit()
{

    DEBUG_PRINT(ANSI_COLOR_GRAY, "FiniteStateMachine::transitionToQuit() -> State is now QUIT");
    this->currentState = State::QUIT;

}


/**
 *  @brief	Function transfer State to END.
 */
void FiniteStateMachine::transitionToEnd()
{

    DEBUG_PRINT(ANSI_COLOR_GRAY, "FiniteStateMachine::transitionToEnd() -> State is now END");
    this->currentState = State::END;

}


/**
 *  @brief	Function return current state.
 */
FiniteStateMachine::State FiniteStateMachine::getState() const
{

    return this->currentState;

}