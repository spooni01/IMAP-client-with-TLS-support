TEST(FiniteStateMachineTest, InitialStateIsUnset) {
    FiniteStateMachine fsm;
    EXPECT_EQ(fsm.getState(), FiniteStateMachine::State::INIT);
}

TEST(FiniteStateMachineTest, TransitionToInit) {
    FiniteStateMachine fsm;
    fsm.transitionToInit();
    EXPECT_EQ(fsm.getState(), FiniteStateMachine::State::INIT);
}

TEST(FiniteStateMachineTest, TransitionToAuth) {
    FiniteStateMachine fsm;
    fsm.transitionToAuth();
    EXPECT_EQ(fsm.getState(), FiniteStateMachine::State::AUTH);
}

TEST(FiniteStateMachineTest, TransitionToSelect) {
    FiniteStateMachine fsm;
    fsm.transitionToSelect();
    EXPECT_EQ(fsm.getState(), FiniteStateMachine::State::SELECT);
}

TEST(FiniteStateMachineTest, TransitionToDownload) {
    FiniteStateMachine fsm;
    fsm.transitionToDownload();
    EXPECT_EQ(fsm.getState(), FiniteStateMachine::State::DOWNLOAD);
}

TEST(FiniteStateMachineTest, TransitionToQuit) {
    FiniteStateMachine fsm;
    fsm.transitionToQuit();
    EXPECT_EQ(fsm.getState(), FiniteStateMachine::State::QUIT);
}