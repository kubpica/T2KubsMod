//host
#include <windows.h>
#include <detours.h>
#pragma comment (lib, "detours.lib")
#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>
#include <list>
#include <Winbase.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <algorithm>
#include <chrono>
#include <thread>
#include <future>
#include <vector>
#include <fstream>
#include <cmath>
#include "md5.h"
#ifdef _DEBUG
# define Debug(fmtstr, ...) printf(fmtstr, ##__VA_ARGS__)
#else
# define Debug(fmtstr, ...)
#endif

using namespace std;

//#define ADDRESS 0x48AE90    //This is the address where our targeted function begins
#define ADDRESS 0x48A7A0 //48A7A0 
string comand;
string dataPath;
//fstream accounts;
list<string> polecenia;
int playersid = 0;
int playersCount = 0;
int observingCount = 0;
int waiting4gameCount = 0;
int ingameCount = 0;
int myid = 99; //-1
//map<pair<int,int>, int> observed;
map<pair<int, int>, int> readed;
map<pair<int,int>, float> event;
map<pair<int, int>, float> eventf;
list<pair<string, int>> commands;
map<int, string> players; //map<string, int> players;
map<int, string> playerslogin;
map<int, string> playerstid;
map<int, int> pid_iloscKomend;
map<int, bool> pid_czyVoice;
map<int, int> pid_status;
bool czy_sprawdzanie_voice = false;
bool czy_wyslane_join = false;
bool blocked = false;
bool czyWystartowano = false;
std::vector < int > waiting4game;
std::vector < string > killStrings;
//map<pair<int,int>, int>::iterator it;
list<string> dowyslania;
char charek;
std::list<string>::iterator iter;
char * writable;
byte dataz[] = {0x00, 0x10, 0xFF, 0xFF};
//DWORD hackBaseAddress = {0x00000000};
DWORD hackOffsets[] = {0x3d};
HMODULE hModule = GetModuleHandle(NULL);
DWORD baseAddress = (DWORD)hModule + 0x00778550;

//ZOMBIES:
//int fazagry = 0;

int (__cdecl* originalFunction)(const char *text); //Pointer to the function we are going to hook, must be declared same as original(returns double and takes double as argument)
int (__cdecl* wysylaniehook)(char *text); //int __cdecl sub_4C3250(char *);
int (__cdecl* wysylaniehook2)(int text1, int text2); //int __cdecl sub_48FC40(int, int)
int (__cdecl* wysylaniehook3)(char *text1, int text2); //int __cdecl sub_4C30E0(char *, int);
int (__cdecl* wysylaniehook4)(char *text1, char *text2); //int __cdecl sub_4A44D0(int, int)
int (__cdecl* wysylaniehook5)(char *text); //int __cdecl sub_48A7A0(int)
int (__cdecl* wysylaniehook6)(char *text); //int __cdecl sub_4A3140(int)
int (__cdecl* wysylaniehook7)(char *text); //int __cdecl sub_471A30(int)
int (__cdecl* wysylaniehook8)(char *text1, char *text2); //int __cdecl sub_4C9DC0(int, int)
int(__cdecl* SpectJoinHook)(int int1, int int2); //int __cdecl sub_485B00(int, int)
int(__cdecl* startowaniehook)(); //int sub_4C0310()
int(__cdecl* strzal)(int var1, int var2); //int __cdecl sub_419260(float, float)
int(__cdecl* damage)(int var1, int var2, int *var3, int *var4, int *var5); //int __cdecl sub_488000(int, int, int, int, int) damage
int(__cdecl* indamage1)(int var1, int var2, int var3); //int __cdecl sub_419220(int, int, int) indamage1
/*int(__cdecl* levelchangeHook)(int *int1, int* int2, int int3, int int4); //int __cdecl sub_4C4D30(int, int, int, int)
int(__cdecl* levelchangeHook2)(int int1, int int2); //int __cdecl sub_4858E0(int, int)
int(__cdecl* levelchangeHook3)(int int1); //int __cdecl sub_48A7A0(int)
int(__cdecl* wysylanieKomendyHook)(char* char1, float* int1); //int __cdecl sub_4C30E0(char *, int);
int(__cdecl* wysylanieKomendyHook2)(int int1, int int2); //int __cdecl sub_4A44D0(int, int)
//int __cdecl sub_4A44D0(int, int)*/



//int __cdecl sub_4C9DC0(int, int)
//int __cdecl sub_471A30(int)
//int sub_482220()
//int __cdecl sub_4C30E0(char *, int);
//int __cdecl sub_4C3250(char *);
//int __cdecl sub_48A7A0(int)
//int __cdecl sub_4A44D0(int, int)
//int __cdecl sub_4A3140(int)
//int __cdecl sub_4A1ED0(int, int, int, int)
//int sub_4A4C50()

typedef void (__cdecl* wysylanie_)(char *text);
wysylanie_ wysylanie = (wysylanie_)0x4C3250; //0x4A4C30   

void WriteToMemory(DWORD addressToWrite, char* valueToWrite, int byteNum)
{
    //used to change our file access type, stores the old
    //access type and restores it after memory is written
    unsigned long OldProtection;
    //give that address read and write permissions and store the old permissions at oldProtection
    VirtualProtect((LPVOID)(addressToWrite), byteNum, PAGE_EXECUTE_READWRITE, &OldProtection);
              
    //write the memory into the program and overwrite previous value
    memcpy( (LPVOID)addressToWrite, valueToWrite, byteNum);
 
    //reset the permissions of the address back to oldProtection after writting memory
    VirtualProtect((LPVOID)(addressToWrite), byteNum, OldProtection, NULL);
}
 
DWORD FindDmaAddy(int PointerLevel, DWORD Offsets[], DWORD BaseAddress)
{
    //DEFINES OUR ADDRESS to write to
    //if statements are crucial to make sure that the address is valid to write
    //otherwise we crash. Address will not be valid when things like map changes or game loads are happening
    DWORD Ptr = *(DWORD*)(BaseAddress); //Base Address
    if(Ptr == 0) return NULL;//prevent crash
 
    //this is done to allow us to have pointers up to many levels e.g.10
    for(int i = 0; i < PointerLevel; i ++)
    {
        //if it = PointerLevel-1 then it reached the last element of the array
        //therefore check if that address plus the offset is valid and leave the loop
        if(i == PointerLevel-1)
        {
            //!!make sure the last address doesnt have the asterisk on DWORD otherwise incoming crash
            Ptr = (DWORD)(Ptr+Offsets[i]);  //Add the final offset to the pointer
            if(Ptr == 0) return NULL;//prevent crash
            //we here return early because when it hits the last element
            //we want to leave the loop, specially adapted for offsets of 1
            return Ptr;
        }
        else
        {
            //if its just a normal offset then add it to the address
            Ptr = *(DWORD*)(Ptr+Offsets[i]); //Add the offsets
            if(Ptr == 0) return NULL;//prevent crash
        }
    }
    return Ptr;
}

void wyslij(string bigos)
{
	if (blocked) return;
	//max 199 zankow mozna wyslac
	//cout << "wysylanie: " << bigos << endl;
	if (bigos.find(" \x4/") == 0) //czy znaleziono komende
	{
		std::stringstream ss;
		int id = atoi(bigos.substr(3).c_str());
		ss.str("");
		if (bigos.find("rdy") != std::string::npos || bigos.find("joined ") != std::string::npos || bigos.find("setCount ") != std::string::npos || id == 0 || id == 99) {
			ss << bigos << " salt";
		}
		else {
			pid_iloscKomend[id]++;
			//cout << "pid_iloscKomend[" << id << "]: " << pid_iloscKomend[id] << endl;
			ss << bigos << " salt" << pid_iloscKomend[id];
		}
		string bigosmd5 = ss.str();
		//cout << "bigosmd5 przed hashowaniem: " << bigosmd5 << endl;
		bigosmd5 = md5(bigosmd5);
		bigosmd5 = " h;" + bigosmd5;
		bigos += bigosmd5;
	}
	dowyslania.push_back(bigos); //if(!blocked) 
}

string zeranumer(int value, int digits = 2){ //const char *
    std::string result;
    while (digits-- > 0) {
        result += ('0' + value % 10);
        value /= 10;
    }
    std::reverse(result.begin(), result.end());
	return result;
    //return result.c_str();
}

void sprawdzVoice(){
	//cout << "przed poczekaniem" << endl;
	//std::this_thread::sleep_for( std::chrono::seconds{20} );
	//Sleep(20000);
	//cout << "po poczekaniu" << endl;
	for(auto it = pid_czyVoice.cbegin(); it != pid_czyVoice.cend();){
		if(pid_czyVoice[it->first] == false){
			cout << "Player number " << it->first << " has disconnected." << endl;
			int status = pid_status[it->first];
			if (status == 0) observingCount--;
			else if (status == 1) waiting4gameCount--;
			else if (status == 2) ingameCount--;
			pid_status.erase(it->first);
			players.erase(it->first);
			playerslogin.erase(it->first);
			pid_iloscKomend.erase(it->first);
			it = pid_czyVoice.erase(it);
			playersCount--;
			wyslij(" \x4/00 rdy");
		} else ++it;
	}
	czy_sprawdzanie_voice = false;
}

void zmienilStatus(int z, int na, int id) { //dla pluginow
	//0=observing, 1=waiting4game, 2=ingame
	if (na == 0) {
		//////////////////////// ZOMBIES vvvv
		/*ss.str("");
		ss << " \x4/" << dec << zeranumer(id) << " rfreeze 0x106D1C94";
		wyslij(ss.str());
		ss.str("");
		ss << " \x4/" << dec << zeranumer(id) << " rfreeze 0x106D1770";
		wyslij(ss.str());
		ss.str("");
		ss << " \x4/" << dec << zeranumer(id) << " rfreeze 0x106D1D8C";
		wyslij(ss.str());
		ss.str("");
		ss << " \x4/" << dec << zeranumer(id) << " robserve 0x106D1394";
		wyslij(ss.str());
		ss.str("");
		ss << " \x4/" << dec << zeranumer(id) << " rfreeze 0x005D5A60";
		wyslij(ss.str());
		ss.str("");
		ss << " \x4/" << dec << zeranumer(id) << " write i 0x005D5A60 0"; //blacout
		wyslij(ss.str());
		ss.str("");
		ss << " \x4/" << dec << zeranumer(id) << " rfreeze 0x00AD02EC"; //set666
		wyslij(ss.str());
		ss.str("");
		ss << " \x4/" << dec << zeranumer(id) << " rfreeze 0x00AD0478";
		wyslij(ss.str());
		ss.str("");
		ss << " \x4/" << dec << zeranumer(id) << " rfreeze 0x106D25A4"; //kolor
		wyslij(ss.str());
		ss.str("");
		ss << " \x4/" << dec << zeranumer(id) << " write i 0x00AD02EC 0";
		wyslij(ss.str());
		ss.str("");
		ss << " \x4/" << dec << zeranumer(id) << " write i 0x106D1D8C 4";
		wyslij(ss.str());
		ss.str("");
		ss << " \x4/" << dec << zeranumer(id) << " unblspect";
		wyslij(ss.str());*/
		///////////////////////// ZOMBIES ^^^^
	}
}

/*void heMissedCommand(int id) { //dlaPluginow
	ss.str("");
	ss << " \x4/" << dec << zeranumer(id) << " forcespect 0 1 Temporarily lost connection";
	wyslij(ss.str());
	//////////////////////// ZOMBIES vvvv
	/*ss.str("");
	ss << " \x4/" << dec << zeranumer(id) << " rfreeze 0x106D1C94";
	wyslij(ss.str());
	ss.str("");
	ss << " \x4/" << dec << zeranumer(id) << " rfreeze 0x106D1770";
	wyslij(ss.str());
	ss.str("");
	ss << " \x4/" << dec << zeranumer(id) << " rfreeze 0x106D1D8C";
	wyslij(ss.str());
	ss.str("");
	ss << " \x4/" << dec << zeranumer(id) << " robserve 0x106D1394";
	wyslij(ss.str());
	ss.str("");
	ss << " \x4/" << dec << zeranumer(id) << " rfreeze 0x005D5A60";
	wyslij(ss.str());
	ss.str("");
	ss << " \x4/" << dec << zeranumer(id) << " write i 0x005D5A60 0"; //blacout
	wyslij(ss.str());
	ss.str("");
	ss << " \x4/" << dec << zeranumer(id) << " rfreeze 0x00AD02EC"; //set666
	wyslij(ss.str());
	ss.str("");
	ss << " \x4/" << dec << zeranumer(id) << " rfreeze 0x00AD0478";
	wyslij(ss.str());
	ss.str("");
	ss << " \x4/" << dec << zeranumer(id) << " rfreeze 0x106D25A4"; //kolor
	wyslij(ss.str());
	ss.str("");
	ss << " \x4/" << dec << zeranumer(id) << " write i 0x00AD02EC 0";
	wyslij(ss.str());
	ss.str("");
	ss << " \x4/" << dec << zeranumer(id) << " write i 0x106D1D8C 4";
	wyslij(ss.str());
	ss.str("");
	ss << " \x4/" << dec << zeranumer(id) << " unblspect";
	wyslij(ss.str()); /
	///////////////////////// ZOMBIES ^^^^
	ss.str("");
	ss << " \x4/" << dec << zeranumer(id) << " forcespect 1 1 Temporarily lost connection. Joining...";
	wyslij(ss.str());
	string nick = players[id];
	ss.str("");
	ss << " " << nick << " temporarily lost connection with bot. Reconnecting...";
	wyslij(ss.str());
}*/

