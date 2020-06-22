open Jest;
open Node;

let parse = (_input: string): node => {
  Int(123);
};

describe("parser", () => {
  describe("with an int", ()
    => {
      Expect.(
        test("returns an Int", () =>
          expect(parse("123")) |> toEqual(Int(123))
        )
      )
    })
    // describe("with a string", () => {
    //   Expect.(
    //     test("returns the same expression", () =>
    //       expect(parse("\Hello\"")) |> toEqual(String("Huhu"))
    //     )
    //   )
    // });
    // describe("with a boolean", () => {
    //   let environment: environment = newEnvironment();
    //   Expect.(
    //     test("returns the same expression", () =>
    //       expect(eval(Boolean(true), environment)) |> toEqual(Boolean(true))
    //     )
    //   );
    // });
    // describe("with a variable (= symbol)", () => {
    //   let environment: environment = newEnvironment();
    //   Environment.setVariableValue(environment, "size", Int(123));
    //   Expect.(
    //     test("returns the variable's value", () =>
    //       expect(eval(Symbol("size"), environment)) |> toEqual(Int(123))
    //     )
    //   );
    // });
    // describe("with nil", () => {
    //   let environment: environment = newEnvironment();
    //   Expect.(
    //     test("returns the same expression", () =>
    //       expect(eval(Nil, environment)) |> toEqual(Nil)
    //     )
    //   );
    // });
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