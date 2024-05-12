#ifndef TS_SYMBOLTABLE_H
#define TS_SYMBOLTABLE_H

#include "unordered_map"
#include "string"

#include "TSConfig.h"
#include "Entry.h"

namespace TS_CPP{

/**
 * SymbolTable class provides the Abstract Data Type (ADT) of a symbol table, which consists of an id, a table name,
 * and a set of rows (aka Entries) consisting of a lexeme, an id, and zero or more attributes.
 */
class SymbolTable
{
public:

    /**
     * The constructor of a SymbolTable
     * It should not be used directly, but using the method TSManager::createNewTable
     * @param id The inuqie identifier of the table
     * @param entryId A pointer to the entries ID counter
     * @param tableName The name of the table
     */
    SymbolTable(int id, int* entryId, const std::string& tableName);

    /**
     * The constructor of a SymbolTable
     * It should not be used directly, but using the method TSManager::createNewTable
     * @param id The inuqie identifier of the table
     * @param entryId A pointer to the entries ID counter
     */
    SymbolTable(int id, int* entryId);

    /**
     * The destructor of a SymbolTable
     * It deletes all its entries before deleting itself
     * It should not be used directly, but using the method TSManager::deleteTable
     */
    ~SymbolTable();

    /**
     * This function returns the ID of the symbol table
     * @return The ID of the symbol table
     */
    int getId() const;

    /**
     * This function returns the name of the symbol table
     * @return The name of the symbol table
     */
    std::string getTableName() const;

    /**
     * This function create a new void entry (row) in the symbol table and set the lexeme property of it
     * @param lexeme The name of the lexeme stored in this Entry
     * @return A pointer to the new Entry
     */
    Entry* createNewEntry(const std::string& lexeme);

    /**
     * This function gets the Entry referenced by the provided entryId
     * @param entryId The unique identifier of the entry
     * @return A pointer to the Entry referenced by the entryId or nullptr if it doesn't exist
     */
    Entry* getEntry(int entryId);

    /**
     * This function search and return the entry that has its lexeme equal to the provided one
     * @param lexeme The name of the entry to search for
     * @return A pointer to the Entry referenced by the entryId or nullptr if it doesn't exist
     */
    Entry* searchEntry(const std::string& lexeme);

    /**
     * This function removes the entry that has its lexeme equal to the provided one from its table
     * @param lexeme The name of the entry to delete
     * @return true if the entry was deleted and false if the entry does not exist
     */
    bool deleteEntry(const std::string& lexeme);

    /**
     * This function removes the entry that has its lexeme equal to the provided one from its table
     * @param entryId The id of the entry to delete
     * @return true if the entry was deleted and false if the entry does not exist
     */
    bool deleteEntry(int entryId);

    /**
     * This function returns the summation of the size of all the entries in the table
     * It is useful to calculate the size of the activation register of the function represented by this table.
     * @return the summation of the size of all the entries in the table
     */
    int getTableEntriesSize();

    /**
     * This function should not be used during normal operation and is intended for advanced users only
     * This function adds the provided size to the summation of the size of all the entries in the table and also advances the displacement of the next entry to be added to the table
     * @param size the size added to the summation of the size of all the entries in the table
     */
    void _addTableEntriesSize(int size);

    /**
     * This function should not be used during normal operation and is intended for advanced users only
     * This function provides the displacement of the next entry to be added to the table
     * @return the displacement of the next entry to be added to the table
     */
    int _getDisplacement() const;

    /**
     * This function should not be used during normal operation and is intended for advanced users only
     * This function provides access to the Entries Storage object
     * @return a reference to the Entries Storage object
     */
    std::unordered_map<int,Entry*>& _getEntriesStorage();


private:

    /// Table unique identifier
    int id;

    /// Entries ID counter reference (there is an unique counter per TSManager)
    int* entryId;

    /// Name of the symbol table (can be void (""))
    std::string tableName;

    /// Table storage (Entries are stored in a hashmap due to its faster search time)
    std::unordered_map<int,Entry*> table;

    /// Hashmap that enables quick search of entries by name (it maps names to their corresponding id)
    std::unordered_map<std::string,int> lexemeToID;

    /// Displacement of the next entry to be added to the table
    int displacement = 0;

    /// The summation of the size of all the entries in the table
    int tableEntriesSize = 0;
};

}

#endif //TS_SYMBOLTABLE_H
