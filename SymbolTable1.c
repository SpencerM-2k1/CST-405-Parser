#include "SymbolTable1.h"

// Create new table
SymbolTable* createSymbolTable(int size)
{
    SymbolTable* newTable = malloc(sizeof(struct SymbolTable));
    newTable->size = size;
    newTable->table  = malloc(sizeof(Symbol*) * newTable->size);
    for (int i = 0; i < size; i++)
    {
        newTable->table[i] = NULL;
    }
    return newTable;
}

// Function to add a symbol to the table
void addSymbol(SymbolTable* table, char* name, char* type) {
    Symbol* newSymbol = malloc(sizeof(struct Symbol));
    if (!newSymbol) return;

    newSymbol->name = strdup(name);
    newSymbol->type = strdup(type);
    // Initialize other fields of Symbol

    unsigned int hashval = hash(table, name);
    newSymbol->next = table->table[hashval];
    table->table[hashval] = newSymbol;
}

// Get symbol in table
Symbol* lookupSymbol(SymbolTable* table, char* name)
{
    unsigned int hashVal = hash(table, name);
    Symbol* currSymbol = table->table[hashVal];
    while (currSymbol != NULL)
    {
        if (strcmp(currSymbol->name, name) == 0) //If name matches
        {
            printf("Symbol found!\n");
            return currSymbol;
        }
        else
        {
            printf("Symbol not found, checking next in index...\n");
            currSymbol = currSymbol->next;
        }
    }
    printf("Symbol does not exist!\n");
    return currSymbol;
}

// Delete symbol table
void freeSymbolTable(SymbolTable* table)
{
    for (int i = 0; i < table->size; i++)
    {
        free(table->table[i]);
    }
    free(table->table);
    free(table);
}

//  Recursive symbol free
void freeSymbol(Symbol* symbol)
{
    if(symbol->next != NULL) //Free linked list, starting from tail
    {
        freeSymbol(symbol->next);
    }
    free(symbol->name);
    free(symbol->type);
    free(symbol);
}

//      HELPER FUNCTIONS

// Hash function to map a name to an index
unsigned int hash(SymbolTable* table, char* name) {
    unsigned int hashval = 0;
    for (; *name != '\0'; name++)
    {
        hashval = *name + (hashval << 5) - hashval;
    }
    return hashval % table->size;
}

void printSymbolTable(SymbolTable* table)
{
    for (int i = 0; i < table->size; i++)
    {
        printf("Index %d:\n", i);
        Symbol* currSymbol = table->table[i];
        while(currSymbol != NULL)
        {
            printf("    %s %s\n", currSymbol->type, currSymbol->name);
            currSymbol = currSymbol->next;
        }
    }
}

int main(int argc, char **argv) {
    printf("Starting!\n");
    SymbolTable* testTable = createSymbolTable(3);
    addSymbol(testTable, "x", "int");
    addSymbol(testTable, "mode", "char");
    addSymbol(testTable, "operator", "char");
    addSymbol(testTable, "str", "string");
    addSymbol(testTable, "index", "int");
    printSymbolTable(testTable);
    
    Symbol* querySymbol = lookupSymbol(testTable, "mode");
    if (querySymbol)
    {
        printf("%s is of type %s\n", querySymbol->name, querySymbol->type);
    }
    freeSymbolTable(testTable);

}