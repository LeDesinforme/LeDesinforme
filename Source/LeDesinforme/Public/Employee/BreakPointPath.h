#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BreakPointPath.generated.h"


UCLASS()
class LEDESINFORME_API ABreakPointPath : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (MakeEditWidget = "true", AllowPrivateAccess = "true"))
	TArray<FVector> m_breakPoints;
	
public:	
	ABreakPointPath();

public:
	// Returns the number of break points
	int Num() const;
	// Returns the breakPoints
	const TArray<FVector>& GetBreakPoints() const; 
};
