#include "TSConfig.h"
#include "Entry.h"

using namespace TS_CPP;

Entry::Entry(const std::string& lexeme, int id)
{
    this->lexeme = lexeme;
    this->id = id;
}

std::string Entry::getLexeme() const
{
    return lexeme;
}

int Entry::getId() const
{
    return id;
}

AttributeValue* Entry::getAttribute(const std::string& attributeName)
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

void Entry::setNumericAttribute(const std::string &attributeName, long long value)
{
#if TS_PRINT_MESSAGES_LEVEL >= TS_LEVEL_ERROR
    if(attributes.find(attributeName) == attributes.end())
    {
        tsinfo("Setting new attribute of entry %d (%s) with name=%s",id,lexeme.c_str(),attributeName.c_str());
    }
    else
    {
        tsinfo("Attribute of entry %d (%s) with name=%s already exist. Overwriting previous value...",id,lexeme.c_str(),attributeName.c_str());
    }
#endif
    attributes[attributeName] = new AttributeValue(value);
}

void Entry::setStringAttribute(const std::string &attributeName, const char *value)
{
#if TS_PRINT_MESSAGES_LEVEL >= TS_LEVEL_INFO
    if(attributes.find(attributeName) == attributes.end())
    {
        tsinfo("Setting new attribute of entry %d (%s) with name=%s & value=%s",id,lexeme.c_str(),attributeName.c_str(),value);
    }
    else
    {
        tsinfo("Attribute of entry %d (%s) with name=%s already exist. Overwriting previous value with the new one (%s)",id,lexeme.c_str(),attributeName.c_str(),value);
    }
#endif
    attributes[attributeName] = new AttributeValue(value);
}

bool Entry::deleteAttribute(const std::string &attributeName)
{
    if(attributes.find(attributeName) == attributes.end()) // if entry does not exist
    {
        tserror("Attribute of entry %d (%s) with name=%s does not exist",id,lexeme.c_str(), attributeName.c_str());
        return false;
    }
    else
    {
        attributes.erase(attributeName);
        tsinfo("Attribute of entry %d (%s) with name=%s successfully deleted",id,lexeme.c_str(), attributeName.c_str());
        return true;
    }
}

std::unordered_map<std::string, AttributeValue*> &Entry::getAttributesStorage()
{
    return attributes;
}
