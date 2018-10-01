open Types;

let component = ReasonReact.statelessComponent("TodoItem");

let todoItem = Css.style([Css.width(Css.pct(100.0))]);

let make = (~todo: todo, ~onChangeState=?, ~onDelete=?, _children) => {
  ...component,
  render: _self =>
    <MaterialUi.Card className=todoItem>
      <MaterialUi.CardHeader title={todo.title |> ReasonReact.string}>
        <MaterialUi.Typography variant=`Title>
          {todo.title |> ReasonReact.string}
        </MaterialUi.Typography>
      </MaterialUi.CardHeader>
      <MaterialUi.CardActions>
        {
          switch (todo.complete) {
          | false =>
            <div>
              <MaterialUi.IconButton
                onClick={
                  switch (onChangeState) {
                  | None => (_ => ())
                  | Some(event) => event
                  }
                }>
                <MaterialUIIcons.Check />
              </MaterialUi.IconButton>
            </div>
          | true =>
            <div>
              <MaterialUi.IconButton
                onClick={
                  switch (onDelete) {
                  | None => (_ => ())
                  | Some(event) => event
                  }
                }>
                <MaterialUIIcons.Delete />
              </MaterialUi.IconButton>
              <MaterialUi.IconButton
                onClick={
                  switch (onChangeState) {
                  | None => (_ => ())
                  | Some(event) => event
                  }
                }>
                <MaterialUIIcons.Undo />
              </MaterialUi.IconButton>
            </div>
          }
        }
      </MaterialUi.CardActions>
      <p> {todo.description |> ReasonReact.string} </p>
    </MaterialUi.Card>,
};