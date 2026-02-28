// Fill out your copyright notice in the Description page of Project Settings.

#include "SVRFirstPersonCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SVRInteractionComponent.h"

ASVRFirstPersonCharacter::ASVRFirstPersonCharacter()
{
	CameraSocketName = TEXT("head");

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(GetMesh(), CameraSocketName);
	FirstPersonCamera->bUsePawnControlRotation = true;

	InteractionComponent = CreateDefaultSubobject<USVRInteractionComponent>(TEXT("InteractionComponent"));

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bOrientRotationToMovement = false;
		GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	}
}

void ASVRFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (!PlayerInputComponent)
	{
		return;
	}

	PlayerInputComponent->BindAxis(TEXT("MoveForward/Backwards"), this, &ASVRFirstPersonCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight/Left"), this, &ASVRFirstPersonCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookLeft/Right"), this, &ASVRFirstPersonCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp/Down"), this, &ASVRFirstPersonCharacter::LookUp);
	PlayerInputComponent->BindAction(TEXT("InteractAction"), IE_Pressed, this, &ASVRFirstPersonCharacter::HandleInteractPressed);
}

void ASVRFirstPersonCharacter::MoveForward(float Value)
{
	if (!Controller || FMath::IsNearlyZero(Value))
	{
		return;
	}

	const FRotator ControlRotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.0f, ControlRotation.Yaw, 0.0f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void ASVRFirstPersonCharacter::MoveRight(float Value)
{
	if (!Controller || FMath::IsNearlyZero(Value))
	{
		return;
	}

	const FRotator ControlRotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.0f, ControlRotation.Yaw, 0.0f);
	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void ASVRFirstPersonCharacter::Turn(float Value)
{
	if (FMath::IsNearlyZero(Value))
	{
		return;
	}

	AddControllerYawInput(Value);
}

void ASVRFirstPersonCharacter::LookUp(float Value)
{
	if (FMath::IsNearlyZero(Value))
	{
		return;
	}

	AddControllerPitchInput(Value);
}

void ASVRFirstPersonCharacter::HandleInteractPressed()
{
	if (!InteractionComponent)
	{
		return;
	}

	InteractionComponent->TryInteract();
}
