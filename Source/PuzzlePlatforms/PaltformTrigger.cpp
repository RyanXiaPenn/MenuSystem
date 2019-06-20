// Fill out your copyright notice in the Description page of Project Settings.


#include "PaltformTrigger.h"

#include "Components/BoxComponent.h"

#include"MovingPlatform.h"
// Sets default values
APaltformTrigger::APaltformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));

	if (!ensure(TriggerVolume != nullptr)) return;
	RootComponent = TriggerVolume;

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APaltformTrigger::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APaltformTrigger::OnOverlapEnd);
}

// Called when the game starts or when spawned
void APaltformTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APaltformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APaltformTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Activated"));
	for (AMovingPlatform* Platform : PlatformsToTrigger)
	{
		Platform->AddActiveTrigger();
	}
}

void APaltformTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Deactivated"));
	for (AMovingPlatform* Platform : PlatformsToTrigger)
	{
		Platform->RemoveActiveTrigger();
	}
}