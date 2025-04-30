#include "Struct/KerraItemInfo.h"

FKerraItemInfo::FKerraItemInfo()
{
}

bool FKerraItemInfo::IsValid() const
{
	return ItemIDTag.IsValid();
}
