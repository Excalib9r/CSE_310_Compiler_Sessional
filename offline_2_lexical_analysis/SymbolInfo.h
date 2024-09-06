#include <iostream>

using namespace std;

class symbolInfo
{
    string name;
    string type;
    symbolInfo *nextSymbol;

public:
    symbolInfo()
    {
        name = "";
        type = "";
        nextSymbol = NULL;
    }

    void setName(string name)
    {
        this->name = name;
    }

    string getName()
    {
        return this->name;
    }

    void setType(string type)
    {
        this->type = type;
    }

    string getType()
    {
        return this->type;
    }

    void setNextSymbol(symbolInfo *nextSymbol)
    {
        this->nextSymbol = nextSymbol;
    }

    symbolInfo *getNextSymbol()
    {
        return this->nextSymbol;
    }
};