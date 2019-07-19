#include "Archiver.h"

Archiver::Archiver(const std::string& NFstr, const inpoutp m)
{
	Mode = Pack;
	Tree = new CodingTree(NFstr,m);
	buffer = new unsigned char[100];
}

Archiver::Archiver(const std::string& name_fText, const std::string& name_fTree, const packun pn)
{
	Mode = pn;
	Tree = new CodingTree(name_fText,name_fTree);
	buffer = new unsigned char[100];
}

std::string Archiver::Zip()
{
	if(Tree->get_Mode() == Console){
		std::string pack_str = Tree->get_Sfor_reading();
		Bits b(pack_str);
		Code inCh;
		for(int i = 0; i < pack_str.size(); i++){
			inCh.let = pack_str[i];
			Code* find = b.binsch_code(Tree->get_CTable(),0,Tree->get_numb_ch()-1,inCh);
			if(find) b.Record_char(*find);
		}
		b.Record_lastCh();
		return b.get_res_nF();
	} else {
		std::ifstream fin(Tree->get_read_nF());
		Code inCh;
		Bits b(Tree->get_read_nF(),Pack);
		char c = 0;
		while(fin.get(c)){
			inCh.let = static_cast<size_t>(c);
			Code* find = b.binsch_code(Tree->get_CTable(),0,Tree->get_numb_ch()-1,inCh);
			if(find) b.Record_char(*find); // Codes with negative numbers can not be read
		}
		fin.close();
		b.Record_lastCh();
		return b.get_res_nF();
	}
}

std::string Archiver::unZip()
{
	std::ifstream fin(Tree->get_read_nF(),std::ios::binary);
	fin.seekg(0,std::ios::end);
	const int file_size = fin.tellg();
	fin.seekg(0,std::ios::beg);
	Bits b(Tree->get_read_nF(),UnPack);
	bool is_done = false;
	while(!is_done && fin.read(reinterpret_cast<char*>(buffer),(file_size - b.get_pos_inF() > 100) ? 100 : file_size - b.get_pos_inF())){
		is_done = b.Record_char(Tree->get_CTree(),buffer,file_size);
	}
	int debug_pos = b.get_pos_inF();
	fin.close();
	return b.get_res_nF();
}

std::string Archiver::get_Result()
{
	if(Mode == Pack) return Zip();
	else return unZip();
}

packun Archiver::get_Mode()
{
	return Mode;
}

void Archiver::set_nF_tosave_str(const std::string& NoF)
{
	Tree->set_svstr_nF(NoF);
}

std::string Archiver::get_nF_tosave_str()
{
	return Tree->get_read_nF();
}

Archiver::~Archiver()
{
	delete Tree;
	delete [] buffer;
}