// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ReadWriteTxtHelper.generated.h"

UENUM(BlueprintType)
enum class ENewsType : uint8
{
	TrueNews UMETA(DisplayName = "True"),
	FakeNews UMETA(DisplayName = "Fake"),
	AINews UMETA(DisplayName = "AI"),
	OINews UMETA(DisplayName = "OI")
};

USTRUCT(BlueprintType)
struct FNews
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "News")
	FString subject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "News")
	FString title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "News")
	FString contents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "News")
	bool bIsTrue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "News")
	ENewsType newsType;

	FNews()
		: subject(TEXT(""))
		, title(TEXT(""))
		, contents(TEXT(""))
		, bIsTrue(false)
	{
	}
};
/**
 * 
 */
UCLASS()
class LEDESINFORME_API UReadWriteTxtHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Tools")
	static FString ReadTxt(FString FileName);

	UFUNCTION(BlueprintCallable, Category = "Tools")
	static bool WriteTxt(FString Text, FString FileName);

	UFUNCTION(BlueprintCallable, Category = "Tools")
	static FString ReadTrueSentences(FString path);

	UFUNCTION(BlueprintCallable, Category = "Tools")
	static FString ReadFakeSentences(FString path);

	UFUNCTION(BlueprintCallable, Category = "Tools")
	static FString MakeOINews(FString path);

	UFUNCTION(BlueprintCallable, Category = "Tools")
	static FNews RandomRead(FString subject = "", ENewsType type = ENewsType::TrueNews);

	UFUNCTION(BlueprintCallable, Category = "Tools")
	static FString ReadTitle(FString FileName);

	UFUNCTION(BlueprintCallable, Category = "Tools")
	static TArray<FString> InputTitleList();

	UFUNCTION(BlueprintCallable, Category = "Tools")
	static void CleanTitleList();

};