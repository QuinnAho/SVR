// Fill out your copyright notice in the Description page of Project Settings.

#include "SVRInteractionComponent.h"

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "SVRInteractable.h"

USVRInteractionComponent::USVRInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	TraceDistance = 300.0f;
	TraceInterval = 0.05f;
	TraceChannel = ECC_Visibility;
	bDrawDebugTrace = false;
	TimeSinceLastTrace = 0.0f;
}

void USVRInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	RefreshFocus();
}

void USVRInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimeSinceLastTrace += DeltaTime;
	if (TimeSinceLastTrace < TraceInterval)
	{
		return;
	}

	TimeSinceLastTrace = 0.0f;
	RefreshFocus();
}

bool USVRInteractionComponent::TryInteract()
{
	if (!CanActorInteract(FocusedActor))
	{
		return false;
	}

	ISVRInteractable::Execute_Interact(FocusedActor, GetOwner());
	return true;
}

void USVRInteractionComponent::RefreshFocus()
{
	AActor* OwnerActor = GetOwner();
	if (!OwnerActor || !GetWorld())
	{
		SetFocusedActor(nullptr, FText::GetEmpty());
		return;
	}

	FVector TraceStart = FVector::ZeroVector;
	FRotator TraceRotation = FRotator::ZeroRotator;

	if (const APawn* OwnerPawn = Cast<APawn>(OwnerActor))
	{
		if (const AController* OwnerController = OwnerPawn->GetController())
		{
			OwnerController->GetPlayerViewPoint(TraceStart, TraceRotation);
		}
		else
		{
			OwnerActor->GetActorEyesViewPoint(TraceStart, TraceRotation);
		}
	}
	else
	{
		OwnerActor->GetActorEyesViewPoint(TraceStart, TraceRotation);
	}

	const FVector TraceEnd = TraceStart + (TraceRotation.Vector() * TraceDistance);
	FCollisionQueryParams QueryParams(SCENE_QUERY_STAT(SVRInteractionTrace), false, OwnerActor);

	FHitResult HitResult;
	const bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, TraceChannel, QueryParams);

	if (bDrawDebugTrace)
	{
		const FColor LineColor = bHit ? FColor::Green : FColor::Red;
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, LineColor, false, TraceInterval);
	}

	if (!bHit || !CanActorInteract(HitResult.GetActor()))
	{
		SetFocusedActor(nullptr, FText::GetEmpty());
		return;
	}

	AActor* HitActor = HitResult.GetActor();
	FText PromptText = ISVRInteractable::Execute_GetInteractPromptText(HitActor, OwnerActor);
	if (PromptText.IsEmpty())
	{
		PromptText = FText::FromString(TEXT("Interact (E)"));
	}

	SetFocusedActor(HitActor, PromptText);
}

void USVRInteractionComponent::SetFocusedActor(AActor* NewActor, const FText& NewPromptText)
{
	if (FocusedActor == NewActor && FocusedPromptText.EqualTo(NewPromptText))
	{
		return;
	}

	AActor* PreviousActor = FocusedActor;
	FocusedActor = NewActor;
	FocusedPromptText = NewPromptText;
	OnFocusChanged.Broadcast(PreviousActor, FocusedActor, FocusedPromptText);
}

bool USVRInteractionComponent::CanActorInteract(AActor* Candidate) const
{
	return IsValid(Candidate) && Candidate->GetClass()->ImplementsInterface(USVRInteractable::StaticClass());
}
