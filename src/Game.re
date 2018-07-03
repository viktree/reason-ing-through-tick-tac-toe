let component = ReasonReact.reducerComponent("Game");

let make = _children => {
  ...component,
  initialState: GameLogic.initialState,
  reducer: (action: GameLogic.action, state: GameTypes.state) =>
    switch (action) {
    | Restart => ReasonReact.Update(GameLogic.initialState())
    | ClickSquare((id: string)) =>
      let updatedBoard =
        GameLogic.updateBoard(state.board, state.gameState, id);
      ReasonReact.Update({
        board: updatedBoard,
        gameState:
          GameLogic.checkGameState3x3(
            updatedBoard,
            state.board,
            state.gameState,
          ),
      });
    },
  render: ({state, send}) =>
    <div className="game">
      <Board
        state
        onRestart=(_event => send(GameLogic.Restart))
        onMark=(id => send(GameLogic.ClickSquare(id)))
      />
    </div>,
};