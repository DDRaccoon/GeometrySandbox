// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGeometryActor.h"
#include "GameFramework/Actor.h"
#include "GeometryHubActor.generated.h"

class ABaseGeometryActor;

//结构体
USTRUCT(BlueprintType)
struct  FGeometryPayload
{
	GENERATED_USTRUCT_BODY()
	//主要生成的类
	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> GeometryClass;	
	//GeometryData
	UPROPERTY(EditAnywhere)
	FGeometryData Data;								
	//负责变换
	UPROPERTY(EditAnywhere)
	FTransform InitialTransform;					
};

UCLASS()
class GEOMETRYSANDBOX_API AGeometryHubActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeometryHubActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> GeometryClass;	

	UPROPERTY(EditAnywhere)
	TArray<FGeometryPayload> GeometryPayloads;

private:
	//生成
	void DoActorSpawn1();
	void DoActorSpawn2();
	void DoActorSpawn3();

	//委托
	UFUNCTION()
	void OnColorChanged(const FLinearColor& Color,const FString& Name);
	
	void OnTimerFinished(AActor* Actor);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
