open Jest;
open AST;
open Parser;

describe("parser", () => {
  describe("with an int", () => {
    Expect.(
      test("returns an Int", () =>
        expect(parse("123")) |> toEqual([Int(123)])
      )
    )
  });

  describe("with an string", () => {
    Expect.(
      test("returns a String", () =>
        expect(parse("\"hello\"")) |> toEqual([String("hello")])
      )
    )
  });

  describe("with an symbol", () => {
    Expect.(
      test("returns a symbol", () =>
        expect(parse("quote")) |> toEqual([Symbol("quote")])
      )
    )
  });

  describe("with multiple AST nodes", () => {
    Expect.(
      test("returns a list of nodes", () =>
        expect(parse("a 1 \"hello\""))
        |> toEqual([Symbol("a"), Int(1), String("hello")])
      )
    )
  });

  describe("with a list", () => {
    Expect.(
      test("returns a list", () =>
        expect(parse("(a 1)")) |> toEqual([List([Symbol("a"), Int(1)])])
      )
    )
  });

  describe("with a nested list", () => {
    Expect.(
      test("returns a list", () =>
        expect(parse("(a (b (c)))"))
        |> toEqual([
             List([
               Symbol("a"),
               List([Symbol("b"), List([Symbol("c")])]),
             ]),
           ])
      )
    )
  });

  describe("with an empty list", () => {
    Expect.(
      test("returns a list", () =>
        expect(parse("()")) |> toEqual([List([])])
      )
    )
  });

  describe("with a nested empty list", () => {
    Expect.(
      test("returns a list", () =>
        expect(parse("(())")) |> toEqual([List([List([])])])
      )
    )
  });
});