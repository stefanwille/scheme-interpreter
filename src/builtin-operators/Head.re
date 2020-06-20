open Node;
open ArgumentsError;

let head: operatorFunction =
  (argumentList: list(node), _environment) =>
    switch (argumentList) {
    | [List(list)] => List.hd(list)
    | _ => raise(ArgumentsError("Expected exactly 1 argument"))
    };