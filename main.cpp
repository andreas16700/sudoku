//
//  main.cpp
//  sudoku
//
//  Created by Andrew Loizides on 24/12/2017.
//  Copyright © 2017 Andrew Loizides. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#define K 9
#define spacing 10
using namespace std;
void printTable(int Table[K][K]);
void fillTable(int Table[K][K]);
void randomFillTable(int Table[K][K], int nums);
void fillTableManually(int Table[K][K], char & rowChar, int & c);
void printDash();
void printRow();
int randomNum();
bool isCorrect(int table[K][K], int row, int column, int number);

bool isProtected[K][K]={};

int main() {
    int c=-1;
    char rowChar='A';   //row is used to check for x (if fillTableManually must end) and c to check for moves.
    srand( static_cast<unsigned int>(time(NULL)));
    int Table[K][K]={};
    cout<<endl;
    cout<<"------------------------------"<<endl;
    cout<<"      Welcome to sudoku!      "<<endl;
    cout<<"------------------------------"<<endl<<endl;
    cout<<"For info on difficulty enter 'info'"<<endl;
    cout<<"Choose difficulty: (easy | medium | hard | ultra hard)"<<endl;
    string difficulty;
    cin>>difficulty;
    if (difficulty=="info"){
        cout<<"Easy has 65 prefilled numbers, Medium has 38, Hard has 25 and Ultra Hard has 17"<<endl<<endl;
        cout<<"Choose difficulty: (easy | medium | hard | ultra hard)"<<endl;
        cin>>difficulty;
    }
    if(!(difficulty == "easy" || difficulty == "medium"|| difficulty == "hard" || difficulty == "ultra hard"))
        do{
            cout<<"Wrong difficulty. Choose between easy, medium and ultra hard."<<endl;
            cin>>difficulty;
        }while (!(difficulty == "easy" ||difficulty == "medium"||difficulty == "hard" || difficulty == "ultra hard"));
    int prefilledNums;
    if (difficulty == "easy")
        prefilledNums = 65;
    else if (difficulty == "medium")
        prefilledNums = 38;
    else if (difficulty == "hard")
        prefilledNums = 25;
    else
        prefilledNums = 17;
    
    randomFillTable(Table, prefilledNums);
    //fillTable(Table);
    do{
        fillTableManually(Table, rowChar, c);
    }while(rowChar!='x' && c<(K*K-prefilledNums));
    cout<<"This is the end.";
}

void fillTableManually(int Table[K][K], char & rowChar, int & c){
    int num, row=0, col=0;
    c=0;
    char colChar;
    cout<<"To remove a number first enter 're' and press enter."<<endl<<"Input number in format [Row][Col][Number]:  ";
    cin>>rowChar;
    if (rowChar=='x')   {return;}
    cin>>colChar;
    bool isInRemoveMode = false;
    if (rowChar=='r' && colChar=='e'){
        isInRemoveMode=true;
        cout<<"Will remove the next number."<<endl<<"Input location of the number in format [Row][Col]:  ";
        cin>>rowChar;
        cin>>colChar;
        num=0;
    }
    else
        cin>>num;
    row=rowChar-'A';
    col=colChar-'A';
    //DIAG  cout<<"rowChar: "<<rowChar<<" colChar: "<<colChar<<" num: "<<num<<endl;
    //DIAG  cout<<"isInRemoveMode: "<<isInRemoveMode<<endl;
    //DIAG  cout<<"isCorrect: "<<isCorrect(Table, row, col, num)<<endl;
    
    
    //Checking number and letters
    
    
    if ((!(num>=1 && num<=9) && !isInRemoveMode) || !(rowChar>='A' && rowChar<='I') || !(colChar>='A' &&colChar<='I'))
        do{
            cout<<"Row and column must be between A and I and number must be between 1 and 9. Try again: ";
            cin>>rowChar;
            cin>>colChar;
            cin>>num;
            row=rowChar-'A';
            cout<<"row: "<<row;
            col=colChar-'A';
            cout<<"col: "<<col<<endl;
        }while(!(num>=1 && num<=9) || !(rowChar>='A' && rowChar<='I') || !(colChar>='A' && colChar<='I'));
    if ((!isCorrect(Table, row, col, num)) && (!isInRemoveMode))
        do{
            cout<<"Wrong number."<<endl<<"Input other number in format [Row][Col][Number]:   ";
            cin>>rowChar;
            cin>>colChar;
            cin>>num;
            row=rowChar-'A';
            col=colChar-'A';
        }while(!(isCorrect(Table, row, col, num)));
    //DIAG      cout<<"row: "<<row<<" "<<"col: "<<col<<endl;
    //DIAG      cout<<"isProtected: "<<isProtected[row][col];
    if (isProtected[row][col]){
        cout<<endl<<endl<<"Cannot remove, "<<rowChar<<colChar<<Table[row][col]<<" is a prefilled number."<<endl<<endl;
        return;
    }
    else if (isInRemoveMode)
        Table[row][col]=0;
    else{
        Table[row][col]=num;
        c++;
    }
    //DIAG  cout<<"entry: "<<"Table["<<row<<"]["<<col<<"]="<<num<<endl;
    //DIAG  cout<<Table[row][col]<<endl;
    printTable(Table);
}


