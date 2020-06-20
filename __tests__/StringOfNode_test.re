open Jest;
open Node;
open StringOfNode;
open NewEnvironment;

describe("stringOfNode", () => {
  Expect.(
    test("int", () =>
      expect(stringOfNode(Int(123))) |> toBe("123")
    )
  );

  Expect.(
    test("string", () =>
      expect(stringOfNode(String("123"))) |> toBe("\"123\"")
    )
  );

  Expect.(
    test("boolean", () =>
      expect(stringOfNode(Boolean(false))) |> toBe("false")
    )
  );

  Expect.(
    test("symbol", () =>
      expect(stringOfNode(Symbol("define"))) |> toBe("define")
    )
  );

  Expect.(
    test("quote", () =>
      expect(stringOfNode(List([Symbol("quote"), Symbol("define")])))
      |> toBe("(quote define)")
    )
  );

  Expect.(test("nil", () =>
            expect(stringOfNode(Nil)) |> toBe("nil")
          ));

  Expect.(
    test("builtin function", () =>
      expect(
        stringOfNode(
          BuiltinOperator("plus", BuiltinOperators.plus, Function),
        ),
      )
      |> toBe("<builtin:plus>")
    )
  );

  Expect.(
    test("application", () => {
      let input =
        List([
          Symbol("begin"),
          List([Symbol("set!"), Symbol("counter"), Int(0)]),
          List([
            Symbol("set!"),
            Symbol("counter"),
            List([Symbol("+"), Symbol("counter"), Int(1)]),
          ]),
        ]);

      expect(stringOfNode(input))
      |> toBe("(begin (set! counter 0) (set! counter (+ counter 1)))");
    })
  );

  Expect.(
    test("lambda-result", () => {
      let input =
        CompoundOperator(
          ["x"],
          List([Symbol("+"), Symbol("x"), Int(4)]),
          newEnvironment(),
          Function,
        );

      expect(stringOfNode(input)) |> toBe("[lambda:(x) (+ x 4)]");
    })
  );
});