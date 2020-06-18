Js.log("Hello, BuckleScript and Reason! I am here!");

let rec fac = (n: int) =>
  if (n == 0) {
    1;
  } else {
    n * fac(n - 1);
  };

Js.log("Your fac is " ++ string_of_int(fac(3)));