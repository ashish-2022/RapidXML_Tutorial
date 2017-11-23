
all:
	g++ Read_XML.cpp -o  Read_XML.o
	g++ Add_XML_Node.cpp -o Add_XML_Node.o
	g++ Delete_XML_Node.cpp -o Delete_XML_Node.o
	g++ Update_XML_Node.cpp -o Update_XML_Node.o

clean:
	rm -f *.o
	rm -f xml_file_add.xml xml_file_delete.xml xml_file_update.xml

