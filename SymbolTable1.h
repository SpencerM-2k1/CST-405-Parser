#ifndef SYMBOL_TABLE1_H
#define SYMBOL_TABLE1_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Symbol structure

//Enum for var type
typedef enum {
    SymbolType_Int,
    SymbolType_Char,
    SymbolType_Undefined
}SymbolType;

// Define the Symbol struct
typedef struct Symbol {
    char* name;
    // char* type;
    SymbolType type;
    struct Symbol* next;

    // Add other fields of Symbol (handle via union)
    union {
        int intVal;
        char charVal;
    };
} Symbol;

// Define the SymbolTable struct
typedef struct SymbolTable {
    int size;
    struct Symbol** table;
} SymbolTable;

// Function declarations
SymbolTable* createSymbolTable(int size);
void addSymbol(SymbolTable* table, char* name, char* type);
Symbol* lookupSymbol(SymbolTable* table, char* name);
void freeSymbolTable(SymbolTable* table);
void freeSymbol(Symbol* symbol);
void printSymbolTable(SymbolTable* table);
unsigned int hash(SymbolTable* table, char* name);

SymbolType stringToType(char* typeString);
char* typeToString(SymbolType type);

#endif // SYMBOL_TABL1_H