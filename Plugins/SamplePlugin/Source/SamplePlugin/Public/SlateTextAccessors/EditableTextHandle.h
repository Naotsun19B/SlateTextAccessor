// Copyright 2021 Naotsun. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class SInlineEditableTextBlock;

namespace SamplePlugin
{
	class IEditableTextAccessor;
	
	/**
	 * A utility structure for replacing only selected parts.
	 */
	class SAMPLEPLUGIN_API FEditableTextHandle
	{
	public:
		// Constructor.
		FEditableTextHandle(const TSharedPtr<IEditableTextAccessor>& InEditableText);

		// If the text is selected, only the selected part is returned.
		FString GetText() const;
		
		// If the text is selected, replace only that part.
		void SetText(const FString& InText);

		// Returns whether the editable text on which this data is based is valid.
		bool IsValid() const;
		
		// Returns editable text from which this data is based.
		TSharedPtr<IEditableTextAccessor> GetEditableTextAccessor() const;

		// Returns text at the time this handle was generated.
		FString GetCachedText() const;

		// Returns whether any character was selected.
		bool IsSelectedText() const;
		
		// Returns selected text at the time this handle was generated.
		FString GetCachedSelectedText() const;

	private:
		// The editable text from which this data is based.
		TSharedPtr<IEditableTextAccessor> EditableTextAccessor;

		// The text at the time this handle was generated.
		FString CachedText;

		// Whether any character was selected.
		bool bIsSelectedText;
		
		// The selected text at the time this handle was generated.
		FString CachedSelectedText;

		// Owner of EditableText.
		TSharedPtr<SInlineEditableTextBlock> InlineEditableTextBlock;
	};
}
