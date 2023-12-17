#include <bits/stdc++.h>

using namespace std;

/*Initializing sizes of Field, adding bombs, also initializing Odd's vector*/
void fieldInit(vector<vector<bool> > &field, vector<double> &odds ,string fieldSize){
    if(fieldSize == "Small"){
        field = vector<vector<bool> >(3,vector<bool>(4,false));
        odds = {1.45, 2.48, 3.27, 4.91};
    }else if(fieldSize == "Medium"){
        field = vector<vector<bool> >(4,vector<bool>(7,false));
        odds = {1.29, 1.72, 2.29, 3.06, 4.08, 5.45, 7.26};
    }else if(fieldSize == "Big"){
        field = vector<vector<bool> >(5,vector<bool>(10,false));
        odds = {1.21, 1.51, 1.89, 2.36, 2.96, 3.7, 4.62, 5.78, 7.22, 9.03};
    }

    for(int i = 0 ; i < field[0].size(); i++){
        field[rand()%field.size()][i] = true;
    }

}

/*Displaying Field, 1 = Bomb, 0 = no Bomb*/
void DisplayField(vector<vector<bool> > &field, vector<double> &odds){
    cout << "Displaying Field:\n\n";
    for (int i = 0; i < field.size(); i++){
        for (int j = 0; j < field[0].size(); j++){
            cout << " " <<field[i][j] << "   ";   
        }
        cout << endl << endl;
    }
    for (int i = 0; i < field[0].size(); i++){
        cout << fixed << setprecision(2) << odds[i] << " ";   
    }
    cout << endl;
    
}

void oneSimulation(double &currBalance, vector<vector<bool> > &field, vector<double> &odds){
    float currBet = 0;
    cout << "Enter Your Bet: ";
    cin >> currBet;
    cout << endl;
    currBet = currBet>100.00 ? 100.00 : currBet;
    currBalance -= currBet;
    double currCashOut = currBet;
    for(int i = 0 ; i < field[0].size(); i++){
        if(i!=0) cout << "You can cashout $" << fixed << setprecision(2) << currCashOut << endl;
        int currPos;
        cout << "Choose Column Position: ";
        cin >> currPos;
        cout << endl;
        /*cashout*/
        if(currPos == -1){
            break;
        }else if(field[currPos][i]){ /*There is Bomb*/
            currCashOut = 0;
            break;
        }else{
            currCashOut = currBet * odds[i]; /*Ther is no Bomb*/
        }
    }
    if(currCashOut != 0)
        cout<< fixed << setprecision(2) << "$" << currCashOut << " Added To Your Balance" << endl;
    else 
        cout << "BOOM!" << endl;
    currBalance += currCashOut;
    cout<< "Your Balance: "<< fixed << setprecision(2) << "$" << currBalance << endl;
}

int main(){
    vector<vector<bool> > field;
    vector<double> odds;
    string fieldSize;
    double currBalance = 9999.00;

    while(true){
        cout << "Enter Size of Field (Small,Medium,Big): "; 
        cin >> fieldSize;
        cout << endl;
        fieldInit(field,odds,fieldSize);
        printf("field sizes: %d x %d\n",(int)field.size(),(int)field[0].size());
        DisplayField(field,odds);
        oneSimulation(currBalance,field,odds);
    }
    
}  