void setCustomCommands(int id) { //dlaPluginow
	//pluginowe custom commands:
	/*ss.str("");
	ss << " \x4/" << zeranumer(id) << " command set color";
	wyslij(ss.str());
	ss.str("");
	ss << " \x4/" << zeranumer(id) << " command set char";
	wyslij(ss.str());*/
	return;
}

void setCustomDamage(int id) {
	fstream customDamage;
	std::stringstream ss;
	customDamage.open(dataPath + "customDamage.txt", std::fstream::in | std::fstream::out);
	if (!customDamage)
	{
		customDamage.open(dataPath + "customDamage.txt", std::fstream::trunc | std::fstream::out);
		customDamage.close();
		// re-open with original flags
		customDamage.open(dataPath + "customDamage.txt", std::fstream::in | std::fstream::out);
		customDamage << "//0.default 1. knife 3.tekbow 4. pistol 5. magnum 7. chargeDart 8. shotgun 9.shueder 10. plasma 11. firestorm 13. cbore 15. grenadeLauncher 16. scorpionLauncher 17. harpoon 18. torpedo 20. flameThrower 22. nuke" << endl;
		customDamage << "//example: (custom damage 2.0 for pistol and 1.2 for all other weapons)" << endl;
		customDamage << "//4; d: 2.0" << endl;
		customDamage << "//0; d: 1.2" << endl;
		customDamage << "//example: (custom node for chargeDart)" << endl;
		customDamage << "//7; n: 3.5" << endl;
		customDamage << "//Warning! Scorpion launcher should always have the greatest dmg and node to protect from fast weapon changing after the rocket was fired. (Maybe I'll make some kind of delay in future version.)" << endl;
		customDamage << "//It should be mainly used to lower the dmg multiplier of some OP weapons. For example: global DamageMultiplier=1.31 is fine for almost every weapon but shotgun - so you can type below \"0; d: 1.3\" and \"8; d: 1.0\"." << endl;
		customDamage << "//Use at your own risk. I haven't tested it well - I guess it doesn't even work for some weapons." << endl;
	}
	string dane;
	//int i = 0;
	while (getline(customDamage, dane)) {
		if (dane.find("//") != std::string::npos) continue;
		int weapon = atoi(dane.substr(0, dane.find("; ")).c_str());
		char co = dane[dane.find("; ")+2];
		float value = atof(dane.substr(dane.find(": ")+2).c_str());
		if (co == 'd') {
			ss.str("");
			ss << " \x4/" << zeranumer(id) << " cdamage " << zeranumer(weapon) << " " << value;
			wyslij(ss.str());
			//i++;
		}
		else if (co == 'n') {
			ss.str("");
			ss << " \x4/" << zeranumer(id) << " cnode " << zeranumer(weapon) << " " << value;
			wyslij(ss.str());
			//i++;
		}
	}
	/*if (i > 0) {
		float value = *((float*)0x00AD44EC);
		ss.str("");
		ss << " \x4/" << zeranumer(id) << " cdamage -1 " << value;
		wyslij(ss.str());
		value = *((float*)0x00AD44F0);
		ss.str("");
		ss << " \x4/" << zeranumer(id) << " cnode -1 " << value;
		wyslij(ss.str());
	}*/
	customDamage.close();

	fstream customDrops;
	customDrops.open(dataPath + "customDrops.txt", std::fstream::in | std::fstream::out);
	if (!customDrops)
	{
		customDrops.open(dataPath + "customDrops.txt", std::fstream::trunc | std::fstream::out);
		customDrops.close();
		// re-open with original flags
		customDrops.open(dataPath + "customDrops.txt", std::fstream::in | std::fstream::out);
		customDrops << "//3.tekbow 5. magnum 7. chargeDart 8. shotgun 9.shueder 10. plasma 11. firestorm 13. cbore 15. grenadeLauncher 16. scorpionLauncher 17. harpoon 18. torpedo 20. flameThrower 22. nuke" << endl;
		customDrops << "//pattern: Map_name; weapon_id: time_until_disappear_in_milliseconds" << endl;
		customDrops << "//example1: (25% chance for shotgun or harpoon drop - for all maps (Default) - 20 seconds until disappear):" << endl;
		customDrops << "//Chance: 25" << endl;
		customDrops << "//Default; 8: 20000" << endl;
		customDrops << "//Default; 17: 20000" << endl;
		customDrops << "//example2: (20% chance for nuke drop on Harbor-5 - \"Default\" weapons won't drop on H-5 (unless you rewrite \"Harbor-5; 8: 20000\" etc) - 0 seconds means it won't disappear until new weapon is dropped)" << endl;
		customDrops << "//Chance: 20" << endl;
		customDrops << "//Harbor-5; 22: 0" << endl;
		customDrops << "//Chance for custom drop in percents (0-100): (Chance is global variable for all maps)" << endl;
	}

	while (getline(customDrops, dane)) {
		if (dane.find("//") != std::string::npos) continue;
		if (dane.find("Chance:") == 0) {
			int chance = atoi(dane.substr(7).c_str());
			//cout << "chance: " << chance << endl;
			ss.str("");
			ss << " \x4/" << zeranumer(id) << " dchance " << chance;
			wyslij(ss.str());
		}
		string map = dane.substr(0, dane.find("; "));
		int weapon = atoi(dane.substr(dane.find("; ")+2, dane.find(": ")).c_str());
		int time = atoi(dane.substr(dane.find(": ") + 2).c_str());
		ss.str("");
		ss << " \x4/" << zeranumer(id) << " cdrop " << map << ", " << zeranumer(weapon) << " " << time;
		wyslij(ss.str());
	}
	customDrops.close();

	fstream customPickups;
	customPickups.open(dataPath + "customPickups.txt", std::fstream::in | std::fstream::out);
	if (!customPickups)
	{
		customPickups.open(dataPath + "customPickups.txt", std::fstream::trunc | std::fstream::out);
		customPickups.close();
		// re-open with original flags
		customPickups.open(dataPath + "customPickups.txt", std::fstream::in | std::fstream::out);
		customPickups << "//2.bow 3.tekbow 4.pistol 5. magnum 6.tranquilizer 7. chargeDart 8. shotgun 9.shueder 10. plasma 11. firestorm 12. sunfirePod 13. cbore 14. P.F.M. 15. grenadeLauncher 16. scorpionLauncher 17. harpoon 18. torpedo 19. flameThrower 20. razorWind 21. nuke" << endl;
		customPickups << "///pattern:" << endl;
		customPickups << "//Chance: id_of_collected_weapon; chance_to_gather_something_else_(in%)" << endl;
		customPickups << "//Pick: id_of_collected_weapon; if_of_item_to_actually_get: amount_of_extra_starting_ammo" << endl;
		customPickups << "//Ammo: id_of_collected_weapon; amount_of_extra_starting_ammo" << endl;
		customPickups << "///example: (25% chance to get plasma with 120 ammo, 25% chance to get razor, 50% to get nuke with 5 ammo (while collecting nuke):" << endl;
		customPickups << "//Chance: 21; 50" << endl;
		customPickups << "//Pick: 21; 10: 20" << endl;
		customPickups << "//Pick: 21; 20: 0" << endl;
		customPickups << "//Ammo: 21; 3" << endl;
		customPickups << "///Leave this file empty to use default customPickups settings." << endl;
	}

	while (getline(customPickups, dane)) {
		if (dane.find("//") != std::string::npos) continue;
		if (dane.find("Chance:") == 0) {
			dane = dane.substr(7);
			int pred = atoi(dane.substr(0, dane.find(";")).c_str());
			//cout << "pred: " << pred << endl;
			dane = dane.substr(dane.find(";") + 1);
			int chance = atoi(dane.substr(0, dane.find(":")).c_str());
			//cout << "chance: " << chance << endl;
			ss.str("");
			ss << " \x4/" << zeranumer(id) << " pchance " << zeranumer(pred) << " " << zeranumer(chance);
			wyslij(ss.str());
		}
		else if (dane.find("Pick:") == 0) {
			dane = dane.substr(5);
			int pred = atoi(dane.substr(0, dane.find(";")).c_str());
			//cout << "pred: " << pred << endl;
			dane = dane.substr(dane.find(";") + 1);
			int pick = atoi(dane.substr(0, dane.find(":")).c_str());
			//cout << "pick: " << pick << endl;
			int ammo = atoi(dane.substr(dane.find(":")+1).c_str());
			//cout << "ammo: " << ammo << endl;
			ss.str("");
			ss << " \x4/" << zeranumer(id) << " cpick " << zeranumer(pred) << " " << zeranumer(pick) << " " << ammo;
			wyslij(ss.str());
		}
		else if (dane.find("Ammo:") == 0) {
			dane = dane.substr(5);
			int pred = atoi(dane.substr(0, dane.find(";")).c_str());
			//cout << "pred: " << pred << endl;
			int ammo = atoi(dane.substr(dane.find(";") + 1).c_str());
			//cout << "pick: " << ammo << endl;
			ss.str("");
			ss << " \x4/" << zeranumer(id) << " pammo " << zeranumer(pred) << " " << zeranumer(ammo);
			wyslij(ss.str());
		}
	}
	customPickups.close();

	fstream customWeapons;
	customWeapons.open(dataPath + "customWeapons.txt", std::fstream::in | std::fstream::out);
	if (!customWeapons)
	{
		customWeapons.open(dataPath + "customWeapons.txt", std::fstream::trunc | std::fstream::out);
		customWeapons.close();
		// re-open with original flags
		customWeapons.open(dataPath + "customWeapons.txt", std::fstream::in | std::fstream::out);
		customWeapons << "torpedoDisabledOnSurface: 1" << endl;
		customWeapons << "howManyExtraNukeExplosions: 2" << endl;
		customWeapons << "//AmmoIds: 2. non-explosive arrows 3.tekbow 4. pistol 5. magnum 7. chargeDart 8. shotgun 9.shueder 10. plasma 11. firestorm 13. cbore 15. grenadeLauncher 16. scorpionLauncher 17. harpoon 18. torpedo 20. flameThrower 22. nuke" << endl;
		customWeapons << "airStrikeAmmoId: 18" << endl;
		customWeapons << "airStrikeAmmoCost: 5" << endl;
		customWeapons << "//delay in miliseconds:" << endl;
		customWeapons << "airStrikeDelay: 0" << endl;
		customWeapons << "//\"With\"s: 4. chargeDart 5. pistol 16. torpedo (for more ask kubpica)" << endl;
		customWeapons << "airStrikeWith: 16" << endl;
		customWeapons << "blackOilWith: 5" << endl;
		customWeapons << "dinoRidingWith: 4" << endl;
	}

	while (getline(customWeapons, dane)) {
		if (dane.find("//") != std::string::npos) continue;
		if (dane.find("torpedoDisabledOnSurface:") == 0) {
			int var = atoi(dane.substr(25).c_str());
			ss.str("");
			ss << " \x4/" << zeranumer(id) << " cwcfg 01 " << var;
			wyslij(ss.str());
		} 
		else if (dane.find("howManyExtraNukeExplosions:") == 0) {
			int var = atoi(dane.substr(27).c_str());
			ss.str("");
			ss << " \x4/" << zeranumer(id) << " cwcfg 02 " << var;
			wyslij(ss.str());
		}
		else if (dane.find("airStrikeAmmoId:") == 0) {
			int var = atoi(dane.substr(16).c_str());
			ss.str("");
			ss << " \x4/" << zeranumer(id) << " cwcfg 03 " << var;
			wyslij(ss.str());
		}
		else if (dane.find("airStrikeAmmoCost:") == 0) {
			int var = atoi(dane.substr(18).c_str());
			ss.str("");
			ss << " \x4/" << zeranumer(id) << " cwcfg 04 " << var;
			wyslij(ss.str());
		}
		else if (dane.find("blackOilWith:") == 0) {
			int var = atoi(dane.substr(13).c_str());
			ss.str("");
			ss << " \x4/" << zeranumer(id) << " cwcfg 05 " << var;
			wyslij(ss.str());
		}
		else if (dane.find("dinoRidingWith:") == 0) {
			int var = atoi(dane.substr(15).c_str());
			ss.str("");
			ss << " \x4/" << zeranumer(id) << " cwcfg 06 " << var;
			wyslij(ss.str());
		}
		else if (dane.find("airStrikeWith:") == 0) {
			int var = atoi(dane.substr(14).c_str());
			ss.str("");
			ss << " \x4/" << zeranumer(id) << " cwcfg 07 " << var;
			wyslij(ss.str());
		}
		else if (dane.find("airStrikeDelay:") == 0) {
			int var = atoi(dane.substr(15).c_str());
			ss.str("");
			ss << " \x4/" << zeranumer(id) << " cwcfg 08 " << var;
			wyslij(ss.str());
		}
	}
	customWeapons.close();

	ss.str("");
	ss << " \x4/" << zeranumer(id) << " sdone";
	wyslij(ss.str());
}

