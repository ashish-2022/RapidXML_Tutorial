#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml-1.13/rapidxml.hpp"

using namespace rapidxml;
using namespace std;

int main(void)
{
  cout << "Parsing ElementStore..." << endl;
  xml_document<> doc;
  xml_node<> * root_node;
  // Read the xml file into a vector
  ifstream theFile ("ElementStore.xml");
  vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
  buffer.push_back('\0');
  // Parse the buffer using the xml file parsing library into doc 
  doc.parse<0>(&buffer[0]);
  // Find our root node
  root_node = doc.first_node("ElementStore");
  // Iterate over the Elements
  for (xml_node<> * element_node = root_node->first_node("Element"); element_node; element_node = element_node->next_sibling())
  {
    cout << "Element:" << endl;
    cout << "Type:" << element_node->first_attribute("type")->value() << endl;
    cout << "Model:" << element_node->first_attribute("model")->value() << endl;
    // Interate over the subElements
    for(xml_node<> * subElement_node = element_node->first_node("SubElement"); subElement_node; subElement_node = subElement_node->next_sibling())
    {
      cout << "Category: " << subElement_node->first_attribute("category")->value() << endl;
      cout << "Node Value: " << subElement_node->value() << endl;
    }
    cout << endl;
  }
}

