open Types;

[@bs.module "@material-ui/core/styles"]
external createMuiTheme: Js.t({..}) => Js.t({..}) = "createMuiTheme";

type state = {
  todos: list(todo),
  newTitle: string,
  newDescription: string,
};

type action =
  | AddTodo
  | ChangeTitle(string)
  | ChangeDescription(string)
  | ChangeComplete(todo)
  | RemoveTodo(todo);

let centered = Css.style([Css.alignSelf(Css.center), Css.margin(Css.auto)]);
let root =
  Css.style([
    Css.display(Css.flexBox),
    Css.minHeight(Css.vh(100.0)),
    Css.flexDirection(Css.column),
  ]);
let layoutContainer = Css.style([Css.display(Css.flexBox), Css.flex(1)]);
let layout = Css.style([Css.flex(1), Css.justifyContent(Css.center)]);
let mainPaper =
  Css.style([Css.minHeight(Css.vh(80.0)), Css.padding(Css.px(8))]);
let form =
  Css.style([
    Css.display(Css.flexBox),
    Css.flexDirection(Css.column),
    Css.alignItems(Css.center),
  ]);

let theme =
  createMuiTheme({
    "palette": {
      "primary": {
        "main": MaterialUi.Colors.Blue.c500,
      },
      "secondary": {
        "main": MaterialUi.Colors.Red.c500,
      },
    },
  });

let component = ReasonReact.reducerComponent("App");

let handleClick = (_event, _self) => Js.log("clicked!");

let make = _children => {
  ...component,
  initialState: () => {todos: [], newTitle: "", newDescription: ""},
  reducer: (action, state) =>
    switch (action) {
    | AddTodo =>
      switch (state.newTitle) {
      | "" => ReasonReact.NoUpdate
      | _ =>
        ReasonReact.Update({
          todos:
            List.append(
              state.todos,
              [
                {
                  title: state.newTitle,
                  description: state.newDescription,
                  complete: false,
                },
              ],
            ),
          newDescription: "",
          newTitle: "",
        })
      }
    | ChangeComplete(todo) =>
      let updatedTodo = {...todo, complete: !todo.complete};
      ReasonReact.Update({
        ...state,
        todos:
          List.append(
            List.filter(t => t != todo, state.todos),
            [updatedTodo],
          ),
      });
    | ChangeDescription(description) =>
      ReasonReact.Update({...state, newDescription: description})
    | ChangeTitle(title) => ReasonReact.Update({...state, newTitle: title})
    | RemoveTodo(todo) =>
      ReasonReact.Update({
        ...state,
        todos: List.filter(t => t != todo, state.todos),
      })
    },
  render: self =>
    <MaterialUi_MuiThemeProvider theme={`ObjectGeneric(theme)}>
      <div className=root>
        <Header />
        <div className=layoutContainer>
          <main className=layout>
            <MaterialUi.Grid xs=V12 sm=V8 md=V6 lg=V4 className=centered>
              <MaterialUi.Paper className=mainPaper>
                <MaterialUi.Typography
                  variant=`Headline className=Styles.textCenter>
                  {"What needs to be done?" |> ReasonReact.string}
                </MaterialUi.Typography>
                <form
                  onSubmit={_event => self.send(AddTodo)}
                  action="#"
                  className=form>
                  <MaterialUi.Typography className=Styles.textCenter>
                    {"Title:" |> ReasonReact.string}
                  </MaterialUi.Typography>
                  <MaterialUi.Input
                    className=centered
                    onChange={
                      event =>
                        self.send(
                          ChangeTitle(ReactEvent.Form.target(event)##value),
                        )
                    }
                    value={`String(self.state.newTitle)}
                  />
                  <MaterialUi.Typography className=Styles.textCenter>
                    {"Description (optional):" |> ReasonReact.string}
                  </MaterialUi.Typography>
                  <MaterialUi.TextField
                    onChange={
                      event =>
                        self.send(
                          ChangeDescription(
                            ReactEvent.Form.target(event)##value,
                          ),
                        )
                    }
                    value={`String(self.state.newDescription)}
                  />
                  <MaterialUi.Button
                    type_="submit"
                    color=`Primary
                    variant=`Raised
                    className=Styles.smBtn>
                    {"Add to-do" |> ReasonReact.string}
                  </MaterialUi.Button>
                </form>
                {
                  switch (
                    List.length(
                      List.filter(t => !t.complete, self.state.todos),
                    )
                  ) {
                  | 0 => ReasonReact.null
                  | _ => <h2> {"To do" |> ReasonReact.string} </h2>
                  }
                }
                <ul>
                  ...{
                       List.map(
                         t =>
                           <TodoItem
                             todo=t
                             onChangeState={
                               _event => ChangeComplete(t) |> self.send
                             }
                           />,
                         List.filter(t => !t.complete, self.state.todos),
                       )
                       |> Array.of_list
                     }
                </ul>
                {
                  switch (
                    List.length(
                      List.filter(t => t.complete, self.state.todos),
                    )
                  ) {
                  | 0 => ReasonReact.null
                  | _ => <h2> {"Completed tasks" |> ReasonReact.string} </h2>
                  }
                }
                <ul>
                  ...{
                       List.map(
                         t =>
                           <TodoItem
                             todo=t
                             onDelete={_event => RemoveTodo(t) |> self.send}
                             onChangeState={
                               _event => ChangeComplete(t) |> self.send
                             }
                           />,
                         List.filter(t => t.complete, self.state.todos),
                       )
                       |> Array.of_list
                     }
                </ul>
              </MaterialUi.Paper>
            </MaterialUi.Grid>
          </main>
        </div>
        <Footer />
      </div>
    </MaterialUi_MuiThemeProvider>,
};

let default = ReasonReact.wrapReasonForJs(~component, _jsProps => make([||]));