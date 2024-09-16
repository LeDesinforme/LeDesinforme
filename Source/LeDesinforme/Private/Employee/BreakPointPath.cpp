#include "Employee/BreakPointPath.h"

ABreakPointPath::ABreakPointPath()
{
	PrimaryActorTick.bCanEverTick = false;
}

int ABreakPointPath::Num() const
{
	return m_breakPoints.Num();
}

const TArray<FVector>& ABreakPointPath::GetBreakPoints() const
{
	return m_breakPoints;
}
