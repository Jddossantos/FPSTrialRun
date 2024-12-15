// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/FPSHUD.h"
#include "Widgets/SWeakWidget.h"

void AFPSHUD::BeginPlay()
{
    Super::BeginPlay();

    ShowGameMenu(startingGameWidget);
    //ShowSettingsMenu();
}

void AFPSHUD::DrawHUD()
{
	Super::DrawHUD();

    if (CrosshairTexture)
    {
        //1. Calculating the center point on the screen
        FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

        //2. Set the crosshair pivot to the center
        float CrosshairHalfWidth = (CrosshairTexture->GetSurfaceWidth() * 0.5f);
        float CrosshairHalfHeight = (CrosshairTexture->GetSurfaceHeight() * 0.5f);
        FVector2D CrossHairDrawPosition(Center.X - CrosshairHalfWidth, Center.Y - CrosshairHalfHeight);

        //Draw the crosshair at the centerpoint.
        FCanvasTileItem TileItem(CrossHairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
        TileItem.BlendMode = SE_BLEND_Translucent;
        Canvas->DrawItem(TileItem);
    }
}

void AFPSHUD::ShowSettingsMenu()
{
    if (GEngine && GEngine->GameViewport)
    {
        settingsWidget = SNew(SSSettingsWidget).OwningHUD(this);
        GEngine->GameViewport->AddViewportWidgetContent(SAssignNew(settingsWidgetContainer, SWeakWidget).PossiblyNullContent(settingsWidget.ToSharedRef()));

        if (PlayerOwner)
        {
            PlayerOwner->bShowMouseCursor = true;
            PlayerOwner->SetInputMode(FInputModeUIOnly());
        }
    }
}

void AFPSHUD::RemoveSettingsMenu()
{
    if (GEngine && GEngine->GameViewport && settingsWidgetContainer.IsValid())
    {
        GEngine->GameViewport->RemoveViewportWidgetContent(settingsWidgetContainer.ToSharedRef());

        if (PlayerOwner)
        {
            PlayerOwner->bShowMouseCursor = false;
            PlayerOwner->SetInputMode(FInputModeGameOnly());
        }
    }
}

void AFPSHUD::ShowGameMenu(TSubclassOf<UFPSGameUI> newGameWidget)
{
    if (gameWidgetContainer) {
        gameWidgetContainer->RemoveFromParent();
        gameWidgetContainer = nullptr;
    }

    if (newGameWidget) {
        gameWidgetContainer = CreateWidget<UFPSGameUI>(GetWorld(), newGameWidget);
        gameWidgetContainer->AddToViewport();
    }
}