int getELO(string player, int doCzego) {
	string filename = player;
	char chars[] = "\\/:*?\"<>|."; //usuniecie tych znakow z nazwy pliku
	for (unsigned int i = 0; i < strlen(chars); ++i) filename.erase(std::remove(filename.begin(), filename.end(), chars[i]), filename.end());
	filename += ".txt";
	//player += ": ";
	string dataFolderPath = dataPath;
	if (doCzego == 1)
		dataFolderPath += "loginsELO\\";
	else if (doCzego == 0)
		dataFolderPath += "nicksELO\\";
	else if (doCzego == 2)
		dataFolderPath += "tidsELO\\";

	cout << "GET dir: " << dataFolderPath + filename << endl;
	fstream ELOtxt;
	ELOtxt.open(dataFolderPath + filename, std::fstream::in | std::fstream::out);
	if (!ELOtxt)
	{
		ELOtxt.open(dataFolderPath + filename, std::fstream::trunc | std::fstream::out);
		ELOtxt.close();
		// re-open with original flags
		ELOtxt.open(dataFolderPath + filename, std::fstream::in | std::fstream::out);
		ELOtxt << "general: 1200" << endl;
		ELOtxt.close();
		return 1200;
	}
	string dane;
	int playerELO = -1;
	while (getline(ELOtxt, dane)) {
		if (dane.find("//") != std::string::npos) continue;
		if (dane.find("general: ") == 0) {
			playerELO = atoi(dane.substr(9).c_str());
			//cout << "found playerELO: " << playerELO << endl;
			break;
		}
	}
	if (playerELO == -1) {
		//cout << "not found" << endl;
		ELOtxt << "general: 1200" << endl;
		playerELO = 1200;
	}
	ELOtxt.close();
	return playerELO;
}

void saveELO(string player, int elo, int doCzego) {
	string filename = player;
	char chars[] = "\\/:*?\"<>|."; //usuniecie tych znakow z nazwy pliku
	for (unsigned int i = 0; i < strlen(chars); ++i) filename.erase(std::remove(filename.begin(), filename.end(), chars[i]), filename.end());
	filename += ".txt";
	//player += ": ";
	string dataFolderPath = dataPath;
	if (doCzego == 1)
		dataFolderPath += "loginsELO\\";
	else if (doCzego == 0)
		dataFolderPath += "nicksELO\\";
	else if (doCzego == 2)
		dataFolderPath += "tidsELO\\";
	fstream ELOtxt;
	//cout << "SAVE dir: " << dataFolderPath + filename << endl;
	//ELOtxt.open(dataFolderPath + filename, std::fstream::in | std::fstream::out);
	//if (!ELOtxt)
	//{
		ELOtxt.open(dataFolderPath + filename, std::fstream::trunc | std::fstream::out);
		ELOtxt.close();
		// re-open with original flags
		ELOtxt.open(dataFolderPath + filename, std::fstream::in | std::fstream::out);
		//ELOtxt << "//ELO" << endl;
	//}

	ELOtxt << "general: " << elo << endl;
	//cout << "SAVE general: " << elo << endl;

	ELOtxt.close();
}

void elo(string winner, string loser) {
	char chars[] = "/:;\\"; //usuniecie tych znakow z nicku:
	for (unsigned int i = 0; i < strlen(chars); ++i) winner.erase(std::remove(winner.begin(), winner.end(), chars[i]), winner.end());
	for (unsigned int i = 0; i < strlen(chars); ++i) loser.erase(std::remove(loser.begin(), loser.end(), chars[i]), loser.end());
	int winnerid = -1;
	int loserid = -1;
	for (auto it = players.begin(); it != players.end(); it++) {
		if (it->second == winner) {
			winnerid = it->first;
		}
		else if (it->second == loser) {
			loserid = it->first;
		}
		if (winnerid != -1 && loserid != -1) break;
	}
	//cout << "winnerid: " << winnerid << endl;
	//cout << "loserid: " << loserid << endl;
	int winnerrank = -1;
	int loserrank = -1;
	if (playerslogin.count(winnerid) > 0) {
		winnerrank = getELO(playerslogin[winnerid],  1);
	}
	else if (playerstid.count(winnerid) > 0) {
		winnerrank = getELO(playerstid[winnerid], 2);
	}
	else {
		winnerrank = getELO(winner, 0);
	}
	if (playerslogin.count(loserid) > 0) {
		loserrank = getELO(playerslogin[loserid],  1);
	}
	else if (playerstid.count(loserid) > 0) {
		loserrank = getELO(playerstid[loserid], 2);
	}
	else {
		loserrank = getELO(loser, 0);
	}

	int d = loserrank - winnerrank;
	if (d > 400) d = 400;
	else if (d < -400) d = -400;
	double we = 1 / (1 + pow(10, d / 400.0));
	double diff = 1 - we;
	//cout << "10 * diff: " << 10 * diff << endl;
	int zmiana = round(10 * diff); //K=10
	//cout << "zmianaELO: " << zmiana << endl;
	winnerrank += zmiana;
	loserrank -= zmiana;

	if (playerstid.count(winnerid) > 0) {
		saveELO(playerstid[winnerid], winnerrank, 2);
	}
	if (playerslogin.count(winnerid) > 0) {
		saveELO(playerslogin[winnerid], winnerrank, 1);
	}
	else {
		saveELO(winner, winnerrank, 0);
	}

	if (playerstid.count(loserid) > 0) {
		saveELO(playerstid[loserid], loserrank, 2);
	}
	if (playerslogin.count(loserid) > 0) {
		saveELO(playerslogin[loserid], loserrank,  1);
	}
	else {
		saveELO(loser, loserrank,  0);
	}
	std::stringstream ss;
	cout << "[*] " << loser << " [" << loserrank << "] <---- " << winner << " [" << winnerrank << "]" << endl;
	ss.str("");
	ss << " \x4/" << dec << zeranumer(0) << " news \x2 " << loser << " [" << loserrank << "] \x3\x3 " << winner << " [" << winnerrank << "] \x4";
	wyslij(ss.str());
}

std::string get_str_between_two_str(const std::string &s,
	const std::string &start_delim,
	const std::string &stop_delim)
{
	unsigned first_delim_pos = s.find(start_delim);
	unsigned end_pos_of_first_delim = first_delim_pos + start_delim.length();
	unsigned last_delim_pos = s.find(stop_delim);

	return s.substr(end_pos_of_first_delim,
		last_delim_pos - end_pos_of_first_delim);
}

bool checkPermission(int id, string permission) {
	std::stringstream ss;
	string login;
	if (playerslogin.find(id) == playerslogin.end()) {
		ss.str("");
		ss << " \x4/" << dec << zeranumer(id) << " news You are not logged in! Use 'login' command.";
		wyslij(ss.str());
		login = "*?*null";
		//continue;
	}
	else {
		login = playerslogin[id];
	}
	login += ";";
	string tid = playerstid[id];
	tid += ";";
	permission += " ";
	//cout << "login: " << login << endl;
	fstream permissions;
	permissions.open(dataPath + "permissions.txt", std::fstream::in | std::fstream::out);
	if (!permissions)
	{
		permissions.open(dataPath + "permissions.txt", std::fstream::trunc | std::fstream::out);
		permissions.close();
		// re-open with original flags
		permissions.open(dataPath + "permissions.txt", std::fstream::in | std::fstream::out);
		permissions << "//examples: (use without \"//\")" << endl;
		permissions << "//players_login; permission1 permission2 ;" << endl;
		permissions << "//players_tid; permission1 permission2 ;" << endl;
		permissions << "//pdestroyer123; kick changelvl ban ;" << endl;
		permissions << "//There must be space after every permission word! (space before 2nd ;)" << endl;
	}
	string dane;
	bool czy_uprawniony = false;
	while (getline(permissions, dane)) {
		//cout << "dane: " << dane << endl;
		if ((dane.find(login) == 0 || dane.find(tid)) && dane.find(permission) != std::string::npos) {
			czy_uprawniony = true;
			break;
		}
	}
	permissions.close();
	if (czy_uprawniony) {
		return true;
	}
	else {
		ss.str("");
		ss << " \x4/" << dec << zeranumer(id) << " news You don't have sufficient permissions to use this command.";
		wyslij(ss.str());
		return false;
	}
}

int wykonanie_komendy( std::string & tekst, std::string szukanaFraza )
{
    size_t znalezionaPozycja = tekst.find( szukanaFraza ); //szukanie pozycji na ktorej jest komenda
    if( znalezionaPozycja == std::string::npos ) //czy znaleziono komende
    {
        int gdzieDWK = tekst.find( ": " );
		if(gdzieDWK == std::string::npos || gdzieDWK >= 17 || gdzieDWK == 0){
			//cout << "info chat msg detected" << endl;
			/*if( tekst.find( " is ready to Rok!" ) != std::string::npos ){
				string login = tekst.substr(0, tekst.find(" is ready to Rok!"));
				bool found = false;
				auto it = players.begin(); // internalMap is std::map
				while (it != players.end())
				{
					found = (it->second == login);
					if (found)
						break;
					++it;
				}
				if (!found) {
					ss.str("");
					ss << " " << tekst.substr(0, tekst.find(" is ready to Rok!")) << " welcome to the server! I'm a bot.";
					//wyslij(ss.str());
					char * writable = new char[ss.str().size() + 1];
					strcpy(writable, ss.str().c_str());
					VirtualProtect((LPVOID)(0x00AD8384), strlen(writable) + 1, PAGE_EXECUTE_READWRITE, 0);
					memcpy((LPVOID)0x00AD8384, writable, strlen(writable) + 1);
					delete[] writable;
				}

			}else*/ if(tekst.find( " disconnected." ) != std::string::npos || tekst.find(" is back for more.") != std::string::npos){
				polecenia.push_back(tekst);
				return 0;
			}
			for (auto it = killStrings.begin(); it != killStrings.end(); it++) { //wykrywanie killi i rozdawanie ELO
				string killstr = *it;
				string tipOfKstr = killstr.substr(killstr.find("%s")+2);
				killstr = killstr.substr(0, killstr.find("%s"));
				int gdzieKillStr = tekst.find(killstr);
				if (gdzieKillStr != -1 && tekst.find(tipOfKstr) != std::string::npos) {
					string killed = tekst.substr(0, gdzieKillStr);
					string killer = get_str_between_two_str(tekst, killstr, tipOfKstr);
					cout << killer << " killed " << killed << endl;
					elo(killer, killed);
					break;
				}
			}
		}
		if (tekst.find(": /login ") != std::string::npos || tekst.find(": /register ") != std::string::npos) return 1;
		return 0; //jezeli nie to return
    }
	polecenia.push_back(tekst);
	return 1;
}

