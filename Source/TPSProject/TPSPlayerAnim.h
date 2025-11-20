// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "TPSPlayerAnim.generated.h"

/**
 * 
 */
UCLASS()
class TPSPROJECT_API UTPSPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	// Animation 을 소유하고 Pawn
	class ATPSPlayer* pawnOwner;
	// 앞뒤 이동에 따른 값
	UPROPERTY(BlueprintReadOnly)
	float dirV;
	// 좌우 이동에 따른 값
	UPROPERTY(BlueprintReadOnly)
	float dirH;
	// 공중에 있는지 여부
	UPROPERTY(BlueprintReadOnly)
	bool isAir;
	// 이동 속도
	UPROPERTY(BlueprintReadOnly)
	FVector moveVelocity;
	// 수평 스피드
	UPROPERTY(BlueprintReadOnly)
	float groundSpeed;
};
