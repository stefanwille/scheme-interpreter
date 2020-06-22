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
      test("returns an Int token", () => {
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
      test("returns a String token", () => {
        let lexer = newLexer("\"abc\"");
        let (token, _lexer) = nextToken(lexer);
        expect(token) |> toEqual(STRING("abc"));
      })
    )
  });

  describe("with a left paren", () => {
    Expect.(
      test("returns a LParen token", () => {
        let lexer = newLexer("\"abc\"");
        let (token, _lexer) = nextToken(lexer);
        expect(token) |> toEqual(STRING("abc"));
      })
    )
  });
  // TODO:
  // Add LPAREN
  // Add RPAREN
  // Add Symbol
  // Add nil to environment
  // Add true, false to environment
  // Add true, false to environment
});