#include <string>
#include <fstream>
#include "OpenGUI_Exception.h"
#include "OpenGUI_GenericResourceProvider.h"

namespace OpenGUI{
	//#####################################################################
	void GenericResourceProvider::loadResource(const std::string& filename, Resource& output)
	{
		if(filename.empty() || filename == ""){
			throw Exception("GenericResourceProvider::loadResource(): No filename provided");
		}
		std::ifstream inputFile(filename.c_str(), std::ios::binary|std::ios::ate);

		if(inputFile.fail()){
			throw Exception("GenericResourceProvider::loadResource(): File not found: '" + filename + "'");
		}
		std::streampos size = inputFile.tellg();
		inputFile.seekg(0,std::ios::beg);

		unsigned char* buffer = new unsigned char[size];

		try{
			inputFile.read((char*)buffer,size);
		}catch(std::ifstream::failure ex){
			delete[] buffer;
			throw Exception("GenericResourceProvider::loadResource(): Error reading file: '" + filename + "'");
		}
		inputFile.close();
		output.setData(buffer);
		output.setSize(size);
	}
	//#####################################################################
	void GenericResourceProvider::unloadResource(Resource& resource)
	{
		/*
			Not that we have to do this, since Resource can take care of itself,
			but we might as well pretend to be good neighbors
		*/
		resource.release();
	}
	//#####################################################################
};//namespace OpenGUI{