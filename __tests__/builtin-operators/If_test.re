open Jest;
open Node;
open Eval;
open NewEnvironment;

describe("with if", () => {
  describe("with consequent and alternative", () => {
    let environment: environment = newEnvironment();

    Expect.(
      test("handles the 'true' case", () =>
        expect(
          eval(
            List([
              Symbol("if"),
              Boolean(true),
              String("Yes"),
              String("No"),
            ]),
            environment,
          ),
        )
        |> toEqual(String("Yes"))
      )
    );

    Expect.(
      test("handles the 'false' case", () =>
        expect(
          eval(
            List([
              Symbol("if"),
              Boolean(false),
              String("Yes"),
              String("No"),
            ]),
            environment,
          ),
        )
        |> toEqual(String("No"))
      )
    );
  });

  describe("with consequent only", () => {
    let environment: environment = newEnvironment();

    Expect.(
      test("handles the 'true' case", () =>
        expect(
          eval(
            List([Symbol("if"), Boolean(true), String("Yes")]),
            environment,
          ),
        )
        |> toEqual(String("Yes"))
      )
    );

    Expect.(
      test("handles the 'false' case", () =>
        expect(
          eval(
            List([Symbol("if"), Boolean(false), String("Yes")]),
            environment,
          ),
        )
        |> toEqual(Nil)
      )
    );
  });
});