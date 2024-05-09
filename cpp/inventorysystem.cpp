#include <iostream>

/* 
	24 inactive slots
	8 hotbar slots
	4 armour slots
	1 offhand slot
	bundle: allowed
*/

char types[4][16] = {"block","tool","weapon","armor"};

struct Item
{
	int bundle;
	char name[64];
	int type;
};

// Inventory Slots
class Slot
{
public:
	char name[64];
	char type[16] = "standard";
};
class Hotbar : public Slot
{
public:
	char type[16] = "hotbar";
};
class Armor: public Slot
{
public:
	char type[16] = "armor";
};
class Offhand: public Slot
{
public:
	char type[16] = "offhand";
};

void makeInventory(){
	
}

int main(int argc, char const *argv[])
{
	
	return 0;
}
