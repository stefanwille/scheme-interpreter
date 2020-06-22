open Jest;
open Lexer;

describe("nextToken", () => {
  Expect.(
    test("returns the next lexer", () => {
      let lexer = newLexer("123");
      let (_token, lexer) = nextToken(lexer);
      expect(lexer.index) |> toEqual(3);
    })
  );

  describe("with an int", () => {
    Expect.(
      test("returns an INT token", () => {
        let lexer = newLexer("456");
        let (token, _lexer) = nextToken(lexer);
        expect(token) |> toEqual(INT(456));
      })
    )
  });

  describe("with leading whitespace", () => {
    Expect.(
      test("skips it", () => {
        let lexer = newLexer("   456");
        let (token, _lexer) = nextToken(lexer);
        expect(token) |> toEqual(INT(456));
      })
    )
  });

  describe("at the end of the input", () => {
    Expect.(
      test("returns an END token", () => {
        let lexer = newLexer("4    ");
        let (_token, lexer) = nextToken(lexer);
        let (token, _lexer) = nextToken(lexer);
        expect(token) |> toEqual(END);
      })
    )
  });

  describe("with a string", () => {
    Expect.(
      test("returns a STRING token", () => {
        let lexer = newLexer("\"abc\"");
        let (token, _lexer) = nextToken(lexer);
        expect(token) |> toEqual(STRING("abc"));
      })
    )
  });

  describe("with a left paren", () => {
    Expect.(
      test("returns a LPAREN token", () => {
        let lexer = newLexer(" (");
        let (token, _lexer) = nextToken(lexer);
        expect(token) |> toEqual(LPAREN);
      })
    )
  });

  describe("with a right paren", () => {
    Expect.(
      test("returns a RPAREN token", () => {
        let lexer = newLexer(" )");
        let (token, _lexer) = nextToken(lexer);
        expect(token) |> toEqual(RPAREN);
      })
    )
  });

  describe("with a symbol", () => {
    Expect.(
      test("returns a SYMBOL token", () => {
        let lexer = newLexer(" begin");
        let (token, _lexer) = nextToken(lexer);
        expect(token) |> toEqual(SYMBOL("begin"));
      })
    )
  });
  // TODO:
  // Add nil to environment
  // Add true, false to environment
  // Add true, false to environment
});