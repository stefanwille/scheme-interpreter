open Jest;
open Lexer;
open Token;

describe("nextToken", () => {
  Expect.(
    test("returns the next lexer", () => {
      let lexer = newLexer("123");
      let lexer = nextToken(lexer);
      expect(lexer.index) |> toEqual(3);
    })
  );

  describe("with an int", () => {
    Expect.(
      test("returns an INT token", () => {
        let lexer = newLexer("456");
        let lexer = nextToken(lexer);
        expect(lexer.token) |> toEqual(INT(456));
      })
    )
  });

  describe("with leading whitespace", () => {
    Expect.(
      test("skips it", () => {
        let lexer = newLexer("   456");
        let lexer = nextToken(lexer);
        expect(lexer.token) |> toEqual(INT(456));
      })
    )
  });

  describe("at the end of the input", () => {
    Expect.(
      test("returns an END token", () => {
        let lexer = newLexer("4    ");
        let lexer = nextToken(lexer);
        let lexer = nextToken(lexer);
        expect(lexer.token) |> toEqual(END);
      })
    )
  });

  describe("with a string", () => {
    Expect.(
      test("returns a STRING token", () => {
        let lexer = newLexer("\"abc\"");
        let lexer = nextToken(lexer);
        expect(lexer.token) |> toEqual(STRING("abc"));
      })
    )
  });

  describe("with a left paren", () => {
    Expect.(
      test("returns a LPAREN token", () => {
        let lexer = newLexer(" (");
        let lexer = nextToken(lexer);
        expect(lexer.token) |> toEqual(LPAREN);
      })
    )
  });

  describe("with a right paren", () => {
    Expect.(
      test("returns a RPAREN token", () => {
        let lexer = newLexer(" )");
        let lexer = nextToken(lexer);
        expect(lexer.token) |> toEqual(RPAREN);
      })
    )
  });

  describe("with a symbol", () => {
    Expect.(
      test("returns a SYMBOL token", () => {
        let lexer = newLexer(" begin");
        let lexer = nextToken(lexer);
        expect(lexer.token) |> toEqual(SYMBOL("begin"));
      })
    )
  });

  describe("with a non character symbol", () => {
    Expect.(
      test("returns a SYMBOL token", () => {
        let lexer = newLexer("!+:$-");
        let lexer = nextToken(lexer);
        expect(lexer.token) |> toEqual(SYMBOL("!+:$-"));
      })
    )
  });
});