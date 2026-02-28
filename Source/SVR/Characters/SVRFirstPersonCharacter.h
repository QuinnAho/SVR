// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SVRFirstPersonCharacter.generated.h"

class UCameraComponent;
class USVRInteractionComponent;

// Desktop first-person character used by SVR scenarios.
UCLASS(Blueprintable)
class SVR_API ASVRFirstPersonCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASVRFirstPersonCharacter();

	UFUNCTION(BlueprintPure, Category = "Camera")
	UCameraComponent* GetFirstPersonCamera() const { return FirstPersonCamera; }

	UFUNCTION(BlueprintPure, Category = "Interaction")
	USVRInteractionComponent* GetInteractionComponent() const { return InteractionComponent; }

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Socket on the mesh used for first-person camera attachment.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	FName CameraSocketName;

	// Dedicated first-person camera owned by this native class.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FirstPersonCamera;

	// Handles interactable focus and interaction calls for this pawn.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USVRInteractionComponent> InteractionComponent;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void HandleInteractPressed();
};
