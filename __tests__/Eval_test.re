open Jest;
open Node;
open Eval;
open Environment;

describe("eval", () => {
  describe("with an int", () => {
    let environment: environment = Environment.newEnvironment();

    Expect.(
      test("returns the same expression", () =>
        expect(eval(Int(123), environment)) |> toEqual(Int(123))
      )
    );
  });

  describe("with a string", () => {
    let environment: environment = Environment.newEnvironment();

    Expect.(
      test("returns the same expression", () =>
        expect(eval(String("Huhu"), environment))
        |> toEqual(String("Huhu"))
      )
    );
  });

  describe("with a boolean", () => {
    let environment: environment = Environment.newEnvironment();

    Expect.(
      test("returns the same expression", () =>
        expect(eval(Boolean(true), environment)) |> toEqual(Boolean(true))
      )
    );
  });

  describe("with a variable (= symbol)", () => {
    let environment: environment = Environment.newEnvironment();
    setVariableValue(environment, "size", Int(123));

    Expect.(
      test("returns the variable's value", () =>
        expect(eval(Symbol("size"), environment)) |> toEqual(Int(123))
      )
    );
  });
});

// let input =
//   Quote(
//     List([
//       Int(123),
//       String("Hello!"),
//       Boolean(true),
//       Quote(String("Hello")),
//       List([]),
//       Symbol("name"),
//       Assignment("counter", Int(0)),
//       Sequence([Int(1), Int(2)]),
//       Nil,
//     ]),
//   ) /* Js.log("Eval: " ++ stringOfNode(evaledApply))*/ /*   "Eval: */ /* )*/ /*   "Eval: " ++ stringOfNode(eval(Quote(Quote(List([]))), myEnvironment))*/ /* let evaledApply */ /*     List([Symbol("head"), String("one"), String("two")])*/ /*   )*/ /*     myEnvironment*/ /*   eval*/ /* )*/ /* Js.log*/ /*   ++ stringOfNode(eval(Sequence([Int(2), Int(3)]), myEnvironment))*/;
// Js.log("input: " ++ stringOfNode(input));
// Js.log("Eval: " ++ stringOfNode(eval(input, myEnvironment)));
// Js.log(
//   "Eval: "
//   ++ stringOfNode(eval(Assignment("counter", Int(3)), myEnvironment)),
// );
// Js.log(

describe("Expect", () => {
  Expect.(test("toBe", () =>
            expect(1 + 2) |> toBe(3)
          ))
});

describe("Expect.Operators", () => {
  open Expect;
  open! Expect.Operators;

  test("==", () =>
    expect(1 + 2) === 3
  );
});