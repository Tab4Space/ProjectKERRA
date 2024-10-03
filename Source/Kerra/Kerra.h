// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Engine.h"

DECLARE_LOG_CATEGORY_EXTERN(KERRALOG, Log, All);

#define KERRALOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define KERRALOG_S(Verbosity) UE_LOG(KERRALOG, Verbosity, TEXT("%s"), *KERRALOG_CALLINFO)
#define KERRALOG(Verbosity, Format, ...) UE_LOG(KERRALOG, Verbosity, TEXT("%s %s"), *KERRALOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

#define ECC_Parkour ECC_GameTraceChannel1
