#include "SymbolInfo.h"
#include<fstream>

int sdbm(string name, int bucketSize)
{
    int hashValue = 0;
    int length = name.length();

    for (unsigned int i = 0; i < length; i++)
    {
        hashValue = ((name[i]) + (hashValue << 6) + (hashValue << 16) - hashValue) % bucketSize;
    }

    return hashValue;
}

int hashFunction(int bucktetSize, string name)
{
    int index = sdbm(name, bucktetSize);
    // cout << "The index for " << name << " is " << index << endl;
    return index;
}

class scopeTable
{
    int uniqueNumber;
    int bucketSize;
    int position1;
    int position2;
    scopeTable *parentTable;
    symbolInfo **arr;

public:
    scopeTable(int size)
    {
        this->bucketSize = size;
        this->parentTable = NULL;
        position1 = 0;
        position2 = 0;
        arr = new symbolInfo *[size];
        for (int i = 0; i < size; i++)
        {
            arr[i] = NULL;
        }
    }

    void setParentTable(scopeTable *parentTable)
    {
        this->parentTable = parentTable;
    }

    scopeTable *getParentTable()
    {
        return this->parentTable;
    }

    void setUniqueNumber(int uniqueNumber)
    {
        this->uniqueNumber = uniqueNumber;
    }

    int getUniqueNumber()
    {
        return this->uniqueNumber;
    }

    int getPosition1()
    {
        return position1;
    }

    int getPosition2()
    {
        return position2;
    }

    bool checkString(string s1, string s2)
    {
        int length = s1.length();
        bool same = true;
        for (int i = 0; i < length; i++)
        {
            if (s1[i] != s2[i])
            {
                same = false;
                break;
            }
        }
        return same;
    }

    symbolInfo *LookUp(string name)
    {
        int index = hashFunction(bucketSize, name);
        position1 = index + 1;
        symbolInfo *root = arr[index];
        bool found = false;
        position2 = 0;
        while (root != NULL)
        {
            position2++;
            string rootString = root->getName();
            if (rootString.length() == name.length())
            {
                found = checkString(name, rootString);
                if (found == true)
                {
                    return root;
                }
            }
            root = root->getNextSymbol();
        }
        return NULL;
    }

    bool Insert(string name, string type)
    {
        symbolInfo *symbol = new symbolInfo;
        symbol->setName(name);
        symbol->setType(type);

        bool inserted = false;

        symbolInfo *value = LookUp(symbol->getName());

        if (value == NULL)
        {
            position2 = 1;
            // cout << "Inside insert function" << endl;
            inserted = true;
            int index = hashFunction(bucketSize, symbol->getName());
            position1 = index + 1;

            if (arr[index] == NULL)
            {
                arr[index] = symbol;
            }
            else
            {
                position2++;
                symbolInfo *root = arr[index];
                while (root->getNextSymbol() != NULL)
                {
                    position2++;
                    root = root->getNextSymbol();
                }

                root->setNextSymbol(symbol);
            }
        }

        return inserted;
    }

    bool Delete(string name)
    {
        symbolInfo *symbol = LookUp(name);
        if (symbol == NULL)
        {
            return false;
        }

        else
        {
            int index = hashFunction(bucketSize, name);
            if (arr[index] == symbol)
            {
                arr[index] = symbol->getNextSymbol();
            }
            else
            {
                symbolInfo *root = arr[index];

                while (root->getNextSymbol() != symbol)
                {
                    root = root->getNextSymbol();
                }
                root->setNextSymbol(symbol->getNextSymbol());
            }
            symbol->setNextSymbol(NULL);
            return true;
        }
    }

    void Print(ofstream& output)
    {
        output << "      ScopeTable# " << uniqueNumber << endl;
        for (int i = 0; i < bucketSize; i++)
        {
            output << "      " << i + 1 << "--> ";
            symbolInfo *root = arr[i];
            while (root != NULL)
            {
                output << "<" << root->getName() << "," << root->getType() << "> ";
                root = root->getNextSymbol();
            }
            output << endl;
        }
    }

    void destroyScopeTable()
    {
        for (int i = 0; i < bucketSize; i++)
        {
            delete arr[i];
        }
        delete[] arr;
    }

    ~scopeTable()
    {
        for (int i = 0; i < bucketSize; i++)
        {
            delete arr[i];
        }
        delete[] arr;
    }
};