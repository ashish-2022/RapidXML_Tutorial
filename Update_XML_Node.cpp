#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "rapidxml-1.13/rapidxml.hpp"

#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using namespace rapidxml;

void setStringAttribute(
    xml_document<>& doc, xml_node<>* node,
    const string& attributeName, const string& attributeValue)
{
  // allocate memory assigned to document for attribute value
  char* rapidAttributeValue = doc.allocate_string(attributeValue.c_str());
  // search for the attribute at the given node
  xml_attribute<>* attr = node->first_attribute(attributeName.c_str());
  if (attr != 0) { // attribute already exists
    // only change value of existing attribute
    attr->value(rapidAttributeValue);
  } else { // attribute does not exist
    // allocate memory assigned to document for attribute name
    char* rapidAttributeName = doc.allocate_string(attributeName.c_str());
    // create new a new attribute with the given name and value
    attr = doc.allocate_attribute(rapidAttributeName, rapidAttributeValue);
    // append attribute to node
    node->append_attribute(attr);
  }
}

int main(int argc, char *argv[])
{      
  std::cout << "Parsing ElementStore..." << std::endl;
  xml_document<> doc;
  xml_node<> * root_node;
  // Read the xml file into a vector
  std::ifstream theFile ("ElementStore.xml");
  std::vector<char> buffer((std::istreambuf_iterator<char>(theFile)), std::istreambuf_iterator<char>());
  buffer.push_back('\0');
  // Parse the buffer using the xml file parsing library into doc 
  doc.parse<0>(&buffer[0]);
  // Find our root node
  root_node = doc.first_node("ElementStore");

  // Change node under root
  xml_node<> * change_node = root_node->first_node("Element");

  setStringAttribute(doc, change_node, "type", "Type Update");
  setStringAttribute(doc, change_node, "model", "Model Update");

  // Save new XML in new file
  std::ofstream file_stored("xml_file_update.xml");
  file_stored << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << std::endl;
  file_stored << doc;
  file_stored.close();
  doc.clear();

  std::cout << doc;
  return EXIT_SUCCESS;
}

