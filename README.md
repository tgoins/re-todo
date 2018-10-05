# re-todo

> TODO app in ReasonML with React.

## Run Project

```sh
yarn
yarn start
# in another tab
yarn webpack
```

Open the `public/index.html` file in your browser to view the application!

### Optional web server

Install Python, then run:

```sh
cd public
python3 -m http.server 8082
```

Then you can view the application at `localhost:8082`

## Build for Production

```sh
npm run build
npm run webpack:production
```

This will replace the development artifact `build/Index.js` for an optimized version.

**To enable dead code elimination**, change `bsconfig.json`'s `package-specs` `module` from `"commonjs"` to `"es6"`. Then re-run the above 2 commands. This will allow Webpack to remove unused code.