DWORD WINAPI wykonywanie_polecen(LPVOID lpParam)
{
	while (!czyWystartowano) Sleep(500);
	std::clock_t voice_delay;
	double duration;
	bool czy_reply = false;
	std::stringstream ss;
	while (true)
	{
		Sleep(16);
		if (!waiting4game.empty()) {
			for (auto it = waiting4game.begin(); it != waiting4game.end();) {
				ss.str("");
				ss << " \x4/" << zeranumer(*it) << " play";
				wyslij(ss.str());
				//ZOMBIES vvvvvvvvvvvvvvv
				/*
				ss.str("");
				ss << " \x4/" << zeranumer(*it) << " blspect";
				wyslij(ss.str());
				//playersingame++;
				if (fazagry == 2) {
					ss.str("");
					ss << " \x4/" << zeranumer(*it) << " robserve 0x106D1394";
					wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(*it) << " rfreeze 0x005D5A60";
					wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(*it) << " write i 0x005D5A60 0"; //blacout
					wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(*it) << " freeze i 0x106D1C94 500";
					wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(*it) << " freeze i 0x106D1770 10";
					wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(*it) << " freeze i 0x106D1D8C 34";
					wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(*it) << " freeze i 0x00AD02EC 1";
					wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(*it) << " freeze i 0x00AD0478 458752";
					wyslij(ss.str());

					//ss.str("");
					//ss << " \x4/" << zeranumer(*it) << " freeze i 0x106D25A4 0";
					//wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(*it) << " callf i2 0x47FE00 (275579912, 275579296)";
					wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(*it) << " callf i1 0x486100 (0)";
					wyslij(ss.str());

					ss.str("");
					ss << " \x4/" << zeranumer(*it) << " respawn";
					wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(*it) << " news You have just been infected.";
					wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(*it) << " news Red players with a burning head are your friends. The others must die!";
					wyslij(ss.str());
					ilosc_zombie++;
				}*/
				//ZOMBIES ^^^^^^^^^^^^^^^^^
				it = waiting4game.erase(it);
			}
		}

		if (czy_sprawdzanie_voice) {
			duration = (std::clock() - voice_delay) / (double)CLOCKS_PER_SEC;
			if (duration > 10 && !czy_reply) {
				czy_reply = true;
				ss.str("");
				ss << " \x4/00" << " gvoice";
				wyslij(ss.str());
			}
			else if (duration > 20) {
				std::async(std::launch::async, sprawdzVoice);
				voice_delay = std::clock();
			}
		}
		if (!polecenia.empty()) {
			string tekst = polecenia.front();
			polecenia.pop_front();


			size_t znalezionaPozycja = tekst.find(": \x4/"); //szukanie pozycji na ktorej jest komenda
			if (znalezionaPozycja == std::string::npos) //czy znaleziono komende
			{
				int gdzieDWK = tekst.find(": ");
				if (gdzieDWK == std::string::npos || gdzieDWK >= 17 || gdzieDWK == 0) {
					if (tekst.find(" disconnected.") != std::string::npos || tekst.find(" is back for more.") != std::string::npos) {
						if (!czy_sprawdzanie_voice) {
							voice_delay = std::clock();
							czy_sprawdzanie_voice = true;
							czy_reply = false;
							for (auto it = pid_czyVoice.begin(); it != pid_czyVoice.end(); it++) {
								pid_czyVoice[it->first] = false;
							}
							ss.str("");
							ss << " \x4/00" << " gvoice";
							wyslij(ss.str());
							//std::async(std::launch::async, sprawdzVoice);

						}
					}
				}
				continue;
			}
			

			int pozycja = znalezionaPozycja;

			do
			{
				//std::cout << "Znak zostal odnaleziony na pozycji " << znalezionaPozycja << std::endl;
				znalezionaPozycja = tekst.find(": \x4/", znalezionaPozycja + 1); //sprawda czy jest jakas komenda dalej (znaki zaczynajace komende)
				if (znalezionaPozycja != std::string::npos) { //jezeli jest dalej to zapisuje pozycje tej dalszej
					pozycja = znalezionaPozycja;
				}
				else break;
			} while (znalezionaPozycja != std::string::npos);

			int adres;
			int var;
			string nick = tekst.substr(0, pozycja);
			tekst = tekst.substr(pozycja);
			int toID = atoi(tekst.substr(4).c_str());
			if (toID != myid && toID != 0) {
				//cout << "atoi: " << atoi(tekst.substr(4).c_str()) << endl;
				continue;
			}

			if (tekst.find("voice") == 7) {
				int id = atoi(tekst.substr(13).c_str());
				if (players.count(id)>0)
					pid_czyVoice[id] = true;
				continue;
			}
			else if (tekst.find("gvoice") == 7) {
				int id = atoi(tekst.substr(14).c_str());
				if (players.count(id) == 0) {
					//if (playersid == 0) wyslij(" \x4/00 rdy");
					wyslij(" \x4/00 rdy");
					continue;
				}
				ss.str("");
				ss << " \x4/" << zeranumer(id) << " voice"; //<< myid;
				wyslij(ss.str());
				continue;
			}
			else {
				string md5tocheck = tekst.substr(1, tekst.find(" h;") - 1);
				string md5recieved = tekst.substr(tekst.find(" h;") + 3);
				//cout << "md5tocheck: " << md5tocheck << endl;
				//cout << "md5recieved: " << md5recieved << endl;
				md5tocheck = md5(md5tocheck + " salt");
				//cout << "md5check: " << md5tocheck << endl;
				if (md5tocheck != md5recieved) {
					cout << "!!! Sumcheck does not fit! Canceling..." << endl;
					cout << "Canceled command: " << tekst << endl;
					continue;
				}
				tekst = tekst.substr(0, tekst.find(" h;"));
			}

			if (tekst.find("eventf") == 7) {
				//cout << "eventf! " << tekst << endl;
				//cout << "adres: " << tekst.substr(14) << endl; // 15 11  // write 500 0x00
				adres = (int)strtol(tekst.substr(14).c_str(), NULL, 0);
				//cout << "dec: " << dec << adres << " hex: " << hex << adres << endl;
				//bool czy_event;
				//cout << "czy event: " << tekst.substr(25) << endl;
				//czy_event = atoi(tekst.substr(25).c_str());

				//cout << "id: " << tekst.substr(27) << endl;
				int id = atoi(tekst.substr(27).c_str());

				//cout << "var: " << tekst.substr(29) << endl;
				float var = atof(tekst.substr(29).c_str());

				cout << dec << var << endl << endl;
				//cout << "przed make pair" << endl;
				//observed[std::make_pair(adres,id)] = var;
				//if(czy_event)
				eventf[std::make_pair(adres, id)] = var;
				//else readed[std::make_pair(adres, id)] = var;
				//cout << "odczytalem eventf!!" << endl;
				continue;
			}
			else

				if (tekst.find("event") == 7) {
					//cout << "event! " << tekst << endl;
					//cout << "adres: " << tekst.substr(13) << endl; // 15 11  // write 500 0x00
					adres = (int)strtol(tekst.substr(13).c_str(), NULL, 0);
					//cout << hex << adres << endl;
					bool czy_event;
					//cout << "czy event: " << tekst.substr(24) << endl;
					czy_event = atoi(tekst.substr(24).c_str());

					//cout << "id: " << tekst.substr(26) << endl;
					int id = atoi(tekst.substr(26).c_str());

					//cout << "var: " << tekst.substr(28) << endl;
					float var = atof(tekst.substr(28).c_str());

					//cout << dec << var << endl << endl;
					//cout << "przed make pair" << endl;
					//observed[std::make_pair(adres,id)] = var;
					if (czy_event)
						event[std::make_pair(adres, id)] = var;
					else
						readed[std::make_pair(adres, id)] = var;
					//cout << "odczytalem event!!" << endl;
					continue;
				}
				else

					if (tekst.find("return") == 7) {
						//cout << "return! " << tekst << endl;
						//cout << "adres: " << tekst.substr(14) << endl; // 15 11  // write 500 0x00
						adres = (int)strtol(tekst.substr(14).c_str(), NULL, 0);
						//cout << hex << adres << endl;

						//cout << "id: " << tekst.substr(25) << endl;
						int id = atoi(tekst.substr(25).c_str());

						//cout << "var: " << tekst.substr(27) << endl;
						var = atoi(tekst.substr(27).c_str());

						//cout << dec << var << endl << endl;
						readed[std::make_pair(adres, id)] = var;
						//cout << "odczytalem return! (readed)" << endl;
						continue;
					}
					else

						if (tekst.find("join") == 7) {
							//string nick = tekst.substr(0, pozycja);
							char chars[] = "/:;\\"; //usuniecie tych znakow z nicku:
							for (unsigned int i = 0; i < strlen(chars); ++i) nick.erase(std::remove(nick.begin(), nick.end(), chars[i]), nick.end());
							cout << "join: " << nick << endl; // 15 11  // write 500 0x00
							playersid++;
							if (playersid >= 99) playersid = 1;
							while (players.find(playersid) != players.end()) playersid++;
							players[playersid] = nick;
							pid_czyVoice[playersid] = true;
							pid_iloscKomend[playersid] = 0;

							int tempid = atoi(tekst.substr(12).c_str());
							ss.str("");
							ss << " \x4/" << tempid << " joined " << playersid;
							wyslij(ss.str());
							playersCount++;
							//int suma = observingCount + ingameCount + waiting4gameCount;
							if ((playersCount - observingCount - ingameCount - waiting4gameCount) == 1) {
								observingCount++;
								pid_status[playersid] = 0;
							}
							setCustomCommands(playersid);
							setCustomDamage(playersid);
							continue;
						}
						else if (tekst.find("cstatus") == 7) {
							int z = atoi(tekst.substr(15).c_str());
							int na = atoi(tekst.substr(17).c_str());
							int id = atoi(tekst.substr(19).c_str());
							if (players.count(id) == 0 || z == na) continue;
							pid_status[id] = na;
							if (z == 0) observingCount--;
							else if (z == 1) waiting4gameCount--;
							else if (z == 2) ingameCount--;
							if (na == 0) observingCount++;
							else if (na == 1) waiting4gameCount++;
							else if (na == 2) ingameCount++;

							zmienilStatus(z, na, id);
							continue;
						}
						else if (tekst.find("stid") == 7) {
							int id = atoi(tekst.substr(12).c_str());
							string tid = tekst.substr(15,37).c_str();
							cout << "assigned player " << id << " to tid: " << tid << endl;
							playerstid[id] = tid;
							
							string dataFolderPath = dataPath;
							dataFolderPath += "bans\\";
							fstream bans;
							bans.open(dataFolderPath + tid + ".txt", std::fstream::in | std::fstream::out);
							if (!bans)
							{
								cout << "this player is NOT banned" << endl;
								continue;
							}
							bans.clear();
							string dane;
							while (getline(bans, dane)) {
								cout << "dane: " << dane << endl;
								if (dane.find(tid) == 0) {
									ss.str("");
									ss << " \x4/" << dec << zeranumer(id) << " write s 0x0051B958 YOU ARE BANNED!\n"; //<< myid;
									wyslij(ss.str());
									ss.str("");
									ss.str("");
									ss << " \x4/" << dec << zeranumer(id) << " write s 0x0046E195 \xA1\x84\x02\xAD\x00"; //<< myid;
									wyslij(ss.str());
									ss.str("");
									ss << " \x4/" << dec << zeranumer(id) << " write i 0x00B74624 0";
									wyslij(ss.str());

									string nick = players[id];
									ss.str("");
									ss << " \x4/" << dec << zeranumer(0) << " news " << nick << " is banned on this server.";
									wyslij(ss.str());

									cout << nick << " tried to join server but got kicked as he is banned." << endl;
									break;
								}
							}
							bans.close();

							continue;
						}
						else if (tekst.find("cmd") == 7) {
							int id = atoi(tekst.substr(11).c_str());
							string s = tekst.substr(14);
							commands.push_back(std::make_pair(s, id));
							continue;
						}
						else if (tekst.find("wplay") == 7) {
							int id = atoi(tekst.substr(13).c_str());
							//cout << "wplay id: " << id << endl;
							waiting4game.push_back(id);
							continue;
						}
						else if (tekst.find("cnick") == 7) {
							int id = atoi(tekst.substr(13).c_str());
							string nick = tekst.substr(16);
							players[id] = nick;
							continue;
						}
						else if (tekst.find("idlist") == 7) {
							int id = atoi(tekst.substr(14).c_str());
							ss.str("");
							//cout << "idlist" << endl;
							string s;
							for (auto it = players.begin(); it != players.end(); it++) {
								ss << " " << it->first << ". " << it->second;
								s = ss.str();
								if (s.length() > 70) {
									ss.str("");
									ss << " \x4/" << dec << zeranumer(id) << " news " << s;
									//cout << "ss.str(): " << ss.str() << endl;
									wyslij(ss.str());
									ss.str("");
									s.clear();
								}
							}
							if (s.length() > 0) {
								ss.str("");
								ss << " \x4/" << dec << zeranumer(id) << " news " << s;
								//cout << "ss.str(): " << ss.str() << endl;
								wyslij(ss.str());
							}
							//cout << "wychodze z idlist" << endl;
							continue;
						}
						else if (tekst.find("idloginlist") == 7) {
							int id = atoi(tekst.substr(19).c_str());
							ss.str("");
							//cout << "idloginlist" << endl;
							string s;
							for (auto it = playerslogin.begin(); it != playerslogin.end(); it++) {
								ss << " " << it->first << ". " << it->second;
								s = ss.str();
								if (s.length() > 70) {
									ss.str("");
									ss << " \x4/" << dec << zeranumer(id) << " news " << s;
									//cout << "ss.str(): " << ss.str() << endl;
									wyslij(ss.str());
									ss.str("");
									s.clear();
								}
							}
							if (s.length() > 0) {
								ss.str("");
								ss << " \x4/" << dec << zeranumer(id) << " news " << s;
								//cout << "ss.str(): " << ss.str() << endl;
								wyslij(ss.str());
							}
							continue;
						}
						else if (tekst.find("login") == 7) {
							int id = atoi(tekst.substr(13).c_str());
							string login = tekst.substr(16);
							string password = login.substr(login.find(" ") + 1);
							login = login.substr(0, login.find(" "));
							cout << "login! login: " << login << " password: " << password << endl;

							string dataFolderPath = dataPath;
							dataFolderPath += "accounts\\";

							fstream accounts;
							accounts.open(dataFolderPath + login + ".txt", std::fstream::in | std::fstream::out);
							if (!accounts)
							{
								cout << login << ".txt not found - creating new one" << endl;
								accounts.open(dataFolderPath + login + ".txt", std::fstream::trunc | std::fstream::out);
								accounts.close();
								// re-open with original flags
								accounts.open(dataFolderPath + login + ".txt", std::fstream::in | std::fstream::out);
							}

							/*if (!accounts.good())
							{
								//cout << "not good" << endl;
								accounts.close(); // re-open with original flags:
								accounts.open(dataPath + "accounts.txt", std::fstream::in | std::fstream::out);
							}
							accounts.clear();
							accounts.seekg(0, ios::beg);*/
							string dane;
							login += "; ";
							bool czy_continue = false;
							while (getline(accounts, dane)) {
								if (dane.find(login) == 0 && dane.find(password) != std::string::npos) {
									login = login.substr(0, login.find("; "));
									playerslogin[id] = login;
									ss.str("");
									ss << " \x4/" << dec << zeranumer(id) << " news You logged in successfully.";
									wyslij(ss.str());
									czy_continue = true;
								}
							}
							accounts.close();
							if (czy_continue) continue;
							ss.str("");
							ss << " \x4/" << dec << zeranumer(id) << " news Failed. Incorrect data or such user does not exist. Try again or use 'register' command.";
							wyslij(ss.str());
							continue;
						}
						else if (tekst.find("register") == 7) {
							int id = atoi(tekst.substr(16).c_str());
							string login = tekst.substr(19);
							string password = login.substr(login.find(" ") + 1);
							login = login.substr(0, login.find(" "));
							cout << "register! login: " << login << " password: " << password << endl;

							char chars[] = "\\/:*?\"<>|."; //usuniecie tych znakow z loginu:
							for (unsigned int i = 0; i < strlen(chars); ++i) login.erase(std::remove(login.begin(), login.end(), chars[i]), login.end());

							string dataFolderPath = dataPath;
							dataFolderPath += "accounts\\";
							fstream accounts;
							accounts.open(dataFolderPath + login + ".txt", std::fstream::in | std::fstream::out);
							if (!accounts)
							{
								cout << login << ".txt not found - creating new one" << endl;
								accounts.open(dataFolderPath + login + ".txt", std::fstream::trunc | std::fstream::out);
								accounts.close();
								// re-open with original flags
								accounts.open(dataFolderPath + login + ".txt", std::fstream::in | std::fstream::out);
							}

							/*if (!accounts.good())
							{
								//cout << "not good" << endl;
								accounts.close(); // re-open with original flags:
								accounts.open(dataPath + "accounts.txt", std::fstream::in | std::fstream::out);
							}
							accounts.clear();
							accounts.seekg(0, ios::beg);*/
							string dane;
							bool czy_continue = false;
							while (getline(accounts, dane)) {
								if (dane.find(login) == 0) {
									ss.str("");
									ss << " \x4/" << dec << zeranumer(id) << " news Account with this nickname already exists. Try again or use 'login' command.";
									wyslij(ss.str());
									czy_continue = true;
								}
							}
							if (czy_continue) {
								accounts.close();
								continue;
							}
							accounts.clear();
							accounts.seekg(0, ios::end);
							accounts << login << "; " << password << endl;
							accounts.flush();
							ss.str("");
							ss << " \x4/" << dec << zeranumer(id) << " news Account created successfully. Use command 'login your_nickname your_password' to log into your account.";
							wyslij(ss.str());
							accounts.close();
							continue;
						}
						else if (tekst.find("kick") == 7) {
							int id = atoi(tekst.substr(12).c_str());
							int idtokick = atoi(tekst.substr(15).c_str());
							//bool czy_uprawniony = checkPermission(id, "kick");
							if (checkPermission(id, "kick")) {
								ss.str("");
								ss << " \x4/" << dec << zeranumer(idtokick) << " write s 0x0051B958 YOU HAVE BEEN KICKED!"; //<< myid;
								wyslij(ss.str());
								ss.str("");
								ss.str("");
								ss << " \x4/" << dec << zeranumer(idtokick) << " write s 0x0046E195 \xA1\x84\x02\xAD\x00"; //<< myid;
								wyslij(ss.str());
								ss.str("");
								ss << " \x4/" << dec << zeranumer(idtokick) << " write i 0x00B74624 0";
								wyslij(ss.str());
								if (players.find(idtokick) == players.end()) {
									ss.str("");
									ss << " \x4/" << dec << zeranumer(id) << " news Player with this id not found.";
									wyslij(ss.str());
								}
								else {
									ss.str("");
									ss << " \x4/" << dec << zeranumer(id) << " news Player has been kicked.";
									wyslij(ss.str());
									string kat = players[id];
									string ofiara = players[idtokick];
									cout << ofiara << " has been kicked by " << kat << "." << endl;
									ss.str("");
									ss << " \x4/" << dec << zeranumer(0) << " news " << ofiara << " has been kicked by " << kat << ".";
									wyslij(ss.str());
								}
							}
							continue;
						}
						else if (tekst.find("ban") == 7) {
							int id = atoi(tekst.substr(11).c_str());
							int idtoban = atoi(tekst.substr(14).c_str());
							if (checkPermission(id, "ban")) {
								if (players.find(idtoban) == players.end() || playerstid.find(idtoban) == players.end()) {
									ss.str("");
									ss << " \x4/" << dec << zeranumer(id) << " news Player's id not found.";
									wyslij(ss.str());
									continue;
								}

								string zbanowany = players[idtoban];
								string tid = playerstid[idtoban];
								//char chars[] = "\\/:*?\"<>|."; //usuniecie tych znakow z loginu:
								//for (unsigned int i = 0; i < strlen(chars); ++i) zbanowany.erase(std::remove(zbanowany.begin(), zbanowany.end(), chars[i]), zbanowany.end());

								string dataFolderPath = dataPath;
								dataFolderPath += "bans\\";
								fstream bans;
								//bans.open(dataFolderPath + tid + ".txt", std::fstream::in | std::fstream::out);
								//if (!bans)
								//{
									bans.open(dataFolderPath + tid + ".txt", std::fstream::trunc | std::fstream::out);
									//bans.close();
									//bans.open(dataFolderPath + tid + ".txt", std::fstream::in | std::fstream::out); // re-open with original flags
									//bans << "//banned_tid" << endl;
									//bans << tid << endl;
								//}
								//bans.clear();
								//bans.seekg(0, ios::end);
								bans << tid << endl;
								bans << "//" << zbanowany << endl;
								bans.flush();

								ss.str("");
								ss << " \x4/" << dec << zeranumer(idtoban) << " write s 0x0051B958 YOU HAVE BEEN BANNED!"; //<< myid;
								wyslij(ss.str());
								ss.str("");
								ss.str("");
								ss << " \x4/" << dec << zeranumer(idtoban) << " write s 0x0046E195 \xA1\x84\x02\xAD\x00"; //<< myid;
								wyslij(ss.str());
								ss.str("");
								ss << " \x4/" << dec << zeranumer(idtoban) << " write i 0x00B74624 0";
								wyslij(ss.str());
								
								ss.str("");
								ss << " \x4/" << dec << zeranumer(id) << " news Player has been banned.";
								wyslij(ss.str());
								string kat = players[id];
								cout << zbanowany << " has been banned by " << kat << "." << endl;
								ss.str("");
								ss << " \x4/" << dec << zeranumer(0) << " news " << zbanowany << " has been banned by " << kat << ".";
								wyslij(ss.str());

								bans.close();
							}
							continue;
						}
						else if (tekst.find("changelvl") == 7) {
							int id = atoi(tekst.substr(17).c_str());
							int levelid = atoi(tekst.substr(20).c_str());
							if (checkPermission(id, "changelvl")) {
								int var = 1;
								memcpy((LPVOID)0x00AD028C, &var, sizeof(var));
								memcpy((LPVOID)0x00B65F68, &var, sizeof(var));
								memcpy((LPVOID)0x00519D30, &levelid, sizeof(levelid));
								Sleep(100);
								var = 0;
								memcpy((LPVOID)0x00AD028C, &var, sizeof(var));
								memcpy((LPVOID)0x00B65F68, &var, sizeof(var));

								ss.str("");
								ss << " \x4/" << dec << zeranumer(id) << " news Changing level. If nothing happens try again.";
								wyslij(ss.str());

								string kat = players[id];
								cout << kat << " just tried to change level." << endl;
								ss.str("");
								ss << " \x4/" << dec << zeranumer(0) << " news " << kat << " just tried to change level.";
								wyslij(ss.str());
							}
							continue;
						}
						else if (tekst.find("checkCount") == 7) {
							int id = atoi(tekst.substr(18).c_str());
							int liczbaKomend = atoi(tekst.substr(21).c_str());
							if (pid_iloscKomend[id] != liczbaKomend) {
								ss.str("");
								//ss << " \x4/" << dec << zeranumer(id) << " setCount " << pid_iloscKomend[id];
								ss << " \x4/" << dec << zeranumer(id) << " setCount 0";
								pid_iloscKomend[id] = 0;
								wyslij(ss.str());
								//eventf[std::make_pair(-2, id)] = 1;
								//heMissedCommand(id);
							}
							continue;
						}
						else if (tekst.find("sresend") == 7) {
							int id = atoi(tekst.substr(15).c_str());
							setCustomCommands(id);
							setCustomDamage(id);
							continue;
						}
						else if (tekst.find("rdy") == 7) {
							wyslij(" \x4/99 block");
							continue;
						}
						else if (tekst.find("block") == 7) {
							blocked = true;
							continue;
						}
						/*else if (tekst.find("z") == 7) {
						wyslij(" \x4/00 forcespect 1 0");
						wyslij(" Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Donec quam felis, ultricies nec, pelle");
						//ss.str("");
						//ss << " \x4/00 write s 0x0051B93C \xD9\x1D\x56\xBD\xAC"; //<< myid;
						//wyslij(ss.str());
						continue;
						}*/

						//cout << "znalezionaPozycja: " << znalezionaPozycja << endl;
						continue;
		}
	}
	return S_OK;
}

