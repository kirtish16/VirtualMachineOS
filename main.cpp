#include<bits/stdc++.h>

using namespace std;

void getdata(string n[10],char a[10][10][4],int dataInd,int endInd,int blockInd);
void loadRegister(string n[10],char a[10][10][4],char reg[4],int dataInd,int endInd,int blockInd);
void storeRegister(string n[10],char a[10][10][4],char reg[4],int dataInd,int endInd,int blockInd);
void run(string n[10],char a[10][10][4],int jobInd,int dataInd,int endInd);
void machine(string n[10],int len);

int main()
{
    //char n[10][50];
    int i,len;
    string n[10];
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
void loadRegister(string n[10],char a[10][10][4],char reg[4],int addr,int dataInd,int endInd)
{
    int i,j=addr/10,k=addr%10;
    for(i=0;i<4;i++)
    {
        reg[i] = a[j][k][i];
    }
}

void storeRegister(string n[10],char a[10][10][4],char reg[4],int addr,int dataInd,int endInd)
{
    int i,j=addr/10,k=addr%10;
    for(i=0;i<4;i++)
    {
        a[j][k][i] = reg[i] ;
    }
}

void getdata(string n[10], char a[10][10][4],int dataInd,int endInd,int blockInd)
{
    //while(dataInd < endInd)
    int t=dataInd+1,data_len,i=0,j=0,k=0;
    data_len = n[t].length();
    //cout<<"Data leng: "<<data_len;
    blockInd = blockInd / 10;
    //cout<<"BlockInd :"<<blockInd;

    while(i<data_len)
    {
            a[blockInd][k][j] = n[t][i];

                j++;
            if(j == 4)
             {
                 j=0;
                k++;}
                i++;
    }

    //cout<<"\nBlockind + 0 + 1:"<<a[blockInd][0][1];
}

void run(string n[10],char a[10][10][4],int jobInd,int dataInd,int endInd)
{
    int blockInd,addr;
    static char reg[4] = {'\0'};
    int numInstr=10,itr=0;
    while(itr<numInstr)
    {
        //cout<<itr<<" ";
        if(a[0][itr][0] == 'G')
        {
            blockInd = (a[0][itr][2] - '0') * 10 + (a[0][itr][3]- '0') ;
            cout<<"|"<<blockInd<<"||";
            getdata(n,a,dataInd,endInd,blockInd);
        }
        //else if(a[0][itr][0] == 'P')

        else if(a[0][itr][0] == 'L')
            {
                addr = (a[0][itr][2] - '0') * 10 + (a[0][itr][3]- '0') ;
                cout<<itr<<"Itr " <<addr<<'/';
                loadRegister(n,a,reg,addr,dataInd,endInd);
                cout<<"Register content: "<<reg[0]<<reg[1]<<reg[2]<<reg[3]<<"\n";
            }
        else if(a[0][itr][0] == 'S')
        {
            addr = (a[0][itr][2] - '0') * 10 + (a[0][itr][3]- '0') ;
            storeRegister(n,a,reg,addr,dataInd,endInd);
        }
        else{cout<<"Nothing: "<<itr<<"Letter: "<< a[0][itr][0]<<"\n";}
        itr++;
    }
}

void machine(string n[10],int len)
{
    static char a[10][10][4]= {'0'};
    int jobidInd,DataInd,EndInd;

    //for(int i=0;i<len;i++)
    //cout << n[i] << endl;

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
    cout<<jobidInd<<" "<<DataInd<<" "<<EndInd<<endl;
    int k=0;

    stringstream strtoint(n[jobidInd].substr(8, 4));
    int numInstr;
    strtoint>>numInstr;
    cout<<numInstr<<endl;

    //store instruction
    //instr_ block stores block number for storing instr
    int i=0,instrInd = jobidInd + 1,instr_block = 0,addrs = 0;
while(i <numInstr)    {
        for(int j=0; j<4; j++)
        {
            a[instr_block][addrs][j] = n[instrInd][k];
                k++;
        }
        //cout<< a[instr_block][addrs] <<"<-" << n[instrInd] <<endl;
        i++;
        addrs++;

        if(i % 10 == 0)
        {instrInd++;instr_block++;addrs = 0;k=0;
        //cout<<i<<"II"<<instrInd<<" IB "<<instr_block;
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

//Gd => get data
//Pd -> Put data
//Lr -> load register
//Sr -> store register
// BT
//Output: A MAN A PLAN A CANAL PANAMA

/*
$AMJ010200210001
GD30LR36SR40LR35SR41LR34SR42LR33SR43LR32
SR44LR31SR45LR30SR46LR39SR47SR38SR49PD40
H
$DTA
AMA  PANANAL A CPLANN A A MA
$END0102
*/

/*
0 4 6
21
Str: G D 3 0
L R 3 6
S R 4 0
L R 3 5
S R 4 1
L R 3 4
S R 4 2
L R 3 3
S R 4 3
L R 3 2
*/
/*
$AMJ010200210001
GD30LR36SR40LR35SR41LR34SR42LR33SR43LR32
SR44LR31SR45LR30SR46LR39SR47SR38SR49PD40
H
$DTA
AMA  PANANAL A CPLANN A A MA
$END0102

0 4 6
21
Str: G D 3 0
L R 3 6
S R 4 0
L R 3 5
S R 4 1
L R 3 4
S R 4 2
L R 3 3
S R 4 3
L R 3 2
|30||
Blockind + 0 + 1:M*/
