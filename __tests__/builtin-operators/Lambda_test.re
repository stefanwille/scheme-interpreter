open Jest;
open Node;
open Eval;
open NewEnvironment;

describe("lambda", () => {
  let environment: environment = newEnvironment();

  describe("when applying the operator", () => {
    Expect.(
      test("returns a new compound function", () => {
        let lambdaFunction =
          eval(
            List([
              Symbol("lambda"),
              List([Symbol("x")]),
              List([Symbol("+"), Symbol("x"), Int(3)]),
            ]),
            environment,
          );
        // let result = eval(List([lambdaFunction, Int(2)]), environment);
        let parameterNames =
          switch (lambdaFunction) {
          | CompoundOperator(
              parameterNames,
              _body,
              _definitionEnvironment,
              _operatorType,
            ) => parameterNames
          | _ => ["something else"]
          };

        expect(parameterNames) |> toEqual(["x"]);
      })
    )
  });

  describe("when applying the compound function", () => {
    Expect.(
      test("evaluates the body", () => {
        let environment: environment = newEnvironment();

        let lambdaFunction =
          eval(
            List([
              Symbol("lambda"),
              List([Symbol("x")]),
              List([Symbol("+"), Symbol("x"), Int(3)]),
            ]),
            environment,
          );
        let result = eval(List([lambdaFunction, Int(2)]), environment);
        expect(result) |> toEqual(Int(5));
      })
    );

    Expect.(
      test("evaluates the body in a new environment", () => {
        let environment: environment = newEnvironment();
        Environment.defineVariable(environment, "x", Int(10));

        let lambdaFunction =
          eval(
            List([
              Symbol("lambda"),
              List([Symbol("x")]),
              List([Symbol("+"), Symbol("x"), Int(3)]),
            ]),
            environment,
          );
        let result = eval(List([lambdaFunction, Int(2)]), environment);
        expect(result) |> toEqual(Int(5));
      })
    );
  });
});