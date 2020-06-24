# Scheme Interpreter in ReasonML

This is an interpreter for the Lisp like programming language Scheme, written in ReasonML. The code follows closely chapter 4 of the book "Structure and Interpretation of Computer Programs" by Abelson/Sussman.

I am writing this code as an exercise to learn ReasonML.

## Build

```bash
yarn build
```

## Build + Watch

```bash
yarn start

```

## Test

```bash
yarn test

```


## API

```reason
let interpreter = SchemeInterpreter.newInterpreter();
let result: string =
  SchemeInterpreter.run(interpreter, "(begin (set! n 10) (+ n 2))");
Js.log(result);
# => 12
```
