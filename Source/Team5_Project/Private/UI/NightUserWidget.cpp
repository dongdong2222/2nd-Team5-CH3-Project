// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/NightUserWidget.h"

void UNightUserWidget::SetWidgetController(UObject* InWidgetController)
{
  WidgetController = InWidgetController;
  WidgetControllerSet();
}
