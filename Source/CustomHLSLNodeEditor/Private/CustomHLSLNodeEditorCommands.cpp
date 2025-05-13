// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomHLSLNodeEditorCommands.h"

#define LOCTEXT_NAMESPACE "FCustomHLSLNodeEditorModule"

void FCustomHLSLNodeEditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "CustomHLSLNodeEditor", "Bring up CustomHLSLNodeEditor window", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(SaveHLSLCode, "Save Current HLSL Code", "Save the current HLSL Code in the editor", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(OpenNewHLSLTab, "Open New HLSL Editor Tab", "Open a new HLSL Editor Tab to edit code", EUserInterfaceActionType::Button, FInputChord());

}

#undef LOCTEXT_NAMESPACE
