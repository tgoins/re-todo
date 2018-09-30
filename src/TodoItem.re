open Types;

let component = ReasonReact.statelessComponent("TodoItem");

let make = (~todo: todo, ~onChangeState=?, ~onDelete=?, _children) => {
  ...component,
  render: _self =>
    <div>
      {
        switch (todo.complete) {
        | false =>
          <MaterialUi.Button
            color=`Primary
            variant=`Raised
            type_="button"
            onClick={
              switch (onChangeState) {
              | None => (_ => ())
              | Some(event) => event
              }
            }>
            {"Mark as done" |> ReasonReact.string}
          </MaterialUi.Button>
        | true =>
          <div>
            <MaterialUi.Button
              color=`Primary
              variant=`Raised
              type_="button"
              onClick={
                switch (onDelete) {
                | None => (_ => ())
                | Some(event) => event
                }
              }>
              {"Delete" |> ReasonReact.string}
            </MaterialUi.Button>
            <MaterialUi.Button
              type_="button"
              color=`Primary
              variant=`Raised
              onClick={
                switch (onChangeState) {
                | None => (_ => ())
                | Some(event) => event
                }
              }>
              {"Set to-do" |> ReasonReact.string}
            </MaterialUi.Button>
          </div>
        }
      }
      <h3> {todo.title |> ReasonReact.string} </h3>
      <p> {todo.description |> ReasonReact.string} </p>
    </div>,
};