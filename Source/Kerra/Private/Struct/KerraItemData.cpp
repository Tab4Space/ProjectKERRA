#include "Struct/KerraItemData.h"

FKerraItemData::FKerraItemData()
{
}

bool FKerraItemData::IsValid() const
{
	return ItemIDTag.IsValid();
}
