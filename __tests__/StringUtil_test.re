open Jest;

describe("join()", () => {
  Expect.(
    test("joins a list of strings", () =>
      expect(StringUtil.join(["a", "b", "c"], ", ")) |> toBe("a, b, c")
    )
  )
});

describe("stringOfList()", () => {
  Expect.(
    test("joins a list of strings", () =>
      expect(StringUtil.stringOfList(["a", "b", "c"])) |> toBe("(a b c)")
    )
  )
});