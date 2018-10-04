open Types;
open Utils;

[@bs.module "@material-ui/core/styles"]
external createMuiTheme: Js.t({..}) => Js.t({..}) = "createMuiTheme";

type state = {
  todos: list(todo),
  newTitle: string,
  newDescription: string,
  lastId: int,
  snackbarOpen: bool,
  lastDeletedTodo: option(todo),
};

type action =
  | AddTodo
  | ChangeTitle(string)
  | ChangeDescription(string)
  | ChangeComplete(todo)
  | RemoveTodo(todo)
  | ResetSnackbar
  | UndoDelete;

let fullWidth = Css.width(Css.pct(100.0));
let flexBox = Css.display(Css.flexBox);
let marginAuto = Css.margin(Css.auto);
let submitBtnContainer =
  Css.style([
    Css.important(Css.marginTop(Css.em(1.0))),
    Css.important(Css.margin(Css.auto)),
  ]);
let centered = Css.style([Css.alignSelf(Css.center), marginAuto]);
let root =
  Css.style([
    flexBox,
    Css.minHeight(Css.vh(100.0)),
    Css.flexDirection(Css.column),
    Css.flexGrow(1),
  ]);
let layoutContainer = Css.style([flexBox, Css.flex(1)]);
let layout =
  Css.style([
    Css.flex(1),
    Css.justifyContent(Css.center),
    Css.maxWidth(Css.pct(100.0)),
  ]);
let mainPaper =
  Css.style([
    Css.width(Css.pct(100.0)),
    Css.marginTop(Css.em(1.0)),
    Css.marginBottom(Css.em(1.0)),
  ]);
let form =
  Css.style([
    fullWidth,
    Css.alignSelf(Css.center),
    Css.alignItems(Css.center),
    Css.marginTop(Css.px(10)),
    Css.marginBottom(Css.px(10)),
    Css.marginLeft(Css.auto),
    Css.marginRight(Css.auto),
    Css.paddingTop(Css.em(0.5)),
    Css.paddingBottom(Css.em(0.5)),
  ]);
let submitBtn =
  Css.style([
    Css.alignSelf(Css.center),
    Css.important(Css.margin(Css.auto)),
    Css.marginTop(Css.em(1.0)),
    Css.important(Css.margin(Css.auto)),
    Css.important(Css.color(Css.white)),
  ]);
let textInput = Css.style([fullWidth]);
let smallMarginTop =
  Css.style([Css.important(Css.marginTop(Css.em(1.0)))]);
let categoryLabel =
  Css.style([
    Css.paddingBottom(Css.em(0.5)),
    Css.paddingTop(Css.em(0.5)),
  ]);
let paperInnerContainer = Css.style([Css.padding(Css.em(0.5))]);
let whiteText = Css.style([Css.important(Css.color(Css.white))]);
let success =
  Css.style([
    Css.important(
      Css.backgroundColor(Css.hex(muiToCss(MaterialUi.Colors.Green.c600))),
    ),
  ]);

