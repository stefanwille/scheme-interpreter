open Jest;

describe("Eval", () => {
  describe("join()", () => {
    Expect.(
      test("joins a list of strings", () =>
        expect(StringUtil.join(["a", "b", "c"], ", ")) |> toBe("a, b, c")
      )
    )
  })
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