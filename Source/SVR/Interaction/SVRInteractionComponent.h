// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SVRInteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FSVRFocusChangedSignature, AActor*, PreviousActor, AActor*, CurrentActor, FText, PromptText);

UCLASS(ClassGroup = (SVR), BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class SVR_API USVRInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USVRInteractionComponent();

	// Attempts to interact with the currently focused actor.
	UFUNCTION(BlueprintCallable, Category = "SVR|Interaction")
	bool TryInteract();

	UFUNCTION(BlueprintPure, Category = "SVR|Interaction")
	AActor* GetFocusedActor() const { return FocusedActor; }

	UFUNCTION(BlueprintPure, Category = "SVR|Interaction")
	FText GetFocusedPromptText() const { return FocusedPromptText; }

	// Broadcast when focus changes. Useful for prompt widgets.
	UPROPERTY(BlueprintAssignable, Category = "SVR|Interaction")
	FSVRFocusChangedSignature OnFocusChanged;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Max interaction trace distance in cm.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SVR|Interaction", meta = (ClampMin = "50.0"))
	float TraceDistance;

	// Seconds between traces to keep interaction checks cheap.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SVR|Interaction", meta = (ClampMin = "0.01"))
	float TraceInterval;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SVR|Interaction")
	TEnumAsByte<ECollisionChannel> TraceChannel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SVR|Interaction")
	bool bDrawDebugTrace;

private:
	void RefreshFocus();
	void SetFocusedActor(AActor* NewActor, const FText& NewPromptText);
	bool CanActorInteract(AActor* Candidate) const;

	UPROPERTY(Transient)
	TObjectPtr<AActor> FocusedActor;

	UPROPERTY(Transient)
	FText FocusedPromptText;

	float TimeSinceLastTrace;
};

