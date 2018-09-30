open Utils;

let component = ReasonReact.statelessComponent("Footer");

let footerClass =
  Css.style([
    MaterialUi.Colors.Blue.c400 |> muiToCss |> Css.hex |> Css.backgroundColor,
    Css.white |> Css.color,
    1.0 |> Css.em |> Css.padding,
  ]);

let make = _children => {
  ...component,
  render: _self =>
    <footer className=footerClass>
      <MaterialUi.Typography
        color=`Inherit variant=`Body1 align=`Center gutterBottom=true>
        [%raw {|'\u00a9'|}]
        {" 2018 Tanner Goins" |> ReasonReact.string}
      </MaterialUi.Typography>
    </footer>,
};