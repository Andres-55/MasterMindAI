#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
using namespace std;

//Function Prototypes
string AI(char,char);
bool eval(string,string,char &,char &);
string set();

int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare variables
    string code,guess;  //code to break, and current guess
    char rr,rw;         //right digit in right place vs. wrong place
    int nGuess;         //number of guesses

    //Initialize Values
    nGuess=0;
    code=set();
    rr=rw=0;

    //Loop until solved and count to find solution
    do{
       nGuess++;
       guess=AI(rr,rw);
    }while(eval(code,guess,rr,rw));

    //Output the solution
    cout<<"Number of guesses using Linear Search = "<<nGuess<<endl;
    cout<<code<<"="<<guess<<endl;

    //Exit the prog
    return 0;
}


string AI(char rr, char rw) 
{
    static bool Version1 = true;
    static bool Version2 = false;
    static bool Version3 = false;
    static bool Version4 = false;
    static bool Version5 = false;

    static string finalGuess = "xxxx";
    static string correctDigits = "xxxx";
    static string guess = "-1111";
    static int pos1 = -1; 
    static int pos2 = -1; 
    static int pos3 = -1; 

    if (Version1) 
    {
        bool escape = true;
        int add = stoi(guess) + 1111;
        guess = to_string(add);
       
        while (guess.length() < 4) 
        {
            guess = "0" + guess;
        }

        if (rr > 0) {
            for (int i = 0; i < rr; i++) 
            {
                for (int j = 0; j < 4; j++) 
                {
                    if (correctDigits[j] == 'x') 
                    {
                        int temp = stoi(guess) - 1111;
                        string temp2 = to_string(temp);
                        while (temp2.length() < 4) 
                        {
                            temp2 = "0" + temp2;
                        }
                        correctDigits[j] = temp2[j];
                        break;
                    }
                }
            }
        }

        for(int i = 0; i < 4; i++)
            {
                if(correctDigits[i] == 'x')
                {
                    escape = false;
                }
            }
        
        if (guess == "9999" || escape) 
        {
            Version1 = false;
            Version2 = true;
            for (int j = 0; j < 4; j++) 
            {
                if (correctDigits[j] == 'x') 
                {
                    correctDigits[j] = '9';
                }
            }
        }

        if (Version1) 
        {
            return guess;
        }
    }

    if (Version2) 
    {
        string guess2;
        static int turn1 = 0;

        if (turn1 == 0) 
        {
            rr = 0;
        }

        if (rr == 1 || turn1 == 3) 
        {
            if (rr == 1)
            {
                finalGuess[turn1 - 1] = correctDigits[0];
                pos1 = turn1 - 1; 
            } 
            else 
            {
                finalGuess[turn1] = correctDigits[0];
                pos1 = turn1; 
            }

            Version2 = false;
            Version3 = true; 
        } 
        else 
        {
            for (int i = 0; i < 4; i++) 
            {
                if (i == turn1) 
                {
                    guess2 += correctDigits[0];
                } 
                else 
                {
                    guess2 += 'x';
                }
            }
            turn1++;
            return guess2;
        }
    }

    if (Version3) 
    {
        string guess3;
        static int turn2 = 0;
        static int pos = 0;

        if (turn2 == 0) 
        {
            rr = 0;
        }

        if (rr == 1 || turn2 == 2 ) 
        {
            if (rr == 1) {
                finalGuess[pos - 1] = correctDigits[1];
                pos2 = pos - 1; 
            } 
            else 
            {
                while(pos == pos1)
                    {
                        pos++;
                    }
                finalGuess[pos] = correctDigits[1];
                pos2 = pos;
            }

            Version3 = false;
            Version4 = true; 
        } 
        else 
        {
            turn2++;
 
            if (pos == pos1) 
            {
                pos++;
            }

            for (int i = 0; i < 4; i++) 
            {
                if (i == pos) 
                {
                    guess3 += correctDigits[1];
                } 
                else 
                {
                    guess3 += 'x';
                }
            }
            pos++;
            return guess3;
        }
    }

    if (Version4) 
    {
        string guess4;
        static int turn3 = 0;
        static int pos = 0;

        if (turn3 == 0) 
        {
            rr = 0;
        }

        if (rr == 1 || turn3 == 1) 
        {
            if (rr == 1)
            {
                finalGuess[pos - 1] = correctDigits[2];
                pos3 = pos - 1; 
            } 
            else 
            {
                while (pos == pos1 || pos == pos2) 
                {
                    pos++;
                }
                finalGuess[pos] = correctDigits[2];
                pos3 = pos; 
            }

            Version4 = false;
            Version5 = true; 
        } 
        else 
        {
            turn3++;
        
            while (pos == pos1 || pos == pos2) 
            {
                pos++;
            }

            for (int i = 0; i < 4; i++)
                {
                if (i == pos) 
                {
                    guess4 += correctDigits[2];
                } 
                else
                {
                    guess4 += 'x';
                }
            }
            pos++;
            return guess4;
        }
    }

    if (Version5) 
    {
        
        for (int i = 0; i < 4; i++) 
        {
            if (finalGuess[i] == 'x') 
            {
                finalGuess[i] = correctDigits[3]; 
            }
        }
        cout << "Final answer: " << finalGuess << endl;

        Version5 = false; 
    }

    return finalGuess;
}

bool eval(string code,string guess,char &rr,char &rw){
    string check="    ";
    rr=0,rw=0;
    
    for(int i=0;i<code.length();i++){
        if(code[i]==guess[i]){
            rr++;
            check[i]='x';
            guess[i]='x';
        }
    }
    
    for(int j=0;j<code.length();j++){
        for(int i=0;i<code.length();i++){
            if((i!=j)&&(code[i]==guess[j])&&(check[i]==' ')){
                rw++;
                check[i]='x';
                break;
            }
        }
    }

    
    if(rr==4)return false;
    return true;
}

string set(){
    string code="0000";
    for(int i=0;i<code.length();i++){
        code[i]=rand()%10+'0';
    }
    return code;
}