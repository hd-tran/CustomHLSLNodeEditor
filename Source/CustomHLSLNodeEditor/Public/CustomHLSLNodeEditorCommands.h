// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "CustomHLSLNodeEditorStyle.h"

class FCustomHLSLNodeEditorCommands : public TCommands<FCustomHLSLNodeEditorCommands>
{
public:

	FCustomHLSLNodeEditorCommands()
		: TCommands<FCustomHLSLNodeEditorCommands>(TEXT("CustomHLSLNodeEditor"), NSLOCTEXT("Contexts", "CustomHLSLNodeEditor", "CustomHLSLNodeEditor Plugin"), NAME_None, FCustomHLSLNodeEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;

	TSharedPtr< FUICommandInfo > SaveHLSLCode;

	TSharedPtr< FUICommandInfo > OpenNewHLSLTab;

};