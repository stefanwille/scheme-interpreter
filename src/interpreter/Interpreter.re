open NewEnvironment;

type interpreter = {environment: AST.environment};

let newInterpreter = (): interpreter => {environment: newEnvironment()};

let run = (interpreter: interpreter, program: string) => {
  "3";
};