let theme =
  createMuiTheme({
    "palette": {
      "primary": {
        "main": MaterialUi.Colors.Blue.c500,
      },
      "secondary": {
        "main": MaterialUi.Colors.Green.c500,
      },
    },
  });

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => {
    todos: [],
    newTitle: "",
    newDescription: "",
    lastId: 0,
    snackbarOpen: false,
    lastDeletedTodo: None,
  },
  reducer: (action, state) =>
    switch (action) {
    | AddTodo =>
      switch (state.newTitle) {
      | "" => ReasonReact.NoUpdate /* TODO: Display a validation warning */
      | _ =>
        ReasonReact.Update({
          ...state,
          todos:
            List.append(
              state.todos,
              [
                {
                  id: state.lastId + 1,
                  title: state.newTitle,
                  description: state.newDescription,
                  complete: false,
                },
              ],
            ),
          newDescription: "",
          newTitle: "",
          lastId: state.lastId + 1,
        })
      }
    | ChangeComplete(todo) =>
      let updatedTodo = {...todo, complete: !todo.complete};
      ReasonReact.Update({
        ...state,
        todos:
          List.append(
            List.filter(t => t.id != todo.id, state.todos),
            [updatedTodo],
          ),
      });
    | ChangeDescription(description) =>
      ReasonReact.Update({...state, newDescription: description})
    | ChangeTitle(title) => ReasonReact.Update({...state, newTitle: title})
    | RemoveTodo(todo) =>
      ReasonReact.Update({
        ...state,
        todos: List.filter(t => t.id != todo.id, state.todos),
        lastDeletedTodo: Some(todo),
        snackbarOpen: true,
      })
    | ResetSnackbar =>
      ReasonReact.Update({
        ...state,
        lastDeletedTodo: None,
        snackbarOpen: false,
      })
    | UndoDelete =>
      switch (state.lastDeletedTodo) {
      | None => ReasonReact.NoUpdate
      | Some(todo) =>
        ReasonReact.Update({
          ...state,
          todos: List.append(state.todos, [todo]),
          lastDeletedTodo: None,
          snackbarOpen: false,
        })
      }
    },
  render: self =>
    <MaterialUi_MuiThemeProvider theme={`ObjectGeneric(theme)}>
      <div className=root>
        <Header />
        <div className=layoutContainer>
          <main className=layout>
            <MaterialUi.Grid
              xs=V12
              sm=V8
              md=V6
              lg=V4
              spacing=V24
              className=centered
              direction=`Column>
              <MaterialUi.Paper className=mainPaper>
                <MaterialUi.Grid
                  xs=V12 container=true className=paperInnerContainer>
                  <MaterialUi.Grid xs=V12 item=true>
                    <MaterialUi.Typography
                      variant=`Headline className=Styles.textCenter>
                      {"What would you like to do?" |> ReasonReact.string}
                    </MaterialUi.Typography>
                  </MaterialUi.Grid>
                  <MaterialUi.Grid
                    className=centered
                    justify=`Center
                    xs=V12
                    direction=`Column
                    item=true>
                    <form
                      onSubmit={_event => self.send(AddTodo)}
                      action="#"
                      className=form>
                      <MaterialUi.Grid
                        justify=`Center
                        xs=V11
                        sm=V9
                        md=V7
                        lg=V5
                        direction=`Column
                        container=true
                        className=centered>
                        <MaterialUi.Grid xs=V12 justify=`Center item=true>
                          <MaterialUi.Input
                            placeholder="Title"
                            className=textInput
                            onChange={
                              event =>
                                self.send(
                                  ChangeTitle(
                                    ReactEvent.Form.target(event)##value,
                                  ),
                                )
                            }
                            value={`String(self.state.newTitle)}
                          />
                        </MaterialUi.Grid>
                        <MaterialUi.Grid xs=V12 justify=`Center item=true>
                          <MaterialUi.TextField
                            multiline=true
                            rows={`Int(4)}
                            placeholder="Description (optional)"
                            className=textInput
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
                        </MaterialUi.Grid>
                        <MaterialUi.Grid
                          xs=V12
                          justify=`Center
                          item=true
                          className=submitBtnContainer>
                          <MaterialUi.Button
                            type_="submit"
                            color=`Secondary
                            variant=`Fab
                            className=submitBtn>
                            <MaterialUIIcons.Add />
                          </MaterialUi.Button>
                        </MaterialUi.Grid>
                      </MaterialUi.Grid>
                    </form>
                  </MaterialUi.Grid>
                  <MaterialUi.Grid xs=V12 spacing=V24>
                    {
                      switch (
                        List.length(
                          List.filter(t => !t.complete, self.state.todos),
                        )
                      ) {
                      | 0 => ReasonReact.null
                      | _ =>
                        <MaterialUi.Typography
                          variant=`Title className=categoryLabel>
                          {"To do" |> ReasonReact.string}
                        </MaterialUi.Typography>
                      }
                    }
                  </MaterialUi.Grid>
                  <MaterialUi.Grid xs=V12 item=true justify=`Center>
                    <MaterialUi.Grid container=true spacing=V8>
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
                    </MaterialUi.Grid>
                  </MaterialUi.Grid>
                  <MaterialUi.Grid xs=V12 spacing=V24>
                    {
                      switch (
                        List.length(
                          List.filter(t => t.complete, self.state.todos),
                        )
                      ) {
                      | 0 => ReasonReact.null
                      | _ =>
                        <MaterialUi.Typography
                          variant=`Title className=categoryLabel>
                          {"Completed tasks" |> ReasonReact.string}
                        </MaterialUi.Typography>
                      }
                    }
                  </MaterialUi.Grid>
                  <MaterialUi.Grid xs=V12 item=true justify=`Center>
                    <MaterialUi.Grid container=true spacing=V8>
                      ...{
                           List.map(
                             t =>
                               <TodoItem
                                 todo=t
                                 onDelete={
                                   _event => RemoveTodo(t) |> self.send
                                 }
                                 onChangeState={
                                   _event => ChangeComplete(t) |> self.send
                                 }
                               />,
                             List.filter(t => t.complete, self.state.todos),
                           )
                           |> Array.of_list
                         }
                    </MaterialUi.Grid>
                  </MaterialUi.Grid>
                </MaterialUi.Grid>
              </MaterialUi.Paper>
            </MaterialUi.Grid>
            <MaterialUi.Snackbar
              open_={self.state.snackbarOpen}
              onClose={(_e, _r) => self.send(ResetSnackbar)}>
              <MaterialUi.SnackbarContent
                className=success
                action={
                  <MaterialUi.Button
                    className=whiteText onClick={_e => self.send(UndoDelete)}>
                    {"Undo" |> ReasonReact.string}
                  </MaterialUi.Button>
                }
                message={"Task deleted" |> ReasonReact.string}
              />
            </MaterialUi.Snackbar>
          </main>
        </div>
        <Footer />
      </div>
    </MaterialUi_MuiThemeProvider>,
};

let default = ReasonReact.wrapReasonForJs(~component, _jsProps => make([||]));