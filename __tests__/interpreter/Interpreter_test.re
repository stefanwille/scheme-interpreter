open Jest;

describe("Interpreter", () => {
  Expect.(
    test("executes the given code", () => {
      let interpreter = Interpreter.newInterpreter();
      let result: string = Interpreter.run(interpreter, "(+ 1 2)");
      expect(result) |> toEqual("3");
    })
  );

  Expect.(
    test("executes nested expressions", () => {
      let interpreter = Interpreter.newInterpreter();
      let result: string =
        Interpreter.run(
          interpreter,
          "(begin (set! counter 10) (+ counter counter))",
        );
      expect(result) |> toEqual("20");
    })
  );

  Expect.(
    test("executes multiple expressions in the same environment", () => {
      let interpreter = Interpreter.newInterpreter();
      let result: string =
        Interpreter.run(interpreter, "(set! counter 10) counter");
      expect(result) |> toEqual("\"OK\", 10");
    })
  );
});