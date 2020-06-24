open Jest;

describe("SchemeInterpreter", () => {
  Expect.(
    test("executes the given code", () => {
      let interpreter = SchemeInterpreter.newInterpreter();
      let result: string = SchemeInterpreter.run(interpreter, "(+ 1 2)");
      expect(result) |> toEqual("3");
    })
  );

  Expect.(
    test("executes nested expressions", () => {
      let interpreter = SchemeInterpreter.newInterpreter();
      let result: string =
        SchemeInterpreter.run(
          interpreter,
          "(begin (set! counter 10) (+ counter counter))",
        );
      expect(result) |> toEqual("20");
    })
  );

  Expect.(
    test("executes multiple expressions in the same environment", () => {
      let interpreter = SchemeInterpreter.newInterpreter();
      let result: string =
        SchemeInterpreter.run(interpreter, "(set! counter 10) counter");
      expect(result) |> toEqual("\"OK\", 10");
    })
  );
});