/*Our modified function code that is going to be executed
before continuing to the code of original function*/
int hookedFunction(char *text)
{
	comand = text;
	if(wykonanie_komendy( comand, ": \x4/" )){ //if( comand.find( ": \x4/" ) != std::string::npos ){ //czy znaleziono komende
		//wykonanie_komendy( comand, ": \x4/" );
		return 0;
	}
	std::cout << text << std::endl;
	return originalFunction(text);                                        //before returning to normal execution of function
}

int hookedFunction2(char *text)
{
	//cout << "hookedFunction2" << endl;

	//int zwrot = wysylaniehook(text);

	//cout << "bzz1: " << text << endl;
	//std::string str = "hax hax hax";
	//strcpy(text, str.c_str());

	//cout << "bzz2: " << bigos << endl;
	//cout << "zwrot: " << zwrot << endl;
	return wysylaniehook(text); //return zwrot;
}

int hookedFunction3(int text1, int text2)
{	
	int zwrot = wysylaniehook2(text1, text2); //liczy ile znakow
	if(zwrot == 0 && !dowyslania.empty()){
		string bigozz = dowyslania.front();
		dowyslania.pop_front();
		if(bigozz.length() != 0){
			writable = new char[bigozz.size() + 1];
			strcpy( writable, bigozz.c_str() );
			//std::copy(bigozz.begin(), bigozz.end(), writable);
			//writable[bigozz.size()] = '\0';
			//cout << "Wysylanie: " << writable << endl; //02FF3C7D
			//WriteToMemory(0x02FF3C7D, writable, sizeof(writable));
			DWORD adresik = FindDmaAddy(1, hackOffsets, baseAddress);
			//unsigned long OldProtection;
			memcpy( (LPVOID)(adresik-4), &dataz, sizeof(dataz));
			VirtualProtect((LPVOID)(adresik), strlen(writable)+1, PAGE_EXECUTE_READWRITE, 0);
			memcpy( (LPVOID)adresik, writable, strlen(writable)+1);
			delete [] writable;
			//memcpy( (LPVOID)0x02FF3C7D, &writable, sizeof(writable)); //0x00ADC88C
		}

		/*cout << "hookedFunction3" << endl;
		cout << "text1: " << text1 << endl;
		cout << "text2: " << text2 << endl;*/
		//cout << "zwrot: " << zwrot << endl;
		//cout << "bigozz.size()+5: " << bigozz.size()+5 << endl;
		return bigozz.size()+5;
	}
	return zwrot;
}

