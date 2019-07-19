#include "CodingTree.h"

bool Branch_ptr_compare::operator () (const Branch* l, const Branch* r) const
{
	return *l > *r;
}

Branch::Branch()
{
	let = 0;
	freq = 0;
	lb_0 = nullptr;
	rb_1 = nullptr;
}

bool Branch::operator > (const Branch& b) const
{
	return freq > b.freq;
}

bool Branch::operator < (const Branch& b) const
{
	return freq < b.freq;
}

Branch::~Branch(){}

Code::Code()
{
	let = 0;
	code = 0;
	length = 0;
}

bool Code::operator < (const Code& c) const
{
	return let < c.let;
}

bool Code::operator > (const Code& c) const
{
	return let > c.let;
}

bool Code::operator == (const Code& c) const
{
	return let == c.let;
}

Code::~Code(){}

CodingTree::CodingTree(const std::string& s, inpoutp m)
{
	Mode = m;
	root = nullptr;
	if(Mode == File) Name_of_File_for_reading = s;
	else s_for_reading = s;
	Symb_Freq = new int[256];
	for(int i = 0; i < 256; i++) Symb_Freq[i] = 0;
	length_of_information = 0;
	num_of_ch = 0;
	Create_Coding_Tree();
	delete [] Symb_Freq;
	Coding_Table = new Code[num_of_ch];
	int index = 0;
	Create_Coding_Table(root,0,0,index);
	std::sort(Coding_Table, Coding_Table + num_of_ch);
}

CodingTree::CodingTree(const std::string& name_fText, const std::string& name_fTree)
{
	Mode = File;
	Name_of_File_for_reading = name_fText;
	Name_of_File_for_recording_Tree = name_fTree;
	root = nullptr;
	Symb_Freq = nullptr;
	num_of_ch = 0;
	readCreate_Tree();
	int index = 0;
	Coding_Table = new Code[num_of_ch];
	Create_Coding_Table(root,0,0,index);
	std::sort(Coding_Table, Coding_Table + num_of_ch);
}

CodingTree::CodingTree(const CodingTree& CdTr)
{
	Mode = CdTr.Mode;
	Name_of_File_for_reading = CdTr.Name_of_File_for_reading;
	Name_of_File_for_recording_Tree = CdTr.Name_of_File_for_recording_Tree;
	s_for_reading = CdTr.s_for_reading;
	length_of_information = CdTr.length_of_information;
	num_of_ch = 0;
	root = nullptr;
	Symb_Freq = nullptr;
	readCreate_Tree();
	Coding_Table = new Code[num_of_ch];
	int index = 0;
	Create_Coding_Table(root,0,0,index);
	std::sort(Coding_Table, Coding_Table + num_of_ch);
	int i = 0;
	for(; Name_of_File_for_recording_Tree[i] != '.'; i++);
	std::string part_1;
	part_1 = Name_of_File_for_recording_Tree.substr(0,i);
	Name_of_File_for_recording_Tree = part_1 + "(copy).tr";
	std::ofstream fout(Name_of_File_for_recording_Tree,std::ios::app);
	for(int j = 0; j < num_of_ch; j++){
		if(!fout.tellp()) fout << Coding_Table[j].let << ' ' << Coding_Table[j].freq;
		else fout << std::endl << Coding_Table[j].let << ' ' << Coding_Table[j].freq;
	}
	fout.close();
}

CodingTree& CodingTree::operator = (const CodingTree& CdTr)
{
	Delete_Tree(root);
	delete [] Coding_Table;
	delete [] Symb_Freq;
	Symb_Freq = nullptr;
	Coding_Table = nullptr;
	Mode = CdTr.Mode;
	Name_of_File_for_reading = CdTr.Name_of_File_for_reading;
	Name_of_File_for_recording_Tree = CdTr.Name_of_File_for_recording_Tree;
	s_for_reading = CdTr.s_for_reading;
	length_of_information = CdTr.length_of_information;
	num_of_ch = 0;
	root = nullptr;
	readCreate_Tree();
	Coding_Table = new Code[num_of_ch];
	int index = 0;
	Create_Coding_Table(root,0,0,index);
	std::sort(Coding_Table, Coding_Table + num_of_ch);
	int i = 0;
	for(; Name_of_File_for_recording_Tree[i] != '.'; i++);
	std::string part_1;
	part_1 = Name_of_File_for_recording_Tree.substr(0,i);
	Name_of_File_for_recording_Tree = part_1 + "(copy).tr";
	std::ofstream fout(Name_of_File_for_recording_Tree,std::ios::app);
	for(int j = 0; j < num_of_ch; j++){
		if(!fout.tellp()) fout << Coding_Table[j].let << ' ' << Coding_Table[j].freq;
		else fout << std::endl << Coding_Table[j].let << ' ' << Coding_Table[j].freq;
	}
	fout.close();
	return *this;
}

