open Jest;
open Node;
open Eval;
open NewEnvironment;

describe("head", () => {
  let environment: environment = newEnvironment();

  Expect.(
    test("returns the rest of the given list", () =>
      expect(
        eval(
          List([
            Symbol("tail"),
            List([Symbol("quote"), List([Int(1), Int(2), Int(3)])]),
          ]),
          environment,
        ),
      )
      |> toEqual(List([Int(2), Int(3)]))
    )
  );
});