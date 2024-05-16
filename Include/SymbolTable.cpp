#include "TSConfig.h"
#include "SymbolTable.h"

using namespace TS_CPP;

SymbolTable::SymbolTable(int id, int* entryId)
{
    this->id = id;
    this->tableName = "";
    this->entryId = entryId;
}

SymbolTable::SymbolTable(const int id, int* entryId, const std::string& tableName)
{
    this->id = id;
    this->tableName = tableName;
    this->entryId = entryId;
}

int SymbolTable::getId() const
{
    return id;
}

std::string SymbolTable::getTableName() const
{
    return tableName;
}

Entry* SymbolTable::createNewEntry(const std::string& lexeme)
{
    if(lexemeToID.find(lexeme) == lexemeToID.end()) // if entry does not exist
    {
        int newEntryID = ++(*entryId);
        lexemeToID[lexeme] = newEntryID;
        auto* entry = new Entry(this, lexeme, newEntryID);
        entry->_setDisplacement(displacement);
        table[newEntryID] = entry;
        tsinfo("Created new Entry for table with id=%d (%s) with entryId=%d, lexeme=%s",id,tableName.c_str(),entry->getId(),entry->getLexeme().c_str());
        return entry;
    }
    else // if entry exists
    {
        Entry* entry = table[lexemeToID[lexeme]];
        tserror("Cannot create Entry; it already exist for table with id=%d (%s) with entryId=%d, lexeme=%s",id,tableName.c_str(),entry->getId(),entry->getLexeme().c_str());
        return entry;
    }
}

Entry *SymbolTable::getEntry(const int entryId)
{
    if(table.find(entryId) == table.end()) // if entry does not exist
    {
        tsinfo("Entry with id=%d does not exist in table with id=%d and name='%s'",entryId, id, tableName.c_str());
        return nullptr;
    }
    else
    {
        Entry* entry = table[entryId];
        tsinfo("Entry with id=%d, lexeme='%s' found in table with id=%d and name='%s'",entry->getId(), entry->getLexeme().c_str(), id, tableName.c_str());
        return entry;
    }
}

Entry *SymbolTable::searchEntry(const std::string& lexeme)
{
    if(lexemeToID.find(lexeme) == lexemeToID.end()) // if entry does not exist
    {
        tsinfo("Entry with lexeme='%s' does not exist in table with id=%d and name='%s'",lexeme.c_str(), id, tableName.c_str());
        return nullptr;
    }
    else
    {
        Entry* entry = table[lexemeToID[lexeme]];
        tsinfo("Entry with id=%d, lexeme='%s' found in table with id=%d and name='%s'",entry->getId(), entry->getLexeme().c_str(), id, tableName.c_str());
        return entry;
    }
}

bool SymbolTable::deleteEntry(const std::string& lexeme)
{
    if(lexemeToID.find(lexeme) == lexemeToID.end()) // if entry does not exist
    {
        tserror("Entry with lexeme='%s' does not exist", lexeme.c_str());
        return false;
    }
    else
    {
        return deleteEntry(lexemeToID[lexeme]);
    }
}

bool SymbolTable::deleteEntry(const int entryId)
{
    if(table.find(entryId) == table.end()) // if entry does not exist
    {
        tserror("Entry with id=%d does not exist", entryId);
        return false;
    }
    else
    {
        Entry* entry = table[entryId];
        const std::string lexeme = entry->getLexeme();
        table.erase(entryId);
        lexemeToID.erase(lexeme);
        delete entry;
        tsinfo("Entry with id=%d successfully deleted", entryId);
        return true;
    }
}

int SymbolTable::getTableEntriesSize()
{
    return tableEntriesSize;
}

void SymbolTable::_addTableEntriesSize(int size)
{
    tableEntriesSize += size;
    displacement += size;
}

AttributeValue* SymbolTable::getAttribute(const std::string& attributeName)
{
    if(attributes.find(attributeName) == attributes.end())
    {
        tsinfo("Attribute of entry %d (%s) with name=%s not found",id,lexeme.c_str(),attributeName.c_str());
        return nullptr;
    }
    else
    {
        tsdebug("Attribute of entry %d (%s) with name=%s found",id,lexeme.c_str(),attributeName.c_str());
        return attributes[attributeName];
    }
}

void SymbolTable::setNumericAttribute(const std::string &attributeName, long long value)
{
    if(attributes.find(attributeName) == attributes.end())
    {
        tsinfo("Setting new attribute of entry %d (%s) with name=%s",id,lexeme.c_str(),attributeName.c_str());
    }
    else
    {
        tsinfo("Attribute of entry %d (%s) with name=%s already exist. Overwriting previous value...",id,lexeme.c_str(),attributeName.c_str());
        delete attributes[attributeName];
    }

    attributes[attributeName] = new AttributeValue(value);
}

void SymbolTable::setStringAttribute(const std::string &attributeName, const char *value)
{
    if(attributes.find(attributeName) == attributes.end())
    {
        tsinfo("Setting new attribute of entry %d (%s) with name=%s & value=%s",id,lexeme.c_str(),attributeName.c_str(),value);
    }
    else
    {
        tsinfo("Attribute of entry %d (%s) with name=%s already exist. Overwriting previous value with the new one (%s)",id,lexeme.c_str(),attributeName.c_str(),value);
        delete attributes[attributeName];
    }

    attributes[attributeName] = new AttributeValue(value);
}


SymbolTable::~SymbolTable()
{
    for(auto entry : table)
    {
        delete entry.second;
    }
}

std::unordered_map<int, Entry *> &SymbolTable::_getEntriesStorage()
{
    return table;
}

int SymbolTable::_getDisplacement() const
{
    return displacement;
}
