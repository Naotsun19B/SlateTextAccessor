// Copyright 2021 Naotsun. All Rights Reserved.

#include "CommandActions/SamplePluginCommands.h"
#include "SamplePluginGlobals.h"
#include "CommandActions/SamplePluginActions.h"
#include "Interfaces/IMainFrameModule.h"
#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "SamplePluginCommands"

namespace SamplePlugin
{
	FSamplePluginCommands::FSamplePluginCommands()
		: TCommands<FSamplePluginCommands>
		(
			TEXT("SamplePlugin"),
			NSLOCTEXT("Contexts", "SamplePlugin", "Sample Plugin"),
			NAME_None,
			FEditorStyle::GetStyleSetName()
		)
		, bIsBound(false)
	{
	}

	void FSamplePluginCommands::RegisterCommands()
	{
		// Register command here.
		UI_COMMAND(
			TestReadOnlyTextAccessor,
			"Test Read Only Text Accessor",
			"Logs the text under the mouse cursor.",
			EUserInterfaceActionType::None,
			FInputChord(EKeys::Insert, false, false, false, false)
		);
		
		UI_COMMAND(
			TestEditableTextAccessor,
			"Test Editable Text Accessor",
			"Replace the text you are currently editing with \"Test Editable Text Accessor\".",
			EUserInterfaceActionType::None,
			FInputChord(EKeys::Home, false, false, false, false)
		);

		UI_COMMAND(
			TestTooltipTextAccessor,
			"Test Tooltip Text Accessor",
			"Log out the text of the currently displayed tooltip.",
			EUserInterfaceActionType::None,
			FInputChord(EKeys::PageUp, false, false, false, false)
		);
	}

	bool FSamplePluginCommands::IsBound()
	{
		return Instance.Pin()->bIsBound;
	}

	void FSamplePluginCommands::Bind()
	{
		Instance.Pin()->BindCommands();
	}

	void FSamplePluginCommands::BindCommands()
	{
		if (!IsRegistered())
		{
			UE_LOG(LogSamplePlugin, Fatal, TEXT("Bound before UI Command was registered.\nPlease be sure to bind after registration."));
		}

		if (IsBound())
		{
			UE_LOG(LogSamplePlugin, Warning, TEXT("The binding process has already been completed."));
		}
		bIsBound = true;

		IMainFrameModule& MainFrame = FModuleManager::LoadModuleChecked<IMainFrameModule>("MainFrame");
		const TSharedRef<FUICommandList>& CommandBindings = MainFrame.GetMainFrameCommandBindings();

		// Bind command here.
		CommandBindings->MapAction(
			TestReadOnlyTextAccessor,
			FExecuteAction::CreateStatic(&FSamplePluginActions::TestReadOnlyTextAccessor)
		);
		
		CommandBindings->MapAction(
			TestEditableTextAccessor,
			FExecuteAction::CreateStatic(&FSamplePluginActions::TestEditableTextAccessor)
		);

		CommandBindings->MapAction(
			TestTooltipTextAccessor,
			FExecuteAction::CreateStatic(&FSamplePluginActions::TestTooltipTextAccessor)
		);
	}
}

#undef LOCTEXT_NAMESPACE
