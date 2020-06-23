open Jest;
open AST;
open Eval;
open NewEnvironment;

describe("with begin", () => {
  let environment: environment = newEnvironment();

  Expect.(
    test("evaluates all arguments and returns the last result", () =>
      expect(
        eval(
          List([
            Symbol("begin"),
            String("One"),
            String("Two"),
            String("Three"),
          ]),
          environment,
        ),
      )
      |> toEqual(String("Three"))
    )
  );
});