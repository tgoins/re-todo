open Types;

let component = ReasonReact.statelessComponent("TodoItem");

let todoItem =
  Css.style([Css.width(Css.pct(100.0)), Css.flexDirection(Css.column)]);
let todoItemContainer = Css.style([]);
let cardActions = Css.style([Css.justifyContent(Css.flexEnd)]);
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
          <MaterialUi.Grid xs=V8 item=true>
            <MaterialUi.CardHeader title={todo.title |> ReasonReact.string}>
              <MaterialUi.Typography>
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