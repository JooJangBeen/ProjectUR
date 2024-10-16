
#include "SpiderEye.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/ArrowComponent.h"


ASpiderEye::ASpiderEye()
{
	GetCapsuleComponent()->DestroyComponent();  // 캡슐 콜리전 제거
	UBoxComponent* BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	BoxCollision->SetBoxExtent(FVector(130.0f, 100.0f, 130.0f));
	BoxCollision->SetCollisionProfileName(TEXT("Pawn"));
	RootComponent = BoxCollision;
	//BoxCollision->SetRelativeLocation(FVector(0.0f, -86.0f, 144.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/03_Monster/98_IKMonster/SpideEye/Mesh/SK_SpideEye.SK_SpideEye'"));
	if (CharacterMeshRef.Object)
		GetMesh()->SetSkeletalMesh(CharacterMeshRef.Object);

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstClassRef(TEXT("/Game/03_Monster/98_IKMonster/SpideEye/ABP_SpiderEye.ABP_SpiderEye_C"));
	if (AnimInstClassRef.Class)
		GetMesh()->SetAnimInstanceClass(AnimInstClassRef.Class);

	GetMesh()->SetupAttachment(RootComponent);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 86.0f, -144.0f));
	GetArrowComponent()->SetupAttachment(RootComponent);

	

}
