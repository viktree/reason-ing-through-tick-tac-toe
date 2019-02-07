open GameTypes;

type action =
  | ClickSquare(string)
  | Restart;

type winner =
  | Cross
  | Circle
  | NoOne;

type winningRows = list(list(int));

let initialState = () : GameTypes.state => {
  board: [
    [Empty, Empty, Empty],
    [Empty, Empty, Empty],
    [Empty, Empty, Empty],
  ],
  gameState: Playing(Cross),
};

let getWinner = board =>
  switch (board) {
  | [
      [Marked(Cross), Marked(Cross), Marked(Cross)],
      [_, _, _],
      [_, _, _],
    ] =>
    Cross
  | [
      [_, _, _],
      [Marked(Cross), Marked(Cross), Marked(Cross)],
      [_, _, _],
    ] =>
    Cross
  | [
      [_, _, _],
      [_, _, _],
      [Marked(Cross), Marked(Cross), Marked(Cross)],
    ] =>
    Cross
  | [
      [_, Marked(Cross), _],
      [_, Marked(Cross), _],
      [_, Marked(Cross), _],
    ] =>
    Cross
  | [
      [Marked(Cross), _, _],
      [Marked(Cross), _, _],
      [Marked(Cross), _, _],
    ] =>
    Cross
  | [
      [_, _, Marked(Cross)],
      [_, _, Marked(Cross)],
      [_, _, Marked(Cross)],
    ] =>
    Cross
  | [
      [Marked(Cross), _, _],
      [_, Marked(Cross), _],
      [_, _, Marked(Cross)],
    ] =>
    Cross
  | [
      [_, _, Marked(Cross)],
      [_, Marked(Cross), _],
      [Marked(Cross), _, _],
    ] =>
    Cross
  /* TODO: We have to check the same cases for the board below as we checked with the board above.
   * Is there a more idomatic way to do this?
   * */
  | [
      [Marked(Circle), Marked(Circle), Marked(Circle)],
      [_, _, _],
      [_, _, _],
    ] =>
    Circle
  | [
      [_, _, _],
      [Marked(Circle), Marked(Circle), Marked(Circle)],
      [_, _, _],
    ] =>
    Circle
  | [
      [_, _, _],
      [_, _, _],
      [Marked(Circle), Marked(Circle), Marked(Circle)],
    ] =>
    Circle
  | [
      [_, Marked(Circle), _],
      [_, Marked(Circle), _],
      [_, Marked(Circle), _],
    ] =>
    Circle
  | [
      [Marked(Circle), _, _],
      [Marked(Circle), _, _],
      [Marked(Circle), _, _],
    ] =>
    Circle
  | [
      [_, _, Marked(Circle)],
      [_, _, Marked(Circle)],
      [_, _, Marked(Circle)],
    ] =>
    Circle
  | [
      [Marked(Circle), _, _],
      [_, Marked(Circle), _],
      [_, _, Marked(Circle)],
    ] =>
    Circle
  | [
      [_, _, Marked(Circle)],
      [_, Marked(Circle), _],
      [Marked(Circle), _, _],
    ] =>
    Circle
  | _ => NoOne
  };

let gameEnded = board =>
  ! List.exists(square => square == Empty, List.flatten(board));

let nextPlayer = (gameState: gameState) =>
  switch (gameState) {
  | Playing(Cross) => Playing(Circle)
  | _ => Playing(Cross)
  };

let getNextGameState =
    (currentBoard: GameTypes.board, currentGameState: GameTypes.gameState) =>
  switch (getWinner(currentBoard)) {
  | Cross => Winner(Cross)
  | Circle => Winner(Circle)
  | _ => gameEnded(currentBoard) ? Draw : nextPlayer(currentGameState)
  };

let checkGameState =
    (
      currentBoard: GameTypes.board,
      oldBoard: GameTypes.board,
      currentGameState: GameTypes.gameState,
    ) => {
  let boardSameAsBefore = oldBoard == currentBoard;
  boardSameAsBefore ?
    currentGameState : getNextGameState(currentBoard, currentGameState);
};

let getSquareId = (rowIndex: int, columnIndex: int) =>
  string_of_int(rowIndex) ++ string_of_int(columnIndex);

let updateBoard = (board: board, gameState: gameState, id) =>
  board
  |> List.mapi((rowIndex: int, row: row) =>
       row
       |> List.mapi((colIndex: int, square: square) =>
            square == Empty && getSquareId(rowIndex, colIndex) === id ?
              switch (gameState) {
              | Playing(player) => Marked(player)
              | _ => Empty
              } :
              square
          )
     );