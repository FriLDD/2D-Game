﻿
#include "FProject.h"
#include "NPC.h"
#include "MyHUD.h"
#include "Avatar.h"


// СФЕРА ВЗАИМОДЕЙСТВИЙ 


ANPC::ANPC(const class FPostConstructInitializeProperties& PCIP) : Super(PCIP)
{
	// Создание компонентов
	//Инициализация в конструкторе путем вызова CreateDefaultSubobject
	//Убитые 8 часов на написание этой строки
	ProxSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("Proximity Sphere"));
	//ProxSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("ProxSphere"));
	
	// Иерархия объектов 
	// Подключение к корневому элементу
	ProxSphere->AttachTo(RootComponent);
	//RootComponent = CreateDefaultSubobject <USceneComponent>(TEXT("Root"));


	// Настройка радиуса сферы 
	// Не редактируется в BP (а должно???)
	ProxSphere->SetSphereRadius(150.f);
	

	// Код для запуска ANPC::Prox(), когда сферу пересекает игрок
	// OnComponentBeginOverlap - вызывается событие при пересечении сферы границ
	ProxSphere->OnComponentBeginOverlap.AddDynamic(this, &ANPC::Prox);
	

	// Сообщение NPC (Редактируется в BP)
	NpcMessage = "Wow, u did it";
}



// ЛОГИКА ПРИ ПЕРЕСЕЧЕНИИ СФЕРЫ

// ANPC::Prox_Implementation() вместо ANPC::Prox()
void ANPC::Prox_Implementation(AActor* OtherActor, UPrimitiveComponent*
	OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult&
	SweepResult) 
{
	//Выполнение кода при персечении с ProxSphere

	// Если пересечение не с игроком, то выходим из функции
	// приведение типов данных
	if (Cast<AAvatar>(OtherActor) == nullptr)
	{
		return;
	}

	// Иначе
	// Отрисовка сообщения и д р
	APlayerController* PController = GetWorld()->GetFirstPlayerController();
	
	if (PController)
	{
		AMyHUD* hud = Cast<AMyHUD>(PController->GetHUD());
		hud->addMessage(Message(NpcMessage, 5.f, FColor::White));

	}

}