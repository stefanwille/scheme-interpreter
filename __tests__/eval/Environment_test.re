open Jest;
open Environment;
open AST;

describe("defineVariable()", () => {
  Expect.(
    test("adds a variable to the given environment", () => {
      let environment = makeEnvironment();
      defineVariable(environment, "counter", String("hey"));
      expect(lookupVariableValue(environment, "counter"))
      |> toEqual(String("hey"));
    })
  )
});

describe("defineVariables()", () => {
  Expect.(
    test("adds many variables to the given environment", () => {
      let environment = makeEnvironment();
      defineVariables(
        environment,
        ["x", "y"],
        [String("hey"), String("you")],
      );

      let values = (
        lookupVariableValue(environment, "x"),
        lookupVariableValue(environment, "y"),
      );
      expect(values) |> toEqual((String("hey"), String("you")));
    })
  )
});

describe("extendEnvironment()", () => {
  let environment = makeEnvironment();
  defineVariable(environment, "x", String("original"));
  let childEnvironment =
    extendEnvironment(
      environment,
      ["x", "y"],
      [String("shadow"), String("hello")],
    );

  Expect.(
    test("adds many variables to a new child environment", () => {
      let values = (
        lookupVariableValue(childEnvironment, "x"),
        lookupVariableValue(childEnvironment, "y"),
      );
      expect(values) |> toEqual((String("shadow"), String("hello")));
    })
  );

  Expect.(
    test("keeps the original environment untouched", () => {
      let value = lookupVariableValue(environment, "x");
      expect(value) |> toEqual(String("original"));
    })
  );
});