#include "SymbolTable.h"
#include <fstream>
#include <sstream>
#include <string>

int main()
{
    ifstream myfile;
    myfile.open("sample_input.txt");
    ofstream output;
    output.open("output.txt");

    string myLine;
    int bucketSize;

    if (myfile.is_open())
    {
        getline(myfile, myLine);
        istringstream bsize(myLine);
        string size;
        bsize >> size;
        bucketSize = stoi(size);
    }

    symbolTable table;
    table.setBucketSize(bucketSize);
    table.EnterScope();
    int number = table.getScoptableNumber();

    output << "      ScopeTable# " << number << " created" << endl;

    if (myfile.is_open())
    {
        int cmdNo = 0;
        while (myfile)
        {
            getline(myfile, myLine);
            cmdNo++;
            istringstream myString(myLine);

            if (myString)
            {
                string cmd;
                string first;
                string second;
                string third;
                myString >> cmd;

                if (cmd == "Q")
                {
                    bool notAlldeleted;
                    output << "cmd " << cmdNo << ": " << myLine << endl;
                    while (true)
                    {
                        notAlldeleted = table.ExitScope();
                        if (notAlldeleted == false)
                        {
                            break;
                        }

                        int number = table.getScoptableNumber();
                        output << "      ScopeTable# " << number << " removed" << endl;
                    }
                    break;
                }

                // insert starts
                else if (cmd == "I")
                {
                    output << "cmd " << cmdNo << ": " << myLine << endl;
                    myString >> first;
                    if (first == "\0")
                    {
                        output << "      Number of parameters mismatch for the command " << cmd << endl;
                    }
                    else
                    {
                        myString >> second;
                        if (second == "\0")
                        {
                            output << "      Number of parameters mismatch for the command " << cmd << endl;
                        }
                        else
                        {
                            myString >> third;
                            if (third != "\0")
                            {
                                output << "      Number of parameters mismatch for the command " << cmd << endl;
                            }
                            else
                            {
                                bool inserted = table.Insert(first, second);
                                int position1 = table.getPosition1();
                                int position2 = table.getPosition2();
                                if (inserted)
                                {
                                    output << "      Inserted in ScopeTable# " << table.getScoptableNumber() << " at position " << position1 << ", " << position2 << endl;
                                }
                                else
                                {
                                    output << "      '" << first << "'"
                                           << " already exists in the current ScopeTable" << endl;
                                }
                            }
                        }
                    }
                }
                // insert ends

                else if (cmd == "L")
                {
                    output << "cmd " << cmdNo << ": " << myLine << endl;
                    myString >> first;
                    if (first == "\0")
                    {
                        output << "      Number of parameters mismatch for the command " << cmd << endl;
                    }
                    else
                    {
                        myString >> second;
                        if (second != "\0")
                        {
                            output << "      Number of parameters mismatch for the command " << cmd << endl;
                        }
                        else
                        {
                            symbolInfo *symbol = table.LookUp(first);
                            if (symbol != NULL)
                            {
                                int position1 = table.getPosition1();
                                int position2 = table.getPosition2();

                                output << "      '" << first << "'"
                                       << " found in ScopeTable# " << table.getScoptableNumber() << " at position " << position1 << ", " << position2 << endl;
                            }
                            else
                            {
                                output << "      '" << first << "'"
                                       << " not found in any of the ScopeTables" << endl;
                            }
                        }
                    }
                }

                else if (cmd == "D")
                {
                    output << "cmd " << cmdNo << ": " << myLine << endl;
                    myString >> first;
                    if (first == "\0")
                    {
                        output << "      Number of parameters mismatch for the command " << cmd << endl;
                    }
                    else
                    {
                        myString >> second;
                        if (second != "\0")
                        {
                            output << "      Number of parameters mismatch for the command " << cmd << endl;
                        }
                        else
                        {
                            bool deleted = table.Remove(first);
                            if (deleted)
                            {
                                int position1 = table.getPosition1();
                                int position2 = table.getPosition2();

                                output << "      Deleted '" << first << "'"
                                       << " from ScopeTable# " << table.getScoptableNumber() << " at position " << position1 << ", " << position2 << endl;
                            }
                            else
                            {
                                output << "      Not found in the current ScopeTable" << endl;
                            }
                        }
                    }
                }

                else if (cmd == "P")
                {
                    output << "cmd " << cmdNo << ": " << myLine << endl;
                    myString >> first;
                    if (first == "\0")
                    {
                        output << "      Number of parameters mismatch for the command " << cmd << endl;
                    }
                    else
                    {
                        myString >> second;
                        if (first == "A")
                        {
                            if (second != "\0")
                            {
                                output << "      Number of parameters mismatch for the command " << cmd << endl;
                            }
                            else
                            {
                                table.PrintAllScopeTable(output);
                            }
                        }
                        else if (first == "C")
                        {
                            if (second != "\0")
                            {
                                output << "      Number of parameters mismatch for the command " << cmd << endl;
                            }

                            else
                            {
                                table.PrintCurrentScopeTable(output);
                            }
                        }
                        else
                        {
                            output << "      Number of parameters mismatch for the command " << cmd << endl;
                        }
                    }
                }

                else if (cmd == "S")
                {
                    output << "cmd " << cmdNo << ": " << myLine << endl;
                    table.EnterScope();
                    int number = table.getScoptableNumber();
                    output << "      ScopeTable# " << number << " created" << endl;
                }

                else if (cmd == "E")
                {
                    output << "cmd " << cmdNo << ": " << myLine << endl;
                    int number = table.getCurrentScoptableNumber();
                    if (number == 1)
                    {
                        output << "      ScopeTable# " << number << " cannot be removed" << endl;
                    }
                    else
                    {
                        table.ExitScope();
                        output << "      ScopeTable# " << number << " removed" << endl;
                    }
                }

                else
                {
                    output << "cmd " << cmdNo << ": " << myLine << endl;
                    cout << "      Invalid cmd" << endl;
                }
            }
        }
    }
    return 0;
}