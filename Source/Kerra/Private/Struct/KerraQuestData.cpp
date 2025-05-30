// Fill out your copyright notice in the Description page of Project Settings.


#include "Struct/KerraQuestData.h"

FKerraQuestData::FKerraQuestData()
{
}

bool FKerraQuestData::IsValid() const
{
	return QuestID.IsValid();
}
