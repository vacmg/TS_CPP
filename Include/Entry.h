#ifndef TS_ENTRY_H
#define TS_ENTRY_H

#include "unordered_map"
#include "string"

#include "TSConfig.h"
#include "AttributeValue.h"

namespace TS_CPP{

/**
 * Entry class provides support for each row inside the symbol table
 * It consists of a lexeme, an id and an undefined amount of pairs consisting of attribute name and value (int/string)
 */
class Entry
{
public:
    /**
     * The constructor of an Entry
     * It should not be used directly, but using the method SymbolTable::createNewEntry
     * @param lexeme The lexeme of this entry
     * @param id The unique identifier of the entry
     */
    Entry(const std::string& lexeme, int id);

    /**
     * This function retrieves the lexeme of this entry
     * @return A string which holds the lexeme of the entry
     */
    std::string getLexeme() const;

    /**
     * This function retrieves the unique identifier of the entry
     * @return The id of the entry
     */
    int getId() const;

    /**
     * This function search the attribute with the specified name and returns its value
     * If the attribute does not exist, it returns a special attribute with attributeType=Null and data.str = nullptr (or data.num = 0)
     * @param attributeName The name of the attribute to search for
     * @return The value of the attribute if the attribute exist or NoAttribute (a special attribute with attributeType=Null and data.str = nullptr (or data.num = 0)) if it doesn't exist
     */
    AttributeValue* getAttribute(const std::string& attributeName);

    /**
     * This function stores a new attribute with the desired name and value
     * If the attribute already exist, it overwrites it
     * @param attributeName The name of the attribute to store
     * @param value The value of the attribute to store
     */
    void setNumericAttribute(const std::string& attributeName, long long value);

    /**
     * This function stores a new attribute with the desired name and value
     * If the attribute already exist, it overwrites it
     * @param attributeName The name of the attribute to store
     * @param value The value of the attribute to store
     */
    void setStringAttribute(const std::string& attributeName, const char* value);

    /**
     * This function deletes the attribute with the specified name from the Entry
     * @param attributeName The name of the attribute to delete
     * @return True if the attribute was successfully deleted or false if the attribute doesn't exist
     */
    bool deleteAttribute(const std::string& attributeName);

    /**
     * This function should not be used during normal operation and is intended for advanced users only
     * This function provides access to the Attribute Storage object
     * @return a reference to the Attribute Storage object
     */
    std::unordered_map<std::string,AttributeValue*>& getAttributesStorage();

private:

    /// The unique identifier of the entry (it is unique for each TSManager, even 2 entries from different tables doesn't share their Entry::id)
    int id;

    /// The lexeme of the entry
    std::string lexeme;

    /// The structure used to store all the attributes of the entry
    std::unordered_map<std::string,AttributeValue*> attributes;
};

}

#endif //TS_ENTRY_H
