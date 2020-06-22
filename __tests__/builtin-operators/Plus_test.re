open Jest;
open Node;
open Eval;
open NewEnvironment;

describe("+", () => {
  let environment: environment = newEnvironment();

  Expect.(
    test("returns the sum", () =>
      expect(eval(List([Symbol("+"), Int(1), Int(2)]), environment))
      |> toEqual(Int(3))
    )
  );

  Expect.(
    test("handles any number of ints", () =>
      expect(
        eval(
          List([Symbol("+"), Int(1), Int(2), Int(3), Int(4)]),
          environment,
        ),
      )
      |> toEqual(Int(1 + 2 + 3 + 4))
    )
  );
});