# MasterMindAI

A C++-based implementation of the classic Mastermind game where the player tries to guess a secret code. In my version, a 4-digit code is randomly generated, and with each guess, the program shows how many of the digits were the right number or both the right number and right placement. The AI is designed to solve the game in 16 or fewer tries. 

### How It Works:

1. **Secret Code Generation**: The AI randomly generates a secret code, which consists of 4 random numbers.
2. **Solving the code**: The AI keeps on guessing and uses the information gained to get an answer. I separated each step the AI has to take in order to move on into functions called Version1-5. As the AI finds more clues, it will have permission to move on to the next step and continue.
   
   - **Version1:** The AI starts with finding each correct digit. So it goes from 0000, 1111, 2222, etc... and keeps track of which digits were correct.
```C++
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
```
   - **Version2:** Then the AI starts off with the first correct digit in the first index and increments until it gets the correct placement. So, if the first correct digit was 1, it would first guess 1xxx. If it was wrong, it would guess x1xx and then xx1x. If none of these are correct, the AI will know it was the last index and remember it.
```C++
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
```
   - **Version3/4:** The AI will then repeat what Version2 did and find the correct placement for the next digits.
   - **Version5:** For the final digit, the AI will find the missing index and insert the correct digit into its place and reveal the final answer.
```C++
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
```
