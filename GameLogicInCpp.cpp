#include <bits/stdc++.h>

using namespace std;

/*Initializing sizes of Field and adding bombs*/
void fieldInit(vector<vector<bool> > &field, vector<double> &odds ,string fieldSize){
    if(fieldSize == "Small"){
        field = vector<vector<bool> >(3,vector<bool>(4,false));
    }else if(fieldSize == "Medium"){
        field = vector<vector<bool> >(4,vector<bool>(7,false));
    }else if(fieldSize == "Big"){
        field = vector<vector<bool> >(5,vector<bool>(10,false));
    }
    odds = vector<double>(field[0].size(),1);
    for(int i = 0 ; i < field[0].size(); i++){
        odds[i] = 1.0/(pow((1.0-(1.0/field.size())),i+1) * 1.0345);
        field[rand()%field.size()][i] = true;
    }

}

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
        }else if(field[currPos][i]){
            currCashOut = 0;
            break;
        }else{
            currCashOut = currBet * odds[i]; 
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
        printf("field sizes: %d x %d\n",field.size(),field[0].size());
        DisplayField(field,odds);
        oneSimulation(currBalance,field,odds);
    }
    
}  