open Types;

let component = ReasonReact.statelessComponent("TodoItem");

let todoItem =
  Css.style([Css.width(Css.pct(100.0)), Css.flexDirection(Css.column)]);
let todoItemContainer = Css.style([]);
let descriptionClass =
  Css.style([Css.whiteSpace(`preWrap), Css.wordWrap(Css.breakWord)]);
let cardContent = Css.style([Css.important(Css.paddingTop(`px(0)))]);

let make = (~todo: todo, ~onChangeState=?, ~onDelete=?, _children) => {
  ...component,
  render: _self =>
    <MaterialUi.Grid
      xs=V12 lg=V6 item=true justify=`Center className=todoItemContainer>
      <MaterialUi.Card className=todoItem>
        <MaterialUi.Grid container=true>
          <MaterialUi.Grid xs=V12 item=true>
            <MaterialUi.CardHeader
              title={todo.title |> ReasonReact.string}
              action={
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
            />
          </MaterialUi.Grid>
          <MaterialUi.Grid xs=V12>
            <MaterialUi.CardContent className=cardContent>
              <MaterialUi.Typography className=descriptionClass>
                {todo.description |> ReasonReact.string}
              </MaterialUi.Typography>
            </MaterialUi.CardContent>
          </MaterialUi.Grid>
        </MaterialUi.Grid>
      </MaterialUi.Card>
    </MaterialUi.Grid>,
};