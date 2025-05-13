


#include "CustomHLSLEditorWindow.h"

#include "SlateOptMacros.h"

#include "LevelEditor.h"

#include "GraphEditorModule.h"

#include "MaterialGraph/MaterialGraphNode.h"
#include "Materials/MaterialExpressionCustom.h"

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

#define LOCTEXT_NAMESPACE "SCustomHLSLNodeEditorWidow"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SCustomHLSLEditorWindow::Construct(const FArguments& InArgs, UEdGraph* Graph, UMaterialGraphNode* MatNode, FString InputCode)
{
	CurrentInputCode = InputCode;
	SavedInputCode = FString(CurrentInputCode);

	SelectedMaterialNode = MatNode;
	CurrentGraph = Graph;

	FString SelectedNodeDescription = SelectedMaterialNode->MaterialExpression->Desc;
	FText CurrentInputCodeText = FText::FromString(CurrentInputCode);

	const FSlateBrush* SaveIcon = FAppStyle::GetBrush("Icons.Save");

	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.MaxHeight(25.0f)
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Top)
		.FillHeight(0.1f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Top)
			[
				SAssignNew(SaveButton, SButton)
				.OnClicked(this, &SCustomHLSLEditorWindow::OnHLSLTextCommitted)
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Top)
				.Text(LOCTEXT("WindowWidgetText", "Save Code"))
				[
					SNew(SImage)
					.Image(SaveIcon)
				]
			]

		]
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Fill)
		.FillHeight(2.0f)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.VAlign(VAlign_Fill)
			[
				SAssignNew(InputTextBox, SMultiLineEditableTextBox)
					.Text(CurrentInputCodeText)
					.Font(FCoreStyle::GetDefaultFontStyle("Mono", 10))
			]
		]
	];
}

FReply SCustomHLSLEditorWindow::OnHLSLTextCommitted()
{
	// Notify the Material Graph is about to be changed (from changing a material node)
	UMaterialGraph* OwnerGraph = Cast<UMaterialGraph>(SelectedMaterialNode->GetGraph());
	OwnerGraph->Modify();
	OwnerGraph->MaterialDirtyDelegate;
	UE_LOG(LogTemp, Log, TEXT("Saving New Code Input for Custom Node"));
	
	// Commit/save whatever is currently inside the text box
	SavedInputCode = InputTextBox->GetText().ToString();

	// Prepare Material Node for a property change and change the Code property to whatever the committed/saved text value
	FName PropertyName = TEXT("Code");
	FProperty* Property = SelectedMaterialNode->GetClass()->FindPropertyByName(PropertyName);
	SelectedMaterialNode->PreEditChange(Property);

	UMaterialExpressionCustom* NodeExpression = Cast<UMaterialExpressionCustom>(SelectedMaterialNode->MaterialExpression);
	NodeExpression->Code = SavedInputCode;
	
	// Notify the Material Node that a change has occurred to show a dirty asset indicator which propagates to the Material showing an unsaved change
	FPropertyChangedEvent ChangeEvent(Property);
	SelectedMaterialNode->PostEditChangeProperty(ChangeEvent);
	SelectedMaterialNode->MaterialExpression->MarkPackageDirty();
	SelectedMaterialNode->MaterialDirtyDelegate.ExecuteIfBound();
	OwnerGraph->NotifyNodeChanged(SelectedMaterialNode);

	return FReply::Handled();
}


END_SLATE_FUNCTION_BUILD_OPTIMIZATION