void CodingTree::sfor_rd_record_inF()
{
	std::ofstream fout(Name_of_File_for_reading);
	fout << s_for_reading;
	fout.close();
}

void CodingTree::Couting_Symb_Freq()
{
	if(Mode == File){
		std::ifstream fin(Name_of_File_for_reading);
		char c = 0;
		while(fin.get(c)){
			Symb_Freq[static_cast<size_t>(c)]++;
			length_of_information++;
		}
		fin.close();
	} else {
		for(int i = 0; s_for_reading[i]; i++){
			Symb_Freq[s_for_reading[i]]++;
			length_of_information++;
		}
	}
}

void CodingTree::Create_Coding_Tree()
{
	Couting_Symb_Freq();
	std::string part_1;
	if(Mode == File){
		int i = 0;
		if(Name_of_File_for_reading.find('.') != std::string::npos){
			for(; Name_of_File_for_reading[i] != '.'; i++);
			part_1 = Name_of_File_for_reading.substr(0,i);
		} else part_1 = Name_of_File_for_reading;
	} else for(int i = 0; i < 6; i++) part_1.push_back(s_for_reading[i]);
	Name_of_File_for_recording_Tree = part_1 + ".tr";
	std::ofstream fout(Name_of_File_for_recording_Tree,std::ios::app);
	std::priority_queue<Branch*,std::vector<Branch*>,Branch_ptr_compare> Nodes;
	for(int i = 0; i < 256; i++){
		if(Symb_Freq[i]){
			Branch* nd = new Branch;
			nd->let = i;
			nd->freq = Symb_Freq[i];
			nd->lb_0 = nullptr;
			nd->rb_1 = nullptr;
			if(!fout.tellp()) fout << nd->let << ' ' << nd->freq;
			else  fout << std::endl << nd->let << ' ' << nd->freq;
			Nodes.emplace(nd);
			num_of_ch++;
		}
	}
	fout.close();
	while(Nodes.size() > 1){
		Branch* nd = new Branch;
		nd->let = -1;
		nd->lb_0 = Nodes.top();
		Nodes.pop();
		nd->rb_1 = Nodes.top();
		Nodes.pop();
		nd->freq = nd->lb_0->freq + nd->rb_1->freq;
		Nodes.emplace(nd);
	}
	root = Nodes.top();
	Nodes.pop();
}

void CodingTree::readCreate_Tree()
{
	std::ifstream fin(Name_of_File_for_recording_Tree);
	std::priority_queue<Branch*,std::vector<Branch*>,Branch_ptr_compare> Nodes;
	Branch* nd = new Branch;
	while(fin >> nd->let >> nd->freq){
		nd->lb_0 = nullptr;
		nd->rb_1 = nullptr;
		Nodes.emplace(nd);
		num_of_ch++;
		nd = new Branch;
	}
	delete nd;
	while(Nodes.size() > 1){
		Branch* nd = new Branch;
		nd->let = -1;
		nd->lb_0 = Nodes.top();
		Nodes.pop();
		nd->rb_1 = Nodes.top();
		Nodes.pop();
		nd->freq = nd->lb_0->freq + nd->rb_1->freq;
		Nodes.emplace(nd);
	}
	root = Nodes.top();
	Nodes.pop();
	fin.close();
}

void CodingTree::Create_Coding_Table(const Branch* tr, unsigned int code, int len, int& i) /////////////////////////
{
	if(tr->let != -1){
		int move = 32 - len;
		Coding_Table[i].let = tr->let;
		Coding_Table[i].length = len;
		Coding_Table[i].freq = tr->freq;
		Coding_Table[i].code = code >> move;
		i++;
	} else { 
		code >>= 1;
		len++;
		Create_Coding_Table(tr->lb_0,code,len,i);
		Create_Coding_Table(tr->rb_1,code | 0x80000000,len,i);
	}
}

void CodingTree::Delete_Tree(Branch* &tr)
{
	if(tr) Delete_Tree(tr->lb_0);
	if(tr) Delete_Tree(tr->rb_1);
	delete tr;
	tr = nullptr;
}

void CodingTree::set_svstr_nF(const std::string& nF_sv)
{
	Name_of_File_for_reading = nF_sv;
	sfor_rd_record_inF();
}

std::string CodingTree::get_record_nF()
{
	return Name_of_File_for_recording_Tree;
}

std::string CodingTree::get_read_nF()
{
	return Name_of_File_for_reading;
}

std::string CodingTree::get_Sfor_reading()
{
	return s_for_reading;
}

int CodingTree::get_length_inf()
{
	return length_of_information;
}

int CodingTree::get_numb_ch()
{
	return num_of_ch;
}

inpoutp CodingTree::get_Mode()
{
	return Mode;
}

Code* CodingTree::get_CTable()
{
	return Coding_Table;
}

Branch* CodingTree::get_CTree()
{
	return root;
}

CodingTree::~CodingTree()
{
	Delete_Tree(root);
	delete [] Coding_Table;
}