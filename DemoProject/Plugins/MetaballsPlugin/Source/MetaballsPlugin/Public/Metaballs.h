
// FileName: Metaballs.h
// 
// Created by: Andrey Harchenko
// Project name: Metaballs FX Plugin
// Unreal Engine version: 4.10
// Created on: 2016/03/17
//
// -------------------------------------------------
// For parts referencing UE4 code, the following copyright applies:
// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
//
// Feel free to use this software in any commercial/free game.
// Selling this as a plugin/item, in whole or part, is not allowed.
// See "License.md" for full licensing details.

#pragma once
//#include "MetaballsPluginPrivatePCH.h"
//#include "MetaballsPlugin.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Metaballs.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(YourLog, Log, All);

struct SMetaBall
{

	FVector p;
	FVector v;
	FVector a;

	float t;
	float m;
};


UCLASS()
class METABALLSPLUGIN_API AMetaballs : public AActor
{
	//GENERATED_UCLASS_BODY()
	GENERATED_BODY()
	
public:	

	enum MinMax
	{
		MAX_METABALLS = 32,
		MIN_GRID_STEPS = 16,
		MAX_GRID_STEPS = 128,
		MIN_SCALE = 1,
		MAX_OPEN_VOXELS = 32,
		MIN_LIMIT = 0,
		MAX_LIMIT = 1,
	};

	
	// Sets default values for this pawn's properties
	AMetaballs(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void PostInitializeComponents() override;


	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;
#endif

	UFUNCTION(BlueprintCallable, Category = "Metaballs")
	void SetBallTransform(int32 index, FVector transfrom);

	UFUNCTION(BlueprintCallable, Category = "Metaballs")
	FVector GetBallTransform(int32 index);

	UFUNCTION(BlueprintCallable, Category = "Metaballs")
	void SetNumBalls(int32 value);

	UFUNCTION(BlueprintCallable, Category = "Metaballs")
	void SetScale(float value);

	UFUNCTION(BlueprintCallable, Category = "Metaballs")
	void SetGridSteps(int32 value);

	UFUNCTION(BlueprintCallable, Category = "Metaballs")
	void SetRandomSeed(bool seed);

	UFUNCTION(BlueprintCallable, Category = "Metaballs")
	void SetAutoMode(bool mode);

	UFUNCTION(BlueprintCallable, Category = "Metaballs")
	void SetAutoLimitX(float limit);

	UFUNCTION(BlueprintCallable, Category = "Metaballs")
	void SetAutoLimitY(float limit);

	UFUNCTION(BlueprintCallable, Category = "Metaballs")
	void SetAutoLimitZ(float limit);

	/*Number of metaballs (0 - disable)*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (DisplayName = "Number of balls"))
	int32 m_NumBalls;

	/*Metaballs area scale*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (DisplayName = "Area Scale"))
	float m_Scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (DisplayName = "Blob Scale"))
	float BlobScale = 100;

	/*If bigger value, then metaballs are more detailed*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (DisplayName = "Grid steps"))
	int32 m_GridStep;

	/*If true, start balls at random positions. Otherwise from center*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (DisplayName = "Random seed"))
	bool m_randomseed;

	/*If true, metaballs will do automatic movement. Otherwise you should set position manually*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (DisplayName = "Auto fly mode"))
	bool m_automode;

	/*Limit direction by X axis. Only for Auto fly mode!*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (DisplayName = "Auto limits"))
	float m_AutoLimitX;

	/*Limit direction by Y axis. Only for Auto fly mode!*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (DisplayName = "Auto limit Y"))
	float m_AutoLimitY;

	/*Limit direction by Z axis. Only for Auto fly mode!*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (DisplayName = "Auto limit Z"))
	float m_AutoLimitZ;

	/*Metaballs material*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Settings, meta = (DisplayName = "Material"))
	UMaterialInterface* m_Material;

	UPROPERTY()
	UBoxComponent* MetaBallsBoundBox;

//	UPROPERTY(VisibleAnywhere, Category = "MyComponents")
//	USceneComponent* m_SceneComponent;

	UPROPERTY()
	UBillboardComponent* m_SpriteComponent;

	void  Update(float fDeltaTime);
	void  Render();

	void  SetGridSize(int nSize);

protected:

	void InitBalls();
	float CheckLimit(float value);

	float ComputeEnergy(float x, float y, float z);
	void  ComputeNormal(FVector vertex);

	float ComputeGridPointEnergy(int x, int y, int z);
	int   ComputeGridVoxel(int x, int y, int z);

	bool  IsGridPointComputed(int x, int y, int z);
	bool  IsGridVoxelComputed(int x, int y, int z);
	bool  IsGridVoxelInList(int x, int y, int z);
	void  SetGridPointComputed(int x, int y, int z);
	void  SetGridVoxelComputed(int x, int y, int z);
	void  SetGridVoxelInList(int x, int y, int z);

	float ConvertGridPointToWorldCoordinate(int x);
	int   ConvertWorldCoordinateToGridPoint(float x);
	void  AddNeighborsToList(int nCase, int x, int y, int z);
	void  AddNeighbor(int x, int y, int z);

	float  m_fLevel;


	SMetaBall  m_Balls[AMetaballs::MAX_METABALLS];

	int		m_nNumOpenVoxels;
	int		m_nMaxOpenVoxels;
	int		*m_pOpenVoxels;

	int		m_nGridSize;
	float	m_fVoxelSize;

	float	*m_pfGridEnergy;
	char	*m_pnGridPointStatus;
	char	*m_pnGridVoxelStatus;

	int		m_nNumVertices;
	int		m_nNumIndices;


	UProceduralMeshComponent* m_mesh;

	TArray<FVector> m_vertices;
	TArray<int32> m_Triangles;
	TArray<FVector> m_normals;

	TArray<FVector2D> m_UV0;
	TArray<FColor> m_vertexColors;

	TArray<FProcMeshTangent> m_tangents;
};
