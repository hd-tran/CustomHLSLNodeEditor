// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomHLSLNodeEditorModule.h"
#include "CustomHLSLNodeEditorStyle.h"
#include "CustomHLSLNodeEditorCommands.h"

#include "CustomHLSLEditorWindow.h"

#include "LevelEditor.h"

#include "GraphEditorModule.h"

#include "MaterialGraph/MaterialGraphNode.h"
#include "Materials/MaterialExpressionCustom.h"

#include "Settings/EditorStyleSettings.h"
#include "Styling/SlateStyle.h"

#include "Toolkits/AssetEditorToolkit.h"
#include "ToolMenus.h"

#include "Widgets/Docking/SDockTab.h"

#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"

#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SScaleBox.h"
#include "Widgets/Layout/SUniformGridPanel.h"

#include "Widgets/Text/STextBlock.h"


static const FName CustomHLSLNodeEditorTabName("Custom HLSL Node Editor");

const FName GraphEditorModuleName(TEXT("GraphEditor"));

#define LOCTEXT_NAMESPACE "FCustomHLSLNodeEditorModule"

void FCustomHLSLNodeEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FCustomHLSLNodeEditorStyle::Initialize();
	FCustomHLSLNodeEditorStyle::ReloadTextures();

	FCustomHLSLNodeEditorCommands::Register();
	
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FCustomHLSLNodeEditorModule::RegisterMenus));
	
}

void FCustomHLSLNodeEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FCustomHLSLNodeEditorStyle::Shutdown();

	FCustomHLSLNodeEditorCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(CustomHLSLNodeEditorTabName);
}

TSharedRef<FExtender> FCustomHLSLNodeEditorModule::HandleOnExtendGraphEditorContextMenu(const TSharedRef<FUICommandList> CommandList, const UEdGraph* Graph, const UEdGraphNode* Node, const UEdGraphPin* Pin, bool bIsConst)
{
	TSharedRef<FExtender> Extender = MakeShared<FExtender>();
	
	const UMaterialGraphNode* MaterialNode = Cast<UMaterialGraphNode>(Node);

	if (MaterialNode && MaterialNode->MaterialExpression->IsA(UMaterialExpressionCustom::StaticClass())) {

		const FName ExtensionHook(TEXT("MaterialSchemaNodeActions"));
		
		CommandList->MapAction(
			FCustomHLSLNodeEditorCommands::Get().OpenNewHLSLTab, 
			FExecuteAction::CreateStatic(&FCustomHLSLNodeEditorModule::InsertNewHLSLDocumentTab, Graph, MaterialNode));

		Extender->AddMenuExtension(
			ExtensionHook,
			EExtensionHook::After,
			CommandList,
			FMenuExtensionDelegate::CreateStatic(&FCustomHLSLNodeEditorModule::HandleOnExtendContextMenu));

		return Extender;

	}

	return Extender;
}

void FCustomHLSLNodeEditorModule::HandleOnExtendContextMenu(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(FCustomHLSLNodeEditorCommands::Get().OpenNewHLSLTab);
}

void FCustomHLSLNodeEditorModule::InsertNewHLSLDocumentTab(const UEdGraph* Graph, const UMaterialGraphNode* ReferencedNode)
{	// Get the Custom node's Code input field and copy it to the new window
	const UMaterialExpressionCustom* CustomExpression = Cast<UMaterialExpressionCustom>(ReferencedNode->MaterialExpression);
	const FString CurrentCode = CustomExpression->Code;
	
	UMaterialGraphNode* SelectedNode = const_cast<UMaterialGraphNode*>(ReferencedNode);
	UEdGraph* CurrentGraph = const_cast<UEdGraph*>(Graph);
	
	TSharedPtr<FTabManager::FSearchPreference> SearchPreference = MakeShareable(new FTabManager::FLiveTabSearch(CustomHLSLNodeEditorTabName));

	TAttribute<FText> Label = TAttribute<FText>(FText::FromString(CustomExpression->GetDescription()));

	TSharedRef<SWidget> TabEditorWidget = SNew(SCustomHLSLEditorWindow, CurrentGraph, SelectedNode, CurrentCode);

	TSharedPtr<SDockTab> NewMajorTab = SNew(SDockTab)
		.ContentPadding(0.0f)
		.TabRole(ETabRole::DocumentTab)
		.Label(Label);

	TSharedPtr<SWindow> Window = NewMajorTab->GetParentWindow();
	if (Window.IsValid())
	{
		Window->BringToFront();
	}

	NewMajorTab->SetContent(TabEditorWidget);

	FGlobalTabmanager::Get()->InsertNewDocumentTab(CustomHLSLNodeEditorTabName, *SearchPreference, NewMajorTab.ToSharedRef());
}

void FCustomHLSLNodeEditorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	// Extend the Context menu used in Graph Editors to have a new option for Opening the CustomHLSLNodeEditor Window
	FGraphEditorModule& GraphEditorModule = FModuleManager::LoadModuleChecked<FGraphEditorModule>(GraphEditorModuleName);
	GraphEditorModule.GetAllGraphEditorContextMenuExtender().Add(FGraphEditorModule::FGraphEditorMenuExtender_SelectedNode::CreateStatic(&FCustomHLSLNodeEditorModule::HandleOnExtendGraphEditorContextMenu));

}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCustomHLSLNodeEditorModule, CustomHLSLNodeEditor)