type player =
  | Cross
  | Circle;

type square =
  | Empty
  | Marked(player);

type row = list(square);
type board = list(row);

type gameState =
  | Playing(player)
  | Winner(player)
  | Draw;

type state = {
  board,
  gameState,
};