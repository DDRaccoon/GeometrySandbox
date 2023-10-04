// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.generated.h"

//委托
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnColorChanged,const FLinearColor&,Color,const FString&,Name);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerFinished,AActor*);

//枚举
UENUM(BlueprintType)
enum class EMovementType:uint8
{
	Sin,
	Static
};

//结构体
USTRUCT(BlueprintType)
struct  FGeometryData
{
	GENERATED_USTRUCT_BODY()
	//枚举
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movement")
	EMovementType MoveType = EMovementType::Static;
	
	//变换
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movement")
	float Amplitude = 50.0f;	

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Movement")
	float Frequency = 2.0f;

	//材质修改
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Design")
	FLinearColor Color = FLinearColor::Black;

	//计时器
	UPROPERTY(EditAnywhere,Category="Design")
	float TimerRate = 3.0f;
};


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

	void SetGeometryData(const FGeometryData& Data){GeometryData = Data;}

	//函数宏
	UFUNCTION(BlueprintCallable)
	FGeometryData GetGeometryData() const {return GeometryData;}

	//委托
	UPROPERTY(BlueprintAssignable)
	FOnColorChanged OnColorChanged;
	
	FOnTimerFinished OnTimerFinished;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//重写的什么
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	//结构体
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Geometry Data")
	FGeometryData GeometryData;
	
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
	//计时器
	FTimerHandle TimerHandle;		
	const int32 MaxTimerCount = 5;		//最大运行次数
	int32 TimerCount = 0;				//计数器
	//位置	
	FVector InitialLocation;
	//字符串
	void printStringTypes();
	//日志
	void printTypes();
	//变换
	void printTransform();
	//移动
	void HandleMovement();
	//材质
	void SetColor(const FLinearColor& Color);
	//计时器函数
	void OnTimerFired();
};
