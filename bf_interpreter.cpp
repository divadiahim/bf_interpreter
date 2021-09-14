#include <iostream>
#include <cstring>
#include <fstream>
#include "termcolor.hpp"
using namespace std;
using namespace termcolor;
char tape[30000] = {0};
char *ptr = tape;
int link[50][2];
string ch;
void interpret(const char *str, char *in)
{

    int x = 0, y = 0, z = 0, loop;
    int temp;
    bool checked = false;
    ifstream ff(in);
    for (int i = 0; i <= strlen(str); i++)
    {
        if (str[i] == '[')
        {
            x = i;
            loop = 1;
            while (loop > 0)
            {
                if (str[++x] == '[')
                {
                    loop++;
                }
                else if (str[x] == ']')
                {
                    loop--;
                }
            }

            link[z][0] = i;
            link[z][1] = x;

            z++;
        }
    }
    for (int i = 0; i <= strlen(str); i++)
    {

        switch (str[i])
        {
        case '>':

            ++ptr;
            break;
        case '<':
            --ptr;
            break;
        case '+':
            ++*ptr;
            break;
        case '-':
            --*ptr;
            break;
        case '[':
            if (*ptr == 0)
            {
                for (int j = 0; j <= z; j++)
                {
                    if (link[j][0] == i)
                    {
                        i = link[j][1];
                    }
                }
            }
            break;

        case ']':
            if (*ptr != 0)
            {

                for (int j = 0; j <= z; j++)
                {
                    if (link[j][1] == i)
                    {
                        i = link[j][0];
                        break;
                    }
                }
            }
            break;
        case ',':
            ff.get(*ptr);
            break;
        case '.':
            putchar(*ptr);
            break;

        default:
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    char *in;
    in = argv[2];
    if (argc == 1)
        cout << red << "Fatal error: No input .bf file" << reset << endl;
    else if (argc >= 2)
    {

        if (argc == 2)
        {
            cout << blue << "No input in file" << reset << endl;
        }
        ifstream fin(argv[1]);
        getline(fin, ch, '\0');
        interpret(ch.c_str(), in);
    }

    return 0;
}