// Copyright 2021 Naotsun. All Rights Reserved.

#include "SlateTextAccessors/DefaultSlateTextAccessor.h"
#include "SlateTextAccessors/CastSlateWidget.h"
#include "SlateTextAccessors/ReadOnlyTextAccessor.h"
#include "SlateTextAccessors/EditableTextAccessor.h"
#include "SlateTextAccessors/TooltipTextAccessor.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/Text/SRichTextBlock.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SHyperlink.h"
#include "Widgets/Input/SEditableText.h"
#include "Widgets/Text/SMultiLineEditableText.h"
#include "Widgets/SToolTip.h"
#include "SDocumentationToolTip.h"

#define GET_CLASS_NAME(Class) ((void)sizeof(Class), TEXT(#Class))

namespace SamplePlugin
{
	namespace DefaultSlateTextAccessor
	{
		class FButtonImpl : public IReadOnlyTextAccessor
		{
		public:
			// Constructor.
			FButtonImpl(TSharedPtr<SButton> InButton)
				: IReadOnlyTextAccessor()
				, Button(InButton)
			{
			}
	
			// IReadOnlyTextAccessor interface.
			virtual FText GetText() const override
			{
				if (Button.IsValid())
				{
					return Button->GetAccessibleText();
				}

				return FText();
			}

			virtual TSharedPtr<SWidget> AsWidget() const override
			{
				return Button;
			}
			// End of IReadOnlyTextAccessor interface.

		private:
			TSharedPtr<SButton> Button;
		};
		
		class FHyperlinkImpl : public IReadOnlyTextAccessor
		{
		public:
			// Constructor.
			FHyperlinkImpl(TSharedPtr<SHyperlink> InHyperlink)
				: IReadOnlyTextAccessor()
				, Hyperlink(InHyperlink)
			{
			}
	
			// IReadOnlyTextAccessor interface.
			virtual FText GetText() const override
			{
				if (Hyperlink.IsValid())
				{
					return Hyperlink->GetAccessibleText();
				}

				return FText();
			}

			virtual TSharedPtr<SWidget> AsWidget() const override
			{
				return Hyperlink;
			}
			// End of IReadOnlyTextAccessor interface.

		private:
			TSharedPtr<SHyperlink> Hyperlink;
		};
	}
	
