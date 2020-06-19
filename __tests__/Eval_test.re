open Jest;
open Node;
open Eval;

describe("eval", () => {
  describe("on an Int", () => {
    let environment: environment = Environment.newEnvironment();

    Expect.(
      test("returns the Int", () =>
        expect(eval(Int(123), environment)) |> toBe(Int(123))
      )
    );
  })
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