// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CDA_CharacterBase.generated.h"

/**
 * 
 */

//USTRUCT(BlueprintType)
//struct TransForm
//{
//	GENERATED_BODY()
//		
//public:
//	UPROPERTY(EditAnywhere, BlueprintReadOnly)
//		FVector Location;
//	UPROPERTY(EditAnywhere, BlueprintReadOnly)
//		FRotator Rotation;
//	UPROPERTY(EditAnywhere, BlueprintReadOnly)
//		FVector Scale;
//};

UCLASS()
class PROJECTPF_API UCDA_CharacterBase : public UDataAsset
{
	GENERATED_BODY()

public:
	//CameraBoom
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Transform")
		FTransform CameraBoom;
	//FollowCamera
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Transform")
		FTransform FollowCamera;
	//CameraBoom
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Transform")
		FTransform Mesh;

	//TSubclassOf<USkeletalMesh> �� �Ϸ��ߴµ� ���ϴµ��� ������ �ʴ´�. ������ ����?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkeletalMesh")
		class USkeletalMesh* SkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimInstance")
		TSubclassOf<UAnimInstance> AnimInstanceClass;


};
