#include "ArchMenu.h"

ArchMenu::ArchMenu(void){}

void ArchMenu::MainPage()
{
	bool exit = false;
	bool is_done = false;
	do{
		char choice = 0;
		std::cout << "\n"
				  << "\t|=======|MENU|=======|\n"
				  << "\t| 1. Zip             |\n"
				  << "\t| 2. UnZip           |\n"
				  << "\t| 3. Exit            |\n"
				  << "\t|====================|\n\n";
		do{
			std::cin.sync();
			std::cin.clear();
			std::cin  >> choice;
			switch(choice){
				case '1' : item_1(); is_done = true; break;
				case '2' : item_2(); is_done = true; break;
				case '3' : exit = true; is_done = true; break;
				default  : incorrect();
			}
		} while(!is_done);
		system("cls");
	} while(!exit);
}

void ArchMenu::item_1()
{
	char choice = 0;
	system("cls");
	std::cout << " 1. File input\n"
			  << " 2. Console input\n"
			  << " 3. File & coding tree input *\n"
			  << " 4. Cancel\n\n"
			  << " * if you have a written in file coding tree,\n"
			  << " you can choose <3> item\n\n";
	Archiver* Arch = nullptr;
	std::string NameOF_or_str;
	std::string NameOF_tree;
	std::string part_1_c32;
	bool is_done = false;
	bool is_done_c2 = false;
	bool is_done_c3 = false;
	int i = 0;
	do{
		std::cin.sync();
		std::cin.clear();
		std::cin >> choice;
		switch(choice){
			case '1' :	system("cls");
						std::cout << " Please, enter name of file,\n"
								  << " which you want to zip : ";
						std::cin.sync();
						std::cin.clear();
						std::getline(std::cin,NameOF_or_str);
						std::cout << " Archiving...\n";
						Arch = new Archiver(NameOF_or_str);
						std::cout << " Done! Name of file with ziped information is << " << Arch->get_Result() << " >>";
						delete Arch;
						Arch = nullptr;
						is_done = true;
						_getch(); break;

			case '2' :	system("cls");
						std::cout << " Please, enter string,\n"
								  << " which you want to zip : ";
						std::cin.sync();
						std::cin.clear();
						std::getline(std::cin,NameOF_or_str);
						std::cout << " Archiving...\n";
						Arch = new Archiver(NameOF_or_str,Console);
						std::cout << " Done! Name of file with ziped information is << " << Arch->get_Result() << " >>\n";
						std::cout << " Do you want to save string in a file? y / n \n";
						do{
							std::cin.sync();
							std::cin.clear();
							std::cin >> choice;
							switch(choice){
								case 'y' :	std::cout << " Enter name of file to save string (specify extention!) : ";
											std::cin.sync();
											std::cin.clear();
											std::getline(std::cin,NameOF_or_str);
											Arch->set_nF_tosave_str(NameOF_or_str);
											std::cout << " Done! Name of file with entered string << " << Arch->get_nF_tosave_str() << " >>";
											is_done_c2 = true;
											_getch(); break;

								case 'n' :	is_done_c2 = true; break;
								default  :	incorrect();
							}
						} while(!is_done_c2);
						delete Arch;
						Arch = nullptr;
						is_done = true; break;

			case '3' :	system("cls");
						std::cout << " Please, enter name of file,\n"
								  << " which you want to zip : ";
						std::cin.sync();
						std::cin.clear();
						std::getline(std::cin,NameOF_or_str);
						std::cout << " 1. Enter name of file with coding tree manualy\n"
								  << " 2. Automatic file search\n\n";
						do{
							std::cin.sync();
							std::cin.clear();
							std::cin >> choice;
							switch(choice){
								case '1' :	system("cls");
											std::cout << " Enter name of file with coding tree (specify extention!) : ";
											std::cin.sync();
											std::cin.clear();
											std::getline(std::cin,NameOF_tree);
											is_done_c3 = true; break;

								case '2' :	for(i = 0; NameOF_or_str[i] != '.'; i++);
											part_1_c32 = NameOF_or_str.substr(0,i);
											NameOF_tree = part_1_c32 + ".tr";
											is_done_c3 = true; break;

								default  :	incorrect();
							}
						} while(!is_done_c3);
						std::cout << " Archiving...\n";
						Arch = new Archiver(NameOF_or_str,NameOF_tree,Pack);
						std::cout << " Done! Name of file with ziped information is << " << Arch->get_Result() << " >>\n";
						delete Arch;
						Arch = nullptr;
						_getch();
						is_done = true; break;

			case '4' :	is_done = true; break;

			default  : incorrect();
		}
	} while(!is_done);
}

void ArchMenu::item_2()
{
	char choice = 0;
	system("cls");
	std::cout << " 1. File & coding tree input\n"
			  << " 2. Cancel\n\n";
	Archiver* Arch = nullptr;
	std::string NameOF, NameOF_tree;
	std::string part_1;
	bool is_done = false;
	bool is_done_c1 = false;
	int i = 0;
	do{
		std::cin.sync();
		std::cin.clear();
		std::cin >> choice;
		switch(choice){
			case '1' :	system("cls");
						std::cout << " Please, enter name of file,\n"
								  << " which you want to unzip (specify extention!) : ";
						std::cin.sync();
						std::cin.clear();
						std::getline(std::cin,NameOF);
						std::cout << " 1. Enter name of file with coding tree manualy\n"
								  << " 2. Automatic file search\n\n";
						do{
							std::cin.sync();
							std::cin.clear();
							std::cin >> choice;
							switch(choice){
								case '1' :	system("cls");
											std::cout << " Enter name of file with coding tree (specify extention!) : ";
											std::cin.sync();
											std::cin.clear();
											std::getline(std::cin,NameOF_tree);
											is_done_c1 = true;
											break;

								case '2'  :	for(i = 0; NameOF[i] != '.'; i++);
											part_1 = NameOF.substr(0,i);
											NameOF_tree = part_1 + ".tr";
											is_done_c1 = true;
											break;

								default  :	incorrect();
							}
						} while(!is_done_c1);
						is_done = true;
						std::cout << " Disarchiving...\n";
						Arch = new Archiver(NameOF,NameOF_tree,UnPack);
						std::cout << " Done! Name of file with unziped information is << " << Arch->get_Result() << " >>\n";
						delete Arch;
						Arch = nullptr;
						_getch();
						is_done = true; break;

			case '2' :	is_done = true; break;

			default  :	incorrect();
		}
	} while(!is_done);
}

void ArchMenu::incorrect()
{
	std::cin.sync();
	std::cin.clear();
	std::cout << " Incorrect item! Input again!\n";
}

ArchMenu::~ArchMenu(void){}