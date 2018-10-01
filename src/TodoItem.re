open Types;

let component = ReasonReact.statelessComponent("TodoItem");

let todoItem =
  Css.style([Css.width(Css.pct(100.0)), Css.flexDirection(Css.column)]);
let todoItemContainer =
  Css.style([
    Css.important(Css.marginTop(Css.em(1.0))),
    Css.important(Css.marginBottom(Css.em(1.0))),
  ]);
let cardActions = Css.style([Css.justifyContent(Css.flexEnd)]);

let make = (~todo: todo, ~onChangeState=?, ~onDelete=?, _children) => {
  ...component,
  render: _self =>
    <MaterialUi.Grid
      spacing=V16 xs=V12 item=true justify=`Center className=todoItemContainer>
      <MaterialUi.Card className=todoItem>
        <MaterialUi.Grid container=true>
          <MaterialUi.Grid xs=V8 item=true>
            <MaterialUi.CardHeader title={todo.title |> ReasonReact.string}>
              <MaterialUi.Typography variant=`Title>
                {todo.title |> ReasonReact.string}
              </MaterialUi.Typography>
            </MaterialUi.CardHeader>
          </MaterialUi.Grid>
          <MaterialUi.Grid xs=V4 item=true>
            <MaterialUi.CardActions className=cardActions>
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
          </MaterialUi.Grid>
          <MaterialUi.Grid xs=V12>
            <p> {todo.description |> ReasonReact.string} </p>
          </MaterialUi.Grid>
        </MaterialUi.Grid>
      </MaterialUi.Card>
    </MaterialUi.Grid>,
};