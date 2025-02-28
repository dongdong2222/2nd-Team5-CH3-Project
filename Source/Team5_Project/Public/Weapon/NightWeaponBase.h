#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NightWeaponInterface.h"
#include "NightWeaponBase.generated.h"

UCLASS()
class TEAM5_PROJECT_API ANightWeaponBase : public AActor,public INightWeaponInterface
{
	GENERATED_BODY()
	
public:	
	ANightWeaponBase();


	//Add Dongju
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "weapon | Animation")
	TSubclassOf<UAnimInstance> AnimLayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "weapon | Animation")
	UAnimMontage* EqipMontage;
	//End of Add Dongju

	int32 MaxBullet;
	int32 CurrentBullet;
	bool isFiring = true;
	FTimerHandle timer;
	float Range;

	//배율
	int32 Zoomtimes;

protected:
	virtual FName GetWeaponType() const override;
	virtual void DestroyWeapon();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "weapon")
	FName WeaponType;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "weapon|Component")
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "weapon|Component")
	USkeletalMeshComponent* SkeletalMesh;




	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void Fire();


};
