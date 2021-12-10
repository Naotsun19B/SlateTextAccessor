// Copyright 2021 Naotsun. All Rights Reserved.

#include "SlateTextAccessors/EditableTextHandle.h"
#include "SlateTextAccessors/EditableTextAccessor.h"
#include "SlateTextAccessors/CastSlateWidget.h"
#include "Utilities/SamplePluginSlateHelpers.h"
#include "Framework/Application/SlateUser.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"

namespace SamplePlugin
{
	namespace EditableTextHandleInternal
	{
		TSharedPtr<SInlineEditableTextBlock> FindInlineEditableTextBlock(const TSharedPtr<SWidget>& SearchTarget)
		{
			if (!SearchTarget.IsValid())
			{
				return nullptr;
			}

			if (!SearchTarget->IsParentValid())
			{
				return nullptr;
			}

			const TSharedPtr<SWidget> Parent = SearchTarget->GetParentWidget();
			const TSharedPtr<SInlineEditableTextBlock> InlineEditableTextBlock = CAST_SLATE_WIDGET(SInlineEditableTextBlock, Parent);
			if (InlineEditableTextBlock.IsValid())
			{
				return InlineEditableTextBlock;
			}

			return FindInlineEditableTextBlock(Parent);
		}
	}
	
	FEditableTextHandle::FEditableTextHandle(const TSharedPtr<IEditableTextAccessor>& InEditableText)
		: EditableTextAccessor(InEditableText)
		, bIsSelectedText(false)
	{
		check(EditableTextAccessor.IsValid());

		CachedText = EditableTextAccessor->GetText().ToString();
		if (EditableTextAccessor->AnyTextSelected())
		{
			bIsSelectedText = true;
			CachedSelectedText = EditableTextAccessor->GetSelectedText().ToString();	
		}

		// Unify the line feed code to "\n".
		CachedText = CachedText.Replace(TEXT("\r\n"), TEXT("\n"));
		CachedSelectedText = CachedSelectedText.Replace(TEXT("\r\n"), TEXT("\n"));

		// When the edit mode and display mode are switched like a comment node or function name,
		// it is necessary to switch the mode from this handle, so the it is cached.
		InlineEditableTextBlock = EditableTextHandleInternal::FindInlineEditableTextBlock(
			EditableTextAccessor->AsWidget()
		);
	}

	FString FEditableTextHandle::GetText() const
	{
		if (bIsSelectedText)
		{
			return CachedSelectedText;
		}
		else
		{
			return CachedText;
		}
	}

	void FEditableTextHandle::SetText(const FString& InText)
	{
		if (!EditableTextAccessor.IsValid())
		{
			return;
		}

		// Switch to edit mode if there is an InlineEditableTextBlock.
		if (InlineEditableTextBlock.IsValid())
		{
			const TSharedPtr<FSlateUser> SlateUser = FSamplePluginSlateHelpers::GetLocalSlateUser();
			if (SlateUser.IsValid())
			{
				SlateUser->ReleaseAllCapture();
				InlineEditableTextBlock->EnterEditingMode();
			}
		}
		
		if (bIsSelectedText)
		{
			const FString ReplacedString = CachedText.Replace(*CachedSelectedText, *InText);
			EditableTextAccessor->SetText(FText::FromString(ReplacedString));
		}
		else
		{
			EditableTextAccessor->SetText(FText::FromString(InText));
		}
	}

	bool FEditableTextHandle::IsValid() const
	{
		return EditableTextAccessor.IsValid(); 
	}

	TSharedPtr<IEditableTextAccessor> FEditableTextHandle::GetEditableTextAccessor() const
	{
		return EditableTextAccessor;
	}

	FString FEditableTextHandle::GetCachedText() const
	{
		return CachedText;
	}

	bool FEditableTextHandle::IsSelectedText() const
	{
		return bIsSelectedText;
	}

	FString FEditableTextHandle::GetCachedSelectedText() const
	{
		return CachedSelectedText;
	}
}
