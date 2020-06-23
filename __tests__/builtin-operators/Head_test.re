open Jest;
open AST;
open Eval;
open NewEnvironment;

describe("head", () => {
  let environment: environment = newEnvironment();

  Expect.(
    test("returns the first element of the given list", () =>
      expect(
        eval(
          List([
            Symbol("head"),
            List([Symbol("quote"), List([Int(1), Int(2)])]),
          ]),
          environment,
        ),
      )
      |> toEqual(Int(1))
    )
  );
});