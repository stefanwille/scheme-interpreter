open Jest;
open Node;
open Eval;
open Environment;

describe("eval", () => {
  describe("with an int", () => {
    let environment: environment = Environment.newEnvironment();

    Expect.(
      test("returns the same expression", () =>
        expect(eval(Int(123), environment)) |> toEqual(Int(123))
      )
    );
  });

  describe("with a string", () => {
    let environment: environment = Environment.newEnvironment();

    Expect.(
      test("returns the same expression", () =>
        expect(eval(String("Huhu"), environment))
        |> toEqual(String("Huhu"))
      )
    );
  });

  describe("with a boolean", () => {
    let environment: environment = Environment.newEnvironment();

    Expect.(
      test("returns the same expression", () =>
        expect(eval(Boolean(true), environment)) |> toEqual(Boolean(true))
      )
    );
  });

  describe("with a variable (= symbol)", () => {
    let environment: environment = Environment.newEnvironment();
    setVariableValue(environment, "size", Int(123));

    Expect.(
      test("returns the variable's value", () =>
        expect(eval(Symbol("size"), environment)) |> toEqual(Int(123))
      )
    );
  });

  describe("with a quote", () => {
    let environment: environment = Environment.newEnvironment();

    Expect.(
      test("returns the unquoted list", () =>
        expect(eval(Quote(List([Symbol("hello")])), environment))
        |> toEqual(List([Symbol("hello")]))
      )
    );
  });

  describe("with nil", () => {
    let environment: environment = Environment.newEnvironment();

    Expect.(
      test("returns the same expression", () =>
        expect(eval(Nil, environment)) |> toEqual(Nil)
      )
    );
  });

  describe("with +", () => {
    let environment: environment = Environment.newEnvironment();

    Expect.(
      test("returns the sum", () =>
        expect(eval(List([Symbol("+"), Int(1), Int(2)]), environment))
        |> toEqual(Int(3))
      )
    );
  });
});

describe("Expect", () => {
  Expect.(test("toBe", () =>
            expect(1 + 2) |> toBe(3)
          ))
});

describe("Expect.Operators", () => {
  open Expect;
  open! Expect.Operators;

  test("==", () =>
    expect(1 + 2) === 3
  );
});