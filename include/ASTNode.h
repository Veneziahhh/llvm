#ifndef _ASTNODE_H_
#define _ASTNODE_H_

#include <string>
#include "SymbolTable.h"
#include "common.h"
#include "llvm/IR/Value.h"

#define PRINT_CHILD_WITH_HINT(child, hint) \
	do { \
		for(int i = 0; i < level; i++) printf("|       "); \
		printf("| [" hint "]\n"); \
		child->PrintInLevel(level + 1); \
	} while(0)

#define NOT_NULL(node) \
	(node != nullptr)

#define NOT_NULL_OF_TYPE(node, type) \
	(dynamic_cast<type>(node) != nullptr)

#define NULLABLE_OF_TYPE(node, type) \
	(node == nullptr || NOT_NULL_OF_TYPE(node, type))

class ASTNode {

public:
	ASTNode() {}
	virtual ~ASTNode() {}

	void PrintInLevel(int level) const;
	virtual void AnalyzeSemantic(SymbolTable *intab) = 0;
	virtual Value *codegen() = 0;

protected:
	
	virtual void PrintContentInLevel(int level) const = 0;

};

class ASTException {

public:
	ASTException(const std::string &message) : message(message) {}
	~ASTException() {}

	void PrintMessage() const;

private:
	std::string message;

};

#endif