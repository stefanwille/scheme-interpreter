open NewEnvironment;
open StringOfNode;

type interpreter = {environment: AST.environment};

let newInterpreter = (): interpreter => {environment: newEnvironment()};

let run = (interpreter: interpreter, program: string): string => {
  let nodes = Parser.parse(program);
  let resultNodes =
    List.map(node => Eval.eval(node, interpreter.environment), nodes);
  let results: list(string) =
    List.map((node: AST.node) => stringOfNode(node), resultNodes);
  let result = StringUtil.join(results, ", ");
  result;
};