#include "stdafx.h"
#include "GlobalOptions.h"

GlobalOptions& GlobalOptions::Get()
{
	static GlobalOptions sGlobalOptions;
	return sGlobalOptions;
}

GlobalOptions::GlobalOptions()
{
}
