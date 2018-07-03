let setStatus = (gameState: GameTypes.gameState) =>
  switch (gameState) {
  | Playing(Cross) => "Cross is playing"
  | Playing(Circle) => "Circle is playing"
  | Winner(Cross) => "The winner is Cross"
  | Winner(Circle) => "The winner is Circle"
  | Draw => "Draw"
  };

let component = ReasonReact.statelessComponent("Board");
let make = (~state: GameTypes.state, ~onMark, ~onRestart, _children) => {
  ...component,
  render: _self =>
    <div className="game-board">
      (
        state.board
        |> List.mapi((index: int, row: GameTypes.row) =>
             <BoardRow
               key=(string_of_int(index))
               gameState=state.gameState
               row
               onMark
               index
             />
           )
        |> Array.of_list
        |> ReasonReact.array
      )
      <div className="status">
        (state.gameState |> setStatus |> ReasonReact.string)
      </div>
      (
        switch (state.gameState) {
        | Playing(_) => ReasonReact.null
        | _ =>
          <button className="restart" onClick=onRestart>
            (ReasonReact.string("Restart"))
          </button>
        }
      )
    </div>,
};