void randomFillTable(int Table[K][K], int nums){
    int c=0;
    do{
        int row=randomNum(), col=randomNum(), num=randomNum();
        if (isCorrect(Table, row, col, num)){
            Table[row][col]=num;
            isProtected[row][col]=true;
            c++;
        }
    }while(c<=nums);
    printTable(Table);
}




int randomNum(){    return rand()%10;   }



void fillTable(int Table[K][K]){
    int plus=0, minus=0;
    for (int r=0; r<K; r++){
        for (int c=0; c<K; c++){
            if (c>5)
                minus=-6;
            else if (c>2)
                minus=-3;
            Table[r][c]=c+1+plus+minus;
        }
        minus=0;
        plus+=3;
        if (plus==9)
            plus=0;
    }
    printTable(Table);
}


void printDash(){
    
    cout<<endl<<setw(3)<<"";
    for(int f=0; f<K; f++)
        if (f==3 || f==6)
            cout<<"-"<<setw(spacing-1)<<""<<setw(6)<<"------";
        else
            cout<<setw(6)<<"------";
    cout<<setw(1)<<"-"<<endl;
    
}

void printRow(){
    for(int f=0; f<K; f++){
        char letterOfColumn='A'+f;
        if (f==3 || f==6)
            cout<<setw(6+spacing)<<letterOfColumn;
        else
            cout<<setw(6)<<letterOfColumn;
    }
}

void printTable(int Table[K][K]){
    cout<<endl<<"Table: ";
    cout<<endl<<setw(1)<<"";
    printRow();
    printDash();
    for (int r=0; r<K; r++){
        char letterOfRow='A'+r;
        if (r==3 || r==6){
            for (int c=0; c<spacing/3; c++)
                cout<<endl;
            cout<<endl<<setw(1)<<"";
            printRow();
            printDash();
            cout<<setw(1)<<letterOfRow;
        }
        else
            cout<<setw(1)<<letterOfRow;
        for (int c=0; c<K; c++){
            string numToPrint;
            if (Table[r][c] == 0)
                numToPrint=" ";
            else
                numToPrint=to_string(Table[r][c]);
            if (c==3 || c==6)
                cout<<setw(3)<<"|"<<setw(spacing-3)<<letterOfRow<<setw(3)<<"|"<<setw(3)<<numToPrint;
            else
                cout<<setw(3)<<"|"<<setw(3)<<numToPrint;
        }
        cout<<setw(3)<<"|";
        printDash();
    }
}

bool isCorrect(int table[K][K], int row, int column, int number){
    /*int square;
    switch (row/(K/3)) {
        case 0:
            if (column/(K/3) == 0)
                square=1;
            else if (column/(K/3) == 1)
                square=2;
            else
                square=3;
            break;
        case 1:
            if (column/(K/3) == 0)
                square=4;
            else if (column/(K/3) == 1)
                square=5;
            else
                square=6;
            break;
            
        default:
            if (column/(K/3) == 0)
                square=7;
            else if (column/(K/3) == 1)
                square=8;
            else
                square=9;
            break;
    }
     */
    
    
    
    // checking in row
    for (int r=0; r<K; r++)
        if (table[r][column]==number)
            return false;
    
    //checking in column
    for (int c=0; c<K; c++)
        if (table[row][c]==number)
            return false;
    
    //checking in square
    int rStart, cStart, rEnd, cEnd;
    if (row%3 == 0){
        rStart=row;
        rEnd=row+2;
    }
    else if (row%3 == 1){
        rStart=row-1;
        rEnd=row+1;
    }
    else{
        rStart=row-2;
        rEnd=row;
    }
    
    
    if (column%3 == 0){
        cStart=column;
        cEnd=column+2;
    }
    else if (column%3 == 1){
        cStart=column-1;
        cEnd=column+1;
    }
    else{
        cStart=column-2;
        cEnd=column;
    }
    //cout<<"rStart: "<<rStart<<" "<<"rEnd: "<<rEnd<<"cStart: "<<cStart<<" "<<"cEnd: "<<cEnd<<endl;
        //actually checking...
    for (int r=rStart; r<(rEnd+1); r++)
        for (int c=cStart; c<(cEnd+1); c++)
            if (table[r][c]==number)
                return false;
    
    return true;
}


