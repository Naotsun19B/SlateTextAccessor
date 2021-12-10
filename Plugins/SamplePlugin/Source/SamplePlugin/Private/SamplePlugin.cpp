// Copyright Epic Games, Inc. All Rights Reserved.

#include "SamplePlugin.h"
#include "SamplePluginGlobals.h"
#include "CommandActions/SamplePluginCommands.h"
#include "SlateTextAccessors/DefaultSlateTextAccessor.h"

DEFINE_LOG_CATEGORY(LogSamplePlugin);

namespace SamplePlugin
{
	void FSamplePluginModule::StartupModule()
	{
		FSamplePluginCommands::Register();
		FSamplePluginCommands::Bind();

		FDefaultSlateTextAccessor::Register();
	}

	void FSamplePluginModule::ShutdownModule()
	{
		FDefaultSlateTextAccessor::Unregister();
		
		FSamplePluginCommands::Unregister();
	}
}

IMPLEMENT_MODULE(SamplePlugin::FSamplePluginModule, SamplePlugin)