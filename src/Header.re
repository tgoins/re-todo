let component = ReasonReact.statelessComponent("Header");

let appBar =
  Css.style([Css.position(Css.relative), Css.marginBottom(Css.em(1.0))]);

let make = _children => {
  ...component,
  render: _self =>
    <MaterialUi.AppBar position=`Static className=appBar color=`Primary>
      <MaterialUi.Toolbar>
        <MaterialUi.Typography variant=`Title color=`Inherit noWrap=true>
          {"To-do App" |> ReasonReact.string}
        </MaterialUi.Typography>
      </MaterialUi.Toolbar>
    </MaterialUi.AppBar>,
};