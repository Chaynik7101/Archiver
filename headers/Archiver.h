#pragma once
#include "Bits.h"
#include <iostream>

class Archiver
{
	private:
		CodingTree* Tree;
		unsigned char* buffer;
		packun Mode;
		std::string Zip();
		std::string unZip();
	public:
		Archiver(const std::string&,const inpoutp m = File);
		Archiver(const std::string&,const std::string&,const packun);
		packun get_Mode();
		std::string get_Result();
		void set_nF_tosave_str(const std::string&);
		std::string get_nF_tosave_str();
		~Archiver(void);
};