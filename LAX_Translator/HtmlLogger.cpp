#include "HtmlLogger.h"

using namespace tinyxml2;
HtmlLogger::HtmlLogger()
{
	XMLElement * html = doc.NewElement("html");
	doc.InsertFirstChild(html);

	XMLElement * head = doc.NewElement("head");
	html->InsertEndChild(head);

	XMLElement * title = doc.NewElement("title");
	title->SetText("tinyxml2 report");
	head->InsertEndChild(title);

	XMLElement * link = doc.NewElement("link");
	link->SetAttribute("rel", "stylesheet");
	link->SetAttribute("href", "stylesheet.css");
	head->InsertEndChild(link);

	XMLElement * body = doc.NewElement("body");
	body_node = body;
	html->InsertEndChild(body);
	XMLElement * paragraph = doc.NewElement("p");
	paragraph->SetText("Report");
	body->InsertEndChild(paragraph);

	current_table = doc.NewElement("table");
	current_container = doc.NewElement("div");
	current_container->SetAttribute("class", "container");
	body->InsertEndChild(current_container);
	SaveFile();
}


HtmlLogger::~HtmlLogger()
{
}

void HtmlLogger::SaveFile()
{
	XMLError eResult = doc.SaveFile("index.html");
	XMLCheckResult(eResult);
}

void HtmlLogger::AddParagraph(std::string str)
{
	XMLElement *new_par = doc.NewElement("p");
	new_par->SetText(str.c_str());
	body_node->InsertEndChild(new_par);
}

void HtmlLogger::InitNewTable()
{
	if (!current_table->NoChildren())
	{
		current_table = doc.NewElement("table");
	}
	

}
void HtmlLogger::PushToTableTop(std::string str)
{
	XMLElement * row = doc.NewElement("tr");
	XMLElement * col = doc.NewElement("td");
	col->SetText(str.c_str());
	row->InsertEndChild(col);
	current_table->InsertFirstChild(row);
}
void HtmlLogger::PushToTableBottom(std::string str)
{
	XMLElement * row = doc.NewElement("tr");
	XMLElement * col = doc.NewElement("td");
	col->SetText(str.c_str());
	row->InsertEndChild(col);
	current_table->InsertEndChild(row);
}
void HtmlLogger::AddTable()
{
	body_node->InsertEndChild(current_table);
}

void HtmlLogger::AddTableToContainer()
{
	current_container->InsertEndChild(current_table);
}

void HtmlLogger::InitNewContainer()
{
	if (!current_container->NoChildren())
	{
		current_container = doc.NewElement("div");
		current_container->SetAttribute("class", "container");
	}
}


void HtmlLogger::AddContainer()
{
	body_node->InsertEndChild(current_container);
}