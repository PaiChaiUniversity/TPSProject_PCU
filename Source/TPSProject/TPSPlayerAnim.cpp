// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayerAnim.h"

#include "TPSPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"

void UTPSPlayerAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// 소유 Pawn 을 가져오자.
	pawnOwner = Cast<ATPSPlayer>(TryGetPawnOwner());
}

void UTPSPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// 만약에  소유 폰이 존재한다면
	if (pawnOwner)
	{
		// 이동 속도 설정
		moveVelocity = pawnOwner->GetVelocity();		
		// 공중에 있는지 여부 설정
		isAir = pawnOwner->GetCharacterMovement()->IsFalling();
		// 수평 이동 속력 설정
		groundSpeed = moveVelocity.Size2D();

		
		// Pawn 이동 속도
		FVector velocity = moveVelocity;
		velocity.Z = 0;
		// 앞으로 이동하는지 (dirV > 0) , 뒤로 이동하는지 (dirV < 0)
		dirV = FVector::DotProduct(velocity, pawnOwner->GetActorForwardVector());
		// 왼쪽으로 이동하는지 (dirH < 0) , 오른쪽으로 이동하지 (dirH > 0)
		dirH = FVector::DotProduct(velocity, pawnOwner->GetActorRightVector());		
	}
}
