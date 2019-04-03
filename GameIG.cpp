#include<iostream>
#include<string>
#include <stdlib.h>
#include <time.h>

using namespace std;

bool showFlags = false;

void enterBattle(int monsterID);
bool user_attackMonster(int monsterID);
bool monster_attackUser(int monsterID);
void scanForMonsters();

int structUserCount = 0;
int structWeaponCount = 0;
int structMonsterCount = 0;

int currentMonsterID = 0;
int currentUserID = 0;

struct userCharacter
{
	string Name;
	int Health; 
	int Damage;
	int DefaultHealth;
	int DefaultDamage;
	int WeaponID;
	bool isDead;
};

struct weaponObject
{
	string weaponName;
	int weaponMaxDamage;
	int weaponMinDamage;
	int weaponID;
	bool isObtainable;
};

struct monsterCharacter
{
	string Name;
	int Damage;
	int DefaultDamage;
	int Health;
	int DefaultHealth;
	int WeaponID;
	bool isDead;
};

struct userCharacter Users[999];
struct monsterCharacter Monsters[999];

void createUser(string userName)
{
	Users[structUserCount].Name = userName;
	Users[structUserCount].Health = 100;
	Users[structUserCount].Damage = 10;
	Users[structUserCount].DefaultHealth = 100;
	Users[structUserCount].DefaultDamage = 10;
	Users[structUserCount].WeaponID = 0;
	Users[structUserCount].isDead = false;
	++structUserCount;

	if (showFlags) {
		cout << "Created User Named " << userName << "\n" << endl;
	}
}


void createMonster(string monsterName, int monsterDamage, int monsterHealth)
{
	Monsters[structMonsterCount].Name = monsterName;
	Monsters[structMonsterCount].Damage = monsterDamage;
	Monsters[structMonsterCount].Health = monsterHealth;
	Monsters[structMonsterCount].DefaultHealth = monsterHealth;
	Monsters[structMonsterCount].DefaultDamage = monsterDamage;
	Monsters[structMonsterCount].WeaponID = 0;
	Monsters[structMonsterCount].isDead = false;
	++structMonsterCount;

	if (showFlags) {
		cout << "Created Monster Named " << monsterName << endl;
		cout << "Monster Named " << monsterName << " Has monsterDamage of " << monsterDamage << endl;
		cout << "Monster Named " << monsterName << " Has monsterHealth of " << monsterHealth << endl;
	}
}

bool coinFlip(string usersChoice)
{
	int toParse = 0;
	if (usersChoice == "Heads" || usersChoice == "heads" || usersChoice == "head" || usersChoice == "Head" || usersChoice == "H" || usersChoice == "h") {
		toParse = 1;
	}
	srand(time_t(NULL));
	int randomNumber = rand() % 2;
	if (randomNumber == toParse) return true;
	return false;
}

bool resetUserStats()
{
	Users[currentUserID].isDead = false;
	Users[currentUserID].Health = Users[currentUserID].DefaultHealth;
	Users[currentUserID].Damage = Users[currentUserID].DefaultDamage;
	return true;
}

bool parseAnswers(string answer)
{
	if (answer == "YES" || answer == "yes" || answer == "Y" || answer == "y") return true;
	return false;
}

bool user_attackMonster(int monsterID)
{
	if (Users[currentUserID].isDead)
	{
		cout << "You have been defeated. " << endl;
		cin.get();
		resetUserStats();
		scanForMonsters();
		return false;
	}
	else
	{
		Monsters[monsterID].Health = Monsters[monsterID].Health - Users[currentUserID].Damage;
		if (Monsters[monsterID].Health <= 0)
		{
			Monsters[monsterID].isDead = true;
			cout << "You have defeated " << Monsters[monsterID].Name << "." << endl;
			cin.get();
			resetUserStats();
			scanForMonsters();
			return true;
		}
		else
		{
			cout << "You have damaged " << Monsters[monsterID].Name << ". Monsters Health: "<< Monsters[monsterID].Health << endl;
			cin.get();
			cout << Monsters[monsterID].Name << "'s Turn" << endl;
			monster_attackUser(monsterID);
		}
	}
	return true;
}

bool monster_attackUser(int monsterID)
{
	if (Monsters[monsterID].isDead)
	{
		cout << "You have defeated " << Monsters[monsterID].Name << "." << endl;
		cin.get();
		resetUserStats();
		scanForMonsters();
		return false;
	}
	else
	{
		Users[currentUserID].Health = Users[currentUserID].Health - Monsters[monsterID].Damage;
		if (Users[currentUserID].Health <= 0)
		{
			Users[currentUserID].isDead = true;
			cout << "You have been defeated by" << Monsters[monsterID].Name << "." << endl;
			cin.get();
			resetUserStats();
			scanForMonsters();
			return true;
		}
		else
		{
			cout << "You have been damaged " << ". Current Health: " << Users[currentUserID].Health << endl;
			cin.get();
			cout << "Its your turn." << endl;
			user_attackMonster(monsterID);
		}
	}
	return true;
}

void scanForMonsters()
{
	srand(time(NULL));
	int monsterChosen = rand() % structMonsterCount;
	string answers;
	if (Monsters[monsterChosen].isDead)
	{
		cout << "The Monster named " << Monsters[monsterChosen].Name << " Has already been defeated, would you like to re-battle him? (Y/n)" << endl;
		cin >> answers;
		if (parseAnswers(answers)) {
			enterBattle(monsterChosen);
		}
		else {
			cout << "Okay, scanning for new monsters" << endl;
			cin.get();
			scanForMonsters();
		}
	}
	else
	{
		cout << "The Monster named " << Monsters[monsterChosen].Name << " Has been selected! would you like to battle him? (Y/n)" << endl;
		cin >> answers;
		if (parseAnswers(answers)) {
			enterBattle(monsterChosen);
		}
		else {
			cout << "Okay, scanning for new monsters" << endl;
			cin.get();
			scanForMonsters();
		}
	}
}

void enterBattle(int monsterID)
{
	string answers;
	if (Monsters[monsterID].isDead) {
		Monsters[monsterID].isDead = false;
		Monsters[monsterID].Damage = Monsters[monsterID].DefaultDamage;
		Monsters[monsterID].Health = Monsters[monsterID].DefaultHealth;
	}
	cout << "Prepaired for battle!" << endl;
	cin.get();
	cout << "Heads or tails? (H/t)" << endl;
	cin >> answers;
	if (coinFlip(answers))
	{
		cout << "You start first." << endl;
		cin.get();
		user_attackMonster(monsterID);
	}
	else
	{
		cout << Monsters[monsterID].Name << " starts first." << endl;
		cin.get();
		monster_attackUser(monsterID);
	}


}

void main()
{
	createUser("U_M9");
	createMonster("Harry Potter", 8, 100);
	createMonster("Harry's Father", 8, 120);
	createMonster("Mr Thompson", 8, 100);

	cout << "Press enter to start" << endl;
	cin.get();
	scanForMonsters();
}
