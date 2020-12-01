#include<bits/stdc++.h>
#define MAX 20
using namespace std;

void getdata(string n[MAX],char a[10][10][4],int dataInd,int endInd,int blockInd);
void putData(string n[MAX],char a[10][10][4],int dataInd,int endInd,int blockInd);
void loadRegister(string n[MAX],char a[10][10][4],char reg[4],int dataInd,int endInd,int blockInd);
void storeRegister(string n[MAX],char a[10][10][4],char reg[4],int dataInd,int endInd,int blockInd);
void run(string n[MAX],char a[10][10][4],int jobInd,int dataInd,int endInd);
void machine(string n[MAX],int len);

int main()
{
    int i,len;
    string n[MAX];
    ifstream foo;
    foo.open("input.txt");
    i=0;
    while (foo)
    {
        getline(foo, n[i],'\n');
        i++;
    }
    len=i;
    machine(n,len);

    foo.close();
    return 0;
}
void loadRegister(string n[MAX],char a[10][10][4],char reg[4],int addr,int dataInd,int endInd)
{
    int i,j=addr/10,k=addr%10;
    for(i=0; i<4; i++)
    {
        reg[i] = a[j][k][i];
    }
}

void storeRegister(string n[MAX],char a[10][10][4],char reg[4],int addr,int dataInd,int endInd)
{
    int i,j=addr/10,k=addr%10;
    for(i=0; i<4; i++)
    {
        a[j][k][i] = reg[i] ;
    }
}

void getdata(string n[MAX], char a[10][10][4],int dataInd,int endInd,int blockInd)
{
    int t=dataInd+1,data_len,i=0,j=0,k=0;
    data_len = n[t].length();
    cout<<"Data leng: "<<data_len;
    blockInd = blockInd / 10;
    //cout<<"BlockInd :"<<blockInd;

    while(i<data_len)
    {
        a[blockInd][k][j] = n[t][i];

        j++;
        if(j == 4)
        {
            j=0;
            k++;
        }
        i++;
    }

    //cout<<"\nBlockind + 0 + 1:"<<a[blockInd][0][1];
}

void putData(string n[MAX], char a[10][10][4],int dataInd,int endInd,int blockInd)
{
    //cout<<"Data is loading ... "<<endl;
    //while(dataInd < endInd)
    int i=0,j;
    blockInd = blockInd / 10;

    while(i<10)
    {
        for(j=0; j<4; j++)
            cout<<a[blockInd][i][j];
        i++;
    }
    cout<<"\n";

}

void run(string n[MAX],char a[10][10][4],int jobInd,int dataInd,int endInd)
{
    int blockInd,reg_addr,instr_block = 0,addrs = 0,dataLine=dataInd;
    static char reg[4] = {'\0'};
    int numInstr=20,itr=0;
    while(itr<numInstr)
    {
        //cout<<a[instr_block][addrs][0] <<" ";
        if(a[instr_block][addrs][0] == 'G')
        {
            blockInd = (a[instr_block][addrs][2] - '0') * 10 + (a[instr_block][addrs][3]- '0') ;
            cout<<"|"<<blockInd<<"|G|";
            getdata(n,a,dataLine,endInd,blockInd);
            dataLine++;
        }
        else if(a[instr_block][addrs][0]  == 'P')
        {
            blockInd = (a[instr_block][addrs][2] - '0') * 10 + (a[instr_block][addrs][3]- '0') ;
            cout<<"|"<<blockInd<<"|P|";
            putData(n,a,dataInd,endInd,blockInd);
        }
        else if(a[instr_block][addrs][0] == 'L')
        {
            reg_addr = (a[instr_block][addrs][2] - '0') * 10 + (a[instr_block][addrs][3]- '0') ;
            loadRegister(n,a,reg,reg_addr,dataInd,endInd);
            //cout<<"Register content: "<<reg[0]<<reg[1]<<reg[2]<<reg[3]<<"\n";
        }
        else if(a[instr_block][addrs][0] == 'S')
        {
            reg_addr = (a[instr_block][addrs][2] - '0') * 10 + (a[instr_block][addrs][3]- '0') ;
            storeRegister(n,a,reg,reg_addr,dataInd,endInd);
        }
        else
        {
            cout<<"Nothing: "<<itr<<"Letter: "<< a[0][itr][0]<<"\n";
        }
        itr++;
        addrs++;

        if(itr % 10 == 0)
        {
            instr_block++;
            addrs = 0;
            //cout<<i<<"II"<<instrInd<<" IB "<<instr_block;
        }
    }
}

void machine(string n[MAX],int len)
{
    static char a[10][10][4]= {'0'};
    int jobidInd,DataInd,EndInd;

    for(int i=0; i<len; i++)
        cout << n[i] << endl;

    int t=0;
    while(t<len)
    {
        if(n[t][0] == '$')
            if(n[t][1] == 'A')
                jobidInd = t;
            else if(n[t][1] == 'D')
                DataInd = t;
            else
                EndInd =t;
        cout<<n[t]<<endl;
        t++;
    }
    int k=0;

    stringstream strtoint(n[jobidInd].substr(8, 4));
    int numInstr;
    strtoint>>numInstr;
    cout<<numInstr<<endl;

    //store instruction
    //instr_ block stores block number for storing instr
    int i=0,instrInd = jobidInd + 1,instr_block = 0,addrs = 0;
    while(i <numInstr)
    {
        for(int j=0; j<4; j++)
        {
            a[instr_block][addrs][j] = n[instrInd][k];
            k++;
        }
        i++;
        addrs++;

        if(i % 10 == 0)
        {
            instrInd++;
            instr_block++;
            addrs = 0;
            k=0;
        }
    }

    cout<<"Str: ";
    for(int itr=0; itr < 10 ; itr++)
        cout<<a[0][itr][0]<<" "<<a[0][itr][1]<<" "<<a[0][itr][2]<<" "<<a[0][itr][3]<<" "<<endl;
    cout<<"Str: ";
    for(int itr=0; itr < 10 ; itr++)
        cout<<a[1][itr][0]<<" "<<a[1][itr][1]<<" "<<a[1][itr][2]<<" "<<a[1][itr][3]<<" "<<endl;

    run(n,a,jobidInd,DataInd,EndInd);

}
