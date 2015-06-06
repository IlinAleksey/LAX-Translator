#pragma once
#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); }
#endif
#include "tinyxml2.h"
#include <iostream>
class HtmlLogger
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode* body_node;
	tinyxml2::XMLNode* current_table;
	tinyxml2::XMLElement* current_container;
public:

	void SaveFile();

	void InitNewTable();
	void PushToTableTop(std::string str);
	void PushToTableBottom(std::string str);
	void AddTable();

	void AddParagraph(std::string str);

	void InitNewContainer();
	void AddTableToContainer();
	void AddContainer();
	HtmlLogger();
	~HtmlLogger();
};

