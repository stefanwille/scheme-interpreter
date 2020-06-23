open Jest;

describe("Interpreter", () => {
  Expect.(
    test("executes the given code", () => {
      let interpreter = Interpreter.newInterpreter();
      let result: string = Interpreter.run(interpreter, "(+ 1 2)");
      expect(result) |> toEqual("3");
    })
  )
});