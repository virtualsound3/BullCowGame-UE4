
#include "BullCowCartridge.h"
#include "HiddenWordList.h"


void UBullCowCartridge::BeginPlay() 
{
    Super::BeginPlay();  
   
    SetupGame();

}


void UBullCowCartridge::OnInput(const FString& Input)  
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }    
    else    
    {
        ProcessGuess(Input);
    }
}
void UBullCowCartridge::SetupGame() 
{
   PrintLine(TEXT("Welcome to our farm!!! "));
    HiddenWord = GetValidWords(Words)[FMath::RandRange( 0, GetValidWords(Words).Num()-1  ) ];
    Lives = HiddenWord.Len(); 
    bGameOver = false;

   PrintLine(TEXT("Guess the %i letter word and open the secrete gate  "), HiddenWord.Len());
   PrintLine(TEXT("DEBUG:The HiddenWord is: %s "), *HiddenWord);
   PrintLine(TEXT("You have %i lives. Try your hand!!!"), Lives);
   PrintLine(TEXT("Type in your guess!!! \n and press Enter to check your answer... "));  
}
void UBullCowCartridge::EndGame()
{
    bGameOver = true;
   
    PrintLine(TEXT("\nPress enter to play again."));
}

//Precess Guess should compare Guess and HiddenWord 
// 1 check if correct anwer, say something and bGameOver = true 
// 2 guess is as long as HiddenWord ?
// 3 guess is Isogram ?                                (throw checking to function -- will be use for words filtraction )                                        
// if any exist remove live ans show bull and cow      (throw checking bull and cow to function)                                             
void UBullCowCartridge::ProcessGuess(FString Guess)
{
     if (Guess == HiddenWord)
        {
            PrintLine(TEXT("U have won!"));
             EndGame();
             return;
        }
       
    if (Guess.Len() != HiddenWord.Len())
        {
          PrintLine(TEXT("Word must have %i letters"), HiddenWord.Len() );
          PrintLine(TEXT("Sorry, try guessing again,\nyou have %i lives remaining"), Lives );
          return;
         }

   
    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letter, guess again"));
        return;
    }
 

        PrintLine(TEXT("You have lost live"));
        --Lives;
 
         if (Lives <= 0 )
            {
                 ClearScreen(); 
                 PrintLine(TEXT("You have no lives left"));
                 PrintLine(TEXT("The hiddenWord is: %s "), *HiddenWord);
                 //Prompt to Play again, and press enter toplay again
                 EndGame();
                 return;  
            }    
            int32 Bull, Cows;
            GetBullCows(Guess, Bull, Cows);
            PrintLine(TEXT("U have %i Bull and %i Cows"), Bull, Cows);
            PrintLine(TEXT("Guess again, you have %i lives left"),  Lives);       
                    
}



bool UBullCowCartridge::IsIsogram(const FString& Word) const   
{
    
    //for example
    /*
                         c a k e s                     x dont need to check 
                       c x * * * *                      * need to check
                       a x x * * * 
                       k x x x * *
                       e x x x x *
                       s x x x x x
    */
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
            
        }
        
    }
    
    return true;
    
}


TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const    // should be referenc here to avoid copping 
 {
// creating varaible of to contain ValidWords 
    TArray<FString> ValidWords;      

     // chose validwords from all words (4-8 charakters),and add this to new word list and isogram
    for (int32 Index = 0; Index < WordList.Num(); Index++)
    {
        if (WordList[Index].Len() >=4 && WordList[Index].Len() <=8 )
        {
            if(IsIsogram(WordList[Index]))
            {
                ValidWords.Emplace(WordList[Index]);// emplae istead of add becouse emplace dont create additonal temporary varaible // adding validwords to array
            }
        }   
    }
    return ValidWords;
 }


//take input and dont change, and give bull and cow , dont change private variable
 void UBullCowCartridge::GetBullCows(const FString& Guess, int32& BullCount, int32& CowCount) const
 {
      BullCount = 0; 
      CowCount = 0; 
     // for every the index od  Guess is the same of Index Hidden , BullCount++
     // if not a bull was it a cow ? if yes  CowCount++

     for (int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
     {
         if (Guess[GuessIndex]  == HiddenWord[GuessIndex])
         {
             BullCount++;
         }
         else
         {
             for ( int32 HiddenIndex  = 0; HiddenIndex  < HiddenWord.Len(); HiddenIndex++)//aakfjaksdasdfasdfasdfa działaj!FJASJGVNA
             {
                 if (Guess[GuessIndex] == HiddenWord[HiddenIndex])
                 {
                     CowCount++;
                 }   
             }   
         }
     }
     

 }



