// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Item/Weapon/KerraWeaponBase.h"

#include "Components/BoxComponent.h"


AKerraWeaponBase::AKerraWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>("WeaponCollisionBox");
	WeaponCollisionBox->SetupAttachment(GetRootComponent());
	WeaponCollisionBox->SetBoxExtent(FVector(20.f));
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &AKerraWeaponBase::OnCollisionBoxBeginOverlap);
	WeaponCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &AKerraWeaponBase::OnCollisionBoxEndOverlap);
}

void AKerraWeaponBase::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* WeaponOwingPawn = GetInstigator<APawn>();
	checkf(WeaponOwingPawn, TEXT("Forgot to assign  instigator of weapon: %s"), *GetName())

	if(APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if(WeaponOwingPawn != HitPawn)
		{
			OnWeaponHitTarget.ExecuteIfBound(OtherActor);
		}
	}
}
void AKerraWeaponBase::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APawn* WeaponOwingPawn = GetInstigator<APawn>();
	checkf(WeaponOwingPawn, TEXT("Forgot to assign  instigator of weapon: %s"), *GetName())

	if(APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if(WeaponOwingPawn != HitPawn)
		{
			OnWeaponPulledFromTarget.ExecuteIfBound(OtherActor);
		}
	}
}
