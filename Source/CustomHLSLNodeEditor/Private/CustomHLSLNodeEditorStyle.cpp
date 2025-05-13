// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomHLSLNodeEditorStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FCustomHLSLNodeEditorStyle::StyleInstance = nullptr;

void FCustomHLSLNodeEditorStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FCustomHLSLNodeEditorStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FCustomHLSLNodeEditorStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("CustomHLSLNodeEditorStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FCustomHLSLNodeEditorStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("CustomHLSLNodeEditorStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("CustomHLSLNodeEditor")->GetBaseDir() / TEXT("Resources"));

	Style->Set("CustomHLSLNodeEditor.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));

	return Style;
}

void FCustomHLSLNodeEditorStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FCustomHLSLNodeEditorStyle::Get()
{
	return *StyleInstance;
}