int hookedStartowanie() {
	int zwrot = startowaniehook();
	czyWystartowano = true;
	//cout << "startowane zwrot: " << zwrot << endl;
	return zwrot;
}

int hookedSpectJoin(int int1, int int2)
{
	//cout << "hookedSpectJoin" << endl;
	//std::cout << "int1: " << int1 << std::endl; //we can access arguments passed to original function
	//std::cout << "int2: " << int2 << std::endl;
	int zwrot = SpectJoinHook(0, 1); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! to przywrocic po testach! (blokada joinowania przez host-bota)
	//int zwrot = SpectJoinHook(int1, int2); //a to zakomentowac
	//cout << "zwrot14: " << zwrot << endl;
	return zwrot;                                        //before returning to normal execution of function
}

int kto = 0x106d1250;
int kto2 = 0x106d1250;
int hookedStrzal(int var1, int var2)
{
	//cout << "hookedStrzal" << endl;
	//std::cout << "Strzal var1 hex: " << hex << var1 << " dec: " << dec << var1 << std::endl; //we can access arguments passed to original function
	//std::cout << "Strzal var2 hex: " << hex << var2 << " dec: " << dec << var2 << std::endl;
	if (var1 != 0x106d1250) {
		if (var2 == 104) {
			kto = var1;
			var1 = 0x106d1250;
		}
		else if (var2 == 10) {
			kto2 = var1;
			var1 = 0x106d1250;
			strzal(kto2, var2);
			return strzal(var1, var2);
		}
		else if (var2 == 3) {
			strzal(var1, var2);
			return strzal(0x106d1250, 10);
		}
		return strzal(var1, var2);
	}
	//cout << "Strzal zwrot: " << hex << zwrot << dec << endl;
	return strzal(var1, var2);;                                        //before returning to normal execution of function
}

int hookedDamage(int var1, int var2, int *var3, int *var4, int *var5)
{
	//cout << "hookedDamage" << endl;
	//std::cout << "Damage var1: " << hex << var1 << dec << endl; //" adress: " << hex << var1 << dec << std::endl; //we can access arguments passed to original function
	//std::cout << "Damage var2: " << var2 << std::endl;
	//std::cout << "Damage var3: " << *var3 << " adress: " << hex << var3 << dec << std::endl; //lokalizacja na mapie
	//std::cout << "Damage var4: " << *var4 << " adress: " << hex << var4 << dec << std::endl; //kierunek celowania (lotu?)
	//std::cout << "Damage var5: " << *var5 << " adress: " << hex << var5 << dec << std::endl;
	if (var2 == 104 && kto != 0x106d1250) {
		var1 = kto;
		kto = 0x106d1250;
	}
	else if (var2 == 10 && kto2 != 0x106d1250 && var1 == 0x106d1250) {
		var1 = kto2;
		kto2 = 0x106d1250;
	}
	return damage(var1, var2, var3, var4, var5);
}

int hookedIndamage1(int var1, int var2, int var3)
{
	//cout << "hookedIndamage1" << endl;
	//std::cout << "Indamage1 var1: " << hex << var1 << dec << endl; //" adress: " << hex << var1 << dec << std::endl; //we can access arguments passed to original function
	//std::cout << "Indamage1 var2: " << var2 << std::endl; //id borni
	//std::cout << "Indamage1 var3: " << var3 << std::endl; //pocisk/efekt
	int zwrot = 0;
	if (var3 == 104) zwrot = indamage1(var1, 21, 104);
	if (var1 != 0x106d1250) {
		//cout << "odbieram!!!!" << endl;
		if (var3 == 104) zwrot = indamage1(var1, 21, 104);
		else if (var3 == 10) zwrot = indamage1(var1, 12, 10);
		else if (var3 == 14) zwrot = indamage1(var1, 16, 14);
		else if (var3 == 16 || var3 == 231) zwrot = indamage1(var1, 18, 16);
		else if (var3 == 15) zwrot = indamage1(var1, 17, 15);
		else if (var3 == 4) zwrot = indamage1(var1, 7, 4);
		else if (var3 == 108 || var3 == 110) zwrot = indamage1(var1, 15, 13);
		else if (var3 == 12 || var3 == 54 || var3 == 150 || var3 == 209 || var3 == 210) zwrot = indamage1(var1, 14, 12);
		else if (var3 == 10) zwrot = indamage1(var1, 12, 10);
		else if (var3 == 205) zwrot = indamage1(var1, 21, 104);
		else if (var3 == 335 || var3 == 117) zwrot = indamage1(var1, 22, 21);
		else if (var3 == 3 || var3 == 111) zwrot = indamage1(var1, 6, 3);
		else if (var3 == 164) zwrot = indamage1(var1, 7, 4);
		else if (var3 == 5) zwrot = indamage1(var1, 4, 5);
		else if (var3 == 11) zwrot = indamage1(var1, 13, 11);
		else if (var3 == 21) zwrot = indamage1(var1, 22, 21);
		else zwrot = indamage1(var1, var2, var3);

		//cout << "Indamage1 zwrot: " << zwrot << endl;
		return zwrot;
	}
	if (var3 == 10) zwrot = indamage1(var1, 12, 10);
	else zwrot = indamage1(var1, var2, var3);
	return zwrot;                                        //before returning to normal execution of function
}

void placeJMP(BYTE * address, DWORD jumpTo, DWORD length)
{
	DWORD oldProtect, newProtect, relativeAddress;
	VirtualProtect(address, length, PAGE_EXECUTE_READWRITE, &oldProtect);
	relativeAddress = (DWORD)(jumpTo - (DWORD)address) - 5;
	*address = 0xE9;
	*((DWORD *)(address + 0x1)) = relativeAddress;
	for (DWORD x = 0x5; x < length; x++)
	{
		*(address + x) = 0x90;
	}
	VirtualProtect(address, length, oldProtect, &newProtect);
}

void serverRules() {
	string rules = (char*)0x00B73874;
	string lvlSet = (char*)0x00B65DD9;
	//cout << "levelSet: " << lvlSet << endl;
	if (lvlSet.find("beta06.lsm") == std::string::npos && lvlSet.find("beta07.lsm") == std::string::npos) {
		memcpy((void*)0x00B65DD4, "You probably have an old or different version of mod than required", 67);
		cout << "Error! You probably have an old or different version of mod than required." << endl;
		string required = lvlSet.substr(lvlSet.find("beta"), lvlSet.find(".lsm") - lvlSet.find("beta"));
		cout << "Your version: beta07 Required: " << required << endl;
		cout << "Contact kubpicapf@gmail.com" << endl;
	}
	else {
		if (rules.find("\\LvlSet\\") != std::string::npos) {
			string subString = rules.substr(rules.find("\\LvlSet\\") + 8);
			//cout << "subString1: " << subString << endl;
			subString = subString.substr(0, subString.find("\\") - 1);
			//cout << "subString2: " << subString << endl;
			subString += ".lsm";
			//cout << "LvlSet: " << subString << endl;
			strcpy((char*)0x00B65DD9, subString.c_str());
		}
	}
}


DWORD retJMP = 0x004D6012;
string lvlSet;

__declspec(naked) void myMidfuncHook() // __declspec(naked) says to the compiler that we will worry about the prolog/epilog/return of the function
{
	__asm and ecx, 03 // do what we overwrote
	__asm repe movsb

	// do what you want now, i'll obtain data from EBX register, for example, and store it for later use
	//__asm mov myData, ebx

	//if you want to do any other calls to other functions, etc and don't need the registers/stack anymore push it
	//for example:
	__asm pushad // push all general registers
	__asm pushfd // push all flags

				 // do your stuff here.. calls, calculations..
				 // remember, you can't do everything in a naked function, it's limited..

	serverRules();

	//restore stack/registers, so we don't corrupt any data and program flow continues as it should
	__asm popfd
	__asm popad

	// return where we left off
	__asm jmp[retJMP]
}

DWORD retJMP3 = 0x004827D2;

__declspec(naked) void fixSpecta() // __declspec(naked) says to the compiler that we will worry about the prolog/epilog/return of the function
{
	__asm mov eax, 0 // do what we overwrote
	__asm test ah, 10
	__asm jmp[retJMP3]
}

