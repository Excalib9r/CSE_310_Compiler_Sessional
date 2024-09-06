#include "ScopeTable.h"

class symbolTable
{
    scopeTable *current;
    int scopeTableNumber;
    int position1;
    int position2;
    int bucketSize;
    int countTable;

public:
    symbolTable()
    {
        current = NULL;
        bucketSize = 0;
        countTable = 0;
        scopeTableNumber = 0;
        position1 = 0;
        position2 = 0;
    }

    void setBucketSize(int bucketSize)
    {
        this->bucketSize = bucketSize;
    }

    void EnterScope()
    {
        countTable++;
        scopeTable *newTable = new scopeTable(bucketSize);
        newTable->setParentTable(current);
        scopeTableNumber = countTable;
        newTable->setUniqueNumber(countTable);
        current = newTable;
    }

    int getPosition1()
    {
        return position1;
    }

    int getPosition2()
    {
        return position2;
    }

    int getScoptableNumber()
    {
        return scopeTableNumber;
    }

    int getCurrentScoptableNumber(){
        return current->getUniqueNumber();
    }

    bool ExitScope()
    {
        bool scopeDeleted = false;
        if (current != NULL)
        {
            scopeTableNumber = current->getUniqueNumber();
            scopeDeleted = true;
            scopeTable *myTable = current->getParentTable();
            delete current;
            current = myTable;
        }
        return scopeDeleted;
    }

    bool Insert(string name, string type)
    {
        bool inserted = current->Insert(name, type);
        scopeTableNumber = current->getUniqueNumber();
        position1 = current->getPosition1();
        position2 = current->getPosition2();
        return inserted;
    }

    bool Remove(string name)
    {
        bool deleted = current->Delete(name);
        scopeTableNumber = current->getUniqueNumber();
        position1 = current->getPosition1();
        position2 = current->getPosition2();
        return deleted;
    }

    symbolInfo *LookUp(string name)
    {
        scopeTable *parent = current;
        symbolInfo *symbol = parent->LookUp(name);
        scopeTableNumber = parent->getUniqueNumber();
        position1 = parent->getPosition1();
        position2 = parent->getPosition2();
        while (symbol == NULL)
        {
            parent = parent->getParentTable();
            if (parent != NULL)
            {
                symbol = parent->LookUp(name);
                scopeTableNumber = parent->getUniqueNumber();
                position1 = parent->getPosition1();
                position2 = parent->getPosition2();
            }
            if (parent == NULL)
            {
                break;
            }
        }
        return symbol;
    }

    void PrintCurrentScopeTable(ofstream& output)
    {
        current->Print(output);
    }

    void PrintAllScopeTable(ofstream& output)
    {
        scopeTable *parent = current;

        while (parent != NULL)
        {
            parent->Print(output);
            cout << endl;
            parent = parent->getParentTable();
        }
    }

    ~symbolTable()
    {
        delete current;
    }
};