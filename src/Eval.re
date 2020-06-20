open Node;
open ArgumentsError;

exception NotAnOperator;

let rec eval = (expression: node, environment: environment): node =>
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
      invocationEnvironment: environment,
    )
    : node => {
  let usedArgumentList =
    switch (operatorType) {
    | Function =>
      List.map(
        argument => eval(argument, invocationEnvironment),
        argumentList,
      )
    | SpecialForm => argumentList
    };

  operatorFunction(usedArgumentList, invocationEnvironment);
}

and applyCompoundOperator =
    (
      body: node,
      operatorType: operatorType,
      parameterNames: list(string),
      argumentList: list(node),
      invocationEnvironment: environment,
      operatorDefinitionEnvironment: environment,
    ) => {
  let usedArgumentList =
    switch (operatorType) {
    | Function =>
      List.map(
        argument => eval(argument, invocationEnvironment),
        argumentList,
      )
    | SpecialForm => argumentList
    };

  let applicationEnvironment =
    Environment.extendEnvironment(
      operatorDefinitionEnvironment,
      parameterNames,
      usedArgumentList,
    );
  eval(body, applicationEnvironment);
};