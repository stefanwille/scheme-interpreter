open Jest;

describe("Regexp learn", () => {
  Expect.(
    test("`Some Js array` can be equal", () => {
      let a = Some([|"bet"|]);
      let b = Some([|"bet"|]);
      expect(a) |> toEqual(b);
    })
  );

  Expect.(
    test("match returns a JS string array", () => {
      let result: option(array(Js.String.t)) =
        Js.String.match([%re "/b[aeiou]t/"], "The better bats");
      let mapped = Belt.Option.mapWithDefault(result, [|"NO_MATCH"|], x => x);
      expect(mapped[0]) |> toEqual("bet");
    })
  );

  Expect.(
    test("no match returns a JS string array", () => {
      let result: option(array(Js.String.t)) =
        Js.String.match([%re "/b[aeiou]t/"], "LALALA");
      expect(result) |> toEqual(None);
    })
  );
});