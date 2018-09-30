let component = ReasonReact.statelessComponent("Footer");

let footerClass =
  Css.style([Css.backgroundColor(Css.aliceblue), Css.color(Css.white)]);

let make = _children => {
  ...component,
  render: _self =>
    <footer className=footerClass>
      <MaterialUi.Typography
        color=`TextSecondary variant=`Body1 align=`Center gutterBottom=true>
        {"Copyright (c) 2018 Tanner Goins" |> ReasonReact.string}
      </MaterialUi.Typography>
    </footer>,
};