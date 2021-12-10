// Copyright 2021 Naotsun. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

namespace SamplePlugin
{
	/**
	 * Class to register the shortcut key used in this plugin.
	 */
	class SAMPLEPLUGIN_API FSamplePluginCommands : public TCommands<FSamplePluginCommands>
	{
	public:
		// Constructor.
		FSamplePluginCommands();

		// TCommands interface.
		virtual void RegisterCommands() override;
		// End of TCommands interface.

		// Is the command registered here bound.
		static bool IsBound();

		// Processing of command binding.
		static void Bind();

	protected:
		// Internal processing of command binding.
		virtual void BindCommands();

	public:
		// Instances of bound commands.
		TSharedPtr<FUICommandInfo> TestReadOnlyTextAccessor;
		TSharedPtr<FUICommandInfo> TestEditableTextAccessor;
		TSharedPtr<FUICommandInfo> TestTooltipTextAccessor;

	private:
		// Is the command registered here bound.
		bool bIsBound;
	};
}
