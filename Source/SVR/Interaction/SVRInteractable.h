// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SVRInteractable.generated.h"

UINTERFACE(BlueprintType)
class SVR_API USVRInteractable : public UInterface
{
	GENERATED_BODY()
};

class SVR_API ISVRInteractable
{
	GENERATED_BODY()

public:
	// Returns whether the interactable can currently be used by this interactor.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "SVR|Interaction")
	bool CanInteract(AActor* Interactor) const;

	// Returns prompt text for UI while this actor is focused.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "SVR|Interaction")
	FText GetInteractPromptText(AActor* Interactor) const;

	// Executes the interaction.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "SVR|Interaction")
	void Interact(AActor* Interactor);
};

