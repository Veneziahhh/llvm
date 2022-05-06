 #ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

#include <unordered_map>
#include <vector>
#include <string>
#include "common.h"

enum class SymbolKind {
	FUNCTION, ARGUMENT, VARIABLE
};

struct SymbolType {

	SymbolType(Type type) : type(type), argTypes() {}
	SymbolType(Type type, const std::vector<Type> &argTypes) : type(type), argTypes(argTypes) { }
	SymbolType(const SymbolType &rhs) : type(rhs.type), argTypes(rhs.argTypes) { }
	~SymbolType() {}

	Type type;
	std::vector<Type> argTypes; // Ignore if not function kind
};

struct SymbolTableEntry {

	SymbolTableEntry(SymbolKind kind, const SymbolType &type) : kind(kind), type(type) {}
	~SymbolTableEntry() {}

	SymbolKind kind;
	SymbolType type;
};

struct SymbolTable {

	SymbolTable() : entry(), prev(nullptr) {}
	~SymbolTable() {}

	bool HasSymbol(const std::string &sym) {
		return (entry.find(sym) != entry.end());
	}

	SymbolTable *FindSymbolOccurrence(const std::string &sym){
		for(SymbolTable *tab = this; tab != nullptr; tab = tab->prev) {
			if(tab->HasSymbol(sym)) return tab;
		}
		return nullptr;
	}

	void AddEntry(const std::string &sym, const SymbolTableEntry &content) {
		entry.insert({sym, content});
	}

	std::unordered_map<std::string, SymbolTableEntry> entry;
	SymbolTable *prev;

};

#endif