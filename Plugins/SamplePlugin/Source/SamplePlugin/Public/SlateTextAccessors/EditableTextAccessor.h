// Copyright 2021 Naotsun. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class SWidget;

namespace SamplePlugin
{
	/**
	 * Accessor interface for editable text widgets.
	 */
	class SAMPLEPLUGIN_API IEditableTextAccessor
	{
	public:
		// Destructor.
		virtual ~IEditableTextAccessor() = default;
		
		// Returns the string set in the widget.
		virtual FText GetText() const = 0;

		// Returns the string selected in the widget.
		virtual FText GetSelectedText() const = 0;
			
		// Sets the text of the widget.
		virtual void SetText(const FText& Text) = 0;

		// Query to see if any text is selected within the widget.
		virtual bool AnyTextSelected() const = 0;
			
		// Returns the wrapped widget.
		virtual TSharedPtr<SWidget> AsWidget() const = 0;
	};

	/**
	 * Template class used when registering widgets in FEditableTextAccessorFactory.
	 * Only classes with functions that must be overridden in
	 * IEditableTextAccessor can be specified in TWidgetClass.
	 */
	template<class TWidgetClass>
	class TEditableText : public IEditableTextAccessor
	{
	public:
		// Constructor.
		TEditableText(TSharedPtr<TWidgetClass> InEditableText)
			: IEditableTextAccessor()
			, EditableText(InEditableText)
		{
			static_assert(TIsDerivedFrom<TWidgetClass, SWidget>::IsDerived, "TWidgetClass must be a SWidget based type.");

			check(EditableText.IsValid() && !EditableText->IsTextReadOnly());
		}
		
		// IEditableTextAccessor interface.
		virtual FText GetText() const override
		{
			if (EditableText.IsValid())
			{
				return EditableText->GetText();
			}

			return {};
		}

		virtual FText GetSelectedText() const override
		{
			if (EditableText.IsValid())
			{
				return EditableText->GetSelectedText();
			}

			return {};
		}

		virtual void SetText(const FText& Text) override
		{
			if (EditableText.IsValid())
			{
				EditableText->SetText(Text);
			}
		}

		virtual bool AnyTextSelected() const override
		{
			if (EditableText.IsValid())
			{
				return EditableText->AnyTextSelected();
			}

			return false;
		}

		virtual TSharedPtr<SWidget> AsWidget() const override
		{
			return EditableText;
		}
		// End of IEditableTextAccessor interface.

	private:
		// An instance of the actual widget.
		TSharedPtr<TWidgetClass> EditableText;
	};

	// The process of converting the passed widget to IEditableTextAccessor.
	DECLARE_DELEGATE_RetVal_OneParam(TSharedPtr<IEditableTextAccessor>, FOnGetEditableTextAccessor, TSharedPtr<SWidget> /* InWidget */);

	/**
	 * Factory class for editable text widgets accessor.
	 */
	class SAMPLEPLUGIN_API FEditableTextAccessorFactory
	{
	public:
		// Register the widget type name and accessor generation function.
		static void RegisterAccessor(const FName& WidgetTypeName, const FOnGetEditableTextAccessor& Generator);

		// Unregister the widget type name and accessor generation function.
		static void UnregisterAccessor(const FName& WidgetTypeName);

		// Returns whether the specified widget type is registered.
		static bool IsAccessorRegistered(const FName& WidgetTypeName);

		// Create a accessor according to the registered widget type.
		static TSharedPtr<IEditableTextAccessor> CreateAccessor(TSharedPtr<SWidget> InWidget);

	private:
		// Registry of widget type name and accessor generation function.
		static TMap<FName, FOnGetEditableTextAccessor> EditableTextAccessorRegistry;
	};
}
