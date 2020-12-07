#include <bits/stdc++.h>
#define MAX 20
using namespace std;

void getdata(string n[MAX], char a[10][10][4], int dataInd, int endInd, int blockInd);
void putData(string n[MAX], char a[10][10][4], int dataInd, int endInd, int blockInd);
void loadRegister(string n[MAX], char a[10][10][4], char reg[4], int dataInd, int endInd);
void storeRegister(string n[MAX], char a[10][10][4], char reg[4], int dataInd, int endInd);
int compareRegister(char a[10][10][4], char reg[4], int addr, int dataInd, int endInd);
void run(string n[MAX], char a[10][10][4], int jobInd, int dataInd, int endInd);
void machine(string n[MAX], int len);

ofstream outputFile;
int main()
{
    int i, len = 0;
    string n[MAX];

    ifstream foo;
    foo.open("input.txt");
    i = 0;

    outputFile.open("output.txt");
    while (foo)
    {

        getline(foo, n[i], '\n');

        if (n[i][0] == '$' && n[i][1] == 'E')
        {
            len = i;
            machine(n, len + 1);
            i = -1;
            outputFile << "\n\n";
        }
        i++;
    }

    foo.close();
    outputFile.close();
    return 0;
}

int compareRegister(char a[10][10][4], char reg[4], int addr, int dataInd, int endInd, int blockInd)
{
    int i, j = addr / 10, k = addr % 10;
    for (i = 0; i < 4; i++)
    {

        if (reg[i] != a[j][k][i])
            return 0;
    }
    return 1;
}

void loadRegister(string n[MAX], char a[10][10][4], char reg[4], int addr, int dataInd, int endInd)
{
    int i, j = addr / 10, k = addr % 10;
    for (i = 0; i < 4; i++)
    {
        reg[i] = a[j][k][i];
    }
}

void storeRegister(string n[MAX], char a[10][10][4], char reg[4], int addr, int dataInd, int endInd)
{
    int i, j = addr / 10, k = addr % 10;
    for (i = 0; i < 4; i++)
    {
        a[j][k][i] = reg[i];
    }
}

void getdata(string n[MAX], char a[10][10][4], int dataInd, int endInd, int blockInd)
{
    int t = dataInd + 1, data_len, i = 0, j = 0, k = 0;
    data_len = n[t].length();
    blockInd = blockInd / 10;

    while (i < data_len)
    {
        a[blockInd][k][j] = n[t][i];

        j++;
        if (j == 4)
        {
            j = 0;
            k++;
        }
        i++;
    }

}

void putData(string n[MAX], char a[10][10][4], int dataInd, int endInd, int blockInd)
{
    int i = 0, j;
    blockInd = blockInd / 10;

    while (i < 10)
    {
        for (j = 0; j < 4; j++)
            outputFile << a[blockInd][i][j];
        i++;
    }
    outputFile << "\n";
}
/*******************************************************RUN************************************************/
void run(string n[MAX], char a[10][10][4], int jobInd, int dataInd, int endInd)
{
    int blockInd, reg_addr, instr_block = 0, addrs = 0, dataLine = dataInd;
    static char reg[4] = {'\0'};
    int itr = 0, c = 0;
    while (true)
    {
        if (a[instr_block][addrs][0] == 'H')
        {
            break;
        }

        if (a[instr_block][addrs][0] == 'G')
        {
            blockInd = (a[instr_block][addrs][2] - '0') * 10 + (a[instr_block][addrs][3] - '0');
            getdata(n, a, dataLine, endInd, blockInd);
            dataLine++;
        }
        else if (a[instr_block][addrs][0] == 'P')
        {
            blockInd = (a[instr_block][addrs][2] - '0') * 10 + (a[instr_block][addrs][3] - '0');
            putData(n, a, dataInd, endInd, blockInd);
        }
        else if (a[instr_block][addrs][0] == 'L')
        {
            reg_addr = (a[instr_block][addrs][2] - '0') * 10 + (a[instr_block][addrs][3] - '0');
            loadRegister(n, a, reg, reg_addr, dataInd, endInd);
        }
        else if (a[instr_block][addrs][0] == 'S')
        {
            reg_addr = (a[instr_block][addrs][2] - '0') * 10 + (a[instr_block][addrs][3] - '0');
            storeRegister(n, a, reg, reg_addr, dataInd, endInd);
        }
        else if (a[instr_block][addrs][0] == 'C')
        {
            reg_addr = (a[instr_block][addrs][2] - '0') * 10 + (a[instr_block][addrs][3] - '0');
            c = compareRegister(a, reg, reg_addr, dataInd, endInd, blockInd);
        }
        if (a[instr_block][addrs][0] == 'B' && c == 1)
        {
            int temp_addrs = (a[instr_block][addrs][3] - '0');
            int temp_instr = (a[instr_block][addrs][2] - '0');
            addrs = temp_addrs;
            instr_block = temp_instr;
        }
        else
        {
            itr++;
            addrs++;
            if (addrs % 10 == 0)
            {
                instr_block++;
                addrs = 0;
            }
        }
    }
}
/***************************************MACHINE************************************************/
void machine(string n[MAX], int len)
{
    static char a[10][10][4] = {' '};
    memset(a, ' ', sizeof(a[0][0][0]) * 10 * 10 * 4);
    int jobidInd, DataInd, EndInd;

    int t = 0;
    while (t < len)
    {
        if (n[t][0] == '$')
            if (n[t][1] == 'A')
                jobidInd = t;
            else if (n[t][1] == 'D')
                DataInd = t;
            else
                EndInd = t;
        t++;
    }
    int k = 0,i = 0, instrInd = jobidInd + 1, instr_block = 0, addrs = 0;
    while (true)
    {
        if (n[instrInd][k] == 'H')
        {
            a[instr_block][addrs][0] = n[instrInd][k];
            break;
        }
        for (int j = 0; j < 4; j++)
        {
            a[instr_block][addrs][j] = n[instrInd][k];
            k++;
        }
        i++;
        addrs++;

        if (i % 10 == 0)
        {
            instrInd++;
            instr_block++;
            addrs = 0;
            k = 0;
        }
    }
    run(n, a, jobidInd, DataInd, EndInd);
}