DWORD WINAPI Main_thread( LPVOID lpParam )
{
	srand(time(NULL));
	HANDLE han = GetStdHandle(STD_OUTPUT_HANDLE);
    WriteConsole(han,"hello",6,new DWORD,0);
	AllocConsole();
	freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
	std::cout << "Wait..." << std::endl;

	float camerafov1 = 70;
	float weaponfov1 = 50;
	float maxpan = 3000;
	dataPath = "D:\\T2KubsModData\\";

	char pathc[MAX_PATH];
	GetModuleFileNameA(hModule, pathc, sizeof(pathc));
	//cout << "pathc: " << pathc << endl;
	string path = pathc;
	path = path.substr(0, path.find_last_of("/\\"));
	string satrib = "attrib -r \"" + path + "\" /S /D"; //"\\*.*\"
	char * writablez = new char[satrib.size() + 1];
	strcpy(writablez, satrib.c_str());
	//cout << "writablez: " << writablez << endl;
	WinExec(writablez, SW_HIDE);
	delete[] writablez;
	path = path + "\\modsBotConfig.txt";
	//cout << "path: " << path << endl;
	fstream config;
	config.open(path, std::fstream::in | std::fstream::out);

	string startParams = "-maxframerate 64 -quickmouse -exclusivemouse";
	string exe = "Turok2MP.exe";
	if (!config) //if (config.good() == true)
	{
		cout << "Config not found!" << endl;
		config.open(path, std::fstream::trunc | std::fstream::out);
		config.close();
		// re-open with original flags
		config.open(path, std::fstream::in | std::fstream::out);

		//ofstream newconfig;
		//newconfig.open("launcherConfig.txt");
		config << "ExeName=Turok2MP.exe" << endl;
		config << "StartupParameters=-maxframerate 64 -quickmouse -exclusivemouse" << endl;
		config << "CameraFOV=70" << endl;
		config << "WeaponFOV=50" << endl;
		config << "DataFiles=D:\\T2KubsModData\\" << endl;
		config.close();
	}
	else {
		string slowo;
		string wiersz;
		//std::stringstream ss;
		while (getline(config, wiersz)) {
			//ss.str( std::string() ); ss.clear();
			//ss << wiersz;
			//ss >> slowo; //while(ss >> slowo){
			slowo = wiersz.substr(0, wiersz.find("=") + 1);
			//cout << slowo << endl;
			if (slowo == "WeaponFOV=") {
				string num = wiersz.substr(wiersz.find("=") + 1);
				weaponfov1 = ::atof(num.c_str());
				//cout << "weaponfov1: " << weaponfov1 << endl;
			}
			else if (slowo == "CameraFOV=") {
				string num = wiersz.substr(wiersz.find("=") + 1);
				camerafov1 = ::atof(num.c_str());
				//cout << "camerafov1: " << camerafov1 << endl;
			}
			else if (slowo == "MaxPan=") {
				string num = wiersz.substr(wiersz.find("=") + 1);
				maxpan = ::atof(num.c_str());
				//cout << "maxpan: " << maxpan << endl;
			}
			else if (slowo == "DataFiles=") {
				dataPath = wiersz.substr(wiersz.find("=") + 1);
				cout << "dataPath: " << dataPath << endl;
			}
			slowo.clear();
			wiersz.clear();
		}
	}

	string tempDataPath = dataPath + "bans\\";
	CreateDirectory(tempDataPath.c_str(), NULL);
	tempDataPath = dataPath + "accounts\\";
	CreateDirectory(tempDataPath.c_str(), NULL);
	tempDataPath = dataPath + "loginsELO\\";
	CreateDirectory(tempDataPath.c_str(), NULL);
	tempDataPath = dataPath + "nicksELO\\";
	CreateDirectory(tempDataPath.c_str(), NULL);
	tempDataPath = dataPath + "tidsELO\\";
	CreateDirectory(tempDataPath.c_str(), NULL);

	satrib = "attrib -r \"" + dataPath + "*.*\" /S /D";
	writablez = new char[satrib.size() + 1];
	strcpy(writablez, satrib.c_str());
	//cout << "writablez: " << writablez << endl;
	WinExec(writablez, SW_HIDE);
	delete[] writablez;

	//satrib = "attrib -r \"" + dataPath.substr(0, dataPath.find_last_of("\\")) + "\" /S /D";
	//writablez = new char[satrib.size() + 1];
	//strcpy(writablez, satrib.c_str());
	//cout << "writablez: " << writablez << endl;
	//WinExec(writablez, SW_HIDE);
	//delete[] writablez;

	/*accounts.open(dataPath + "accounts.txt", std::fstream::in | std::fstream::out);

	if (!accounts)
	{
		accounts.open(dataPath + "accounts.txt", std::fstream::trunc | std::fstream::out);
		accounts.close();
		// re-open with original flags
		accounts.open(dataPath + "accounts.txt", std::fstream::in | std::fstream::out);
	}
	if (accounts.good() == true)
	{
		std::cout << "accounts.txt opened successfully." << std::endl;
	}
	else std::cout << "Failed to open accounts.txt!" << std::endl;*/
	//accounts << "sieeeemanko ziomeczkiiii" << endl;
	Sleep(1000);
	DWORD address = (DWORD)hModule + 0x28D28;
	//cout << "address: " << hex << address << endl;

	placeJMP((BYTE*)0x004D600D, (DWORD)myMidfuncHook, 5);
	placeJMP((BYTE*)0x004827CC, (DWORD)fixSpecta, 6);

	killStrings.push_back(" was sliced and diced by %s."); //WarBladew
	killStrings.push_back(" was skewered by %s."); //TekBow
	killStrings.push_back(" caught a bullet from %s."); //Pistol
	killStrings.push_back(" took a fatal slug from %s."); //Magnum
	killStrings.push_back(" got a charge out of %s."); //ChargeDart
	killStrings.push_back(" couldn't dodge %s's buckshot."); //ShotGun
	killStrings.push_back(" was blown away by %s's shredder."); //Shredder
	killStrings.push_back(" got seared by %s."); //PlasmaRifle
	killStrings.push_back(" got caught in %s's fire storm."); //FirestormCannon
	killStrings.push_back(" couldn't handle %s's grenade."); //GrenadeLauncher
	killStrings.push_back(" was vaporized by %s's rocket."); //ScorpionRocket
	killStrings.push_back(" got torched by %s."); //FlameThrower
	killStrings.push_back(" got speared by %s."); //Speargun (harpoon)
	killStrings.push_back(" took a ride on %s's torpedo."); //Torpedo
	killStrings.push_back(" got a noogie from %s."); //CerebralBore
	killStrings.push_back(" was clawed by %s."); //RaptorClaw
	killStrings.push_back(" was in the way of %s's shredder."); //ShredderExplosion
	killStrings.push_back(" tried to run from %s's grenade."); //GrenadeExplosion
	killStrings.push_back(" got caught in %s's blast zone."); //ScorpionExplosion
	killStrings.push_back(" saw %s's mushroom cloud."); //NukeExplosion
	killStrings.push_back(" died in %s's explosion."); //DefaultExplosion
	//killStrings.push_back(" was in %s's teleport zone."); //TeleportKill
	killStrings.push_back(" was killed by %s."); //unknown weapon? (got this killing with zoomed tekbow)

	cout << "Bot (dll) injected successfully. b0.7" << endl;

	//while(*((int*)0x00AD0280)!=1);
	while (!czyWystartowano) Sleep(500);
	DWORD origProtect;
	VirtualProtect((void*)address, 5, PAGE_EXECUTE_READWRITE, &origProtect);
	memcpy((void*)address, "\xD9\x1D\x56\xBD\xAC", 5);
	VirtualProtect((void*)address, 5, origProtect, NULL);

	Sleep(1000);
	int spect = 4198400;
	VirtualProtect((LPVOID)(0x00AD03D8), sizeof(spect), PAGE_EXECUTE_READWRITE, 0);
	while (true) {
		Sleep(16);
		memcpy((LPVOID)0x00AD03D8, &spect, sizeof(spect));
		int var = *((int*)0x106D1C84);
		if (var == 1 || var == 2) {
			VirtualProtect((LPVOID)(0x106FD408), sizeof(camerafov1), PAGE_EXECUTE_READWRITE, 0);
			VirtualProtect((LPVOID)(0x00523E5C), sizeof(weaponfov1), PAGE_EXECUTE_READWRITE, 0);
			memcpy((LPVOID)0x106FD408, &camerafov1, sizeof(camerafov1));
			memcpy((LPVOID)0x00523E5C, &weaponfov1, sizeof(weaponfov1));
			break;
		}
	}
	Sleep(400);
	memcpy((LPVOID)0x00AD03D8, &spect, sizeof(spect));
	SpectJoinHook(0, 1);

	string bigozz = " \x4/aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	char * writable = new char[bigozz.size() + 1];
	strcpy( writable, bigozz.c_str() );
	VirtualProtect((LPVOID)(0x00AD8384), strlen(writable)+1, PAGE_EXECUTE_READWRITE, 0);
	memcpy( (LPVOID)0x00AD8384, writable, strlen(writable)+1);
	delete [] writable;
	//cout << "SIEMA! host" << endl;
	memcpy((LPVOID)0x106FD408, &camerafov1, sizeof(camerafov1));
	memcpy((LPVOID)0x00523E5C, &weaponfov1, sizeof(weaponfov1));
	
	Sleep(2000);
	wyslij(" \x4/00 rdy");

	//ZOMBIES vvvvvvvvvvvvvvvvvvvvvvvv
	//plugin:	
		/*
        std::stringstream ss;
		std::clock_t start;
        int sekunda;
        int ilosc_zombie;
        double duration;
        int punktyzombie = 0;
        int punktysurvivors = 0;
	
	do{
		for (auto it = commands.begin(); it != commands.end();) {
			string command = std::get<0>(*it);
			cout << "custom command: " << command << endl;

			if (command.find("set char ") == 0) {
				int var = -1;
				var = atoi(command.substr(9).c_str());
				if (var >= 0 && var <= 10) {
					ss.str("");
					ss << " \x4/" << dec << zeranumer(std::get<1>(*it)) << " write i 0x106D1770 " << dec << var;
					wyslij(ss.str());
				}
				else {
					ss.str("");
					ss << " \x4/" << dec << zeranumer(std::get<1>(*it)) << " news You entered the wrong variable (Valid range is 0-10).";
					wyslij(ss.str());
				}
			} else if (command.find("set color ") == 0) {
				int var = -1;
				var = atoi(command.substr(10).c_str());
				if (var >= 0 && var <= 8) {
					if (var == 0) var = 4294967295;
					else var--;
					ss.str("");
					ss << " \x4/" << dec << zeranumer(std::get<1>(*it)) << " write i 0x106D25A4 " << dec << var;
					wyslij(ss.str());
				}
				else {
					ss.str("");
					ss << " \x4/" << dec << zeranumer(std::get<1>(*it)) << " news You entered the wrong variable (Valid range is 0-8).";
					wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << dec << zeranumer(std::get<1>(*it)) << " news 0-none 1-red 2-blue 3-green 4-yellow 5-purple 6-cyan 7-brown 8-turquoise";
					wyslij(ss.str());
				}
			} else if (command.find("set color") == 0) {
				ss.str("");
				ss << " \x4/" << dec << zeranumer(std::get<1>(*it)) << " news 0-none 1-red 2-blue 3-green 4-yellow 5-purple 6-cyan 7-brown 8-turquoise";
				wyslij(ss.str());
			}

			it = commands.erase(it);
		}*/
		
        /*if(ingameCount >= 2 && fazagry == 0){ //if(players.size() >= 1 && fazagry == 0){ //playersCount >= 1
            fazagry = 1;
            start = std::clock();
            sekunda = 1;
        }
		else if(fazagry == 1){
            duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
            if(duration > sekunda){
                if(duration > 10){
                    ss.str("");
                    ss << " \x4/00" << " rfreeze 0x106D1D8C"; //0x106D1C70
                    wyslij(ss.str());
                    fazagry = 2;
                    start = std::clock();
                    sekunda = 1;
                    //std::mt19937 rnd( std::time( NULL ) );
                    //std::uniform_real_distribution < double > dist( 1, players.size()); //tu podajesz przedział
					//int rzombie = dist(rnd);
					int rzombie = (std::rand() % ingameCount) + 1;
					int i = 1;
					for (auto it = players.begin(); it != players.end(); it++) {
						if (i == rzombie) {
							while (pid_status[it->first] != 2 && it != players.end()) it++;
							if (it == players.end()) {
								rzombie = 98;
								fazagry = 3;
							}
							rzombie = it->first;
							break;
						}
						i++;
					}
					//rzombie = 2;
                    ilosc_zombie = 1;
					//rzombie = 2;
					ss.str("");
					ss << " \x4/" << zeranumer(rzombie) << " blspect";
					wyslij(ss.str());
                    ss.str("");
                    ss << " \x4/" << zeranumer(rzombie) << " freeze i 0x106D1C94 500"; //waterfog
                    wyslij(ss.str());
                    ss.str("");
                    ss << " \x4/" << zeranumer(rzombie) << " freeze i 0x106D1770 10"; //numerChar
                    wyslij(ss.str());
                    ss.str("");
                    ss << " \x4/" << zeranumer(rzombie) << " freeze i 0x106D1D8C 34"; //ktoraBron
                    wyslij(ss.str());
                    ss.str("");
                    ss << " \x4/" << zeranumer(rzombie) << " freeze i 0x00AD02EC 1"; //set666
                    wyslij(ss.str());
                    ss.str("");
                    ss << " \x4/" << zeranumer(rzombie) << " freeze i 0x00AD0478 458752";
                    wyslij(ss.str());

                    //ss.str("");
                    //ss << " \x4/" << zeranumer(rzombie) << " freeze i 0x106D25A4 0"; //kolor
                    //wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(rzombie) << " callf i2 0x47FE00 (275579912, 275579296)";
					wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(rzombie) << " callf i1 0x486100 (0)";
					wyslij(ss.str());

					ss.str("");
					ss << " \x4/" << zeranumer(rzombie) << " respawn";
					wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(rzombie) << " news You have just been infected.";
					wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(rzombie) << " news Red players with a burning head are your friends. The others must die!";
					wyslij(ss.str());
                    for(int i = 1; i <= playersid; i++ ){
                        if(i == rzombie) continue;
                        ss.str("");
                        ss << " \x4/" << zeranumer(i) << " freeze i 0x005D5A60 16384"; //blacout
                        wyslij(ss.str());
                        ss.str("");
                        ss << " \x4/" << zeranumer(i) << " observe 0x106D1394 0 1 0";
                        wyslij(ss.str());
                        ss.str("");
                        ss << " \x4/" << zeranumer(i) << " freeze i 0x106D1C94 0";
                        wyslij(ss.str());

                        //ss.str("");
                        //ss << " \x4/" << zeranumer(i) << " freeze i 0x00AD0480 4294967295";
                        //wyslij(ss.str());
						ss.str("");
						ss << " \x4/" << zeranumer(i) << " callf i2 0x47FE00 (275579872, 275579296)";
						wyslij(ss.str());
						ss.str("");
						ss << " \x4/" << zeranumer(i) << " callf i1 0x486100 (-1)";
						wyslij(ss.str());

						ss.str("");
						ss << " \x4/" << zeranumer(i) << " freeze i 0x106D1770 0";
						wyslij(ss.str());
						ss.str("");
						ss << " \x4/" << zeranumer(i) << " unblspect";
						wyslij(ss.str());
						ss.str("");
						ss << " \x4/" << zeranumer(i) << " respawn";
						wyslij(ss.str());
						ss.str("");
						ss << " \x4/" << zeranumer(i) << " news You are one of the survivors. Work with other colorless players to survive - but... Can you trust them?";
						wyslij(ss.str());
						ss.str("");
						ss << " \x4/" << zeranumer(i) << " news Red players with a burning head are zombies. Try to avoid them!";
						wyslij(ss.str());
                    }
                }else{
                //ss << " //00 write " << hex << "0x" << std::setfill ('0') << std::setw (8) << adres << " " << dec << 10 - sekunda;
                ss.str("");
                ss << " " << dec << 10 - sekunda;
                wyslij(ss.str());
                //cout << ss.str() << endl;
                sekunda++;
				Sleep(500);
                }
            }
        }
		else if(fazagry == 2){
            //losowanie jednego gracza jako zombie i noc dla pozosta³ych
            //kontrolowanie czy zyje, bo jak nie to zamiania w zombie
            //kontrola czasu do dnia i ilosci ocaleñców
            //for (auto const& p : event) {}
            auto it = eventf.begin();
            while (it != eventf.end())
			//for(it = event.begin(); it != event.end(); it++)
            {
                //pair<int,int> para = p.first;
                //cout << "jestem w eventach" << endl;
                //cout << "Adres: " << std::get<0>(it->first) << endl;
                //cout << "ID: " << std::get<1>(it->first) << endl;
                //cout << "var: " << it->second << endl;
                if(std::get<0>(it->first) == 0x106D1394){ // && it->second == 0
                    //cout << "zara zrobie wysylanie do gracza numer " << zeranumer(std::get<1>(it->first)) << endl;
					ss.str("");
					ss << " \x4/" << zeranumer(std::get<1>(it->first)) << " blspect";
					wyslij(ss.str());
					ss.str("");
                    ss << " \x4/" << zeranumer(std::get<1>(it->first)) << " robserve 0x0054C684";
                    wyslij(ss.str());
                    ss.str("");
                    ss << " \x4/" << zeranumer(std::get<1>(it->first)) << " rfreeze 0x005D5A60";
                    wyslij(ss.str());
					ss.str("");
                    ss << " \x4/" << zeranumer(std::get<1>(it->first)) << " write i 0x005D5A60 0"; //blacout
                    wyslij(ss.str());
                    ss.str("");
                    ss << " \x4/" << zeranumer(std::get<1>(it->first)) << " freeze i 0x106D1C94 500";
                    wyslij(ss.str());
                    ss.str("");
                    ss << " \x4/" << zeranumer(std::get<1>(it->first)) << " freeze i 0x106D1770 10";
                    wyslij(ss.str());
                    ss.str("");
                    ss << " \x4/" << zeranumer(std::get<1>(it->first)) << " freeze i 0x106D1D8C 34";
                    wyslij(ss.str());
                    ss.str("");
                    ss << " \x4/" << zeranumer(std::get<1>(it->first)) << " freeze i 0x00AD02EC 1";
                    wyslij(ss.str());
                    ss.str("");
                    ss << " \x4/" << zeranumer(std::get<1>(it->first)) << " freeze i 0x00AD0478 458752";
                    wyslij(ss.str());

                    //ss.str("");
                    //ss << " \x4/" << zeranumer(std::get<1>(it->first)) << " freeze i 0x106D25A4 0";
                    //wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(std::get<1>(it->first)) << " callf i2 0x47FE00 (275579912, 275579296)";
					wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(std::get<1>(it->first)) << " callf i1 0x486100 (0)";
					wyslij(ss.str());

					ss.str("");
					ss << " \x4/" << zeranumer(std::get<1>(it->first)) << " news You have just been infected.";
					wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(std::get<1>(it->first)) << " news Red players with a burning head are your friends. The others must die!";
					wyslij(ss.str());
                    ilosc_zombie++;
                    if(ilosc_zombie >= ingameCount){
						ss.str("");
						ss << " ZOMBIES WIN!";
						wyslij(ss.str());
						punktyzombie++;
						fazagry = 3;
                    }
				}
				else if (std::get<0>(it->first) == -1) {
					//wyslij("omg ktos wlaz na specta");
					//cout << "omg ktos wlaz na specta" << endl;
					ss.str("");
					ss << " \x4/" << zeranumer(std::get<1>(it->first)) << " rfreeze 0x106D1C94";
					wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(std::get<1>(it->first)) << " rfreeze 0x106D1770";
					wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(std::get<1>(it->first)) << " rfreeze 0x106D1D8C";
					wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(std::get<1>(it->first)) << " robserve 0x106D1394";
					wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(std::get<1>(it->first)) << " rfreeze 0x005D5A60";
					wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(std::get<1>(it->first)) << " write i 0x005D5A60 0"; //blacout
					wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(std::get<1>(it->first)) << " rfreeze 0x00AD02EC"; //set666
					wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(std::get<1>(it->first)) << " rfreeze 0x00AD0478";
					wyslij(ss.str());

					//ss.str("");
					//ss << " \x4/" << zeranumer(std::get<1>(it->first)) << " rfreeze 0x106D25A4"; //kolor
					//wyslij(ss.str());

					ss.str("");
					ss << " \x4/" << zeranumer(std::get<1>(it->first)) << " write i 0x00AD02EC 0";
					wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(std::get<1>(it->first)) << " write i 0x106D1D8C 4";
					wyslij(ss.str());
					ss.str("");
					ss << " \x4/" << zeranumer(std::get<1>(it->first)) << " unblspect";
					wyslij(ss.str());
					if (ilosc_zombie >= ingameCount) {
						ss.str("");
						ss << " ZOMBIES WIN!";
						wyslij(ss.str());
						punktyzombie++;
						fazagry = 3;
					}
				}
                //event.erase(p.first);
				//event.erase (it);
				//it = event.begin();
				it = eventf.erase(it);
            }

            if(fazagry == 2){
                auto duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
                if(duration > sekunda){
                    if(sekunda == 60){
                        ss.str("");
                        ss << " 2 minutes left to the day!";
                        wyslij(ss.str());
                    } else
                    if(sekunda == 120){
                        ss.str("");
                        ss << " 1 minute left to the day!";
                        wyslij(ss.str());
                    } else
                    if(sekunda == 150){
                        ss.str("");
                        ss << " 30 seconds left to the day!";
                        wyslij(ss.str());
                    } else
                    if(sekunda == 170){
                        ss.str("");
                        ss << " 10 seconds left to the day!";
                        wyslij(ss.str());
                    } else
                    if(sekunda == 177){
                        ss.str("");
                        ss << " 3";
                        wyslij(ss.str());
                    } else
                    if(sekunda == 178){
                        ss.str("");
                        ss << " 2";
                        wyslij(ss.str());
                    } else
                    if(sekunda == 179){
                        ss.str("");
                        ss << " 1";
                        wyslij(ss.str());
                    } else
                    if(sekunda > 180){
                        fazagry = 3;
                        ss.str("");
                        ss << " SURVIVORS WIN!";
                        wyslij(ss.str());
                        punktysurvivors++;
                    }
                    sekunda++;
                }
            }
			Sleep(200);
        }
		else if(fazagry == 3){
            fazagry = 4;
			ss.str("");
			ss << " \x4/00" << " blspect";
			wyslij(ss.str());
            ss.str("");
            ss << " \x4/00" << " rfreeze 0x106D1C94";
            wyslij(ss.str());
            ss.str("");
            ss << " \x4/00" << " rfreeze 0x106D1770";
            wyslij(ss.str());
            ss.str("");
            ss << " \x4/00" << " rfreeze 0x106D1D8C";
            wyslij(ss.str());
            ss.str("");
            ss << " \x4/00" << " robserve 0x106D1394";
            wyslij(ss.str());
            ss.str("");
            ss << " \x4/00" << " rfreeze 0x005D5A60";
            wyslij(ss.str());
			ss.str("");
            ss << " \x4/00" << " write i 0x005D5A60 0"; //blacout
            wyslij(ss.str());
            ss.str("");
            ss << " \x4/00" << " rfreeze 0x00AD02EC"; //set666
            wyslij(ss.str());
            ss.str("");
            ss << " \x4/00" << " rfreeze 0x00AD0478";
            wyslij(ss.str());

            //ss.str("");
            //ss << " \x4/00" << " rfreeze 0x106D25A4"; //kolor
            //wyslij(ss.str());

            ss.str("");
            ss << " \x4/00" << " write i 0x00AD02EC 0";
            wyslij(ss.str());
            ss.str("");
            ss << " \x4/00" << " write i 0x106D1D8C 4";
            wyslij(ss.str());

			//ss.str("");
			//ss << " \x4/00" << " write i 0x106D25A4 2";
			//wyslij(ss.str());
			ss.str("");
			ss << " \x4/00" << " callf i2 0x47FE00 (275579952, 275579296)";
			wyslij(ss.str());
			ss.str("");
			ss << " \x4/00" << " callf i1 0x486100 (2)";
			wyslij(ss.str());

			ss.str("");
			ss << " \x4/00" << " write i 0x106D1770 0";
			wyslij(ss.str());
            ss.str("");
            ss << " \x4/00" << " freeze i 0x106D1D8C 14";
            wyslij(ss.str());
            start = std::clock();
            sekunda = 1;
        }
		else if(fazagry == 4){
            duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
            if(duration > sekunda){
                if(sekunda > 7){
                    fazagry = 0;
                }
				else if(sekunda == 2){
                    ss.str("");
                    ss << "SURVIVORS " << punktysurvivors << ":" << punktyzombie << " ZOMBIES";
                    wyslij(ss.str());
                }
                sekunda++;
				Sleep(500);
            }
		} else Sleep(3000);

        }while(true);*/
	//ZOMBIES ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    return S_OK;
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
{
if (dwReason == DLL_PROCESS_ATTACH)
	{
		originalFunction = (int(__cdecl*)(const char *text))DetourFunction((PBYTE)ADDRESS, (PBYTE)hookedFunction); //Magic
		wysylaniehook = (int(__cdecl*)(char *text))DetourFunction((PBYTE)0x4C3250, (PBYTE)hookedFunction2); //4C3250 4C30E0
		wysylaniehook2 = (int(__cdecl*)(int text1, int text2))DetourFunction((PBYTE)0x48FC40, (PBYTE)hookedFunction3); //0048FC40 //int __cdecl sub_48FC40(int, int)
		//wysylaniehook3 = (int(__cdecl*)(char *text1, int text2))DetourFunction((PBYTE)0x4C30E0, (PBYTE)hookedFunction4); //int (__cdecl* wysylaniehook3)(char *text, int var);
		//wysylaniehook4 = (int(__cdecl*)(char *text1, char *text2))DetourFunction((PBYTE)0x4A44D0, (PBYTE)hookedFunction5); //int (__cdecl* wysylaniehook4)(char *text1, char *text2); //crashuje
		//wysylaniehook5 = (int(__cdecl*)(char *text))DetourFunction((PBYTE)0x48A7A0, (PBYTE)hookedFunction6); //(char *text); //int __cdecl sub_48A7A0(int)
		//wysylaniehook6 = (int(__cdecl*)(char *text))DetourFunction((PBYTE)0x4A3140, (PBYTE)hookedFunction7); //(char *text); //int __cdecl sub_4A3140(int)
		//wysylaniehook7 = (int(__cdecl*)(char *text))DetourFunction((PBYTE)0x471A30, (PBYTE)hookedFunction8); //(char *text); //int __cdecl sub_471A30(int)
		//wysylaniehook8 = (int(__cdecl*)(char *text1, char *text2))DetourFunction((PBYTE)0x4C9DC0, (PBYTE)hookedFunction9); //(char *text1, char *text2); //int __cdecl sub_4C9DC0(int, int)
		startowaniehook = (int(__cdecl*)())DetourFunction((PBYTE)0x4C0310, (PBYTE)hookedStartowanie);
		SpectJoinHook = (int(__cdecl*)(int int1, int int2))DetourFunction((PBYTE)0x485B00, (PBYTE)hookedSpectJoin); //int(__cdecl* SpectJoinHook)(int int1, int int2); //int __cdecl sub_485B00(int, int)
		strzal = (int(__cdecl*)(int var1, int var2))DetourFunction((PBYTE)0x419260, (PBYTE)hookedStrzal); //int(__cdecl* zmianaAmmoHook)(float var1, float var2);//int(__cdecl* strzal)(float var1, float var2); //int __cdecl sub_419260(float, float)
		damage = (int(__cdecl*)(int var1, int var2, int *var3, int *var4, int *var5))DetourFunction((PBYTE)0x488000, (PBYTE)hookedDamage); //int(__cdecl* damage)(int var1, int var2, int var3, int var4, int var5); //int __cdecl sub_488000(int, int, int, int, int) damage
		indamage1 = (int(__cdecl*)(int var1, int var2, int var3))DetourFunction((PBYTE)0x419220, (PBYTE)hookedIndamage1); //int(__cdecl* indamage1)(int var1, int var2, int var3); //int __cdecl sub_419220(int, int, int) indamage1
		CreateThread(0, 0x1000, &Main_thread, 0, 0, NULL); 
		CreateThread(0, 0, &wykonywanie_polecen, 0, 0, NULL);
	}
return TRUE;
}
