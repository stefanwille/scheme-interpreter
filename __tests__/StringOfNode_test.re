open Jest;
open Node;
open StringOfNode;

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
      expect(stringOfNode(Quote(List([Symbol("define")]))))
      |> toBe("(quote (define))")
    )
  );

  Expect.(test("nil", () =>
            expect(stringOfNode(Nil)) |> toBe("nil")
          ));

  Expect.(
    test("builtin function", () =>
      expect(
        stringOfNode(
          BuiltinOperator("plus", BuiltinFunctions.plus, Function),
        ),
      )
      |> toBe("<builtin:plus>")
    )
  );

  Expect.(
    test("application", () => {
      let input =
        Quote(
          List([
            List([Symbol("set!"), Symbol("counter"), Int(0)]),
            List([Symbol("begin"), Int(1), Int(2)]),
          ]),
        );

      expect(stringOfNode(input))
      |> toBe("(quote ((set! counter 0) (begin 1 2)))");
    })
  );
});