// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseGeometry, All,All);

// Sets default values
ABaseGeometryActor::ABaseGeometryActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh=CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh");
	SetRootComponent(BaseMesh);
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation=GetActorLocation();
	
	//printStringTypes();
	//printTypes();
	printTransform();
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentLocation =GetActorLocation();
	float time=GetWorld()->GetTimeSeconds();
	CurrentLocation.Z=InitialLocation.Z+Amplitude*FMath::Sin(Frequency*time);
	
	SetActorLocation(CurrentLocation);
}

void ABaseGeometryActor::printStringTypes()
{
	//字符串
	FString Name= "Chen SiCheng";
	UE_LOG(LogBaseGeometry,Display,TEXT("Name:%s"),*Name);
	
	FString WeaponsNumStr = "Weapons num = " + FString::FromInt(WeaponsNum);
	FString HealthStr = "Health = " + FString::SanitizeFloat(Health);
	FString IsDeadStr = "Is dead = " + FString(IsDead?"true":"fa");

	FString Stat = FString::Printf(TEXT("\n All Stat \n %s %s %s "),*WeaponsNumStr,*HealthStr,*IsDeadStr);
	UE_LOG(LogBaseGeometry,Warning,TEXT("%s"),*Stat);

	GEngine->AddOnScreenDebugMessage(-1,3.0f,FColor::Red,Name);
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Green,Stat,true,FVector2D(1.5F,1.5F));
	
	//日志
	UE_LOG(LogBaseGeometry,Error,TEXT("你谁啊"));
	UE_LOG(LogBaseGeometry,Display,TEXT("一条信息"));
	UE_LOG(LogBaseGeometry,Error,TEXT("一条信息"));
	UE_LOG(LogBaseGeometry,Warning,TEXT("一条信息"));
}

void ABaseGeometryActor::printTypes()
{
	UE_LOG(LogBaseGeometry,Warning,TEXT("Actor name %s"),*GetName());
	UE_LOG(LogBaseGeometry, Warning,TEXT("Weapons Num: num: &d,kills num:%i"),WeaponsNum,KillsNum);
	UE_LOG(LogBaseGeometry, Warning, TEXT("Health: %f"), Health);
	//UE_LOG(LogTemp, Display, TEXT("Health: %.2f"), Health);
	UE_LOG(LogBaseGeometry, Warning, TEXT("IsDead:%d"), IsDead);
	UE_LOG(LogBaseGeometry, Warning, TEXT("HasWeapon:%d"), static_cast<int>(HasWeapon));
}

void ABaseGeometryActor::printTransform()
{
	//变换
	FTransform Transform = GetActorTransform();
	
	FVector Location = Transform.GetLocation();
	FRotator Rotator = Transform.Rotator();
	FVector Scale = Transform.GetScale3D();

	UE_LOG(LogBaseGeometry,Warning,TEXT("Actor Name:%s"),*GetName());
	UE_LOG(LogBaseGeometry,Warning,TEXT("Transform:%s"),*Transform.ToString());
	UE_LOG(LogBaseGeometry,Warning,TEXT("Location:%s"),*Location.ToString());
	UE_LOG(LogBaseGeometry,Warning,TEXT("Rotator:%s"),*Rotator.ToString());
	UE_LOG(LogBaseGeometry,Warning,TEXT("Scale:%s"),*Scale.ToString());
	
	UE_LOG(LogBaseGeometry,Error,TEXT("Transform:%s"),*Transform.ToHumanReadableString());
}
