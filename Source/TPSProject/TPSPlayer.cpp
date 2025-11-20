// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATPSPlayer::ATPSPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// SpringArm Component 생성
	compArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("ARM"));
	// RootComponent 에 자식으로 하자.	
	compArm->SetupAttachment(RootComponent);
	// 위치를 오른쪽 위로 배치
	compArm->SetRelativeLocation(FVector(0, 70, 110));
	// 카메라 달리는 위치를 160 으로 하자.
	compArm->TargetArmLength = 160;

	// 카메라 Component 생성
	compCam = CreateDefaultSubobject<UCameraComponent>(TEXT("CAM"));
	// compArm 의 자식으로 하자.
	compCam->SetupAttachment(compArm);

	// 나의 움직이는 속력을 500 으로 하자.	
	GetCharacterMovement()->MaxWalkSpeed = 500;
}

// Called when the game starts or when spawned
void ATPSPlayer::BeginPlay()
{
	Super::BeginPlay();

	// IMC 설정
	//APlayerController* pc = Cast<APlayerController>(Controller);
	APlayerController* pc = GetWorld()->GetFirstPlayerController();
	if (pc)
	{
		UEnhancedInputLocalPlayerSubsystem* subSystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer());
		if (subSystem)
		{
			subSystem->AddMappingContext(imcTPSInput, 0);
		}
	}	
}

// Called every frame
void ATPSPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATPSPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Input 설정
	UEnhancedInputComponent* playerInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (playerInput)
	{
		// WASD 키 눌렀을 호출되는 함수 등록
		playerInput->BindAction(iaMove, ETriggerEvent::Triggered, this, &ATPSPlayer::Move);
		// 마우스 상하좌우 움직일 때 호출되는 함수 등록
		playerInput->BindAction(iaLookUp, ETriggerEvent::Triggered, this, &ATPSPlayer::LookUp);
		playerInput->BindAction(iaTurn, ETriggerEvent::Triggered, this, &ATPSPlayer::Turn);
		// 스페이스 바 눌렀을 때 호출되는 함수 등록
		playerInput->BindAction(iaJump, ETriggerEvent::Started, this, &ATPSPlayer::JumpAction);
		// 마우스 왼쪽 버튼 눌렀을 때 호출되는 함수 등록
		playerInput->BindAction(iaFire, ETriggerEvent::Started, this, &ATPSPlayer::Fire);
	}
}

void ATPSPlayer::Move(const FInputActionValue& value)
{
	// 입력 값을 2d 벡터로 얻어오자.
	FVector2D inputValue = value.Get<FVector2D>();
	//UE_LOG(LogTemp, Warning, TEXT("%f : %f"), inputValue.X, inputValue.Y);

	// 이동할 방향 만들자. (월드 방향)
	FVector dir = FVector(inputValue.X, inputValue.Y, 0);
	// 나를 기준으로 하는 방향으로 전환
	dir = FTransform(GetControlRotation()).TransformVector(dir);
	dir.Z = 0;

	// 크기를 1로 만들자.
	dir.Normalize();

	// dir 방향으로 움직이자.
	AddMovementInput(dir);
}



void ATPSPlayer::LookUp(const FInputActionValue& value)
{
	float inputValue = -value.Get<float>();
	AddControllerPitchInput(inputValue);
}

void ATPSPlayer::Turn(const FInputActionValue& value)
{
	float inputValue = value.Get<float>();
	AddControllerYawInput(inputValue);
}

void ATPSPlayer::JumpAction()
{
	Jump();
}

void ATPSPlayer::Fire()
{
	// LineTrace 로 부딪힌 곳 찾아내자.
	// 시작 지점
	FVector startPos = compCam->GetComponentLocation();
	// 끝 지점
	FVector endPos = startPos + compCam->GetForwardVector() * 100000;
	// 그 외 옵션
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	// 부딪힌 결과를 담는 변수
	FHitResult hitInfo;
	// 위 정보를 이용해서 LineTrace 발사!
	bool bHit = GetWorld()->LineTraceSingleByChannel(hitInfo, startPos, endPos, ECC_Camera, params);
	// 만약에 어딘가 부딪혔다면
	if (bHit)
	{
		// 맞은 지점의 Normal 방향으로 효과가 퍼지게 각도를 구하자.
		FRotator rot = UKismetMathLibrary::MakeRotFromX(hitInfo.Normal);
		// 부딪힌 위치에 파티클(나이아가라) 효과 표현
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), hitEffect, hitInfo.Location, rot);
	}
}










