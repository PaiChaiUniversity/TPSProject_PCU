// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPSPlayer.generated.h"

UCLASS()
class TPSPROJECT_API ATPSPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATPSPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// 카메라 Boom (SpringArm)
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* compArm;

	// 카메라 Component
	UPROPERTY(EditAnywhere)
	class UCameraComponent* compCam;


	// IMC 담을 변수
	UPROPERTY(EditAnywhere)
	class UInputMappingContext* imcTPSInput;
	// W A S D Input Action
	UPROPERTY(EditAnywhere)
	class UInputAction* iaMove;
	// 마우스 상하좌우 Input Action
	UPROPERTY(EditAnywhere)
	class UInputAction* iaLookUp;
	UPROPERTY(EditAnywhere)
	class UInputAction* iaTurn;
	// 점프 Input Action
	UPROPERTY(EditAnywhere)
	class UInputAction* iaJump;
	// Fire Input Action
	UPROPERTY(EditAnywhere)
	class UInputAction* iaFire;	

	// W A S D 입력 처리 함수
	void Move(const struct FInputActionValue& value);
	// 마우스 상하좌우 움직임 처리 함수
	void LookUp(const struct FInputActionValue& value);
	void Turn(const struct FInputActionValue& value);
	// 점프 처리 함수
	void JumpAction();
	// 공격 처리 함수
	UFUNCTION(BlueprintCallable)
	void Fire();
	

	// 총 맞은 곳에 Effect
	UPROPERTY(EditAnywhere)
	class UNiagaraSystem* hitEffect;	
};
