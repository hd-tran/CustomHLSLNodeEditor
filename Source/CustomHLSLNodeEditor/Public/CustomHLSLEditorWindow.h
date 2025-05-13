

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

#include "Toolkits/AssetEditorToolkit.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"

#include "MaterialGraph/MaterialGraphNode.h"
#include "Materials/MaterialExpressionCustom.h"
/**
 * 
 */
class CUSTOMHLSLNODEEDITOR_API SCustomHLSLEditorWindow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCustomHLSLEditorWindow)
	{}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs, UEdGraph* Graph, UMaterialGraphNode* MatNode, FString InputCode);

	FReply OnHLSLTextCommitted();

	FString CurrentInputCode;
	FString SavedInputCode;

	TSharedPtr< SMultiLineEditableTextBox > InputTextBox;

	TSharedPtr< SButton > SaveButton;

	UMaterialGraphNode* SelectedMaterialNode;

	UEdGraph* CurrentGraph;

private:
	
};
