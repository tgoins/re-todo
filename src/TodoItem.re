open Types;

let component = ReasonReact.statelessComponent("TodoItem");

let make = (~todo: todo, ~onChangeState=?, ~onDelete=?, _children) => {
  ...component,
  render: _self =>
    <li>
      {
        switch (todo.complete) {
        | false =>
          <button
            type_="button"
            onClick={
              switch (onChangeState) {
              | None => (_ => ())
              | Some(event) => event
              }
            }>
            {"Mark as done" |> ReasonReact.string}
          </button>
        | true =>
          <div>
            <button
              type_="button"
              onClick={
                switch (onDelete) {
                | None => (_ => ())
                | Some(event) => event
                }
              }>
              {"Delete" |> ReasonReact.string}
            </button>
            <button
              type_="button"
              onClick={
                switch (onChangeState) {
                | None => (_ => ())
                | Some(event) => event
                }
              }>
              {"Set to-do" |> ReasonReact.string}
            </button>
          </div>
        }
      }
      <h3> {todo.title |> ReasonReact.string} </h3>
      <p> {todo.description |> ReasonReact.string} </p>
    </li>,
};