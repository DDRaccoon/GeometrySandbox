// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"
#include "BaseGeometryActor.h"

DEFINE_LOG_CATEGORY_STATIC(LogGeometryHub, All,All);

// Sets default values
AGeometryHubActor::AGeometryHubActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AGeometryHubActor::DoActorSpawn1()
{
	UWorld* World = GetWorld();		//返回一个指向全局游戏世界对象的指针
	if(World)
	{
		for (int32 i = 0; i < 10 ; ++i)
		{
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator,FVector(0.0f,300.0f * i,300.0f));
			ABaseGeometryActor* Geometry = World->SpawnActor<ABaseGeometryActor>( GeometryClass,GeometryTransform);
			if(Geometry)
			{
				FGeometryData Data;
				Data.MoveType=FMath::RandBool()?EMovementType::Static:EMovementType::Sin;
				Geometry->SetGeometryData(Data);
			}
		}
	}
}

void AGeometryHubActor::DoActorSpawn2()
{
	UWorld* World = GetWorld();		//返回一个指向全局游戏世界对象的指针
	if(World)
	{
		for (int32 i = 0; i < 10 ; ++i)
		{
			const FTransform GeometryTransform = FTransform(FRotator::ZeroRotator,FVector(0.0f,300.0f * i,700.0f));
			ABaseGeometryActor* Geometry = World->SpawnActorDeferred<ABaseGeometryActor>(GeometryClass,GeometryTransform);
			if(Geometry)
			{
				FGeometryData Data;
				Data.Color=FLinearColor::MakeRandomColor();
				Geometry->SetGeometryData(Data);
				Geometry->FinishSpawning(GeometryTransform);
			}
		}
	}
}

void AGeometryHubActor::DoActorSpawn3()
{
		UWorld* World = GetWorld();		//返回一个指向全局游戏世界对象的指针
		if(World)
		{
			for(const FGeometryPayload Payload:GeometryPayloads)
			{
				ABaseGeometryActor* Geometry = World->SpawnActorDeferred<ABaseGeometryActor>(Payload.GeometryClass,Payload.InitialTransform);
				if(Geometry)
				{
					Geometry->SetGeometryData(Payload.Data);
					//委托
					Geometry->OnColorChanged.AddDynamic(this,&AGeometryHubActor::OnColorChanged);
					Geometry->OnTimerFinished.AddUObject(this,&AGeometryHubActor::OnTimerFinished);
					
					Geometry->FinishSpawning(Payload.InitialTransform);
				}
			}
		}
}

void AGeometryHubActor::OnColorChanged(const FLinearColor& Color, const FString& Name)
{
	UE_LOG(LogGeometryHub,Warning,TEXT("Actor name:%s"),*Name,*Color.ToString());
}

void AGeometryHubActor::OnTimerFinished(AActor* Actor)
{
	if(!Actor) return;
	UE_LOG(LogGeometryHub,Error,TEXT("Timer finished:%s"),*Actor->GetName());

	ABaseGeometryActor* Geomtry = Cast<ABaseGeometryActor>(Actor);
	if(!Geomtry) return;;

	UE_LOG(LogGeometryHub,Display,TEXT("Cast is success,amplitude %f"),Geomtry->GetGeometryData().Amplitude);

	Geomtry->Destroy();
	//Geomtry->SetLifeSpan(2.0f);
}

// Called when the game starts or when spawned
void AGeometryHubActor::BeginPlay()
{
	Super::BeginPlay();

	//DoActorSpawn1();
	//DoActorSpawn2();
	DoActorSpawn3();
}
	
// Called every frame
void AGeometryHubActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

