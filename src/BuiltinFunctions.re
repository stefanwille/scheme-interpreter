open Node;
open ArgumentsError;

let head: operatorFunction =
  (argumentList, _environment) =>
    switch (argumentList) {
    | [] => raise(ArgumentsError("Missing list"))
    | [List(list)] => List.hd(list)
    | _ => raise(ArgumentsError("Too many arguments"))
    };