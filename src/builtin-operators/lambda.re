open Node;
open ArgumentsError;

let lambda: operatorFunction =
  (argumentList: list(node), environment) => {
    switch (argumentList) {
    | [List(parameterList), body] =>
      let parameterNames: list(string) =
        List.map(
          parameter =>
            switch (parameter) {
            | Symbol(name) => name
            | _ => raise(ArgumentsError("Parameter is not a symbol"))
            },
          parameterList,
        );
      CompoundOperator(parameterNames, body, environment, Function);
    | _ => raise(ArgumentsError("Exactly 2 arguments expected"))
    };
  };