

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
class CUSTOMHLSLNODEEDITOR_API CustomHLSLNodeObject : public UObject
{
public:
	CustomHLSLNodeObject();
	~CustomHLSLNodeObject();

public:
	FString CurrentInputCode;
	FString SavedInputCode;

	TSharedPtr< SMultiLineEditableTextBox > InputTextBox;

	TSharedPtr< SButton > SaveButton;
};
