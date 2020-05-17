
#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge 
{
	GENERATED_BODY()//SetUp

	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override; 
	void SetupGame();
	void EndGame();
	void ProcessGuess(FString Guess);
	bool IsIsogram(const FString& Word) const;
	TArray<FString> GetValidWords(const TArray<FString>& WordList) const;
	void GetBullCows(const FString& Guess, int32& BullCount, int32& CowCount) const;


	// Any function can't change this variable
	private:
	FString HiddenWord;
	int32 Lives;
	bool bGameOver;
	
};
