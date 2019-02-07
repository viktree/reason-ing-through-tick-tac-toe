let component = ReasonReact.statelessComponent("Square");

let getClass = (gameState: GameTypes.gameState, square: GameTypes.square) =>
  switch (gameState) {
  | Winner(player) => square == Marked(player) ? "winner square" : "square"
  | _ => "square"
  };

let isFinished = (value: GameTypes.gameState) =>
  switch (value) {
  | Winner(_) => true
  | _ => false
  };

let toValue = (square: GameTypes.square) =>
  switch (square) {
  | Marked(Cross) => "X"
  | Marked(Circle) => "O"
  | Empty => ""
  };

let make =
    (
      ~value: GameTypes.square,
      ~gameState: GameTypes.gameState,
      ~onMark,
      _children,
    ) => {
  ...component,
  render: _self =>
    <button
      className=(getClass(gameState, value))
      disabled=(gameState |> isFinished |> Js.Boolean.to_js_boolean)
      onClick=(_event => onMark())>
      (value |> toValue |> ReasonReact.string)
    </button>,
};