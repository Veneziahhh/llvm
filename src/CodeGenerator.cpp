#include "CodeGenerator.h"

Value *TranslationUnitNode::codegen() {
    for (auto iter = definitions.begin(); iter != definitions.end(); iter++)
        (*iter)->codegen();
    return nullptr;
}

Value *FunctionNode::codegen() {
    returnType->codegen();
    name->codegen();
    parameters->codegen();
    body->codegen();

    return nullptr;
}

Value *ParameterListNode::codegen() {
    for (auto iter = parameters.begin(); iter != parameters.end(); iter++)
        (*iter)->codegen();
    
    return nullptr;
}

Value *DeclarationNode::codegen() {
    type->codegen;
    name->codegen;
    if (initValue) 
        initValue->codegen();
    
    return nullptr;
}

Value *TypeNode::codegen() {
    switch (type)
    {
        case Type::INTEGER: return Builder.getInt32Ty();
        case Type::FLOAT: return Builder.getDoubleTy();
        case Type::VOID: return Builder.getVoidTy();
        default: LogErrorV("[ERROR] Invalid Type!"); return nullptr;
    }
}

Value *IdentifierNode::codegen() {
    string Name = id;
    Value *V = NamedValues[Name];
    if (!V)
        return LogErrorV("[ERROR] Unknown Identifier name!");
    return V;
}

Value *CompoundStatementNode::codegen() {
    for (auto iter = items.begin(); iter != items.end(); iter++)
        (*iter)->codegen();
    return nullptr;
}

Value *ExpressionNode::codegen() {
    switch (valueType)
    {
        case Type::INTEGER: return Builder.getInt32Ty();
        case Type::FLOAT: return Builder.getDoubleTy();
        case Type::VOID: return Builder.getVoidTy();
        default: LogErrorV("[ERROR] Invalid Type!"); return nullptr;
    }
}

Value *AssignOpNode::codegen() {
    Value *L = leftValue->codegen();
    Value *R = rightValue->codegen();

    return Builder.CreateEqual(L, R, "equltmp");
}

Value *BinaryOpNode::codegen() {
    Value *L = leftOperand->codegen();
    Value *R = rightOperand->codegen();
    Value *tmp;

    if (!L || !R) 
        return nullptr;

    switch(op) {
        case Operator::ADD: return Builder.CreateFAdd(L, R, "addtmp");
        case Operator::AND: return Builder.CreateFAnd(L, R, "andtmp");
        case Operator::DIV: return Builder.CreateFDiv(L, R, "divtmp");
        case Operator::EQ: return Builder.CreateOEQ(L, R, "eqtmp");
        case Operator::GT: return Builder.CreateFUGT(L, R, "gttmp");
        case Operator::GTE: return Builder.CreateFOGE(L, R, "gtetmp");
        case Operator::LOGAND: 
        case Operator::LOGOR: 
        case Operator::LT: L = Builder.CreateFCmpULT(L, R, "cmptmp");
                            return Builder.CreateUIToFP(L, Type::getDoubleTy(TheContext), "booltmp");
        case Operator::LTE: return Builder.CreateFOLE(L, R, "ltetmp");
        case Operator::MOD: 
        case Operator::MUL: return Builder.CreateFMUL(L, R, "multmp");
        case Operator::NEQ: return Builder.CreateFONE(L, R, "neqtmp");
        case Operator::NOT: return 
        case Operator::OR:  return
        case Operator::SUB: return Builder.CreateFMul(L, R, "multmp");
        case Operator::XOR: return 
    }
}

Value *FunctionCallNode::codegen() {
    Function *CalleeF = TheModule->getFunction(string(name->GetName()));
    if (!CalleeF)
        return LogErrorV("[ERROR] Unknown Function Referenced!");

    vector<Value *> ArgsV;
    for (unsigned i = 0, e = arguments->arguments.size(); i != e; ++i) {
        ArgsV.push_back(arguments->arguments[i]->codegen());
        if (!ArgsV.back())
            return nullptr;
    }

    return Builder.CreatCall(CalleeF, ArgsV, "calltmp");
}

Value *IntergerNode::codegen() {
    return Builder.getInt32(num);
}

Value *FloatNode:codegen() {
    return ConstantFP::get(Builder.getDoubleTy(), num);
}

Value *ArgumentListNode::codegen() {
    for (auto iter = arguments.begin(); iter != arguments.end(); iter++)
        (*iter)->codegen();
    
    return nullptr;
}