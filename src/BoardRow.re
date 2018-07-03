let component = ReasonReact.statelessComponent("BoardRow");

let make =
    (
      ~gameState: GameTypes.gameState,
      ~row: GameTypes.row,
      ~onMark,
      ~rowIndex: int,
      _children,
    ) => {
  ...component,
  render: _self =>
    <div className="board-row">
      (
        row
        |> List.mapi((colIndex: int, value: GameTypes.field) => {
             let id = string_of_int(rowIndex) ++ string_of_int(colIndex);
             <Square key=id value onMark=(() => onMark(id)) gameState />;
           })
        |> Array.of_list
        |> ReasonReact.array
      )
    </div>,
};