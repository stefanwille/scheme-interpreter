open Jest;
open AST;
open Eval;
open NewEnvironment;

describe("set!", () => {
  let environment: environment = newEnvironment();

  Expect.(
    test("updates the environment with the variable's value", () => {
      let _ =
        eval(
          List([Symbol("set!"), Symbol("answer"), String("Yes")]),
          environment,
        );
      expect(Environment.lookupVariableValue(environment, "answer"))
      |> toEqual(String("Yes"));
    })
  );
});