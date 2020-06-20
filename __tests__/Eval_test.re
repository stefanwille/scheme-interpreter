open Jest;
open Node;
open Eval;
open NewEnvironment;

describe("eval", () => {
  describe("with an int", () => {
    let environment: environment = newEnvironment();

    Expect.(
      test("returns the same expression", () =>
        expect(eval(Int(123), environment)) |> toEqual(Int(123))
      )
    );
  });

  describe("with a string", () => {
    let environment: environment = newEnvironment();

    Expect.(
      test("returns the same expression", () =>
        expect(eval(String("Huhu"), environment))
        |> toEqual(String("Huhu"))
      )
    );
  });

  describe("with a boolean", () => {
    let environment: environment = newEnvironment();

    Expect.(
      test("returns the same expression", () =>
        expect(eval(Boolean(true), environment)) |> toEqual(Boolean(true))
      )
    );
  });

  describe("with a variable (= symbol)", () => {
    let environment: environment = newEnvironment();
    Environment.setVariableValue(environment, "size", Int(123));

    Expect.(
      test("returns the variable's value", () =>
        expect(eval(Symbol("size"), environment)) |> toEqual(Int(123))
      )
    );
  });

  describe("with a quote", () => {
    let environment: environment = newEnvironment();

    Expect.(
      test("returns the unquoted argument", () =>
        expect(
          eval(List([Symbol("quote"), Symbol("hello")]), environment),
        )
        |> toEqual(Symbol("hello"))
      )
    );
  });

  describe("with nil", () => {
    let environment: environment = newEnvironment();

    Expect.(
      test("returns the same expression", () =>
        expect(eval(Nil, environment)) |> toEqual(Nil)
      )
    );
  });

  describe("with +", () => {
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

  describe("with if", () => {
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

  describe("with set!", () => {
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

  describe("with lambda", () => {
    let environment: environment = newEnvironment();

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
    );
  });

  describe("when applying a lambda", () => {
    describe("execevaluates the body", () => {
      let environment: environment = newEnvironment();

      Expect.(
        test("evaluates the body in a new environment", () => {
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

    describe("evaluates in a new environment", () => {
      let environment: environment = newEnvironment();
      Environment.defineVariable(environment, "x", Int(10));

      Expect.(
        test("evaluates the body in a new environment", () => {
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
});