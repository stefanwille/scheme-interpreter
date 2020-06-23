open Jest;
open Node;
open Parser;

describe("parser", () => {
  describe("with an int", () => {
    Expect.(
      test("returns an Int", () =>
        expect(parse("123")) |> toEqual([Int(123)])
      )
    )
  });

  describe("with an string", () => {
    Expect.(
      test("returns a String", () =>
        expect(parse("\"hello\"")) |> toEqual([String("hello")])
      )
    )
  });

  describe("with an symbol", () => {
    Expect.(
      test("returns a symbol", () =>
        expect(parse("quote")) |> toEqual([Symbol("quote")])
      )
    )
  });

  describe("with multiple AST nodes", () => {
    Expect.(
      test("returns a list of nodes", () =>
        expect(parse("a 1 \"hello\""))
        |> toEqual([Symbol("a"), Int(1), String("hello")])
      )
    )
  });

  describe("with a list", () => {
    Expect.(
      test("returns a list", () =>
        expect(parse("(a 1)")) |> toEqual([List([Symbol("a"), Int(1)])])
      )
    )
  });
  // describe("with a builtin function: +", () => {
  //   let environment: environment = newEnvironment();
  //   Expect.(
  //     test("evaluates the arguments and applies the operator function", () =>
  //       expect(eval(List([Symbol("+"), Int(1), Int(2)]), environment))
  //       |> toEqual(Int(3))
  //     )
  //   );
  //   Expect.(
  //     test("works recursively", () =>
  //       expect(
  //         eval(
  //           List([
  //             Symbol("+"),
  //             Int(1),
  //             Int(2),
  //             List([Symbol("+"), Int(3), Int(4)]),
  //           ]),
  //           environment,
  //         ),
  //       )
  //       |> toEqual(Int(1 + 2 + 3 + 4))
  //     )
  //   );
  // });
  // describe("with a builtin special form: quote", () => {
  //   let environment: environment = newEnvironment();
  //   Expect.(
  //     test(
  //       "does not evaluate the arguments and applies the operator function ",
  //       () =>
  //       expect(
  //         eval(List([Symbol("quote"), Symbol("hello")]), environment),
  //       )
  //       |> toEqual(Symbol("hello"))
  //     )
  //   );
  // });
  // //
  // CompundOperator is tested in Lambda_test.re
});