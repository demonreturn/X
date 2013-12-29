

#include "EXLogFile.h"
#include "EXTypeDefine.h"

#include <iostream>
#include <string>

int main()
{
	std::string str = "0123456789\n";
	bool bret = CEXLogFile::Instance()->Write( str.c_str(), str.length() );

	if ( bret )
	{
		int counter = 10;
		while (counter-- > 0 )
		{
			CEXLogFile::Instance()->Write( str.c_str(), str.length() );
		}
	}

	return 0;
}

