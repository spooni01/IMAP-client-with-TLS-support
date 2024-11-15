/**
 *	@file	src/classes/FiniteStateMachine/FiniteStateMachine.hpp
 *	@brief	Finite state machine header file
 *	@author	Adam Ližičiar (xlizic00@stud.fit.vutbr.cz)
 */


#ifndef FINITESTATEMACHINE_HPP
#define FINITESTATEMACHINE_HPP


/**
 *  @class FiniteStateMachine
 * 
 *  This class works with finite state machine.
 */
class FiniteStateMachine {
public:

    /**
     *  @enum State
     *  States of finite state machine.
     */
    enum class State {
        INIT,
        AUTH,
        SELECT,
        DOWNLOAD,
        QUIT
    };


    /**
	 *  @brief	Function transfer State to INIT.
	 */
    void transitionToInit();


    /**
	 *  @brief	Function transfer State to AUTH.
	 */
    void transitionToAuth();


    /**
	 *  @brief	Function transfer State to SELECT.
	 */
    void transitionToSelect();


    /**
	 *  @brief	Function transfer State to DOWNLOAD.
	 */
    void transitionToDownload();


    /**
	 *  @brief	Function transfer State to QUIT.
	 */
    void transitionToQuit();

    
    /**
	 *  @brief	Function return current State.
     *  @return Current state.
	 */
    State getState() const;


private:

    /**
	 *  @brief	Current state of finite state machine.
	 */
    State currentState = State::INIT;

};

#endif // FINITESTATEMACHINE_HPP