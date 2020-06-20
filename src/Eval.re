open Node;
open ArgumentsError;

exception NotAnOperator;

let rec eval = (expression: node, environment: environment): node =>
  // Most nodes are self-evaluating.
  // The big exception is the application of an operator to some arguments.
  switch (expression) {
  | Int(_) => expression
  | String(_) => expression
  | Boolean(_) => expression
  | Symbol(name) => Environment.lookupVariableValue(environment, name)
  | BuiltinOperator(_name, _function, _type) => expression
  | CompoundOperator(
      _parameterNames,
      _body,
      _operatorDefinitionEnvironment,
      _operatorType,
    ) => expression
  | List(list) => evalApplication(list, environment)
  | Nil => expression
  }

and evalApplication = (list: list(node), environment: environment): node =>
  switch (list) {
  | [] => raise(ArgumentsError("Missing operator"))
  | [operatorExpression, ...argumentList] =>
    let operator = eval(operatorExpression, environment);
    apply(operator, argumentList, environment);
  }

// An operator can be builtin or compound,
// and it can be either a function or a special form.
and apply =
    (operator: node, argumentList: list(node), environment: environment)
    : node =>
  switch (operator) {
  | BuiltinOperator(_name, operatorFunction, operatorType) =>
    applyBuiltinOperator(
      operatorFunction,
      operatorType,
      argumentList,
      environment,
    )

  | CompoundOperator(
      parameterNames,
      body,
      operatorDefinitionEnvironment,
      operatorType,
    ) =>
    applyCompoundOperator(
      body,
      operatorType,
      parameterNames,
      argumentList,
      environment,
      operatorDefinitionEnvironment,
    )

  | _ => raise(NotAnOperator)
  }

and applyBuiltinOperator =
    (
      operatorFunction: operatorFunction,
      operatorType: operatorType,
      argumentList: list(node),
      environment: environment,
    )
    : node => {
  let usedArgumentList =
    evalArgumentList(operatorType, argumentList, environment);
  operatorFunction(usedArgumentList, environment);
}

and applyCompoundOperator =
    (
      body: node,
      operatorType: operatorType,
      parameterNames: list(string),
      argumentList: list(node),
      callSiteEnvironment: environment,
      operatorDefinitionEnvironment: environment,
    ) => {
  let usedArgumentList =
    evalArgumentList(operatorType, argumentList, callSiteEnvironment);
  // Since Scheme uses lexical scoping,
  // the application's environment is based on the environment in which
  // the operator was defined.
  let applicationEnvironment =
    Environment.extendEnvironment(
      operatorDefinitionEnvironment,
      parameterNames,
      usedArgumentList,
    );
  eval(body, applicationEnvironment);
}

// A function receives its argments readily evaluated within the call site's environment,
// while a special form receives its argument unevaluated.
and evalArgumentList =
    (
      operatorType: operatorType,
      argumentList: list(node),
      callSiteEnvironment: environment,
    ) =>
  switch (operatorType) {
  | Function =>
    List.map(argument => eval(argument, callSiteEnvironment), argumentList)
  | SpecialForm => argumentList
  };