	void FDefaultSlateTextAccessor::Register()
	{
		FReadOnlyTextAccessorFactory::RegisterAccessor(
			GET_CLASS_NAME(STextBlock),
			FOnGetReadOnlyTextAccessor::CreateLambda(
			[](TSharedPtr<SWidget> InWidget) -> TSharedPtr<IReadOnlyTextAccessor>
			{
				if (TSharedPtr<STextBlock> TextBlock = CAST_SLATE_WIDGET(STextBlock, InWidget))
				{
					return MakeShared<TReadOnlyText<STextBlock>>(TextBlock);
				}

				return nullptr;
			})
		);

		FReadOnlyTextAccessorFactory::RegisterAccessor(
			GET_CLASS_NAME(SRichTextBlock),
			FOnGetReadOnlyTextAccessor::CreateLambda(
			[](TSharedPtr<SWidget> InWidget) -> TSharedPtr<IReadOnlyTextAccessor>
			{
				if (TSharedPtr<SRichTextBlock> RichTextBlock = CAST_SLATE_WIDGET(SRichTextBlock, InWidget))
				{
					return MakeShared<TReadOnlyText<SRichTextBlock>>(RichTextBlock);
				}

				return nullptr;
			})
		);

		FReadOnlyTextAccessorFactory::RegisterAccessor(
			GET_CLASS_NAME(SEditableText),
			FOnGetReadOnlyTextAccessor::CreateLambda(
			[](TSharedPtr<SWidget> InWidget) -> TSharedPtr<IReadOnlyTextAccessor>
			{
				if (TSharedPtr<SEditableText> EditableText = CAST_SLATE_WIDGET(SEditableText, InWidget))
				{
					if (!EditableText->IsTextPassword())
					{
						return MakeShared<TReadOnlyText<SEditableText>>(EditableText);
					}
				}

				return nullptr;
			})
		);

		FReadOnlyTextAccessorFactory::RegisterAccessor(
			GET_CLASS_NAME(SMultiLineEditableText),
			FOnGetReadOnlyTextAccessor::CreateLambda(
			[](TSharedPtr<SWidget> InWidget) -> TSharedPtr<IReadOnlyTextAccessor>
			{
				if (TSharedPtr<SMultiLineEditableText> MultiLineEditableText = CAST_SLATE_WIDGET(SMultiLineEditableText, InWidget))
				{
					if (!MultiLineEditableText->IsTextPassword())
					{
						return MakeShared<TReadOnlyText<SMultiLineEditableText>>(MultiLineEditableText);
					}
				}

				return nullptr;
			})
		);

		FReadOnlyTextAccessorFactory::RegisterAccessor(
			GET_CLASS_NAME(SButton),
			FOnGetReadOnlyTextAccessor::CreateLambda(
			[](TSharedPtr<SWidget> InWidget) -> TSharedPtr<IReadOnlyTextAccessor>
			{
				if (TSharedPtr<SButton> Button = CAST_SLATE_WIDGET(SButton, InWidget))
				{
					return MakeShared<DefaultSlateTextAccessor::FButtonImpl>(Button);
				}

				return nullptr;
			})
		);

		FReadOnlyTextAccessorFactory::RegisterAccessor(
			GET_CLASS_NAME(SHyperlink),
			FOnGetReadOnlyTextAccessor::CreateLambda(
			[](TSharedPtr<SWidget> InWidget) -> TSharedPtr<IReadOnlyTextAccessor>
			{
				if (TSharedPtr<SHyperlink> Hyperlink = CAST_SLATE_WIDGET(SHyperlink, InWidget))
				{
					return MakeShared<DefaultSlateTextAccessor::FHyperlinkImpl>(Hyperlink);
				}

				return nullptr;
			})
		);
		
		FEditableTextAccessorFactory::RegisterAccessor(
			GET_CLASS_NAME(SEditableText),
			FOnGetEditableTextAccessor::CreateLambda([](TSharedPtr<SWidget> InWidget) -> TSharedPtr<IEditableTextAccessor>
			{
				if (TSharedPtr<SEditableText> EditableText = CAST_SLATE_WIDGET(SEditableText, InWidget))
				{
					if (!EditableText->IsTextPassword() && !EditableText->IsTextReadOnly())
					{
						return MakeShared<TEditableText<SEditableText>>(EditableText);
					}
				}

				return nullptr;
			})
		);

		FEditableTextAccessorFactory::RegisterAccessor(
			GET_CLASS_NAME(SMultiLineEditableText),
			FOnGetEditableTextAccessor::CreateLambda([](TSharedPtr<SWidget> InWidget) -> TSharedPtr<IEditableTextAccessor>
			{
				if (TSharedPtr<SMultiLineEditableText> MultiLineEditableText = CAST_SLATE_WIDGET(SMultiLineEditableText, InWidget))
				{
					if (!MultiLineEditableText->IsTextPassword() && !MultiLineEditableText->IsTextReadOnly())
					{
						return MakeShared<TEditableText<SMultiLineEditableText>>(MultiLineEditableText);
					}
				}

				return nullptr;
			})
		);

		FTooltipTextAccessorFactory::RegisterAccessor(
			GET_CLASS_NAME(SToolTip),
			FOnGetTooltipTextAccessor::CreateLambda([](TSharedPtr<SWidget> InWidget) -> TSharedPtr<ITooltipTextAccessor>
			{
				if (TSharedPtr<SToolTip> ToolTip = CAST_SLATE_WIDGET(SToolTip, InWidget))
				{
					if (!ToolTip->GetTextTooltip().IsEmpty())
					{
						return MakeShared<TTooltipText<SToolTip>>(ToolTip);
					}
				}

				return nullptr;
			})
		);

		FTooltipTextAccessorFactory::RegisterAccessor(
			GET_CLASS_NAME(SDocumentationToolTip),
			FOnGetTooltipTextAccessor::CreateLambda([](TSharedPtr<SWidget> InWidget) -> TSharedPtr<ITooltipTextAccessor>
			{
				if (TSharedPtr<SDocumentationToolTip> DocumentationToolTip = CAST_SLATE_WIDGET(SDocumentationToolTip, InWidget))
				{
					if (!DocumentationToolTip->GetTextTooltip().IsEmpty())
					{
						return MakeShared<TTooltipText<SDocumentationToolTip>>(DocumentationToolTip);
					}
				}

				return nullptr;
			})
		);
	}

	void FDefaultSlateTextAccessor::Unregister()
	{
		FTooltipTextAccessorFactory::UnregisterAccessor(GET_CLASS_NAME(SDocumentationToolTip));
		FTooltipTextAccessorFactory::UnregisterAccessor(GET_CLASS_NAME(SToolTip));
		
		FEditableTextAccessorFactory::UnregisterAccessor(GET_CLASS_NAME(SMultiLineEditableText));
		FEditableTextAccessorFactory::UnregisterAccessor(GET_CLASS_NAME(SEditableText));

		FReadOnlyTextAccessorFactory::UnregisterAccessor(GET_CLASS_NAME(SMultiLineEditableText));
		FReadOnlyTextAccessorFactory::UnregisterAccessor(GET_CLASS_NAME(SEditableText));
		FReadOnlyTextAccessorFactory::UnregisterAccessor(GET_CLASS_NAME(SRichTextBlock));
		FReadOnlyTextAccessorFactory::UnregisterAccessor(GET_CLASS_NAME(STextBlock));
	}
}

#undef GET_CLASS_NAME
