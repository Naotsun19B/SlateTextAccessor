// Copyright 2021 Naotsun. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

namespace SamplePlugin
{
	/**
	 * Functions called from a shortcut key.
	 */
	class SAMPLEPLUGIN_API FSamplePluginActions
	{
	public:
		static void TestReadOnlyTextAccessor();
		static void TestEditableTextAccessor();
		static void TestTooltipTextAccessor();
	};
}
