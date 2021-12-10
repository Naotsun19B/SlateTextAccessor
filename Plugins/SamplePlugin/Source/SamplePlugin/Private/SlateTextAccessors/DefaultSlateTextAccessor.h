// Copyright 2021 Naotsun. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

namespace SamplePlugin
{
	/**
	 * Register and unregister the standard SlateTextAccessor from this plugin.
	 */
	class FDefaultSlateTextAccessor
	{
	public:
		// Register the SlateTextAccessor that is registered by default.
		static void Register();

		// Unregister the SlateTextAccessor that is registered by default.
		static void Unregister();
	};
}
