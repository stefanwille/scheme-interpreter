open AST;
open ArgumentsError;

let tail: operatorFunction =
  (argumentList: list(node), _environment) => (
    switch (argumentList) {
    | [List(list)] => List(List.tl(list))
    | _ => raise(ArgumentsError("Expected exactly 1 argument"))
    }: node
  );

let operator: node = BuiltinOperator("tail", tail, Function);