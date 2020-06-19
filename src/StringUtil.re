let join = (list: list(string), separator) =>
  List.fold_left(
    (sum: string, s: string) =>
      switch (sum) {
      | "" => s
      | _ => sum ++ separator ++ s
      },
    "",
    list,
  );

let stringOfList = (list: list(string)): string => {
  let joined = join(list, " ");
  "(" ++ joined ++ ")";
};