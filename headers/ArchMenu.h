#pragma once
#include "Archiver.h"
#include <conio.h>

class ArchMenu
{
	private:
		void item_1();
		void item_2();
		void incorrect();
	public:
		ArchMenu(void);
		void MainPage();
		~ArchMenu(void);
};