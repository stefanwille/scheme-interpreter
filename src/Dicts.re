let myDict = Js.Dict.empty();
Js.Dict.set(myDict, "hello", "worldidlein");
Js.Dict.set(myDict, "acko", "omatolat");
let result = Js.Dict.get(myDict, "acko");
switch (result) {
| Some(string) => Js.log("halllooo " ++ string)
| None => Js.log("Noooofffing")
};