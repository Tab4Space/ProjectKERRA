// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Projectile/KerraProjectileBase.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "KerraFunctionLibrary.h"
#include "KerraGameplayTags.h"
#include "AbilitySystemBlueprintLibrary.h"


AKerraProjectileBase::AKerraProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileCollision = CreateDefaultSubobject<UBoxComponent>("ProjectileCollision");
	SetRootComponent(ProjectileCollision);
	ProjectileCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	ProjectileCollision->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	ProjectileCollision->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	ProjectileCollision->OnComponentHit.AddUniqueDynamic(this, &AKerraProjectileBase::OnProjectileHit);
	ProjectileCollision->OnComponentBeginOverlap.AddUniqueDynamic(this, &AKerraProjectileBase::OnProjectileBeginOverlap);

	ProjectileNiagara = CreateDefaultSubobject<UNiagaraComponent>("ProjectileNiagara");
	ProjectileNiagara->SetupAttachment(ProjectileCollision);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 700.f;
	ProjectileMovement->MaxSpeed = 900.f;
	ProjectileMovement->Velocity = FVector(1.f, 0.f, 0.f);
	ProjectileMovement->ProjectileGravityScale = 0.f;

	InitialLifeSpan = 4.f;
}

void AKerraProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	if(ProjectileDamagePolicy == EProjectileDamagePolicy::OnBeginOverlap)
	{
		ProjectileCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	}
}

void AKerraProjectileBase::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	BP_OnSpawnProjectileHitFX(Hit.ImpactPoint);
	
	APawn* HitPawn = Cast<APawn>(OtherActor);
	if(!HitPawn || !UKerraFunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPawn))
	{
		Destroy();
		return;
	}

	bool bIsValidBlock = false;
	const bool bIsPlayerBlocking = UKerraFunctionLibrary::NativeDoesActorHaveTag(HitPawn, KerraGameplayTags::Player_Status_Blocking);

	if(bIsPlayerBlocking)
	{
		bIsValidBlock = UKerraFunctionLibrary::IsValidBlock(this, HitPawn);
	}

	FGameplayEventData Data;
	Data.Instigator = this;
	Data.Target = HitPawn;
	if(bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitPawn, KerraGameplayTags::Player_Event_SuccessBlock, Data);
	}
	else
	{
		HandleApplyProjectileDamage(HitPawn, Data);
	}

	Destroy();
}

void AKerraProjectileBase::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Begin Overlap %s"), *OtherActor->GetActorNameOrLabel());
}

void AKerraProjectileBase::HandleApplyProjectileDamage(APawn* InHitPawn, const FGameplayEventData& InPayload)
{
	checkf(ProjectileDamageEffectSpecHandle.IsValid(), TEXT("Assign valid spec handle %s"), *GetActorNameOrLabel());

	const bool bWasApplied = UKerraFunctionLibrary::ApplyGameplayEffectSpecHandleToTargetActor(GetInstigator(), InHitPawn, ProjectileDamageEffectSpecHandle);
	if(bWasApplied)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(InHitPawn, KerraGameplayTags::Shared_Event_HitReact, InPayload);
	}
}
