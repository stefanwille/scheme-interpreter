open Node;
open ArgumentsError;

let head: operatorFunction =
  (argumentList: list(node), _environment) =>
    switch (argumentList) {
    | [] => raise(ArgumentsError("Missing list"))
    | [List(list)] => List.hd(list)
    | _ => raise(ArgumentsError("Too many arguments"))
    };

let plus: operatorFunction =
  (argumentList: list(node), _environment) => (
    {
      let intOfNode = (summand: node) => {
        switch (summand) {
        | Int(value) => value
        | _ => raise(ArgumentsError("Not an int"))
        };
      };

      let summands: list(int) = List.map(intOfNode, argumentList);
      let sum = List.fold_left((x, y) => x + y, 0, summands);
      Int(sum);
    }: node
  );