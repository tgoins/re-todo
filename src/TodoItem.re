open Types;

let component = ReasonReact.statelessComponent("TodoItem");

let todoItem =
  Css.style([Css.width(Css.pct(100.0)), Css.flexDirection(Css.column)]);
let todoItemContainer = Css.style([]);
let descriptionClass =
  Css.style([Css.whiteSpace(`preWrap), Css.wordWrap(Css.breakWord)]);
let cardContent = Css.style([Css.important(Css.paddingTop(`px(0)))]);

let make = (~todo: todo, ~onChangeState, ~onDelete=?, _children) => {
  ...component,
  render: _self =>
    MaterialUi.(
      <Grid xs=V12 lg=V6 item=true justify=`Center className=todoItemContainer>
        <Card className=todoItem>
          <Grid container=true>
            <Grid xs=V12 item=true>
              <CardHeader
                title={todo.title |> ReasonReact.string}
                action={
                  switch (todo.complete) {
                  | false =>
                    <div>
                      <IconButton onClick=onChangeState>
                        <MaterialUIIcons.Check />
                      </IconButton>
                    </div>
                  | true =>
                    <div>
                      <IconButton
                        onClick={
                          switch (onDelete) {
                          | None => (_ => ())
                          | Some(event) => event
                          }
                        }>
                        <MaterialUIIcons.Delete />
                      </IconButton>
                      <IconButton onClick=onChangeState>
                        <MaterialUIIcons.Undo />
                      </IconButton>
                    </div>
                  }
                }
              />
            </Grid>
            <Grid xs=V12>
              <CardContent className=cardContent>
                <Typography className=descriptionClass>
                  {todo.description |> ReasonReact.string}
                </Typography>
              </CardContent>
            </Grid>
          </Grid>
        </Card>
      </Grid>
    ),
};