// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.generated.h"

UCLASS()
class GEOMETRYSANDBOX_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGeometryActor();

	//组件
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//变换
	UPROPERTY(EditAnywhere,Category="Movement")
	float Amplitude = 50.0f;	

	UPROPERTY(EditAnywhere,Category="Movement")
	float Frequency = 2.0f;
	
	//变量
	UPROPERTY(EditAnywhere,Category="Weapon")
	int32 WeaponsNum = 4;

	UPROPERTY(EditDefaultsOnly,Category="Stat")
	int32 KillsNum = 7;

	UPROPERTY(EditInstanceOnly,Category="Health")
	float Health = 34.1235;

	UPROPERTY(EditAnywhere,Category="Health")
	bool IsDead = false;

	UPROPERTY(VisibleAnywhere,Category="Weapon")
	bool HasWeapon = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	//位置	
	FVector InitialLocation;
	//字符串
	void printStringTypes();
	//日志
	void printTypes();
	//变换
	void printTransform();
};
