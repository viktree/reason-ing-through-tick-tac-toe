open GameTypes;

type action =
  | ClickSquare(string)
  | Restart;

type winner =
  | Cross
  | Circle
  | NoOne;

type winningRows = list(list(int));
let winningCombs = [
  [0, 1, 2],
  [3, 4, 5],
  [6, 7, 8],
  [0, 3, 6],
  [1, 4, 7],
  [2, 5, 8],
  [0, 4, 8],
  [2, 4, 6],
];

let initialState = () : GameTypes.state => {
  board: [
    [Empty, Empty, Empty],
    [Empty, Empty, Empty],
    [Empty, Empty, Empty],
  ],
  gameState: Playing(Cross),
};

let gameEnded = board =>
  List.for_all(
    field => field == Marked(Circle) || field == Marked(Cross),
    board,
  );

let whosPlaying = (gameState: GameTypes.gameState) =>
  switch (gameState) {
  | Playing(Cross) => Playing(Circle)
  | _ => Playing(Cross)
  };

let getWinner = (flattenBoard, coords) =>
  switch (
    List.nth(flattenBoard, List.nth(coords, 0)),
    List.nth(flattenBoard, List.nth(coords, 1)),
    List.nth(flattenBoard, List.nth(coords, 2)),
  ) {
  | (Marked(Cross), Marked(Cross), Marked(Cross)) => Cross
  | (Marked(Circle), Marked(Circle), Marked(Circle)) => Circle
  | (_, _, _) => NoOne
  };

let checkGameState =
    (
      winningRows: winningRows,
      updatedBoard: GameTypes.board,
      oldBoard: GameTypes.board,
      gameState: GameTypes.gameState,
    ) =>
  oldBoard == updatedBoard ?
    gameState :
    {
      let flattenBoard = List.flatten(updatedBoard);
      let rec check = (rest: winningRows) => {
        let head = List.hd(rest);
        let tail = List.tl(rest);
        let gameEnded = board =>
          List.for_all(
            field => field == Marked(Circle) || field == Marked(Cross),
            board,
          );
        let whosPlaying = (gameState: gameState) =>
          switch (gameState) {
          | Playing(Cross) => Playing(Circle)
          | _ => Playing(Cross)
          };
        switch (
          getWinner(flattenBoard, head),
          gameEnded(flattenBoard),
          tail,
        ) {
        | (Cross, _, _) => Winner(Cross)
        | (Circle, _, _) => Winner(Circle)
        | (_, true, []) => Draw
        | (_, false, []) => whosPlaying(gameState)
        | _ => check(tail)
        };
      };
      check(winningRows);
    };

let checkGameState3x3 = checkGameState(winningCombs);

let updateBoard = (board: board, gameState: gameState, id) =>
  board
  |> List.mapi((rowIndex: int, row: row) =>
       row
       |> List.mapi((colIndex: int, value: field) =>
            string_of_int(rowIndex) ++ string_of_int(colIndex) === id ?
              switch (gameState, value) {
              | (_, Marked(_)) => value
              | (Playing(player), Empty) => Marked(player)
              | (_, Empty) => Empty
              } :
              value
          )
     );