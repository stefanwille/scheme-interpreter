open Jest;
open AST;
open Eval;
open NewEnvironment;

describe("with a quote", () => {
  let environment: environment = newEnvironment();

  Expect.(
    test("returns the unquoted argument", () =>
      expect(eval(List([Symbol("quote"), Symbol("hello")]), environment))
      |> toEqual(Symbol("hello"))
    )
  );
});