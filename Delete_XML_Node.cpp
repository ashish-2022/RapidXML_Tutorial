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

  // Delete the node
  xml_node<> * element_node = root_node->first_node("Element");
  root_node->remove_node(element_node); 

  // Save new XML in new file
  std::ofstream file_stored("xml_file_delete.xml");
  file_stored << "<?xml version=\"1.0\" encoding=\"utf-8\"?>" << std::endl;
  file_stored << doc;
  file_stored.close();
  doc.clear();

  std::cout << doc;
  return EXIT_SUCCESS;
}

