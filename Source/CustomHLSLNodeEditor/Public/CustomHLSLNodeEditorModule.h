// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#include "Toolkits/AssetEditorToolkit.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"

class FMenuBuilder;
class UMaterialGraphNode;

class FCustomHLSLNodeEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:

	void RegisterMenus();

	static TSharedRef<FExtender> HandleOnExtendGraphEditorContextMenu(const TSharedRef<FUICommandList> CommandList, const UEdGraph* Graph, const UEdGraphNode* Node, const UEdGraphPin* Pin, bool bIsConst);

	static void HandleOnExtendContextMenu(FMenuBuilder& MenuBuilder);
	static void InsertNewHLSLDocumentTab(const UEdGraph* Graph, const UMaterialGraphNode* ReferencedNode);

};
