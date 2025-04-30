// Fill out your copyright notice in the Description page of Project Settings.


#include "Struct/KerraQuestInfo.h"

FKerraQuestInfo::FKerraQuestInfo()
{
}

bool FKerraQuestInfo::IsValid() const
{
	return QuestID.IsValid();
}
