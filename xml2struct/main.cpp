#include "pugixml.hpp"
#include "LuckyDrawMeta.hpp"


#include <iostream>
#include <stdio.h>
#include <vector>
#include <utility>
#include <string>
#include <fstream>


namespace
{
	std::vector<std::string> stAllCfg;
}


int GenProto(std::string& strFilename)
{
	pugi::xml_document doc;
	
	if(!doc.load_file(strFilename.c_str())) return -1;

	pugi::xml_node stPackage = doc.child("metalib");
	pugi::xml_node stStruct = doc.child("metalib").child("struct");
	

	std::string strResult;
	
	strResult.append("#include \"pugixml.hpp\"\n#include <stdint.h>\n\n");
	strResult.append("struct ");
	strResult.append(stPackage.attribute("name").value());
	strResult.append(" {\n");

	for(pugi::xml_node_iterator it = stStruct.begin(); it != stStruct.end(); ++it)
	{
		char st[64];
		if(it->attribute("type").value() == std::string("string"))
		{
			snprintf(st, sizeof(st), "    std::%s %s;  //%s \n", 
						it->attribute("type").value(), 
						it->attribute("name").value(), 
						it->attribute("desc").value());
	
		}
		else if(it->attribute("type").value() == std::string("float"))
		{
			snprintf(st, sizeof(st), "    %s %s;  //%s \n", 
						it->attribute("type").value(), 
						it->attribute("name").value(), 
						it->attribute("desc").value());

		}
		else
			snprintf(st, sizeof(st), "    %s_t %s;  //%s \n", 
						it->attribute("type").value(), 
						it->attribute("name").value(), 
						it->attribute("desc").value());
		strResult.append(st);
	}

	strResult.append("\n    ");
	strResult.append(stPackage.attribute("name").value());
	strResult.append("()\n    {\n\n        pugi::xml_document doc;\n");

	char st[64];
	snprintf(st, sizeof(st), "        if(!doc.load_file(\"%s.xml\")) exit(-1);", stPackage.attribute("name").value());
	strResult.append(st);

	char st2[128];
	snprintf(st2, sizeof(st2), "\n        pugi::xml_node stStructs = doc.child(\"%s\");", stPackage.attribute("name").value());
	strResult.append(st2);
	
	strResult.append("\n        for(pugi::xml_node_iterator it = stStructs.begin(); it != stStructs.end(); ++it)\n        {\n");
	
	for(pugi::xml_node_iterator it = stStruct.begin(); it != stStruct.end(); ++it)
	{
		char st[128];
		
		if(it->attribute("type").value() == std::string("uint32"))
			snprintf(st, sizeof(st), "               %s = static_cast<uint32_t>(atoi(it->attribute(\"%s\").value()));\n", 
						it->attribute("name").value(), it->attribute("name").value());
		else if(it->attribute("type").value() == std::string("float"))
			snprintf(st, sizeof(st), "               %s = atof(it->attribute(\"%s\").value());\n", 
						it->attribute("name").value(), it->attribute("name").value());
		else
			snprintf(st, sizeof(st), "               %s = it->attribute(\"%s\").value();\n", 
						it->attribute("name").value(), it->attribute("name").value());


		strResult.append(st);
	}


	
	
	strResult.append("\n        }\n    }\n");
	strResult.append("};\n");

	//std::ofstream stOf;
	//stOf.open();

	std::cout<<strResult<<std::endl;
	stAllCfg.push_back(std::move(strResult));
	return 0;
}


void WriteToFile(std::string& strFilename)
{
	std::ofstream stOf;
	stOf.open(strFilename, std::ios::out|std::ios::trunc);
	stOf<<stAllCfg[0];
}

int main()
{
	std::string strFilename("LuckyDrawMeta.xml");
	std::string strOFilename("LuckyDrawMeta.hpp");
	GenProto(strFilename);
	WriteToFile(strOFilename);


	//test
	//LuckyDraw ld;

	//std::cout<<ld.PrizeName<<std::endl;
	
}


