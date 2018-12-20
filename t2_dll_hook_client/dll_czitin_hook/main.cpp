//player
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
#include <chrono>
#include <thread>
#include <future>
#include <algorithm>
#include <fstream>
#include "md5.h"
#include <ctime>
#include <stdio.h>
#define CURL_STATICLIB
#include "curl/curl.h"
#include <iterator>

//#include <cstdlib>
//#include "sha256.h"
#ifdef _DEBUG
# define Debug(fmtstr, ...) printf(fmtstr, ##__VA_ARGS__)
#pragma comment (lib, "curl/libcurl_a_debug.lib")
#else
//# define Debug(fmtstr, ...)
#pragma comment (lib, "curl/libcurl_a.lib")
#endif

using namespace std;

//#define ADDRESS 0x48AE90    //This is the address where our targeted function begins
#define ADDRESS 0x48A7A0 //48A7A0 
int myid = -1;
map<int, int> frezeI;
map<int, float> frezeF;
map<int, string> frezeS;
map<int, float> observe;
map<int, float> observef;
map<int, float> customDamage;
map<int, float> customNode;
map<string, list<pair<int, int>>> customDrop;
map<int, list<pair<int, int>>> customPickup;
map<int, int> customPchance;
map<int, int> extraAmmo;
bool czy_wyslane_join = false;
map<int, int>::iterator it;
list<string> dowyslania;
list<string> commands;
list<string> polecenia;
vector<string> startingWeapons;
vector<string> turokWeapons;
vector<string> adonWeapons;
vector<string> gantWeapons;
vector<string> fleshWeapons;
vector<string> purWeapons;
vector<string> endWeapons;
vector<string> fireWeapons;
vector<string> iggyWeapons;
vector<string> campWeapons;
vector<string> telWeapons;
map<int, string> charMOTD;
char charek;
std::list<string>::iterator iter;
char * writable;
byte dataz[] = { 0x00, 0x10, 0xFF, 0xFF };
//DWORD hackBaseAddress = {0x00000000};
DWORD hackOffsets[] = { 0x3d };
HMODULE hModule = GetModuleHandle(NULL);
DWORD baseAddress = (DWORD)hModule + 0x00778550;
bool czyWystartowano = false;
//std::string lastcommand = " ";
bool hideUnkCommandText = false;
bool czyJoined = false;
bool czyHostVoice = false;
bool czy_sprawdzanie_voice = false;
bool czy_blokada_specta = true;
bool czy_unfreezeall = false;
bool czy_unobserveall = false;
bool czy_mozna_spect = true;
bool czy_spectate_enabled = true;
bool czy_setColor_enabled = false;
bool czy_potwierdzenie_rejestracji = false;
bool czy_zalogowany = false;
bool czy_customDrops_enabled = false;
//bool czy_arena = false;
bool czy_ServerBotRequired = false;
bool czy_ServerBot = false;
bool czy_custom_damage = false;
bool czy_customDrops_config = false;
bool czy_customPickups_config = false;
bool czy_customPickups_enabled = false;
bool czy_customWeapons = false;
bool czy_userBlackOil = true;
bool czyInfoOil = false;
int dchance = 25;
//int pchance = 25;
int licznik_komend = 0;
std::string login;
std::string password;
//int ilenasekunde = 0;
int status = 0; //0-observator 1-waiting4game 2-inGame
bool pfmlayer = false;
bool sunfirepod = false;
bool czyPiorun = false;
//int lokalizacja = 0;
//int kierunek = 0;
bool strzelRidingGun = false;
bool strzel2 = false;
bool strzel3 = false;
bool strzel4 = false;
bool strzel5 = false;
bool strzelBlackOil = false;
bool strzelAirStrike = false;
bool razor = false;
bool cbore = false;
bool usypiacz = false;
bool nuke = false;
bool pistol = false;
bool bow = false;
bool tekbow = false;
bool shotgun = false;
int indmg1var2 = 0;
int indmg1var3 = 0;
bool stronaRidingGun = false;
bool czyLastAmmo = false;
bool czyinfo1 = false;
bool czyinfo2 = false;
bool czyinfo3 = false;
bool czyinfo4 = false;
bool czyinfoRazor = false;
int czyinfoAirStrike = 0;
int customWeaponId = 0;
int airStrikeWith = 16; //torpedo
int dinoRidingWith = 4; //chargeDart
int blackOilWith = 5; //pistol
bool czyTorpedoDisabledOnGround = false;
int airStrikeDelay = 0;
int airStrikeAmmoId = 18; //torpedo
int airStrikeAmmoCost = 6;
int howManyExtraNukeExplosions = 2;
bool czyUserRazors = true;
bool czyForceSpectNaStart = false;
bool czyPobranoUstawienia = false;
bool startingMaxAmmo = false;
bool isTeamGameMode = false;
string globalnick;
string tid;
float defaultDamage = -1;
float defaultNode = -1;
float currentfov = 0;
string cfgurl = "null";
string adminPassword;
string passedPassword;

int(__cdecl* originalFunction)(const char *text); //Pointer to the function we are going to hook, must be declared same as original(returns double and takes double as argument)
int(__cdecl* wysylaniehook)(char *text); //int __cdecl sub_4C3250(char *);
int(__cdecl* wysylaniehook2)(int text1, int text2); //int __cdecl sub_48FC40(int, int)
/*int(__cdecl* wysylaniehook3)(char *text1, int text2); //int __cdecl sub_4C30E0(char *, int);
int(__cdecl* wysylaniehook4)(char *text1, char *text2); //int __cdecl sub_4A44D0(int, int)
int(__cdecl* wysylaniehook5)(char *text); //int __cdecl sub_48A7A0(int)
int(__cdecl* wysylaniehook6)(char *text); //int __cdecl sub_4A3140(int)
int(__cdecl* wysylaniehook7)(char *text); //int __cdecl sub_471A30(int)
int(__cdecl* wysylaniehook8)(char *text1, char *text2); //int __cdecl sub_4C9DC0(int, int)*/
int(__cdecl* SpectJoinHook)(int int1, int int2); //int __cdecl sub_485B00(int, int)
int(__cdecl* startowaniehook)(); //int sub_4C0310()
int(__cdecl* wydropienieBroniHook)(int var1, int var2, float var3); //int __cdecl sub_4261F0(float, int, float);
int(__cdecl* podniesienieBroniHook)(int int1, int int2); //int __cdecl sub_480D80(int, int)
int(__cdecl* strzal)(int var1, int var2); //int __cdecl sub_419260(float, float)
int(__cdecl* damage)(int var1, int var2, int *var3, int *var4, int *var5); //int __cdecl sub_488000(int, int, int, int, int) damage
int(__cdecl* indamage1)(int var1, int var2, int var3); //int __cdecl sub_419220(int, int, int) indamage1
//int(__cdecl* sfx)(__int16 var1); //int __cdecl sub_431FD0(__int16) realDzwiekCzatu
//int(__cdecl* zmiananickuHook)(); //int sub_482220()
int(__cdecl* TeamChangeHook)(int int1); //int __cdecl sub_485EB0(int)
//int(__cdecl* zmianaKoloru)(int int1); //int __cdecl sub_486100(int)
//int(__cdecl* preZmianaKoloru)(int int1, int int2); //int __cdecl sub_47FE00(int, int)
//int __cdecl sub_4C4D30(int, int, int, int)
//int __cdecl sub_4C6ED0(int, int)
int(__cdecl* respawn)(int int1); //int __cdecl sub_425F50(int)
int(__cdecl* changeChar)(int int1);
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

								 //int __cdecl sub_4BCBD0(HWND hDlg, int);



typedef void(__cdecl* fcstr_)(char *text);
fcstr_ wysylanie = (fcstr_)0x4C3250; //0x4A4C30 

//typedef void(__cdecl* komunikat_)(char *text);
fcstr_ komunikat = (fcstr_)0x48A7A0;

typedef void(__cdecl* f1int_)(int int1);
f1int_ zmianaKoloru = (f1int_)0x486100;

typedef void(__cdecl* f2ints_)(int int1, int int2);
f2ints_ preZmianaKoloru = (f2ints_)0x47FE00;

//typedef void(__cdecl* SpectJoin_)(int int1, int int2);
f2ints_ SpectJoin = (f2ints_)0x485B00;

typedef void(__cdecl* f2ints1float_)(int var1, int var2, float var3);
f2ints1float_ dropWeapon = (f2ints1float_)0x4261F0;

typedef void(__cdecl* sfx_)(__int16 var1);
sfx_ sfx = (sfx_)0x431FD0;

typedef void(__cdecl* f1float_)(float float1);
typedef void(__cdecl* f2floats_)(float float1, float float2);
typedef void(__cdecl* fnoarg_)();

void WriteToMemory(void * addressToWrite, const void * valueToWrite, size_t byteNum)
{
	//used to change our file access type, stores the old
	//access type and restores it after memory is written
	unsigned long OldProtection;
	//give that address read and write permissions and store the old permissions at oldProtection
	VirtualProtect(addressToWrite, byteNum, PAGE_EXECUTE_READWRITE, &OldProtection);

	//write the memory into the program and overwrite previous value
	memcpy(addressToWrite, valueToWrite, byteNum);

	//reset the permissions of the address back to oldProtection after writting memory
	VirtualProtect(addressToWrite, byteNum, OldProtection, NULL);
}

DWORD FindDmaAddy(int PointerLevel, DWORD Offsets[], DWORD BaseAddress)
{
	//DEFINES OUR ADDRESS to write to
	//if statements are crucial to make sure that the address is valid to write
	//otherwise we crash. Address will not be valid when things like map changes or game loads are happening
	DWORD Ptr = *(DWORD*)(BaseAddress); //Base Address
	if (Ptr == 0) return NULL;//prevent crash

							  //this is done to allow us to have pointers up to many levels e.g.10
	for (int i = 0; i < PointerLevel; i++)
	{
		//if it = PointerLevel-1 then it reached the last element of the array
		//therefore check if that address plus the offset is valid and leave the loop
		if (i == PointerLevel - 1)
		{
			//!!make sure the last address doesnt have the asterisk on DWORD otherwise incoming crash
			Ptr = (DWORD)(Ptr + Offsets[i]);  //Add the final offset to the pointer
			if (Ptr == 0) return NULL;//prevent crash
									  //we here return early because when it hits the last element
									  //we want to leave the loop, specially adapted for offsets of 1
			return Ptr;
		}
		else
		{
			//if its just a normal offset then add it to the address
			Ptr = *(DWORD*)(Ptr + Offsets[i]); //Add the offsets
			if (Ptr == 0) return NULL;//prevent crash
		}
	}
	return Ptr;
}

void wyslij(string bigos)
{
	if (bigos.find(" \x4/") == 0 && bigos.find("voice") == std::string::npos && bigos.find("gvoice") == std::string::npos) //czy znaleziono komende
	{
		string bigosmd5 = md5(bigos+" salt");
		bigosmd5 = " h;" + bigosmd5;
		bigos += bigosmd5;
	}
	if(czy_ServerBot) dowyslania.push_back(bigos);
}

string zeranumer(int value, int digits = 2) { //const char *
	std::string result;
	while (digits-- > 0) {
		result += ('0' + value % 10);
		value /= 10;
	}
	std::reverse(result.begin(), result.end());
	return result;
	//return result.c_str();
}

void dodaj_customPickup(int main, int pick, int ammo) {
	if (customPickup.find(main) == customPickup.end()) {
		list<pair<int, int>> lista;
		customPickup[main] = lista;
	}
	auto it = customPickup.find(main);

	if (it != customPickup.end()) {
		std::list<pair<int, int>> *p = NULL;
		p = &(it->second);
		(*p).push_back(std::make_pair(pick, ammo));
		//cout << "add cPick main: " << main << " pick: " << pick << " ammo: " << ammo << endl;
	}
}

void sendJoin() {
		czy_wyslane_join = true;
		
		std::mt19937 rnd(std::time(NULL));
		std::uniform_real_distribution < double > dist(100, 999); //tu podajesz przedział
		myid = dist(rnd);
		std::stringstream ss;
		ss.str("");
		ss << " \x4/99 join " << myid;
		wyslij(ss.str());
}

void sprawdzNick() {
	//Sleep(500);
	string nick = (char*)0x00AD045C;
	char chars[] = "/:;\\"; //usuniecie tych znakow z nicku:
	for (unsigned int i = 0; i < strlen(chars); ++i) nick.erase(std::remove(nick.begin(), nick.end(), chars[i]), nick.end());

	if (nick != globalnick && czyJoined) {
		globalnick = nick;
		std::stringstream ss;
		ss.str("");
		ss << " \x4/99 cnick " << zeranumer(myid) << " " << nick;
		wyslij(ss.str());
	}

	char * writable = new char[nick.size() + 1];
	strcpy(writable, nick.c_str());
	WriteToMemory((LPVOID)0x00AD045C, writable, strlen(writable) + 1);
	delete[] writable;
}

void forcespect(bool czy_w4game, bool czy_custom_napis, string s) {
	int adres = 0x00AD03D8;
	int var = 4198400;
	WriteToMemory((LPVOID)adres, &var, sizeof(var));
	//printf("komenda write adres Error Code: %i\n", GetLastError());
	SpectJoin(0, 1);
	std::stringstream ss;
	if (czy_w4game) {
		if (!czy_custom_napis) s = "WAITING FOR GAME TO JOIN";
		ss.str("");
		ss << " \x4/99" << " wplay " << myid;
		wyslij(ss.str());
		ss.str("");
		ss << " \x4/99" << " cstatus " << status << " 1 " << myid;
		wyslij(ss.str());
		status = 1;
	}
	else {
		if (!czy_custom_napis) s = "SPECTATOR   ESC FOR OPTIONS";
		ss.str("");
		ss << " \x4/99" << " cstatus " << status << " 0 " << myid;
		wyslij(ss.str());
		status = 0;
	}
	char * writable = new char[s.size() + 1];
	strcpy(writable, s.c_str());
	WriteToMemory((LPVOID)0x0051B93C, writable, strlen(writable) + 1);
	delete[] writable;
}

int wykonanie_komendy(std::string & tekst, std::string szukanaFraza)
{
	size_t znalezionaPozycja = tekst.find(szukanaFraza); //szukanie pozycji na ktorej jest komenda
	if (znalezionaPozycja == std::string::npos) //czy znaleziono komende
	{
		if (tekst.find(": /login ") != std::string::npos || tekst.find(": /register ") != std::string::npos) return 1;
		if (tekst.find(": ") < 17) sfx(300);
		return 0; //jezeli nie to return
	}
	polecenia.push_back(tekst);
	return 1;
}

bool isAdmin(){
	string s = md5(passedPassword + " gdfhr3tyswenxld5knoirhwlk6ns");
	if (s == adminPassword) {
		return true;
	}
	return false;
}

DWORD WINAPI wykonywanie_polecen(LPVOID lpParam)
{
	bool czySprawdzanieLicznika = false;
	std::stringstream ss;
	int* czy_w_wodzie = (int*)0x00ADC09C;
	bool isDiving = false;
	while (!czyWystartowano) Sleep(500);
	while (true)
	{
		Sleep(16);
		//for (auto it = commands.begin(); it != commands.end(); it = commands.erase(it)) {
		//string tekst = *it;

		if (currentfov > 113) { //lock fov in water on 113 max
			if (isDiving && *czy_w_wodzie == 0) {
				float temp = currentfov * 0.017444445;
				WriteToMemory((LPVOID)0x00508380, &temp, 4);
				isDiving = false;
			}
			else if (!isDiving && *czy_w_wodzie) {
				float temp = 113 * 0.017444445;
				WriteToMemory((LPVOID)0x00508380, &temp, 4);
				isDiving = true;
			}
		}

		if (!polecenia.empty()) {
			string tekst = polecenia.front();
			polecenia.pop_front();
			//komunikat("polecenie");
			//cout << "polecenie: " << tekst << endl;

			size_t znalezionaPozycja = tekst.find(": \x4/"); //szukanie pozycji na ktorej jest komenda
			//commands.push_back(tekst);
			int pozycja = znalezionaPozycja; //jezeli znaleziono to zapisuje na ktorej pozycji

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
			//string nick = tekst.substr(0, pozycja);
			tekst = tekst.substr(pozycja);
			int toID = atoi(tekst.substr(4).c_str());
			//cout << "toID: " << toID << endl;


			if (toID != myid && toID != 0) {
				//cout << "atoi: " << dec << atoi(tekst.substr(4).c_str()) << endl;
				//cout << "myid: " << dec << myid << endl;
				continue;
			}

			if (tekst.find("gvoice") == 7 && myid != -1) {
				ss.str("");
				ss << " \x4/99" << " voice " << myid;
				wyslij(ss.str());
				continue;
			}
			else {
				if (tekst.find(" h;") == std::string::npos) continue;
				string md5tocheck = tekst.substr(1, tekst.find(" h;") - 1);
				string md5recieved = tekst.substr(tekst.find(" h;") + 3);
				//cout << "md5tocheck: " << md5tocheck << endl;
				//cout << "md5recieved: " << md5recieved << endl;
				//cout << "licznik_komend: " << licznik_komend << endl;
				bool czy_dodano_licznik = false;
				ss.str("");
				if (md5tocheck.find("rdy") != std::string::npos || md5tocheck.find("joined ") != std::string::npos || md5tocheck.find("setCount ") != std::string::npos || toID == 0)
					ss << md5tocheck << " salt";
				else {
					czy_dodano_licznik = true;
					licznik_komend++;
					ss << md5tocheck << " salt" << licznik_komend;
				}
				md5tocheck = ss.str();
				//cout << "md5tocheck2: " << md5tocheck << endl;
				md5tocheck = md5(md5tocheck);
				//cout << "md5check: " << md5tocheck << endl;
				if (md5tocheck != md5recieved) {
					//cout << "sumcheck sie nie zgadza!! anuluje funkcje!" << endl;
					if (czy_dodano_licznik && !czySprawdzanieLicznika) {
						czySprawdzanieLicznika = true;
						licznik_komend--;
						cout << "!!! Command does not fit! Canceling..." << endl;
						cout << "Canceled command: " << tekst << endl;
						ss.str("");
						ss << " \x4/99 checkCount " << dec << zeranumer(myid) << " " << licznik_komend;
						wyslij(ss.str());
					}
					continue;
				}
				tekst = tekst.substr(0, tekst.find(" h;"));
			}

			//cout << "substr(7); " << tekst.substr(7) << endl;

			if (tekst.find("write") == 7) {
				//cout << "write" << endl;
				//cout << tekst.substr(15) << endl; // 15 11  // write 500 0x00
				adres = (int)strtol(tekst.substr(15).c_str(), NULL, 0);
				//cout << hex << adres << endl;
				//cout << tekst.substr(26) << endl;

				string subtekst = tekst.substr(13);

				if (subtekst.find("i") == 0) {
					int var = atoi(tekst.substr(26).c_str());
					//cout << dec << var << endl << endl;
					WriteToMemory((LPVOID)adres, &var, sizeof(var));
					//printf("komenda write adres Error Code: %i\n", GetLastError());
				}
				else if (subtekst.find("f") == 0) {
					float var = atof(tekst.substr(26).c_str());
					//cout << dec << var << endl << endl;
					WriteToMemory((LPVOID)adres, &var, sizeof(var));
					//printf("komenda write adres Error Code: %i\n", GetLastError());
				}
				else if (subtekst.find("t") == 0 || subtekst.find("b") == 0 || subtekst.find("s") == 0) {
					std::string s = tekst.substr(26).c_str();
					WriteToMemory((void*)adres, s.c_str(), s.size());
				}

				continue;
			}
			if (tekst.find("read") == 7) {
					//cout << "read" << endl;
					//cout << tekst.substr(12) << endl; // 15 11  // write 500 0x00
					adres = (int)strtol(tekst.substr(12).c_str(), NULL, 0);
					//cout << hex << adres << endl;
					//cout << tekst.substr(23) << endl;
					//var = atoi(tekst.substr(23).c_str());
					//cout << dec << var << endl << endl;
					// ReadProcessMemory(proc, (void*)adres, &var, sizeof(var), NULL);
					var = *((int*)adres);
					ss.str("");
					ss << " \x4/99" << " return " << hex << "0x" << std::setfill('0') << std::setw(8) << adres << " " << dec << zeranumer(myid) << " " << var;
					wyslij(ss.str());

					continue;
				}
				if (tekst.find("freeze") == 7) {
						//cout << "freeze" << endl;
						//cout << tekst.substr(16) << endl; // 15 11  // write 500 0x00
						adres = (int)strtol(tekst.substr(16).c_str(), NULL, 0);
						//cout << hex << adres << endl;
						//cout << tekst.substr(27) << endl;

						string subtekst = tekst.substr(14);

						if (subtekst.find("i") == 0) {
							int var = atoi(tekst.substr(27).c_str());
							//cout << dec << var << endl << endl;
							//VirtualProtect((LPVOID)(adres), sizeof(var), PAGE_EXECUTE_READWRITE, 0);
							frezeI[adres] = var;
						}
						else if (subtekst.find("f") == 0) {
							int var = atof(tekst.substr(27).c_str());
							//cout << dec << var << endl << endl;
							//VirtualProtect((LPVOID)(adres), sizeof(var), PAGE_EXECUTE_READWRITE, 0);
							frezeF[adres] = var;
						}
						else if (subtekst.find("t") == 0 || subtekst.find("b") == 0 || subtekst.find("s") == 0) {
							string s = tekst.substr(27).c_str();
							//cout << dec << s << endl << endl;
							//VirtualProtect((LPVOID)(adres), sizeof(s), PAGE_EXECUTE_READWRITE, 0);
							frezeS[adres] = s;
						}

						continue;
					}
					if (tekst.find("rfreeze") == 7) {
							//cout << "rfreeze" << endl;
							//cout << tekst.substr(15) << endl; // 15 11  // write 500 0x00
							adres = (int)strtol(tekst.substr(15).c_str(), NULL, 0);
							//cout << hex << adres << endl;
							//cout << tekst.substr(26) << endl;
							//var = atoi(tekst.substr(26).c_str());
							//cout << dec << var << endl << endl;
							if (frezeI.count(adres)>0)
								frezeI.erase(adres);
							if (frezeF.count(adres)>0)
								frezeF.erase(adres);
							if (frezeS.count(adres)>0)
								frezeS.erase(adres);
							continue;
						}
						if (tekst.find("observe") == 7) {
								//cout << "observe" << endl;
								//cout << tekst.substr(15) << endl; // 15 11  // write 500 0x00
								adres = (int)strtol(tekst.substr(15).c_str(), NULL, 0);
								//cout << hex << adres << endl;
								bool czy_read;
								//cout << "czy read: " << tekst.substr(26) << endl;
								czy_read = atoi(tekst.substr(26).c_str());
								bool czy_eventf; //when true: returns event only when variable is = to some var (not always when changed) 
												 //cout << "czy eventf: " << tekst.substr(28) << endl;
								czy_eventf = atoi(tekst.substr(28).c_str());
								if (czy_eventf) {
									float compareto = atof(tekst.substr(30).c_str());
									observef[adres] = compareto;
								}
								else {
									float var = *((int*)adres);
									//if (observe.count(adres)>0)
									//	observe.erase(adres);
									observe[adres] = var;
								}

								if (czy_read) {
									ss.str("");
									//ss << " //" << zeranumer(myid) << " event " << hex << "0x" << std::setfill ('0') << std::setw (8) << adres << " 0 " << dec << var;
									ss << " \x4/99" << " event " << hex << "0x" << std::setfill('0') << std::setw(8) << adres << " 0 " << dec << zeranumer(myid) << " " << var;
									wyslij(ss.str());
								}
								continue;
							}
							if (tekst.find("robserve") == 7) {
									//cout << "robserve" << endl;
									//cout << tekst.substr(16) << endl; // 15 11  // write 500 0x00
									adres = (int)strtol(tekst.substr(16).c_str(), NULL, 0);
									//cout << hex << adres << endl;
									//cout << tekst.substr(27) << endl;
									//var = atoi(tekst.substr(27).c_str());
									//cout << dec << var << endl << endl;
									if (observe.count(adres)>0)
										observe.erase(adres);
									if (observef.count(adres)>0)
										observef.erase(adres);
									continue;
								}
								if (tekst.find("unfreezeall") == 7) {
									//freze.clear();
									czy_unfreezeall = true;
									continue;
								}
								if (tekst.find("unobserveall") == 7) {
									//observe.clear();
									czy_unobserveall = true;
									continue;
								}
								if (tekst.find("news") == 7) {
									string s = tekst.substr(12).c_str();
									char * writable = new char[s.size() + 1];
									strcpy(writable, s.c_str());
									komunikat(writable);
									delete[] writable;

									if (tekst.find("news You logged in successfully.") == 7) {
										czy_zalogowany = true;
									}
									continue;
								}
								if (tekst.find("voice") == 7) {
									//int id = atoi(tekst.substr(13).c_str());
									czyHostVoice = true;
									continue;
								}
								//cout << "tekst.find(\"play\"): " << tekst.find("play") << endl;
								//cout << "substr(7): " << tekst.substr(7) << endl;
								if (tekst.find("play") == 7) {
									//cout << "play" << endl;
									czy_mozna_spect = true;
									czy_blokada_specta = false;
									ss.str("");
									ss << " \x4/99" << " cstatus " << status << " 2 " << myid;
									wyslij(ss.str());
									status = 2;
									SpectJoin(1, 0);
									//SpectJoinHook(1, 0);

									string bigozz = "FAILED TO JOIN??";
									char * writable = new char[bigozz.size() + 1];
									strcpy(writable, bigozz.c_str());
									WriteToMemory((LPVOID)0x0051B93C, writable, strlen(writable) + 1);
									delete[] writable;

									continue;
								}
								if (tekst.find("respawn") == 7) {
									SpectJoin(1, 0);
									ss.str("");
									ss << " \x4/99" << " cstatus " << status << " 2 " << myid;
									wyslij(ss.str());
									status = 2;
									continue;
								}
								if (tekst.find("forcespect") == 7) {
									bool czy_w4game = atoi(tekst.substr(18).c_str());
									bool czy_custom_napis = atoi(tekst.substr(20).c_str());
									string s;
									if (czy_custom_napis) s = tekst.substr(22).c_str();
									forcespect(czy_w4game, czy_custom_napis, s);

									continue;
								}
								if (tekst.find("callf") == 7) {
									adres = (int)strtol(tekst.substr(16).c_str(), NULL, 0);
									string subtekst = tekst.substr(13);

									if (subtekst.find("na") == 0) {
										fnoarg_ func = (fnoarg_)adres;
										func();
									}
									else if (subtekst.find("i1") == 0) {
										int var = 0;
										if (tekst.find("(") != std::string::npos) {
											subtekst = tekst.substr(tekst.find("(") + 1); //tekst.substr(27);
											subtekst = subtekst.substr(0, tekst.find(")"));
											var = atoi(subtekst.c_str());
										}
										//cout << "callf i1 var: " << var << endl;
										f1int_ func = (f1int_)adres;
										func(var);
									}
									else if (subtekst.find("i2") == 0) {
										int var1 = 0;
										int var2 = 0;
										if (tekst.find("(") != std::string::npos) {
											subtekst = tekst.substr(tekst.find("(") + 1); //tekst.substr(27);
											subtekst = subtekst.substr(0, tekst.find(","));
											var1 = atoi(subtekst.c_str());

											if (tekst.find(",") != std::string::npos) {
												subtekst = tekst.substr(tekst.find(",") + 1);
												subtekst = subtekst.substr(0, tekst.find(")"));
												var2 = atoi(subtekst.c_str());
											}
										}
										//cout << "callf i2 var1: " << var1 << " var2 : " << var2 << endl;
										f2ints_ func = (f2ints_)adres;
										func(var1, var2);
									}
									else if (subtekst.find("f1") == 0) {
										float var = 0;
										if (tekst.find("(") != std::string::npos) {
											subtekst = tekst.substr(tekst.find("(") + 1); //tekst.substr(27);
											subtekst = subtekst.substr(0, tekst.find(")"));
											var = atof(subtekst.c_str());
										}
										f1float_ func = (f1float_)adres;
										func(var);
									}
									else if (subtekst.find("f2") == 0) {
										float var1 = 0;
										float var2 = 0;
										if (tekst.find("(") != std::string::npos) {
											subtekst = tekst.substr(tekst.find("(") + 1); //tekst.substr(27);
											subtekst = subtekst.substr(0, tekst.find(","));
											var1 = atof(subtekst.c_str());

											if (tekst.find(",") != std::string::npos) {
												subtekst = tekst.substr(tekst.find(",") + 1);
												subtekst = subtekst.substr(0, tekst.find(")"));
												var2 = atof(subtekst.c_str());
											}
										}
										f2floats_ func = (f2floats_)adres;
										func(var1, var2);
									}
									else if (subtekst.find("cs") == 0) {
										int var = 0;
										if (tekst.find("(") != std::string::npos) {
											subtekst = tekst.substr(tekst.find("(") + 1); //tekst.substr(27);
											subtekst = subtekst.substr(0, tekst.find(")"));
										}
										char * writable = new char[subtekst.size() + 1];
										strcpy(writable, subtekst.c_str());
										fcstr_ func = (fcstr_)adres;
										func(writable);
										delete[] writable;
									}

									continue;
								}
								if (tekst.find("joined") == 8 && czy_wyslane_join) {
									//cout << "joined" << endl;
									//cout << tekst.substr(15) << endl; // 15 11  // write 500 0x00
									myid = atoi(tekst.substr(15).c_str());
									czyJoined = true;
									czy_blokada_specta = false;

									ss.str("");
									ss << " \x4/99" << " cstatus 0 " << status << " " << myid;
									wyslij(ss.str());

									ss.str("");
									ss << " \x4/99" << " stid " << zeranumer(myid) << " " << tid;
									wyslij(ss.str());

									string bigozz = "SPECTATOR   ESC FOR OPTIONS";
									char * writable = new char[bigozz.size() + 1];
									strcpy(writable, bigozz.c_str());
									WriteToMemory((LPVOID)0x0051B93C, writable, strlen(writable) + 1);
									delete[] writable;

									if (status == 0) komunikat("Successfully connected to server bot! Click Esc to join.");
									else komunikat("Successfully connected to server bot!");
									globalnick = (char*)0x00AD045C;

									continue;
								}
								if (tekst.find("command") == 7) {
									string s = tekst.substr(15).c_str();
									commands.push_back(s);
									//commands.unique();
									continue;
								}
								if (tekst.find("cdamage") == 7) {
									//czy_custom_damage = true;
									int weapon = atoi(tekst.substr(15).c_str());
									float damage = atof(tekst.substr(18).c_str());
									if (weapon == 0) defaultDamage = damage;
									else customDamage[weapon] = damage;
									continue;
								}
								if (tekst.find("cnode") == 7) {
									//czy_custom_damage = true;
									int weapon = atoi(tekst.substr(13).c_str());
									float node = atof(tekst.substr(16).c_str());
									if (weapon == 0) defaultNode = node;
									else customNode[weapon] = node;
									continue;
								}
								if (tekst.find("cdrop") == 7) {
									czy_customDrops_config = true;
									string map = tekst.substr(13, tekst.find(", ")-13);
									int weapon = atoi(tekst.substr(tekst.find(", ")+2).c_str());
									int time = atoi(tekst.substr(tekst.find(", ") + 5).c_str());
									if (customDrop.find(map) == customDrop.end()) {
										list<pair<int, int>> lista;
										customDrop[map] = lista;
									}
									auto it = customDrop.find(map);

									if (it != customDrop.end()) {
										std::list<pair<int, int>> *p = NULL;
										p = &(it->second);
										(*p).push_back(std::make_pair(weapon, time));
										//cout << "cdrop map: " << map << " weapon: " << weapon << " time: " << time << endl;
									}
									//customDrop[map] = std::make_pair(weapon, time);
									continue;
								}
								if (tekst.find("cpick") == 7) {
									if (!czy_customPickups_config) {
										czy_customPickups_config = true;
										customPickup.clear();
										customPchance.clear();
										extraAmmo.clear();
									}

									int pred = atoi(tekst.substr(13).c_str());
									int pick = atoi(tekst.substr(16).c_str());
									int ammo = atoi(tekst.substr(19).c_str());
									dodaj_customPickup(pred, pick, ammo);
									continue;
								}
								if (tekst.find("cwcfg") == 7) {
									int i = atoi(tekst.substr(13).c_str());
									int var = atoi(tekst.substr(16).c_str());
									if (i == 1) {
										czyTorpedoDisabledOnGround = var;
									}
									else if (i == 2) {
										howManyExtraNukeExplosions = var;
									}
									else if (i == 3) {
										airStrikeAmmoId = var;
									}
									else if (i == 4) {
										airStrikeAmmoCost = var;
									}
									else if (i == 5) {
										blackOilWith = var;
									}
									else if (i == 6) {
										dinoRidingWith = var;
									}
									else if (i == 7) {
										airStrikeWith = var;
									}
									else if (i == 8) {
										airStrikeDelay = var;
									}

									continue;
								}
								if (tekst.find("dchance") == 7) {
									//cout << "dchance tekst.substr(15).c_str(): " << tekst.substr(15).c_str() << endl;
									dchance = atoi(tekst.substr(15).c_str());
									continue;
								}
								if (tekst.find("pchance") == 7) {
									//cout << "pchance tekst.substr(15).c_str(): " << tekst.substr(15).c_str() << endl;
									//cout << "pchance tekst.substr(18).c_str(): " << tekst.substr(18).c_str() << endl;
									customPchance[atoi(tekst.substr(15).c_str())] = atoi(tekst.substr(18).c_str());
									continue;
								}
								if (tekst.find("pammo") == 7) {
									//cout << "pammo tekst.substr(13).c_str(): " << tekst.substr(13).c_str() << endl;
									//cout << "pammo tekst.substr(16).c_str(): " << tekst.substr(16).c_str() << endl;
									extraAmmo[atoi(tekst.substr(13).c_str())] = atoi(tekst.substr(16).c_str());
									continue;
								}
								if (tekst.find("checknick") == 7) {
									sprawdzNick();
									continue;
								}
								if (tekst.find("rdy") == 7 && !czyJoined) {
									if (czy_ServerBotRequired) {
										string bigozz = "CONNECTING TO SERVER BOT";
										char * writable = new char[bigozz.size() + 1];
										strcpy(writable, bigozz.c_str());
										WriteToMemory((LPVOID)0x0051B93C, writable, strlen(writable) + 1);
										delete[] writable;
									}
									sendJoin();
									//else wyslij(" \x4/99 block");
									continue;
								}
								if (tekst.find("blspect") == 7) {
									czy_mozna_spect = false;
									continue;
								}
								if (tekst.find("unblspect") == 7) {
									czy_mozna_spect = true;
									continue;
								}
								if (tekst.find("setCount") == 7) {
									int liczbaKomend = atoi(tekst.substr(16).c_str());
									licznik_komend = liczbaKomend;
									polecenia.clear();
									forcespect(false, true, "Temporarily lost connection");
									forcespect(true, true, "Temporarily lost connection. Joining...");
									komunikat("Lost connection with bot. Reconnecting...");
									czySprawdzanieLicznika = false;
									if (!czyPobranoUstawienia) {
										ss.str("");
										ss << " \x4/99 sresend " << dec << zeranumer(myid);
										wyslij(ss.str());
									}
									continue;
								}
								if (tekst.find("sdone") == 7) {
									czyPobranoUstawienia = true;
									continue;
								}

								//cout << "doszlo do konca znalezionaPozycja: " << znalezionaPozycja << endl;

		}
	}
	return S_OK;
}

/*Our modified function code that is going to be executed
before continuing to the code of original function*/
int hookedFunction(char *text)
{
	if (wykonanie_komendy((string)text, ": \x4/")) { //if( comand.find( ": //" ) != std::string::npos ){ //czy znaleziono komende
											 //wykonanie_komendy( comand, ": //" );
		return 0;
	}
	else {
		if (hideUnkCommandText) {
			string comand = text;
			if (comand.find("unrecognized command: ") == 0 || comand.find("UNKNOWN VARIABLE ") == 0 || comand.find("OUT OF RANGE: ") == 0 || comand.find("set level command only ") == 0) {
				hideUnkCommandText = false;
				return 0;
			}
		}
	}
	cout << text << endl;
	int zwrotek = originalFunction(text);
	//cout << "zwrotek1: " << zwrotek << endl;
	return zwrotek;                                        //before returning to normal execution of function
}

int hookedFunction2(char *text)
{
	//cout << "hookedFunction2" << endl;
	//cout << "hF2 text: " << text << endl;
	int zwrot = wysylaniehook(text);
	if (text[0] != ' ' || text[1] == '/') {
		std::stringstream ss;
		//cout << "tak to komenda" << endl;
		string command = text;
		//cout << "komenda: " << command << endl;
		//bool czy_return_zero = false;
		if (text[1] == '/') {
			command = command.substr(2);
			//czy_return_zero = true;
		}
		hideUnkCommandText = true;

		if (command.find("set weaponfov ") == 0) {
			if(command.length()<16) komunikat("You entered the wrong variable (Valid range is 10-90).");
			else {
				float var = atof(command.substr(14).c_str());
				//cout << "var: " << var << " substr: " << command.substr(14).c_str() << endl;
				if (var < 10 || var>90) {
					komunikat("You entered the wrong variable (Valid range is 10-90).");
				}
				else {
					WriteToMemory((LPVOID)0x00523E5C, &var, 4);
				}
			}
		}
		else if (command.find("set camerafov ") == 0) {
			if (command.length()<16) komunikat("You entered the wrong variable (Valid range is 30-90).");
			else {
				float var = atof(command.substr(14).c_str());
				//cout << "var: " << var << " substr: " << command.substr(14).c_str() << endl;
				if (var < 30 || var>135) {
					komunikat("You entered the wrong variable (Valid range is 30-135).");
				}
				else {
					currentfov = var;
					if (var >= 90) {
						if (var > 90) komunikat("Warning! FOV over 90 may be bugged!");
						if (var > 113 && *((int*)0x00ADC09C)) var = 113;
						var *= 0.017444445;
						WriteToMemory((LPVOID)0x00508380, &var, 4);
						var = 90;
					}
					WriteToMemory((LPVOID)0x106FD408, &var, 4);
				}
			}
		}
		else if (command.find("fov ") == 0) {
			if (command.length()<6) komunikat("You entered the wrong variable (Valid range is 30-90).");
			else {
				float var = atof(command.substr(4).c_str());
				//cout << "var: " << var << " substr: " << command.substr(8).c_str() << endl;
				if (var < 30 || var>135) {
					komunikat("You entered the wrong variable (Valid range is 30-135).");
				}
				else {
					currentfov = var;
					float camerafov = var;
					float weaponfov = var * 0.714285714;
					if (var >= 90) {
						if (var > 90) komunikat("Warning! FOV over 90 may be bugged!");
						if (var > 113 && *((int*)0x00ADC09C)) camerafov = 113;
						camerafov = camerafov * 0.017444445;
						WriteToMemory((LPVOID)0x00508380, &camerafov, 4);
						camerafov = 90;
					}
					if (weaponfov > 90)
						weaponfov = 90;

					WriteToMemory((LPVOID)0x106FD408, &camerafov, 4);
					WriteToMemory((LPVOID)0x00523E5C, &weaponfov, 4);
					ss.str("");
					ss << "camerafov has been set to " << var << " and weaponfov to " << weaponfov;
					char * writable = new char[ss.str().size() + 1];
					strcpy(writable, ss.str().c_str());
					komunikat(writable);
					delete[] writable;
					komunikat("You can use separate commands: \'set weaponfov\' and \'set camerafov\'");
				}
			}
		}
		else if (command.find("set fov ") == 0) {
			if (command.length()<10) komunikat("You entered the wrong variable (Valid range is 30-90).");
			else {
				float var = atof(command.substr(8).c_str());
				//cout << "var: " << var << " substr: " << command.substr(8).c_str() << endl;
				if (var < 30 || var>135) {
					komunikat("You entered the wrong variable (Valid range is 30-135).");
				}
				else {
					currentfov = var;
					float camerafov = var;
					float weaponfov = var * 0.714285714;
					if (var >= 90) {
						if (var > 90) komunikat("Warning! FOV over 90 may be bugged!");
						if (var > 113 && *((int*)0x00ADC09C)) camerafov = 113;
						camerafov = var * 0.017444445;
						WriteToMemory((LPVOID)0x00508380, &camerafov, 4);
						camerafov = 90;
					}
					if (var > 90)
						weaponfov = 90;
					
					WriteToMemory((LPVOID)0x106FD408, &camerafov, 4);
					WriteToMemory((LPVOID)0x00523E5C, &weaponfov, 4);
					komunikat("You can use separate commands: \'set weaponfov\' and \'set camerafov\'");
					komunikat("You can use shorter command, just: \'fov\'");
				}
			}
		}
		else if (command.find("set level ") == 0) {
			if (command.length()<11) komunikat("You entered the wrong variable.");
			else {
				int var = atoi(command.substr(10).c_str());
				//cout << "var: " << var << " substr: " << command.substr(8).c_str() << endl;
				if (var < 0 || var>99) {
					komunikat("You entered the wrong variable (Valid range is 0-99).");
				}
				else {
					ss.str("");
					ss << " \x4/99 changelvl " << dec << zeranumer(myid) << " " << dec << var;
					wyslij(ss.str());
					//komunikat("set level 300");
				}
			}
		}
		/*else if (command.find("drop weapon ") == 0) {
			if (command.length()<12) komunikat("You entered the wrong variable.");
			else {
				int var = atoi(command.substr(11).c_str());
				//cout << "var: " << var << " substr: " << command.substr(8).c_str() << endl;
				if (var < -99 || var>99) {
					komunikat("You entered the wrong variable (Valid range is 0-34).");
				}
				else {
					dropWeapon(0x106d1250, var, 20000);
					//dropWeapon(0x106d25a8, var, 20000);
				}
			}
		}*/
		else if (command.compare("spectate") == 0 || command.compare("observe") == 0) {
			if (czy_mozna_spect && czy_spectate_enabled && status!=0) {
				string bigozz = "SPECTATOR   ESC FOR OPTIONS";
				char * writable = new char[bigozz.size() + 1];
				strcpy(writable, bigozz.c_str());
				WriteToMemory((LPVOID)0x0051B93C, writable, strlen(writable) + 1);
				delete[] writable;

				ss.str("");
				ss << " \x4/99" << " cstatus " << status << " 0 " << myid;
				wyslij(ss.str());
				status = 0;
				strzal(0x106d1250, 209);
				int adres = 0x00AD03D8;
				int var = 4198400;
				WriteToMemory((LPVOID)adres, &var, sizeof(var));
				//printf("komenda write adres Error Code: %i\n", GetLastError());
				SpectJoin(0, 1);
				
				char frags = *((char*)0x00AD0470);
				short pain = *((short*)0x00AD0472);

				frags -= 1;
				pain -= 100;
				if (frags < 0 || frags > 100) frags = 0; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				if (pain < 0) pain = 0;
				//cout << "frags: " << frags << endl;
				//cout << "pain: " << pain << endl;
				WriteToMemory((LPVOID)0x00AD0470, &frags, 1);
				WriteToMemory((LPVOID)0x00AD0472, &pain, 2);

				//czy_blokada_specta = true;
				ss.str("");
				ss << " \x4/99" << " eventf " << "-1         1 " << dec << zeranumer(myid) << " " << 1;
				wyslij(ss.str());
			}
			else if(!czy_spectate_enabled) komunikat("This command is disabled on this server.");
			else komunikat("You can't go into observer mode right now.");
		}
		else if (command.find("set color ") == 0) {
			if (command.length()<11) komunikat("You entered the wrong variable (Valid range is 0-8).");
			else {
				if (czy_setColor_enabled) {
					int var = -1;
					var = atoi(command.substr(10).c_str());
					if (var >= 0 && var <= 8) {
						//if (var == 0) var = 4294967295;
						//elsevar--;
						/*
						WriteToMemory((LPVOID)0x106D25A4, &var, sizeof(var));
						printf("komenda set color Error Code: %i\n", GetLastError());*/

						//cout << "color var przed: " << var << endl;
						//cout << "color var po: " << (275579872 + var * 40) << endl;
						int var2 = 275579296;
						preZmianaKoloru( (275579872 + var * 40) ,var2);
						var--;
						zmianaKoloru(var);
					}
					else {
						komunikat("You entered the wrong variable (Valid range is 0-8).");
						komunikat("0-none 1-red 2-blue 3-green 4-yellow 5-purple 6-cyan 7-brown 8-turquoise");
					}
				}
				else komunikat("Set color command is disabled on this server.");
			}
		}
		else if (command.compare("set color") == 0) {
			komunikat("0-none 1-red 2-blue 3-green 4-yellow 5-purple 6-cyan 7-brown 8-turquoise");
		}
		else if (command.compare("oil") == 0) {
			if (czy_userBlackOil) {
				czy_userBlackOil = false;
				komunikat("Generation of black oil canceled. (You still will see oil produced by other players)");
			}
			else {
				czy_userBlackOil = true;
				komunikat("Generation of black oil resumed.");
			}
		}
		else if (command.compare("razor") == 0) {
			if (czyUserRazors) {
				czyUserRazors = false;
				komunikat("Enemy razor efect has been disabled.");
			}
			else {
				czyUserRazors = true;
				komunikat("Enemy razor efect has been resumed.");
			}
		}
		else if (command.find("login ") == 0) {
			if (command.length()<14) komunikat("Correct use: login your_nickname your_password");
			else {
				if (czy_zalogowany) {
					komunikat("You are already logged in.");
				}
				else {
					string login = command.substr(6);
					string password = login.substr(login.find(" ") + 1);
					login = login.substr(0, login.find(" "));
					//cout << "login: " << login << " password: " << password << endl;
					string md5pass = md5(password);
					//cout << "md5 of '" << password << "': " << md5pass << endl;

					char chars[] = "\\/:*?\"<>|."; //usuniecie tych znakow z loginu:
					for (unsigned int i = 0; i < strlen(chars); ++i) login.erase(std::remove(login.begin(), login.end(), chars[i]), login.end());

					ss.str("");
					ss << " \x4/99 login " << dec << zeranumer(myid) << " " << login << " " << md5pass;
					wyslij(ss.str());
				}
			}
		}
		else if (command.compare("login") == 0) {
			komunikat("Correct use: login your_nickname your_password");
		}
		else if (command.find("register ") == 0) {
			if (command.length()<12) komunikat("Correct use: register nickname_you_want password_you_want");
			else {
				if (czy_zalogowany) {
					komunikat("Please use only one account.");
				}
				else {
					string loginR = command.substr(9);
					//cout << "loginR: " << loginR << endl;
					password = loginR.substr(loginR.find(" ") + 1);
					login = loginR.substr(0, loginR.find(" "));
					char chars[] = "\\/:*?\"<>|."; //usuniecie tych znakow z loginu:
					for (unsigned int i = 0; i < strlen(chars); ++i) login.erase(std::remove(login.begin(), login.end(), chars[i]), login.end());

					if (login.length() > 16) komunikat("This nickname is too long! Max length is 16 chars.");
					else if (login.length() < 3) komunikat("This nickname is too short! Min length is 3 chars.");
					else if (password.length() > 20) komunikat("This password is too long! Max length is 20 chars.");
					else if (password.length() < 6) komunikat("This password is too short! Min length is 6 chars.");
					else {
						ss.str("");
						ss << "Do you want to create account with nickname '" << dec << login << "' and password '" << password << "'?";
						string s = ss.str();
						char * writable = new char[s.size() + 1];
						strcpy(writable, s.c_str());
						komunikat(writable);
						komunikat("Type 'yes' to confirm.");
						delete[] writable;
						czy_potwierdzenie_rejestracji = true;
					}
				}
			}
		}
		else if (command.compare("register") == 0) {
			komunikat("Correct use: register nickname_you_want password_you_want");
		}
		else if ( (command.compare("yes") == 0 || command.compare("YES") == 0) && czy_potwierdzenie_rejestracji ) {
			czy_potwierdzenie_rejestracji = false;
			//cout << "login: " << login << " password: " << password << endl;
			string md5pass = md5(password);
			//cout << "md5 of '" << password << "': " << md5pass << endl;

			ss.str("");
			ss << " \x4/99 register " << dec << zeranumer(myid) << " " << login << " " << md5pass;
			wyslij(ss.str());
		}
		else if (command.find("kick ") == 0) {
			if (command.length()<6) komunikat("Correct use: kick player_id (type 'players' to get IDs)");
			else {
				int id = atoi(command.substr(5).c_str());
				ss.str("");
				ss << " \x4/99 kick " << dec << zeranumer(myid) << " " << dec << id;
				wyslij(ss.str());
			}
		}
		else if (command.compare("kick") == 0) {
			komunikat("Correct use: kick player_id (type 'players' to get IDs)");
		}
		else if (command.find("ban ") == 0) {
			if (command.length()<5) komunikat("Correct use: ban player_id (type 'players' to get IDs)");
			else {
				int id = atoi(command.substr(4).c_str());
				ss.str("");
				ss << " \x4/99 ban " << dec << zeranumer(myid) << " " << dec << id;
				wyslij(ss.str());
			}
		}
		else if (command.compare("ban") == 0) {
			komunikat("Correct use: ban player_id (type 'players' to get IDs)");
		}
		else if (command.compare("logins") == 0) {
			ss.str("");
			ss << " \x4/99 idloginlist " << dec << zeranumer(myid);
			wyslij(ss.str());
		}
		else if (command.compare("players") == 0) {
			ss.str("");
			ss << " \x4/99 idlist " << dec << zeranumer(myid);
			wyslij(ss.str());
		}
		else if (command.compare("pass ") == 0) {
			string passedPassword = command.substr(5).c_str();
		}
		else if (command.compare("md5 ") == 0) {
			string s = command.substr(4).c_str();
			s = md5(s + " gdfhr3tyswenxld5knoirhwlk6ns");
			char * writable = new char[s.size() + 1];
			strcpy(writable, s.c_str());
			komunikat(writable);
			delete[] writable;
		}
		else {
			hideUnkCommandText = false;
			//czy_return_zero = false;
			for (auto const& i : commands) {
				if (command.find(i) == 0) {
					/*if (command.size() > i.size() + 1) {
						int var = -1;
						var = atoi(command.substr(i.size() + 1).c_str());
						cout << "custom commands var: " << var << endl;
						ss.str("");
						ss << " \x4/99 cmd " << dec << zeranumer(myid) << " " << dec << var << " " << i;
						ss << " \x4/99 cmd " << dec << zeranumer(myid) << " " << command;
						wyslij(ss.str());
					}*/

					ss.str("");
					ss << " \x4/99 cmd " << dec << zeranumer(myid) << " " << command;
					wyslij(ss.str());

					if (text[0] != ' ') hideUnkCommandText = true;
					//if (text[1] == '/') czy_return_zero = true;
				}
			}
		}
		command = text;
		//cout << "komenda2: " << command << endl;
		if (text[1] == '/') {
			if (hideUnkCommandText) hideUnkCommandText = false;
			else komunikat("Command not found.");
		}
		//if (czy_return_zero) return 0;
	}

	//cout << "zwrot2: " << zwrot << endl;
	return zwrot;
	//return wysylaniehook(text); //return zwrot;
}

int hookedFunction3(int text1, int text2)
{
	//ilenasekunde++;
	int zwrot = wysylaniehook2(text1, text2); //liczy ile znakow
	if (zwrot == 0 && !dowyslania.empty()) {
		string bigozz = dowyslania.front();
		dowyslania.pop_front();
		if (bigozz.length() != 0) {
			writable = new char[bigozz.size() + 1];
			strcpy(writable, bigozz.c_str());
			//std::copy(bigozz.begin(), bigozz.end(), writable);
			//writable[bigozz.size()] = '\0';
			//cout << "Wysylanie: " << writable << endl; //02FF3C7D
													   //WriteToMemory(0x02FF3C7D, writable, sizeof(writable));
			DWORD adresik = FindDmaAddy(1, hackOffsets, baseAddress);
			//unsigned long OldProtection;
			WriteToMemory((LPVOID)(adresik - 4), &dataz, sizeof(dataz));
			WriteToMemory((LPVOID)adresik, writable, strlen(writable) + 1);
			delete[] writable;
			//WriteToMemory( (LPVOID)0x02FF3C7D, &writable, sizeof(writable)); //0x00ADC88C
		}

		/*cout << "hookedFunction3" << endl;
		cout << "text1: " << text1 << endl;
		cout << "text2: " << text2 << endl;*/
		//cout << "zwrot: " << zwrot << endl;
		//cout << "bigozz.size()+5: " << bigozz.size() + 5 << endl;
		return bigozz.size() + 5;
	}

	if (czy_unfreezeall) {
		frezeI.clear();
		frezeF.clear();
		frezeS.clear();
		czy_unfreezeall = false;
	}
	else {
		for (auto it = frezeI.begin(); it != frezeI.end() && !czy_unfreezeall; it++) //for (auto const& p : freze)
		{
			WriteToMemory((LPVOID)it->first, &it->second, sizeof(it->second));
			if (it == frezeI.end()) break;
		}
		for (auto it = frezeF.begin(); it != frezeF.end() && !czy_unfreezeall; it++) //for (auto const& p : freze)
		{
			WriteToMemory((LPVOID)it->first, &it->second, sizeof(it->second));
			if (it == frezeF.end()) break;
		}
		for (auto it = frezeS.begin(); it != frezeS.end() && !czy_unfreezeall; it++) //for (auto const& p : freze)
		{
			WriteToMemory((LPVOID)it->first, it->second.c_str(), sizeof(it->second));
			if (it == frezeS.end()) break;
		}
	}

	if (czy_unobserveall) {
		observe.clear(); 
		observef.clear();
		czy_unobserveall = false;
	}
	else {
		float vart;
		int adresik;
		std::stringstream ss;
		for (auto it = observe.begin(); it != observe.end() && !czy_unobserveall; it++) //for (auto const& p : observe)
		{
			adresik = it->first;
			//ReadProcessMemory(proc, (void*)p.first, &vart, sizeof(vart), NULL);
			vart = *((int*)adresik);
			if (vart != it->second) {
				//std::stringstream ss;
				//ss << " \x4/" << myid << " event " << hex << "0x" << std::setfill ('0') << std::setw (8) << p.first << " 1 " << dec << p.second;
				//cout << "wysylanie eventu: it->first: " << hex << it->first << " it->second: " << dec << it->second << " vart: " << vart << endl;
				ss.str("");
				ss << " \x4/99" << " event " << hex << "0x" << std::setfill('0') << std::setw(8) << it->first << " 1 " << dec << zeranumer(myid) << " " << vart; //<< it->second;
				wyslij(ss.str());

				//observe.erase(adresik);
				observe[adresik] = vart;
				//it = observe.begin();
			}
		}
		for (auto it = observef.begin(); it != observef.end() && !czy_unobserveall; it++) //for (auto const& p : observe)
		{
			adresik = it->first;
			vart = *((int*)adresik);
			if (vart == it->second) {
				//cout << "wysylanie eventuf: it->first: " << hex << adresik << " it->second: " << dec << it->second << " vart: " << vart << endl;
				ss.str("");
				ss << " \x4/99" << " eventf " << hex << "0x" << std::setfill('0') << std::setw(8) << adresik << " 1 " << dec << zeranumer(myid) << " " << vart; //<< it->second;
				wyslij(ss.str());
				//if (observe.count(it->first)>0)
				it = observef.erase(it);
					//observef.erase(adresik);
					//it = observef.begin();
				if (it == observef.end()) break;
			}
		}
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
	int zwrot = 0;
	std::stringstream ss;
	if (czy_blokada_specta) {
		zwrot = SpectJoinHook(0, 1);
		if (!czyJoined) {
			ss.str("");
			ss << " \x4/99" << " gvoice " << myid;
			wyslij(ss.str());
		}
	}
	else if (status == 0 && int1 == 1 && int2 == 0) {
		if (czy_ServerBotRequired) {
			if(!czyJoined) return SpectJoinHook(0, 1);
			czy_mozna_spect = false;
			string bigozz = "WAITING FOR GAME TO JOIN";
			char * writable = new char[bigozz.size() + 1];
			strcpy(writable, bigozz.c_str());
			WriteToMemory((LPVOID)0x0051B93C, writable, strlen(writable) + 1);
			delete[] writable;

			ss.str("");
			ss << " \x4/99" << " wplay " << myid;
			wyslij(ss.str());
			ss.str("");
			ss << " \x4/99" << " cstatus " << status << " 1 " << myid;
			wyslij(ss.str());
			status = 1;
			zwrot = SpectJoinHook(0, 1);
		}
		else {
			ss.str("");
			ss << " \x4/99" << " cstatus " << status << " 2 " << myid;
			wyslij(ss.str());
			status = 2;
			zwrot = SpectJoinHook(int1, int2);
		}
	} else zwrot = SpectJoinHook(int1, int2);
	//cout << "zwrot14: " << zwrot << endl;
	return zwrot;                                        //before returning to normal execution of function
}

int hookedTeamChange(int int1)
{
	//cout << "hookedTeamChange" << endl;
	//std::cout << "int1: " << int1 << std::endl; //we can access arguments passed to original function
	int zwrot = 0;
	zwrot = TeamChangeHook(int1);
	//cout << "zwrotTeamChange: " << zwrot << endl;
	SpectJoin(1, 0);
	return zwrot;                                        //before returning to normal execution of function
}

void dodajAmmo(int weapon, int ammo) {
	switch (weapon)
	{
	case 2: //bow
		*((short*)0x106D1B84) += ammo; //normal arrows
		break;
	case 3: //tekbow
		*((short*)0x106D1B86) += ammo; //explosive arrows
		break;
	case 4: //pistol
		*((short*)0x106D1B88) += ammo;
		break;
	case 5: //magnum
		*((short*)0x106D1B88) += ammo;
		break;
	case 6: //usypiacz
		*((short*)0x106D1B8C) += ammo;
		break;
	case 7: //chargeDart
		*((short*)0x106D1B8E) += ammo;
		break;
	case 8: //shotgun
		*((short*)0x106D1B90) += ammo; //green
		break;
	case 9: //szłeder
		*((short*)0x106D1B92) += ammo; //red
		break;
	case 10: //plasma 
		*((short*)0x106D1B96) += ammo;
		break;
	case 11: //firestorm
		*((short*)0x106D1B96) += ammo;
		break;
	case 12: //sunfirepod
		*((short*)0x106D1B98) += ammo;
		break;
	case 13: //cbore
		*((short*)0x106D1B9A) += ammo;
		break;
	case 14: //pfm
		*((short*)0x106D1B9C) += ammo;
		break;
	case 15: //grenade
		*((short*)0x106D1B9E) += ammo;
		break;
	case 16: //scorpion
		*((short*)0x106D1BA0) += ammo;
		break;
	case 17: //harpoon
		*((short*)0x106D1BA2) += ammo;
		break;
	case 18: //torpedo
		*((short*)0x106D1BA4) += ammo;
		break;
	case 19: //flame
		*((short*)0x106D1BAC) += ammo;
		break;
	case 21: //nuke
		*((short*)0x106D1BB0) += ammo;
		break;
	default:
		break;
	}
}

void setStartingWeapons(int character = -1) {
	vector<string>* v;
	switch (character)
	{
	case 0:
		v = &turokWeapons;
		break;
	case 1:
		v = &adonWeapons;
		break;
	case 2:
		v = &gantWeapons;
		break;
	case 3:
		v = &fleshWeapons;
		break;
	case 4:
		v = &purWeapons;
		break;
	case 5:
		v = &endWeapons;
		break;
	case 6:
		v = &fireWeapons;
		break;
	case 7:
		v = &iggyWeapons;
		break;
	case 8:
		v = &campWeapons;
		break;
	case 9:
		v = &telWeapons;
		break;
	case -1:
	default:
		v = &startingWeapons;
		break;
	}
	for (auto const& value : *v) {
		int id_broni = -1;
		int i;
		short ammo = -1;
		if (value.find(";") != std::string::npos) {
			i = stoi(value.substr(0, value.find(";")));
			ammo = stoi(value.substr(value.find(";") + 1));
		}
		else i = stoi(value);

		byte equip = 1;
		if (i < 0) {
			i *= -1;
			equip = 0;
		}

		switch (i)
		{
		case 0:
		case 99: //remove warblade
			*((byte*)0x106D1BC3) = equip;
			break;
		case 1:
			*((byte*)0x106D1BC5) = equip;
			if (ammo >= 0) {
				*((short*)0x106D1B84) = ammo;
				*((short*)0x106D1B86) = ammo;
			} 
			else if (startingMaxAmmo) {
				*((short*)0x106D1B84) = 50;
				*((short*)0x106D1B86) = 50;
			}
			else {
				*((short*)0x106D1B84) = 10;
				*((short*)0x106D1B86) = 10;
			}
			id_broni = 3;
			break;
		case 2:
			*((byte*)0x106D1BC6) = equip;
			if (ammo >= 0) {
				*((short*)0x106D1B88) = ammo;
			}
			else if (startingMaxAmmo)
				*((short*)0x106D1B88) = 300;
			else
				*((short*)0x106D1B88) = 50;
			id_broni = 4;
			break;
		case 3:
			*((byte*)0x106D1BC7) = equip;
			if (ammo >= 0) {
				*((short*)0x106D1B88) = ammo;
			}
			else if (startingMaxAmmo)
				*((short*)0x106D1B88) = 300;
			else
				*((short*)0x106D1B88) = 50;
			id_broni = 5;
			break;
		case 4:
			*((byte*)0x106D1BC9) = equip;
			if (ammo >= 0) {
				*((short*)0x106D1B8E) = ammo;
			}
			else if (startingMaxAmmo)
				*((short*)0x106D1B8E) = 50;
			else
				*((short*)0x106D1B8E) = 15;
			id_broni = 7;
			break;
		case 5: //shotgun
			*((byte*)0x106D1BCA) = equip;
			if (ammo >= 0) {
				*((short*)0x106D1B90) = ammo;
			}
			else if (startingMaxAmmo)
				*((short*)0x106D1B90) = 100;
			else
				*((short*)0x106D1B90) = 20;
			id_broni = 8;
			break;
		case 6:
			*((byte*)0x106D1BCB) = equip;
			if (ammo >= 0) {
				*((short*)0x106D1B92) = ammo;
			}
			else if (startingMaxAmmo)
				*((short*)0x106D1B92) = 50;
			else
				*((short*)0x106D1B92) = 15;
			id_broni = 9;
			break;
		case 7:
			*((byte*)0x106D1BCC) = equip;
			if (ammo >= 0) {
				*((short*)0x106D1B96) = ammo;
			}
			else if (startingMaxAmmo)
				*((short*)0x106D1B96) = 300;
			else
				*((short*)0x106D1B96) = 100;
			id_broni = 10;
			break;
		case 8:
			*((byte*)0x106D1BCD) = equip;
			if (ammo >= 0) {
				*((short*)0x106D1B96) = ammo;
			}
			else if (startingMaxAmmo)
				*((short*)0x106D1B96) = 300;
			else
				*((short*)0x106D1B96) = 100;
			id_broni = 11;
			break;
		case 9:
			*((byte*)0x106D1BCF) = equip;
			if (ammo >= 0) {
				*((short*)0x106D1B9A) = ammo;
			}
			else if (startingMaxAmmo)
				*((short*)0x106D1B9A) = 25;
			else
				*((short*)0x106D1B9A) = 5;
			id_broni = 13;
			break;
		case 10:
			*((byte*)0x106D1BD1) = equip;
			if (ammo >= 0) {
				*((short*)0x106D1B9E) = ammo;
			}
			else if (startingMaxAmmo)
				*((short*)0x106D1B9E) = 100;
			else
				*((short*)0x106D1B9E) = 14;
			id_broni = 15;
			break;
		case 11:
			*((byte*)0x106D1BD2) = equip;
			if (ammo >= 0) {
				*((short*)0x106D1BA0) = ammo;
			}
			else if (startingMaxAmmo)
				*((short*)0x106D1BA0) = 50;
			else
				*((short*)0x106D1BA0) = 5;
			id_broni = 16;
			break;
		case 12:
			*((byte*)0x106D1BD6) = equip;
			if (ammo >= 0) {
				*((short*)0x106D1BAC) = ammo;
			}
			else if (startingMaxAmmo)
				*((short*)0x106D1BAC) = 300;
			else
				*((short*)0x106D1BAC) = 100;
			id_broni = 19;
			break;
		case 13:
			*((byte*)0x106D1BD8) = equip;
			if (ammo >= 0) {
				*((short*)0x106D1BB0) = ammo;
			}
			else if (startingMaxAmmo)
				*((short*)0x106D1BB0) = 10;
			else
				*((short*)0x106D1BB0) = 2;
			id_broni = 21;
			break;
		case 14: //tranquilizer
			*((byte*)0x106D1BC8) = equip;
			if (ammo >= 0) {
				*((short*)0x106D1B8C) = ammo;
			}
			else if (startingMaxAmmo)
				*((short*)0x106D1B8C) = 50;
			else
				*((short*)0x106D1B8C) = 15;
			id_broni = 6;
			break;
		case 15: //sunfirepod
			*((byte*)0x106D1BCE) = equip;
			if (ammo >= 0) {
				*((short*)0x106D1B98) = ammo;
			}
			else if (startingMaxAmmo)
				*((short*)0x106D1B98) = 300;
			else
				*((short*)0x106D1B98) = 50;
			id_broni = 12;
			break;
		case 16: //pfm
			*((byte*)0x106D1BD0) = equip;
			if (ammo >= 0) {
				*((short*)0x106D1B9C) = ammo;
			}
			else if (startingMaxAmmo)
				*((short*)0x106D1B9C) = 50;
			else
				*((short*)0x106D1B9C) = 15;
			id_broni = 14;
			break;
		case 17: //harpoon
			*((byte*)0x106D1BD3) = equip;
			if (ammo >= 0) {
				*((short*)0x106D1BA2) = ammo;
			}
			else if (startingMaxAmmo)
				*((short*)0x106D1BA2) = 50;
			else
				*((short*)0x106D1BA2) = 12;
			id_broni = 17;
			break;
		case 18: //torpedo
			*((byte*)0x106D1BD4) = equip;
			if (ammo >= 0) {
				*((short*)0x106D1BA4) = ammo;
			}
			else if (startingMaxAmmo)
				*((short*)0x106D1BA4) = 100;
			else
				*((short*)0x106D1BA4) = 30;
			id_broni = 18;
			break;
		case 19: //razor
			*((byte*)0x106D1BD7) = equip;
			break;
		}

		if (!startingMaxAmmo && ammo < 0 && extraAmmo.find(id_broni) != extraAmmo.end()) {
			dodajAmmo(id_broni, extraAmmo[id_broni]);
		}
		if (id_broni == 3 && czy_customWeapons) dodajAmmo(2, 30);
	}
}

void startingChar() {
	int character = *((int*)0x106D1770);
	setStartingWeapons(-1);
	setStartingWeapons(character);
	if (charMOTD.find(-1) != charMOTD.end()) {
		string s = charMOTD[-1];
		char * writable = new char[s.size() + 1];
		strcpy(writable, s.c_str());
		komunikat(writable);
		delete[] writable;
	}
	if (charMOTD.find(character) != charMOTD.end()) {
		string s = charMOTD[character];
		char * writable = new char[s.size() + 1];
		strcpy(writable, s.c_str());
		komunikat(writable);
		delete[] writable;
	}
}

int hookedRespawn(int int1)
{
	int zwrot = 0;
	zwrot = respawn(int1);
	startingChar();
	return zwrot;
}

int hookedChangeChar(int int1)
{
	int zwrot = 0;
	zwrot = changeChar(int1);
	//cout << "change char int1: " << int1 << " zwrot: " << zwrot << endl;
	startingChar();
	return zwrot;
}

int hookedWydropienieBroni(int var1, int var2, float var3)
{
	//cout << "hookedWydropienieBroni" << endl;
	//std::cout << "WydropienieBroni var1: " << hex << var1 << std::endl; //we can access arguments passed to original function
	//std::cout << "WydropienieBroni var2: " << dec << var2 << std::endl;
	//std::cout << "WydropienieBroni var3: " << var3 << std::endl;
	//if (var1 == 0x106d1250) wydropienieBroniHook(var1, var2, var3);
	if (czy_customDrops_enabled) { //&& czyJoined
		if (czy_customDrops_config) {
			int wylosowana_liczba = (std::rand() % 100) + 1;
			//cout << "config wylosowana_liczba: " << wylosowana_liczba << endl;
			//cout << "dchance: " << dchance << endl;
			if (wylosowana_liczba <= dchance) {
				string level = (char*)0x005740A8;
				//cout << "level: " << level << endl;
				if (customDrop.find(level) == customDrop.end()) {
					//cout << "nie znaleziono takiego levela" << endl;
					level = "Default";
					if (customDrop.find("Default") == customDrop.end()) return wydropienieBroniHook(var1, var2, var3);
				}
				//cout << "wiec Default" << endl;
				//cout << "customDrop[level].size(): " << customDrop[level].size() << endl;
				int rweapon = (std::rand() % customDrop[level].size()) + 1;
				//cout << "rweapon: " << rweapon << endl;
				int time = 20000;
				int i = 1;
				for (auto it = customDrop[level].begin(); it != customDrop[level].end(); it++) {
					if (i == rweapon) {
						rweapon = std::get<0>(*it);
						time = std::get<1>(*it);
						break;
					}
					i++;
				}
				//cout << "rweapon: " << rweapon << " time: " << time << endl;
				return wydropienieBroniHook(var1, rweapon, time);
			}
		}
		else {
			int wylosowana_liczba = (std::rand() % 100) + 1;
			//cout << "wylosowana_liczba: " << wylosowana_liczba << endl;
			if (wylosowana_liczba <= dchance) {
				int weapon = 19;
				if(czy_customPickups_enabled && !czy_customPickups_config) weapon = (std::rand() % 18);
				else weapon = (std::rand() % 14);
				switch (weapon)
				{
				case 0:
					weapon = 3; //tekbow
					break;
				case 1:
					weapon = 5; //magnum
					break;
				case 2:
					weapon = 7; //chargeDart 
					break;
				case 3:
					weapon = 8; //shotgun 
					break;
				case 4:
					weapon = 9; //shueder
					break;
				case 5:
					weapon = 10; //plasma 
					break;
				case 6:
					weapon = 11; //firestorm 
					break;
				case 7:
					weapon = 13; //cbore 
					break;
				case 8:
					weapon = 15; //grenadeLauncher 
					break;
				case 9:
					weapon = 16; //scorpionLauncher 
					break;
				case 10:
					weapon = 17; //harpoon
					break;
				case 11:
					weapon = 18; //torpedo 
					break;
				case 12:
					weapon = 20; //flameThrower
					break;
				case 13:
					weapon = 22; //nuke
					break;
				case 14:
					weapon = 18; //torpedo 
					break;
				case 15:
					weapon = 18; //torpedo 
					break;
				case 16:
					weapon = 18; //torpedo 
					break;
				case 17:
					weapon = 18; //torpedo 
					break;
				case 18:
					weapon = 18; //torpedo 
					break;
				default:
					weapon = 19; //riding gun
					break;
				}
				//cout << "custom drop: " << weapon << endl;
				return wydropienieBroniHook(var1, weapon, var3);
			}
		}
	}
	return wydropienieBroniHook(var1, var2, var3);
}

int* getAmmo(int weapon) {
	switch (weapon)
	{
	case 2: //bow
		return (int*)0x106D1B84; //normal arrows
	case 3: //tekbow
		return (int*)0x106D1B86; //explosive arrows
	case 4: //pistol
		return (int*)0x106D1B88;
	case 5: //magnum
		return (int*)0x106D1B88;
	case 6: //usypiacz
		return (int*)0x106D1B8C;
	case 7: //chargeDart
		return (int*)0x106D1B8E;
	case 8: //shotgun
		return (int*)0x106D1B90; //green
	case 9: //szłeder
		return (int*)0x106D1B92; //red
	case 10: //plasma 
		return (int*)0x106D1B96;
	case 11: //firestorm
		return (int*)0x106D1B96;
	case 12: //sunfirepod
		return (int*)0x106D1B98;
	case 13: //cbore
		return (int*)0x106D1B9A;
	case 14: //pfm
		return (int*)0x106D1B9C;
	case 15: //grenade
		return (int*)0x106D1B9E;
	case 16: //scorpion
		return (int*)0x106D1BA0;
	case 17: //harpoon
		return (int*)0x106D1BA2;
	case 18: //torpedo
		return (int*)0x106D1BA4;
	case 20: //flame
		return (int*)0x106D1BAC;
	case 22: //nuke
		return (int*)0x106D1BB0;
	default:
		break;
	}
}

int kto = 0x106d1250;
int kto2 = 0x106d1250;

int hookedStrzal(int var1, int var2)
{
	//cout << "hookedStrzal" << endl;
	////std::cout << "Strzal var1 hex: " << hex << var1 << " dec: " << dec << var1 << std::endl; //we can access arguments passed to original function
	//std::cout << "Strzal var2 hex: " << hex << var2 << " dec: " << dec << var2 << std::endl;
	if (var1 != 0x106d1250) {
		if (var2 == 104) {
			kto = var1;
			var1 = 0x106d1250;
			if (!czyinfoRazor) {
				czyinfoRazor = true;
				komunikat("Razor winds are just visual effect. Enemy razors always go to you but don't make damage (arrows do).");
				komunikat("You can disable razor winds typing /razor");
			}
			if(!czyUserRazors) return strzal(var1, 0);
		}
		else if (var2 == 10) {
			kto2 = var1;
			var1 = 0x106d1250;
			strzal(kto2, var2);
			return strzal(var1, var2);
		}
		else if (var2 == 3) {
			/*strzal(var1, var2);
			return strzal(0x106d1250, 10);*/
			kto2 = var1;
			var1 = 0x106d1250;
			strzal(kto2, var2);
			return strzal(var1, 10);
		}
		return strzal(var1, var2);
	}

	int zwrot = 0;
	//if (wdamage != -1) zwrot = strzal(var1, wdamage); else {
		if (pfmlayer) zwrot = strzal(var1, 12);
		else if (sunfirepod) {
			zwrot = strzal(var1, 10);
		}
		else if (czyPiorun && var2 == 4) {
			//strzelRidingGun = true;
			zwrot = strzal(var1, var2);
		}
		else if (razor) {
			strzel2 = true;
			zwrot = strzal(var1, 104);
		}
		else if (cbore) {
			if (czy_customWeapons) strzel3 = true;
			zwrot = strzal(var1, var2);
		}
		else if (nuke && var2 == 21) {
			if (czy_customWeapons) strzel4 = true;
			zwrot = strzal(var1, var2);
		}
		else if (usypiacz) {
			strzel5 = true;
			zwrot = strzal(var1, 3);
		}
		else if (pistol && var2 == 5) {
			//if (czy_customWeapons) strzel6 = true;
			zwrot = strzal(var1, var2);
		}
		else if ((var2 == 16 || var2 == 231) && czyTorpedoDisabledOnGround) {
			int czy_w_wodzie = *((int*)0x00ADC09C);
			if (czy_w_wodzie == 0) zwrot = strzal(var1, 0);
			else zwrot = strzal(var1, var2);
		}
		else zwrot = strzal(var1, var2);
		
		if (dinoRidingWith == var2 && czy_customWeapons) {
			strzelRidingGun = true;
		}
		if (blackOilWith == var2 && czy_customWeapons) {
			if(czy_userBlackOil) strzelBlackOil = true;
		}
		if (airStrikeWith == var2 && czy_customWeapons) {
			int czy_w_wodzie = *((int*)0x00ADC09C);
			if (czy_w_wodzie == 0){
				int* ammo = getAmmo(airStrikeAmmoId);

				int tempvar = 1;
				if (var2 == 16 && czyTorpedoDisabledOnGround) tempvar = 0;
				if (*ammo - tempvar <= 0) {
					*ammo = 1;
					czyLastAmmo = true;
				}
				strzelAirStrike = true;
			}
		}

	//}
	//cout << "Strzal zwrot: " << hex << zwrot << dec << endl;
	return zwrot;                                        //before returning to normal execution of function
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
	else if ((var2 == 10 || var2 == 3) && kto2 != 0x106d1250 && var1 == 0x106d1250) {
		var1 = kto2;
		kto2 = 0x106d1250;
	}
	return damage(var1, var2, var3, var4, var5);
	/*int zwr = 0;
	zwr = damage(var1, var2, var3, var4, var5);
	cout << "Damage zwr: " << zwr << endl;
	if (var2 == 4) zwr = 1;
	return zwr;*/
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
		else if (var3 == 108 || var3 == 110 || var3 == 117) zwrot = indamage1(var1, 15, 13);
		else if (var3 == 12) zwrot = indamage1(var1, 14, 12);
		else if (var3 == 10) zwrot = indamage1(var1, 12, 10);
		else if (var3 == 205) zwrot = indamage1(var1, 21, 104);
		else if (var3 == 335) zwrot = indamage1(var1, 22, 21);
		else if (var3 == 3 || var3 == 111) zwrot = indamage1(var1, 6, 3);
		else if (var3 == 164) zwrot = indamage1(var1, 7, 4);
		else if (var3 == 5 || var3 == 54 || var3 == 150 || var3 == 209 || var3 == 210) zwrot = indamage1(var1, 4, 5);
		else if (var3 == 11) zwrot = indamage1(var1, 13, 11);
		else if (var3 == 21) zwrot = indamage1(var1, 22, 21);
		else zwrot = indamage1(var1, var2, var3);

		//cout << "Indamage1 zwrot: " << zwrot << endl;
		return zwrot;
	}
	//if (wdamage != -1) zwrot = indamage1(var1, 10, 9);else {
		//if (var3 == 10) zwrot = indamage1(var1, 12, 10);
		if (var3 == 117 || var3 == 108 || var3 == 110) zwrot = indamage1(var1, 15, 13);
		else if (var3 == 5 || var3 == 54 || var3 == 150 || var3 == 209 || var3 == 210) zwrot = indamage1(var1, 4, 5);
		else if (pfmlayer || sunfirepod || razor || cbore || usypiacz) zwrot = indamage1(var1, indmg1var2, indmg1var3);
		/*else if (czyPiorun) {
			if (var3 == 108 || var3 == 110) zwrot = indamage1(var1, 15, 13);
			else zwrot = indamage1(var1, var2, var3);
		}*/
		else if (nuke) {
			if (var3 == 335 || var3 == 117) zwrot = indamage1(var1, 22, 21);
			else zwrot = indamage1(var1, var2, var3);
		}
		else zwrot = indamage1(var1, var2, var3); //indamage1(var1, var2, var3);
	//}
	//cout << "Indamage1 zwrot: " << zwrot << endl;
	return zwrot;                                        //before returning to normal execution of function
}

int hookedPodniesienieBroni(int int1, int int2)
{
	//cout << "hookedzmianabroni" << endl;
	//std::cout << "PodniesienieBroni int1: " << hex << int1 << std::endl; //we can access arguments passed to original function
	//std::cout << "PodniesienieBroni int2: " << dec << int2 << std::endl;
	int zwrot = 0;
	//if (numer_broni != -1) int2 = 5320896 + 24 * numer_broni;
	int id_broni = (int2 - 5320896) / 24;

	if (czy_customPickups_enabled) { //&& czyJoined
		//if (czy_customPickups_config) {
			int wylosowana_liczba = (std::rand() % 100) + 1;
			//cout << "config wylosowana_liczba: " << wylosowana_liczba << endl;
			//map<int, list<int>> customPickup;
			//map<int, int> customPchance;
			int pchance = 0;
				if (customPchance.find(id_broni) != customPchance.end()) pchance = customPchance[id_broni];

			//cout << "pchance: " << pchance << endl;
			if (wylosowana_liczba <= pchance) {
				
				//cout << "customPickup[id_broni].size(): " << customPickup[id_broni].size() << endl;
				int rweapon = (std::rand() % customPickup[id_broni].size()) + 1;
				//cout << "rweapon: " << rweapon << endl;
				int i = 1;
				int ammo = 0;
				for (auto it = customPickup[id_broni].begin(); it != customPickup[id_broni].end(); it++) {
					if (i == rweapon) {
						rweapon = std::get<0>(*it);
						ammo = std::get<1>(*it);
						break;
					}
					i++;
				}
				//cout << "rweapon: " << rweapon << " ammo: " << ammo << endl;
				dodajAmmo(rweapon, ammo);

				int2 = 5320896 + 24 * rweapon;
				return podniesienieBroniHook(int1, int2);
			}
			else {
				if (extraAmmo.find(id_broni) != extraAmmo.end()) {
					dodajAmmo(id_broni, extraAmmo[id_broni]);
				}
				if(id_broni == 3 && czy_customWeapons) dodajAmmo(2, 30);
				else if (id_broni == 8 && czy_customWeapons) dodajAmmo(9, 3);
			}
		//}
	}

	zwrot = podniesienieBroniHook(int1, int2);
	//cout << "PodniesienieBroni zwrot: " << zwrot << endl;
	return zwrot;                                        //before returning to normal execution of function
}

/*int hookedZmianaKoloru(int int1)
{
	int zwrot = 0;
	cout << "ZmianaKoloru int1: " << int1 << endl;
	zwrot = zmianaKoloru(int1);
	cout << "zwrotZmianaKoloru: " << zwrot << endl;
	return zwrot;                                        //before returning to normal execution of function
}

int hookedPreZmianaKoloru(int int1, int int2)
{
	int zwrot = 0;
	cout << "PreZmianaKoloru int1: " << int1 << endl;
	cout << "PreZmianaKoloru int2: " << int2 << endl;
	int var = int1 - 275579872;
	if (var != 0) var /= 40;
	cout << "PreZmianaKoloru var: " << var << endl;
	int var2 = 275579296;
	zwrot = preZmianaKoloru(var, var2);
	cout << "zwrotPreZmianaKoloru: " << zwrot << endl;
	return zwrot;                                        //before returning to normal execution of function
}*/

void sprawdzVoice() {
	std::stringstream ss;
	std::this_thread::sleep_for(std::chrono::seconds{ 10 });
	if (czyHostVoice == false) {
		ss.str("");
		ss << " \x4/99" << " gvoice " << myid;
		wyslij(ss.str());
		std::this_thread::sleep_for(std::chrono::seconds{ 10 });
	}
	if (czyHostVoice == false) {
		ss.str("");
		ss << " \x4/99" << " gvoice " << myid;
		wyslij(ss.str());
		std::this_thread::sleep_for(std::chrono::seconds{ 5 });
	}
	if (czyHostVoice == false) {
		cout << "DISCONNECTED WITH BOT! or lost connection." << endl;

		if (czy_ServerBotRequired) {
			string bigozz = "DISCONNECTED WITH BOT!";
			char * writable = new char[bigozz.size() + 1];
			strcpy(writable, bigozz.c_str());
			WriteToMemory((LPVOID)0x0051B93C, writable, strlen(writable) + 1);
			delete[] writable;

			//wrzuc na specta
			int adres = 0x00AD03D8;
			int var = 4198400;
			WriteToMemory((LPVOID)adres, &var, sizeof(var));
			//printf("komenda write adres Error Code: %i\n", GetLastError());
			ss.str("");
			ss << " \x4/99" << " cstatus " << status << " 0 " << myid;
			wyslij(ss.str());
			status = 0;
			SpectJoin(0, 1);
			czy_blokada_specta = true;
		}

		commands.clear();
		myid = -1;
		czy_wyslane_join = false;
		czyJoined = false;
		czy_unfreezeall = true;
		czy_unobserveall = true;
		czy_zalogowany = false;
	}
	czy_sprawdzanie_voice = false;
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

static size_t my_write(void *buffer, size_t size, size_t nmemb, void *param)
{
	std::string& text = *static_cast<std::string*>(param);
	size_t totalsize = size * nmemb;
	text.append(static_cast<char*>(buffer), totalsize);
	return totalsize;
}

bool readWebSite(string *result, string url) {
	CURL *curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		/* Define our callback to get called when there's data to be written */
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write);
		/* Set a pointer to our struct to pass to the callback */
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, result);

		/* Switch on full protocol/debug output */
		//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

		res = curl_easy_perform(curl);

		/* always cleanup */
		curl_easy_cleanup(curl);

		if (CURLE_OK != res) {
			/* we failed */
			cout << "curl error: " << res << '\n'; //std::cerr
			curl_global_cleanup();
			return false;
		}
	}
	curl_global_cleanup();
	return true;
}

void serverRules() {
	string rules = (char*)0x00B73874;
	czy_ServerBot = false;
	czy_ServerBotRequired = false;
	czy_spectate_enabled = true;
	czy_setColor_enabled = false;
	czy_customDrops_enabled = false;
	czy_custom_damage = false;
	czy_customPickups_enabled = false;
	czy_customWeapons = false;
	czyForceSpectNaStart = false;

	if (rules.find("\\ServerBot\\") != std::string::npos) {
		string subString = rules.substr(rules.find("\\ServerBot\\") + 11);
		//cout << "ServerBotRequiredsubString1: " << subString << endl;
		subString = subString.substr(0, subString.find("\\") - 1);
		//cout << "ServerBot: " << subString << endl;
		if (subString.find("TRUE") == 0 || subString.find("REQUIRED") == 0) {
			czy_ServerBotRequired = true;
			czy_ServerBot = true;
		}
		else if (subString.find("NOTREQUIRED") == 0) {
			czy_ServerBotRequired = false;
			czy_ServerBot = true;
		}
	}

	string lvlSet = (char*)0x00B65DD9;
	//cout << "levelSet: " << lvlSet << endl;
	if (czy_ServerBot && lvlSet.find("beta07.lsm") == std::string::npos && lvlSet.find("beta08.lsm") == std::string::npos && lvlSet.find("beta084.lsm") == std::string::npos) {
		WriteToMemory((void*)0x00B65DD4, "You probably have an old or different version of mod than required", 67);
		ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);
		cout << "\n!!!!" << endl;
		cout << "Error! You probably have an old or different version of mod than required." << endl;
		string required = lvlSet.substr(lvlSet.find("beta"), lvlSet.find(".lsm")-lvlSet.find("beta"));
		cout << "Your version: beta07 Required: " << required << endl;
		cout << "Get new version at http://rebrand.ly/t2mod or contact me (kubpicapf@gmail.com)." << endl;
		cout << "!!!!\n" << endl;
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

		if (rules.find("\\ModSettings\\") != std::string::npos) {
			string subString = rules.substr(rules.find("\\ModSettings\\") + 13);
			//cout << "SetColsubString1: " << subString << endl;
			subString = subString.substr(0, subString.find("\\"));
			//cout << "ModSettings: " << subString << endl;
			//cout << "subString[0]: " << subString[0] << endl;
			//cout << "subString[1]: " << subString[1] << endl;
			if (subString[0] == '0') czy_spectate_enabled = false;
			if (subString[1] == '1') czy_setColor_enabled = true;
			if (subString[2] == '1') czy_customDrops_enabled = true; 
			if (subString[3] == '1') czy_custom_damage = true;
			if (subString[4] == '1') { // useWeaponsEverywhere
				WriteToMemory((void*)0x0041D0C6, "\xEB", 1);
			}
			if (subString[5] == '1') { //flame thrower in water
				WriteToMemory((void*)0x0041D0B6, "\xEB", 1);
			}
			if (subString[6] == '1') czy_customPickups_enabled = true;
			if (subString[7] == '1') {
				czy_customWeapons = true;
				czyTorpedoDisabledOnGround = true;
			}
		}

		if (rules.find("\\GameType\\") != std::string::npos) {
			string subString = rules.substr(rules.find("\\GameType\\") + 10);
			//cout << "GameTypesubString1: " << subString << endl;
			subString = subString.substr(0, subString.find("\\"));
			//cout << "GameType: " << subString << endl;
			if (subString.find("Team Arena") == 0 || subString.find("Arena") == 0) czy_ServerBotRequired = false;
			else if (subString.find("Rok Match") == 0 || subString.find("AWR Match") == 0) {
				if(!czy_ServerBot) czy_setColor_enabled = true;
				czyForceSpectNaStart = true;
			}
			//else if (subString.find("Team Rok Match") == 0 || subString.find("Team AWR Match") == 0) czyForceSpectNaStart = false;
			if (subString.find("Team") != std::string::npos)
				isTeamGameMode = true;
		}

		if (rules.find("\\CfgURL\\") != std::string::npos) {
			cfgurl = rules.substr(rules.find("\\CfgURL\\") + 8);
			cfgurl = cfgurl.substr(0, cfgurl.find("\\"));
			cfgurl = cfgurl.substr(0, cfgurl.find(" "));
			if (cfgurl.find("://") != std::string::npos) {
				cfgurl = "http://" + cfgurl;
			}
		}
		else if (lvlSet.find("beta07.lsm") != std::string::npos) {
			cfgurl = "http://rebrand.ly/t2cfg";
		}

		if (rules.find("\\ArenaWeapons\\") != std::string::npos && rules.find("AWR") != std::string::npos) {
			string s = rules.substr(rules.find("\\ArenaWeapons\\") + 14);
			s = s.substr(0, s.find("\\"));
			istringstream iss(s);
			vector<string> tokens{ istream_iterator<string>{iss},
				istream_iterator<string>{} };
			for (auto const& value : tokens) {
				startingWeapons.push_back(value);
			}
		}
	}
}


DWORD retJMP = 0x004D6012;
//string lvlSet;

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

DWORD retJMP2 = 0x0048297E;

__declspec(naked) void MidChangeNameHook() // __declspec(naked) says to the compiler that we will worry about the prolog/epilog/return of the function
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

	//lvlSet = (char*)0x00B65DD9;
	//cout << "MidChangeNameHook" << endl;
	sprawdzNick();

	//restore stack/registers, so we don't corrupt any data and program flow continues as it should
	__asm popfd
	__asm popad

	// return where we left off
	__asm jmp[retJMP2]
}

DWORD retJMP3 = 0x004827D2;

__declspec(naked) void fixSpecta() // __declspec(naked) says to the compiler that we will worry about the prolog/epilog/return of the function
{
	__asm mov eax, 0 // do what we overwrote
	__asm test ah, 10
	__asm jmp[retJMP3]
}

void zmianka() {
	short var = *((short*)0x106D1BE6);
	//cout << "zmianka var: " << var << endl;
	if (var == 15 && pfmlayer
		|| var == 5 && sunfirepod
		|| var == 10 && razor
		|| var == 7 && czyPiorun
		|| var == 13 && cbore
		|| var == 9 && usypiacz
		|| var == 22 && nuke
		|| var == 4 && pistol
		|| var == 3 && bow
		|| var == 3 && tekbow
		|| var == 8 && shotgun) {
		return;
	}

	//WriteToMemory((LPVOID)0x00AD4538, &var, sizeof(var));
	//WriteToMemory((LPVOID)0x00AD453B, &var, sizeof(var));
	customWeaponId = var;
	sunfirepod = false;
	czyPiorun = false;
	razor = false;
	pfmlayer = false;
	cbore = false;
	usypiacz = false;
	nuke = false;
	pistol = false;
	bow = false;
	tekbow = false;
	shotgun = false;
	//zm = 0;
	
	if (var == 14) {
		pfmlayer = true;
		if (!czyinfo4) {
			czyinfo4 = true;
			komunikat("Mines will spawn only for players in your rendering distance.");
			komunikat("Players far from you may not see some mines.");
		}
		indmg1var2 = 14;
		indmg1var3 = 12;

		short var2 = 15;
		WriteToMemory((LPVOID)0x106D1D8C, &var2, sizeof(var2));
	}
	else if (var == 12) {
		sunfirepod = true;
		indmg1var2 = 12;
		indmg1var3 = 10;

		short var2 = 5;
		WriteToMemory((LPVOID)0x106D1D8C, &var2, sizeof(var2));
	}
	else if (var == 21) {
		razor = true;
		indmg1var2 = 21;
		indmg1var3 = 104;

		short var2 = 10;
		WriteToMemory((LPVOID)0x106D1D8C, &var2, sizeof(var2));
	}
	else if (var == 7) {
		czyPiorun = true;
		//indmg1var2 = 7;
		//indmg1var3 = 4;
	}
	else if (var == 13) {
		cbore = true;
		indmg1var2 = 13;
		indmg1var3 = 11;
	}
	else if (var == 2) {
		bow = true;
		if (!czyinfo1) {
			czyinfo1 = true;
			komunikat("Use zoom to shoot faster. [Shift]");
		}
		short var2 = 3;
		WriteToMemory((LPVOID)0x106D1D8C, &var2, sizeof(var2));
	}
	else if (var == 3) {
		tekbow = true;
		if (!czyinfo1) {
			czyinfo1 = true;
			komunikat("Use zoom to shoot faster. [Shift]");
		}
	}
	else if (var == 8) {
		shotgun = true;
		if (!czyinfo2) {
			czyinfo2 = true;
			komunikat("[H] to change ammo type.");
		}
	}
	else if (var == 4) {
		pistol = true;
	}
	else if (var == 6) {
		usypiacz = true;
		if (!czyinfo3) {
			czyinfo3 = true;
			komunikat("Every shot will throw SunfirePod visible only for other players (to blind them for awhile).");
		}
		indmg1var2 = 6;
		indmg1var3 = 3;
		short var2 = 9;
		WriteToMemory((LPVOID)0x106D1D8C, &var2, sizeof(var2));
	}
	else if (var == 22) {
		nuke = true;
	}


	if (czy_custom_damage) { //&& czyJoined
		if (customDamage.find(var) != customDamage.end()) {
			float var2 = customDamage[var];
			//cout << "zmiankaD var2: " << var2 << endl;
			WriteToMemory((LPVOID)0x00AD44EC, &var2, sizeof(var2));

			/*ss.str("");
			ss << "Weapon: " << dec << var << " damage: " << var2;
			string s = ss.str();
			char * writable = new char[s.size() + 1];
			strcpy(writable, s.c_str());
			komunikat(writable);
			delete[] writable;*/
		}
		else if(defaultDamage != -1){
			float var2 = defaultDamage;
			//var2 = customDamage[-1];
			//cout << "zmiankaD var2: " << var2 << endl;
			WriteToMemory((LPVOID)0x00AD44EC, &var2, sizeof(var2));
		}

		if (customNode.find(var) != customNode.end()) {
			float var2 = customNode[var];
			//cout << "zmiankaN var2: " << var2 << endl;
			WriteToMemory((LPVOID)0x00AD44F0, &var2, sizeof(var2));

			/*ss.str("");
			ss << "Weapon: " << dec << var << " node: " << var2;
			string s = ss.str();
			char * writable = new char[s.size() + 1];
			strcpy(writable, s.c_str());
			komunikat(writable);
			delete[] writable;*/
		}
		else if (defaultNode != -1) {
			float var2 = defaultNode;
			//var2 = customNode[-1];
			//cout << "zmiankaN var2: " << var2 << endl;
			WriteToMemory((LPVOID)0x00AD44F0, &var2, sizeof(var2));
		}

	}
}

DWORD retJMP4 = 0x0042693F;

__declspec(naked) void midZmianaBroni() // __declspec(naked) says to the compiler that we will worry about the prolog/epilog/return of the function
{
	__asm mov eax, [edx + 0x48] // do what we overwrote
		__asm mov[edi + 0x2C], eax

	// do what you want now, i'll obtain data from EBX register, for example, and store it for later use
	//__asm mov myData, ebx

	//if you want to do any other calls to other functions, etc and don't need the registers/stack anymore push it
	//for example:
	__asm pushad // push all general registers
	__asm pushfd // push all flags

				 // do your stuff here.. calls, calculations..
				 // remember, you can't do everything in a naked function, it's limited..

	zmianka();

	//restore stack/registers, so we don't corrupt any data and program flow continues as it should
	__asm popfd
	__asm popad

	// return where we left off
	__asm jmp[retJMP4]
}

DWORD WINAPI custom_weapons(LPVOID lpParam) {
	while (1) {
		Sleep(16);
		if (strzelRidingGun) {
			strzelRidingGun = false;
			Sleep(80);
			if (stronaRidingGun) {
				stronaRidingGun = false;
				strzal(0x106d1250, 110); //riding gun prawe
			}
			else {
				stronaRidingGun = true;
				strzal(0x106d1250, 108); //riding gun lewe
			}
		}
		else if (strzel2) {
			strzel2 = false;
			Sleep(2); //Sleep(35);
			strzal(0x106d1250, 205);
			strzal(0x106d1250, 205);
			strzal(0x106d1250, 205);
			Sleep(2);
			strzal(0x106d1250, 205);
			strzal(0x106d1250, 205);
			strzal(0x106d1250, 205);
			Sleep(5);
			strzal(0x106d1250, 205);
			strzal(0x106d1250, 205);
			strzal(0x106d1250, 205);
		}
		else if (strzel3) {
			strzel3 = false;

			strzal(0x106d1250, 14);
		}
		else if (strzel4 && howManyExtraNukeExplosions) {
			strzel4 = false;
			Sleep(35);
			for (int i = 0; i < howManyExtraNukeExplosions; i++) {
				short* var = (short*)0x106D1BB0;
				*var += 1;
				strzal(0x106d1250, 21);
				Sleep(35);
			}
		}
		else if (strzelAirStrike) {
			strzelAirStrike = false;
			//strzal(0x106d1250, 335);
			if (airStrikeDelay >= 500 && czyinfoAirStrike < 3) {
				komunikat("Move to open space or else Katyusha rockets will kill you! (Change weapon to cancel)");
				czyinfoAirStrike++;
			}
			else if (czyinfoAirStrike < 2) {
				komunikat("Katyusha launched! Move to open space or else rockets will kill you! (Air-strike)");
				czyinfoAirStrike++;
			}
			Sleep(airStrikeDelay);
			short var = *((short*)0x106D1D8C);
			if (var == airStrikeAmmoId) {
				int* ammo = getAmmo(airStrikeAmmoId);
				int tempammo = *ammo;
				tempammo -= airStrikeAmmoCost;
				if (tempammo < 0) tempammo = 0;
				*ammo = tempammo;
				if (airStrikeDelay >= 400) komunikat("Katyusha launched! (Air-strike)");
				strzal(0x106d1250, 117);
				Sleep(35);
				strzal(0x106d1250, 117);
				Sleep(35);
				strzal(0x106d1250, 117);
				Sleep(35);
				strzal(0x106d1250, 117);
				Sleep(35);
				strzal(0x106d1250, 117);
				Sleep(35);
				strzal(0x106d1250, 117);
				Sleep(35);
				strzal(0x106d1250, 117);
			}
			else {
				komunikat("You changed weapon - Airstrike canceled.");
			}
			if (czyLastAmmo) {
				czyLastAmmo = false;
				int* ammo = getAmmo(airStrikeAmmoId);
				*ammo -= 1;
			}
		}
		else if (strzel5) {
			strzel5 = false;
			strzal(0x106d1250, 5);
			Sleep(35);
			strzal(0x106d1250, 111);
			Sleep(35);
			strzal(0x106d1250, 111);
			Sleep(35);
			strzal(0x106d1250, 111);
			Sleep(35);
			strzal(0x106d1250, 111);
			Sleep(35);
			strzal(0x106d1250, 111);
			Sleep(35);
			strzal(0x106d1250, 111);
			Sleep(35);
			strzal(0x106d1250, 111);
			Sleep(35);
			strzal(0x106d1250, 111);
			Sleep(35);
			strzal(0x106d1250, 111);
			Sleep(35);
			strzal(0x106d1250, 111);
		}
		else if (strzelBlackOil) {
			if (!czyInfoOil) {
				czyInfoOil = true;
				komunikat("Type /oil to disable generation of black oil.");
			}
			strzelBlackOil = false;
			strzal(0x106d1250, 54);
			Sleep(35);
			strzal(0x106d1250, 150);
		}
	}

	return S_OK;
}

void generateTID(char pathc[]) {
	string path = pathc;
	path = path.substr(0, path.find_last_of("/\\"));
	path = path + "\\turok2.ini";
	fstream config;
	config.open(path, std::fstream::in);
	string seed = "hi";
	if (!config) //if (config.good() == true)
	{
		//cout << "turok2.ini not found!" << endl;
		seed += "omgT2iniNOTfound";
		for (int i = 0; i < 20; i++) {
			char losowyZnak = 'a' + (std::rand() % 26);
			seed += losowyZnak;
		}
	}
	else {
		string slowo;
		string wiersz;
		while (getline(config, wiersz)) {
			slowo = wiersz.substr(0, wiersz.find("=") + 1);
			//cout << slowo << endl;
			if (slowo == "Names=" || slowo == "Names_0=" || slowo == "Names_1=" || slowo == "Names_2=" || slowo == "Names_3=" || slowo == "Names_4=") {
				string temp = wiersz.substr(wiersz.find("=") + 1);
				seed += temp;
			}
			char losowyZnak = 'a' + (std::rand() % 26);
			seed += losowyZnak;
			slowo.clear();
			wiersz.clear();
		}
		config.close();
	}
	//cout << "seed: " << seed << endl;
	tid = md5(seed);
	for (int i = 0; i < 5; i++) {
		char losowyZnak = 'a' + (std::rand() % 26);
		tid += losowyZnak;
	}
}

DWORD WINAPI Main_thread(LPVOID lpParam)
{
	srand(time(NULL));
	HANDLE han = GetStdHandle(STD_OUTPUT_HANDLE);
	WriteConsole(han, "hello", 6, new DWORD, 0);
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	string version = "B0.8.4";
	cout << "T2 kub's mod " << version << endl;
	cout << "Mod\'s website: http://rebrand.ly/t2mod" << endl;
	cout << "Loading... Wait..." << endl;

	placeJMP((BYTE*)0x00426939, (DWORD)myMidfuncHook, 6);
	WriteToMemory((void*)0x0041D0D8, "\xEB", 1);
	std::stringstream ss;
	ss.str("");
	ss << &customWeaponId;
	//cout << "&customWeaponId = 0: " << ss.str() << endl;
	char adresWbajtach[4];
	//cout << "1: " << hex << strtol(ss.str().substr(6).c_str(), NULL, 16) << endl;
	//cout << "2: " << strtol(ss.str().substr(4, 2).c_str(), NULL, 16) << endl;
	//cout << "3: " << strtol(ss.str().substr(2, 2).c_str(), NULL, 16) << endl;
	//cout << "4: " << strtol(ss.str().substr(0, 2).c_str(), NULL, 16) << endl;
	adresWbajtach[0] = strtol(ss.str().substr(6).c_str(), NULL, 16);
	adresWbajtach[1] = strtol(ss.str().substr(4, 2).c_str(), NULL, 16);
	adresWbajtach[2] = strtol(ss.str().substr(2, 2).c_str(), NULL, 16);
	adresWbajtach[3] = strtol(ss.str().substr(0, 2).c_str(), NULL, 16);
	//cout << "adresWbajtach: " << hex << (int)adresWbajtach[0] << " " << (int)adresWbajtach[1] << " " << (int)adresWbajtach[2] << " " << (int)adresWbajtach[3] << dec << endl;

	ss.str("");
	ss << "\x0F\xBF\x0D" << adresWbajtach;
	WriteToMemory((void*)0x0041928D, ss.str().c_str(), 7);
	ss.str("");
	ss << "\x0F\xBF\x15" << adresWbajtach;
	WriteToMemory((void*)0x004192B2, ss.str().c_str(), 7);
	ss.str("");
	ss << "\x0F\xBF\x3D" << adresWbajtach;
	WriteToMemory((void*)0x0041D8CA, ss.str().c_str(), 7);
	ss.str("");
	ss << "\x0F\xBF\x0D" << adresWbajtach;
	WriteToMemory((void*)0x00426C8B, ss.str().c_str(), 7);
	ss.str("");
	ss << "\x0F\xBF\x05" << adresWbajtach;
	WriteToMemory((void*)0x00426AE8, ss.str().c_str(), 7);
	ss.str("");
	ss << "\x0F\xBF\x05" << adresWbajtach;
	WriteToMemory((void*)0x0041DD5A, ss.str().c_str(), 7);
	ss.str("");
	ss << "\x0F\xBF\x05" << adresWbajtach;
	WriteToMemory((void*)0x0041DDF2, ss.str().c_str(), 7);
	ss.str("");
	ss << "\x0F\xBF\x15" << adresWbajtach;
	WriteToMemory((void*)0x00426981, ss.str().c_str(), 7);
	ss.str("");
	ss << "\x0F\xBF\x0D" << adresWbajtach;
	WriteToMemory((void*)0x00426ECA, ss.str().c_str(), 7);
	WriteToMemory((LPVOID)0x00B723CC, "\x01", 1);

	customPchance[18] = 80;
	//dodaj_customPickup(18, 2, 30);
	dodaj_customPickup(18, 6, 12);
	dodaj_customPickup(18, 12, 200);
	dodaj_customPickup(18, 14, 22);
	dodaj_customPickup(18, 20, 0);
	customPchance[5] = 20;
	dodaj_customPickup(5, 12, 200);
	//customPchance[3] = 20;
	//dodaj_customPickup(3, 2, 30);
	customPchance[9] = 20;
	dodaj_customPickup(9, 6, 12);
	customPchance[15] = 20;
	dodaj_customPickup(15, 14, 22);
	customPchance[10] = 15;
	dodaj_customPickup(10, 20, 0);
	customPchance[8] = 15;
	dodaj_customPickup(8, 21, 1);
	customPchance[7] = 15;
	dodaj_customPickup(7, 17, 0);
	customPchance[13] = 15;
	dodaj_customPickup(13, 18, 0);
	extraAmmo[19] = 100;
	extraAmmo[5] = 150;
	extraAmmo[7] = 20;
	//extraAmmo[8] = 5;
	extraAmmo[9] = 6;
	//extraAmmo[11] = 20;
	extraAmmo[13] = 7;
	extraAmmo[21] = 1;
	extraAmmo[17] = 5;

	float camerafov1 = 73.74;
	float weaponfov1 = 52.6714;
	float maxpan = 4000;
	bool hideconsole = true;

	char pathc[MAX_PATH];
	GetModuleFileNameA(hModule, pathc, sizeof(pathc));
	//cout << "pathc: " << pathc << endl;
	string path = pathc;
	path = path.substr(0, path.find_last_of("/\\"));
	
	/*string satrib = "attrib -r \"" + path + "\\launcherConfig.txt\" /S /D"; //"\\*.*\"
	char * writablez = new char[satrib.size() + 1];
	strcpy(writablez, satrib.c_str());
	//cout << "writablez: " << writablez << endl;
	WinExec(writablez, SW_HIDE);
	delete[] writablez;

	satrib = "attrib -r \"" + path + "\" /S /D"; //"\\*.*\"
	writablez = new char[satrib.size() + 1];
	strcpy(writablez, satrib.c_str());
	//cout << "writablez: " << writablez << endl;
	WinExec(writablez, SW_HIDE);
	delete[] writablez;*/

	path = path + "\\launcherConfig.txt";
	//cout << "path: " << path << endl;
	fstream config;
	config.open(path, std::fstream::in | std::fstream::out);

	//string startParams = "-maxframerate 64 -quickmouse -exclusivemouse -AverageMouse 0";
	//string exe = "Turok2MP.exe";
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
		config << "StartupParameters=-maxframerate 64 -quickmouse -exclusivemouse -AverageMouse 0" << endl;
		config << "CameraFOV=73.74" << endl;
		config << "WeaponFOV=52.6714" << endl;
		//config << "ShowGUI=1" << endl;
		config << "//MaxPan is about directional (\"3D\") sound (600 is default, 10000 is best for competitive gameplay but may be annoying) - you can test it in game with 'set maxpan' command." << endl;
		config << "MaxPan=4000" << endl;
		config << "ShowModConsole=0" << endl;
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
			else if (slowo == "ShowModConsole=") {
				string num = wiersz.substr(wiersz.find("=") + 1);
				int show = ::atoi(num.c_str());
				if (show > 0)
					hideconsole = false;
			}
			slowo.clear();
			wiersz.clear();
		}
		config.close();
	}

	path = pathc;
	path = path.substr(0, path.find_last_of("/\\"));
	path = path + "\\Video_DLL.imp";

	fstream ftid;
	ftid.open(path, std::fstream::in | std::fstream::out);
	if (!ftid) {
		ftid.open(path, std::fstream::trunc | std::fstream::out);
		ftid.close();
		// re-open with original flags
		ftid.open(path, std::fstream::in | std::fstream::out);

		//ofstream newconfig;
		//newconfig.open("launcherConfig.txt");
		generateTID(pathc);
		ftid << "//do NOT remove or change this file!" << endl;
		ftid << "system=" << tid << endl;
	}
	else {
		string slowo;
		string wiersz;
		//std::stringstream ss;
		while (getline(ftid, wiersz)) {
			slowo = wiersz.substr(0, wiersz.find("=") + 1);
			//cout << slowo << endl;
			if (slowo == "system=") {
				tid = wiersz.substr(wiersz.find("=") + 1);
			}
			slowo.clear();
			wiersz.clear();
		}
		if (tid.length() != 37) {
			//cout << "bledna dlugosc tid" << endl;
			//cout << "tid: " << tid << endl;
			generateTID(pathc);
			ftid.open(path, std::fstream::trunc | std::fstream::out);
			ftid.close();
			ftid.open(path, std::fstream::in | std::fstream::out);
			ftid << "//do NOT remove or change this file!" << endl;
			ftid << "system=" << tid << endl;
		}
		ftid.close();
	}

	Sleep(1000);
	DWORD address = (DWORD)hModule + 0x28D28;
	//cout << "address: " << hex << address << endl;

	placeJMP((BYTE*)0x004D600D, (DWORD)myMidfuncHook, 5);
	placeJMP((BYTE*)0x00482979, (DWORD)MidChangeNameHook, 5);
	placeJMP((BYTE*)0x004827CC, (DWORD)fixSpecta, 6);
	placeJMP((BYTE*)0x00426939, (DWORD)midZmianaBroni, 6);

	string result;
	readWebSite(&result, "http://rebrand.ly/t2motd");
	//cout << "curl: " << result << "\n\n";

	istringstream stream(result);
	for (string line; std::getline(stream, line); ) {
		string slowo = line.substr(0, line.find("=") + 1);
		if (slowo == "Version=") {
			string v = line.substr(line.find("=") + 1);
			if (v != version) {
				ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);
				cout << "\n!!!!" << endl;
				cout << "New version of mod is available!!!" << endl;
				cout << "Your version: " << version << " Newest: " << v << endl;
				cout << "Get new version at http://rebrand.ly/t2mod or contact me (kubpicapf@gmail.com)." << endl;
				hideconsole = false;
				cout << "!!!!\n" << endl;
			}
		}
		if (slowo == "MOTD=") {
			cout << line.substr(line.find("=") + 1) << endl;
		}
	}

	cout << "Mod loaded successfully." << endl;
	cout << "Do NOT close this window!!!" << endl;

	if(hideconsole)
		ShowWindow(GetConsoleWindow(), SW_HIDE);

	//while(*((int*)0x00AD0280)!=1);
	while (!czyWystartowano) Sleep(500);
	WriteToMemory((void*)address, "\xD9\x1D\x56\xBD\xAC", 5);
	result = "";
	if (!czy_ServerBotRequired) {
		czy_blokada_specta = false;
		if (cfgurl != "null") {
			if (!readWebSite(&result, cfgurl))
				result = "null";
		}
	}
	Sleep(400);
	if (isTeamGameMode && *((int*)0x106D1770) == 0) {
		int temp = -1;
		WriteToMemory((LPVOID)0x106D1770, &temp, sizeof(temp));
	}
	int spect = 4198400;
	while (true) { //game is loading (joining to server)
		Sleep(16);
		if(czyForceSpectNaStart) WriteToMemory((LPVOID)0x00AD03D8, &spect, sizeof(spect)); //if (czy_ServerBotRequired)
		int var = *((int*)0x106D1C84);
		int var2 = *((int*)0x106D1770);
		if (var == 1 || var == 2 || (isTeamGameMode && var2) ) {
			/*
			WriteToMemory((LPVOID)0x106FD408, &camerafov1, sizeof(camerafov1));
			WriteToMemory((LPVOID)0x00523E5C, &weaponfov1, sizeof(weaponfov1));
			WriteToMemory((LPVOID)0x00528824, &maxpan, sizeof(maxpan));
			*/

			break;
		}
	}
	//cout << hex << "baseAddress: " << baseAddress << endl;
	//cout << hex << "baseAddress2: " << FindDmaAddy(1, hackOffsets, baseAddress) << endl;
	if (czy_ServerBotRequired && cfgurl != "null") {
		if (!readWebSite(&result, cfgurl))
			result = "null";
	}
	Sleep(30);//Sleep(400);
	//WriteToMemory((LPVOID)0x00AD03D8, &spect, sizeof(spect));
	//SpectJoin(0, 1);
	byte bicik = *((byte*)0x0051A00F);
	//cout << "bicik: " << hex << (int) bicik << endl;
	if (bicik == 0x3F) { //if allCharsSame==TRUE then fix raptor's speed
		float turokspeed = *((float*)0x101423C4);
		//set raptor speed to be 1.25 times faster than turok:
		turokspeed *= 1.25;
		WriteToMemory((LPVOID)0x10144644, &turokspeed, sizeof(turokspeed));
		*((float*)0x10144648) = 1.6;
	}
	sprawdzNick();
	WriteToMemory((LPVOID)0x00523E5C, &weaponfov1, sizeof(weaponfov1));
	WriteToMemory((LPVOID)0x00528824, &maxpan, sizeof(maxpan));
	if (camerafov1 >= 90) {
		camerafov1 *= 0.017444445;
		WriteToMemory((LPVOID)0x00508380, &camerafov1, 4);
		camerafov1 = 90;
		if (camerafov1 > 90) komunikat("Warning! FOV over 90 may be bugged!");
	}
	WriteToMemory((LPVOID)0x106FD408, &camerafov1, 4);
	defaultDamage = *((float*)0x00AD44EC);
	defaultNode = *((float*)0x00AD44F0);
	string s = "T2 kub's mod " + version + " (type /fov 90 to change field of view)";
	char * writable = new char[s.size() + 1];
	strcpy(writable, s.c_str());
	komunikat(writable);
	delete[] writable;

	map<string, unsigned int> floatCfgs;
	floatCfgs["fleshLength="] = 0x101424C0;
	floatCfgs["fleshHeight="] = 0x101424BC;
	floatCfgs["fleshWidth="] = 0x101424B8;
	floatCfgs["fleshJump="] = 0x101424A0;
	floatCfgs["fleshSpeed="] = 0x1014249C;
	floatCfgs["adonLength="] = 0x10142430;
	floatCfgs["adonHeight="] = 0x1014242C;
	floatCfgs["adonWidth="] = 0x10142428;
	floatCfgs["adonJump="] = 0x10142410;
	floatCfgs["adonSpeed="] = 0x1014240C;
	floatCfgs["turokLength="] = 0x101423E8;
	floatCfgs["turokHeight="] = 0x101423E4;
	floatCfgs["turokWidth="] = 0x101423E0;
	floatCfgs["turokJump="] = 0x101423C8;
	floatCfgs["turokSpeed="] = 0x101423C4;
	floatCfgs["purLength="] = 0x10142508;
	floatCfgs["purHeight="] = 0x10142504;
	floatCfgs["purWidth="] = 0x10142500;
	floatCfgs["purJump="] = 0x101424E8;
	floatCfgs["purSpeed="] = 0x101424E4;
	floatCfgs["endLength="] = 0x10142550;
	floatCfgs["endHeight="] = 0x1014254C;
	floatCfgs["endWidth="] = 0x10142548;
	floatCfgs["endJump="] = 0x10142530;
	floatCfgs["endSpeed="] = 0x1014252C;
	floatCfgs["fireLength="] = 0x10142598;
	floatCfgs["fireHeight="] = 0x10142594;
	floatCfgs["fireWidth="] = 0x10142590;
	floatCfgs["fireJump="] = 0x10142578;
	floatCfgs["fireSpeed="] = 0x10142574;
	floatCfgs["iggyLength="] = 0x101425E0;
	floatCfgs["iggyHeight="] = 0x101425DC;
	floatCfgs["iggyWidth="] = 0x101425D8;
	floatCfgs["iggyJump="] = 0x101425C0;
	floatCfgs["iggySpeed="] = 0x101425BC;
	floatCfgs["campLength="] = 0x10142628;
	floatCfgs["campHeight="] = 0x10142624;
	floatCfgs["campWidth="] = 0x10142620;
	floatCfgs["campJump="] = 0x10142608;
	floatCfgs["campSpeed="] = 0x10142604;
	floatCfgs["telLength="] = 0x10142670;
	floatCfgs["telHeight="] = 0x1014266C;
	floatCfgs["telWidth="] = 0x10142668;
	floatCfgs["telJump="] = 0x10142650;
	floatCfgs["telSpeed="] = 0x1014264C;
	floatCfgs["gantLength="] = 0x10142478;
	floatCfgs["gantHeight="] = 0x10142474;
	floatCfgs["gantWidth="] = 0x10142470;
	floatCfgs["gantJump="] = 0x10142458;
	floatCfgs["gantSpeed="] = 0x10142454;
	floatCfgs["raptorLength="] = 0x10144668;
	floatCfgs["raptorHeight="] = 0x10144664;
	floatCfgs["raptorWidth="] = 0x10144660;
	floatCfgs["raptorJump="] = 0x10144648;
	floatCfgs["raptorSpeed="] = 0x10144644;
	map<string, unsigned int> intCfgs;
	intCfgs["fleshHP="] = 0x10142498;
	intCfgs["adonHP="] = 0x10142408;
	intCfgs["turokHP="] = 0x101423C0;
	intCfgs["purHP="] = 0x101424E0;
	intCfgs["endHP="] = 0x10142528;
	intCfgs["fireHP="] = 0x10142570;
	intCfgs["iggyHP="] = 0x101425B8;
	intCfgs["campHP="] = 0x10142600;
	intCfgs["telHP="] = 0x10142648;
	intCfgs["gantHP="] = 0x10142450;
	intCfgs["raptorHP="] = 0x10144640;
	map<string, unsigned int> charactersCfgs;
	charactersCfgs["startingWeapons="] = -1;
	charactersCfgs["turokWeapons="] = 0;
	charactersCfgs["adonWeapons="] = 1;
	charactersCfgs["gantWeapons="] = 2;
	charactersCfgs["fleshWeapons="] = 3;
	charactersCfgs["purWeapons="] = 4;
	charactersCfgs["endWeapons="] = 5;
	charactersCfgs["fireWeapons="] = 6;
	charactersCfgs["iggyWeapons="] = 7;
	charactersCfgs["campWeapons="] = 8;
	charactersCfgs["telWeapons="] = 9;
	charactersCfgs["respawnMOTD="] = -1;
	charactersCfgs["turokMOTD="] = 0;
	charactersCfgs["adonMOTD="] = 1;
	charactersCfgs["gantMOTD="] = 2;
	charactersCfgs["fleshMOTD="] = 3;
	charactersCfgs["purMOTD="] = 4;
	charactersCfgs["endMOTD="] = 5;
	charactersCfgs["fireMOTD="] = 6;
	charactersCfgs["iggyMOTD="] = 7;
	charactersCfgs["campMOTD="] = 8;
	charactersCfgs["telMOTD="] = 9;

	if (cfgurl != "null") {
		/*string result;
		//cout << cfgurl << endl;
		if (readWebSite(&result, cfgurl)) {
			//cout << "curl: " << result << "\n\n";
		}
		else result = "null";*/

		istringstream stream(result);
		bool loop = true;
		std::string line;
		if (!std::getline(stream, line))
			loop = false;
		bool continueLoop = false;
		while (loop) {
			//cout << line << endl;
			if (line.find("//") != std::string::npos || line.length() < 3) {
				if (!std::getline(stream, line)) //get new line
					loop = false;
				continue;
			}
			string slowo = line.substr(0, line.find("=") + 1);

			if (floatCfgs.count(slowo)) {
				//*((float*)floatCfgs[slowo]) = stof(line.substr(line.find("=") + 1));
				float f = stof(line.substr(line.find("=") + 1));
				WriteToMemory((LPVOID)floatCfgs[slowo], &f, 4);
			}
			else if (intCfgs.count(slowo)) {
				//*((int*)intCfgs[slowo]) = stoi(line.substr(line.find("=") + 1));
				int i = stoi(line.substr(line.find("=") + 1));
				WriteToMemory((LPVOID)intCfgs[slowo], &i, 4);
			}
			else if (charactersCfgs.count(slowo)) {
				if (slowo.find("Weapons") != std::string::npos) {
					vector<string>* v;
					switch (charactersCfgs[slowo])
					{
					case 0:
						v = &turokWeapons;
						break;
					case 1:
						v = &adonWeapons;
						break;
					case 2:
						v = &gantWeapons;
						break;
					case 3:
						v = &fleshWeapons;
						break;
					case 4:
						v = &purWeapons;
						break;
					case 5:
						v = &endWeapons;
						break;
					case 6:
						v = &fireWeapons;
						break;
					case 7:
						v = &iggyWeapons;
						break;
					case 8:
						v = &campWeapons;
						break;
					case 9:
						v = &telWeapons;
						break;
					case -1:
					default:
						v = &startingWeapons;
						break;
					}

					string s = line.substr(line.find("=") + 1);
					istringstream iss(s);
					vector<string> tokens{ istream_iterator<string>{iss},
						istream_iterator<string>{} };
					for (auto const& value : tokens) {
						if (value == "-100")
							(*v).clear();
						else
							(*v).push_back(value);
					}
				}
				else { //motd
					charMOTD[charactersCfgs[slowo]] = line.substr(line.find("=") + 1);
				}
			}
			else if (slowo == "customDamage=") {
				while (1) {
					if (!std::getline(stream, line)) {
						loop = false;
						continueLoop = true;
						break;
					}
					if (line.find("=") != std::string::npos) {
						continueLoop = true; //continue first loop without getting new line
						break;
					}
					if (line.find("//") != std::string::npos || line.length() < 3 || line.find(";") == std::string::npos || line.find(":") == std::string::npos) continue;
					int weapon = atoi(line.substr(0, line.find("; ")).c_str());
					char co = line[line.find("; ") + 2];
					float value = atof(line.substr(line.find(": ") + 2).c_str());
					if (co == 'd') { //damage
						if (weapon == 0) defaultDamage = value;
						else customDamage[weapon] = value;
					}
					else if (co == 'n') { //node
						if (weapon == 0) defaultNode = value;
						else customNode[weapon] = value;
					}
				}
			}
			else if (slowo == "customDrops=") {
				while (1) {
					if (!std::getline(stream, line)) {
						loop = false;
						continueLoop = true;
						break;
					}
					if (line.find("=") != std::string::npos) {
						continueLoop = true; //continue first loop without getting new line
						break;
					}
					if (line.find("//") != std::string::npos || line.length()<3 || line.find(":") == std::string::npos) continue;
					if (line.find("Chance:") == 0) {
						dchance = atoi(line.substr(7).c_str());
						continue;
					}
					string map = line.substr(0, line.find("; "));
					int weapon = atoi(line.substr(line.find("; ") + 2, line.find(": ")).c_str());
					int time = atoi(line.substr(line.find(": ") + 2).c_str());
					czy_customDrops_config = true;
					if (customDrop.find(map) == customDrop.end()) {
						list<pair<int, int>> lista;
						customDrop[map] = lista;
					}
					auto it = customDrop.find(map);
					if (it != customDrop.end()) {
						std::list<pair<int, int>> *p = NULL;
						p = &(it->second);
						(*p).push_back(std::make_pair(weapon, time));
						//cout << "cdrop map: " << map << " weapon: " << weapon << " time: " << time << endl;
					}
				}
			}
			else if (slowo == "customPickups=") {
				while (1) {
					if (!std::getline(stream, line)) {
						loop = false;
						continueLoop = true;
						break;
					}
					if (line.find("=") != std::string::npos) {
						continueLoop = true; //continue first loop without getting new line
						break;
					}

					if (line.find("//") != std::string::npos || line.length()<3 || line.find(";") == std::string::npos) continue;
					if (line.find("Chance:") == 0) {
						line = line.substr(7);
						int pred = atoi(line.substr(0, line.find(";")).c_str());
						//cout << "pred: " << pred << endl;
						line = line.substr(line.find(";") + 1);
						int chance = atoi(line.substr(0, line.find(":")).c_str());
						//cout << "chance: " << chance << endl;
						customPchance[pred] = chance;
					}
					else if (line.find("Pick:") == 0) {
						line = line.substr(5);
						int pred = atoi(line.substr(0, line.find(";")).c_str());
						//cout << "pred: " << pred << endl;
						line = line.substr(line.find(";") + 1);
						int pick = atoi(line.substr(0, line.find(":")).c_str());
						//cout << "pick: " << pick << endl;
						int ammo = atoi(line.substr(line.find(":") + 1).c_str());
						//cout << "ammo: " << ammo << endl;

						if (!czy_customPickups_config) {
							czy_customPickups_config = true;
							customPickup.clear();
							customPchance.clear();
							extraAmmo.clear();
						}
						dodaj_customPickup(pred, pick, ammo);
					}
					else if (line.find("Ammo:") == 0) {
						line = line.substr(5);
						int pred = atoi(line.substr(0, line.find(";")).c_str());
						//cout << "pred: " << pred << endl;
						int ammo = atoi(line.substr(line.find(";") + 1).c_str());
						//cout << "pick: " << ammo << endl;
						extraAmmo[pred] = ammo;
					}

				}
			}
			else if (slowo == "customWeapons=") {
				while (1) {
					if (!std::getline(stream, line)) {
						loop = false;
						continueLoop = true;
						break;
					}
					if (line.find("=") != std::string::npos) {
						continueLoop = true; //continue first loop without getting new line
						break;
					}

					if (line.find("//") != std::string::npos || line.length()<3) continue;
					if (line.find("torpedoDisabledOnSurface:") == 0) {
						int var = atoi(line.substr(25).c_str());
						czyTorpedoDisabledOnGround = var;
					}
					else if (line.find("howManyExtraNukeExplosions:") == 0) {
						int var = atoi(line.substr(27).c_str());
						howManyExtraNukeExplosions = var;
					}
					else if (line.find("airStrikeAmmoId:") == 0) {
						int var = atoi(line.substr(16).c_str());
						airStrikeAmmoId = var;
					}
					else if (line.find("airStrikeAmmoCost:") == 0) {
						int var = atoi(line.substr(18).c_str());
						airStrikeAmmoCost = var;
					}
					else if (line.find("blackOilWith:") == 0) {
						int var = atoi(line.substr(13).c_str());
						blackOilWith = var;
					}
					else if (line.find("dinoRidingWith:") == 0) {
						int var = atoi(line.substr(15).c_str());
						dinoRidingWith = var;
					}
					else if (line.find("airStrikeWith:") == 0) {
						int var = atoi(line.substr(14).c_str());
						airStrikeWith = var;
					}
					else if (line.find("airStrikeDelay:") == 0) {
						int var = atoi(line.substr(15).c_str());
						airStrikeDelay = var;
					}

				}
			}
			else if (slowo == "MOTD=") {
				string s = line.substr(line.find("=") + 1);
				char * writable = new char[s.size() + 1];
				strcpy(writable, s.c_str());
				komunikat(writable);
				delete[] writable;
			}
			else if (slowo == "fleshCamera=") {
				float f = stof(line.substr(line.find("=") + 1));
				float* camsize = (float*)0x101424B0;
				if (f == -1)
					*camsize = *((float*)0x101424BC) / 0.6875 * 168.9599915;
				else
					*camsize = f;
			}
			else if (slowo == "adonCamera=") {
				float f = stof(line.substr(line.find("=") + 1));
				float* camsize = (float*)0x10142420;
				if (f == -1)
					*camsize = *((float*)0x1014242C) / 0.5625 * 138.2399902;
				else
					*camsize = f;
			}
			else if (slowo == "turokCamera=") {
				float f = stof(line.substr(line.find("=") + 1));
				float* camsize = (float*)0x101423D8;
				if (f == -1)
					*camsize = *((float*)0x101423E4) / 0.625 * 153.5999908;
				else
					*camsize = f;
			}
			else if (slowo == "purCamera=") {
				float f = stof(line.substr(line.find("=") + 1));
				float* camsize = (float*)0x101424F8;
				if (f == -1)
					*camsize = *((float*)0x10142504) / 0.78125 * 191.9999847;
				else
					*camsize = f;
			}
			else if (slowo == "endCamera=") {
				float f = stof(line.substr(line.find("=") + 1));
				float* camsize = (float*)0x10142540;
				if (f == -1)
					*camsize = *((float*)0x1014254C) / 0.71875 * 176.6399994;
				else
					*camsize = f;
			}
			else if (slowo == "fireCamera=") {
				float f = stof(line.substr(line.find("=") + 1));
				float* camsize = (float*)0x10142588;
				if (f == -1)
					*camsize = *((float*)0x10142594) / 0.625 * 153.5999908;
				else
					*camsize = f;
			}
			else if (slowo == "iggyCamera=") {
				float f = stof(line.substr(line.find("=") + 1));
				float* camsize = (float*)0x101425D0;
				if (f == -1)
					*camsize = *((float*)0x101425DC) / 0.59375 * 145.9199829;
				else
					*camsize = f;
			}
			else if (slowo == "campCamera=") {
				float f = stof(line.substr(line.find("=") + 1));
				float* camsize = (float*)0x10142618;
				if (f == -1)
					*camsize = *((float*)0x10142624) / 0.6875 * 168.9599915;
				else
					*camsize = f;
			}
			else if (slowo == "telCamera=") {
				float f = stof(line.substr(line.find("=") + 1));
				float* camsize = (float*)0x10142660;
				if (f == -1)
					*camsize = *((float*)0x1014266C) / 0.65625 * 161.2799835;
				else
					*camsize = f;
			}
			else if (slowo == "gantCamera=") {
				float f = stof(line.substr(line.find("=") + 1));
				float* camsize = (float*)0x10142468;
				if (f == -1)
					*camsize = *((float*)0x10142474) / 0.5 * 122.8800049;
				else
					*camsize = f;
			}
			else if (slowo == "raptorCamera=") {
				float f = stof(line.substr(line.find("=") + 1));
				float* camsize = (float*)0x10144658;
				if (f == -1)
				*camsize = *((float*)0x10144664) / 0.625 * 92.15999603;
				else
				*camsize = f;
			}
			else if (slowo == "ArenaMaxAmmo=" || slowo == "startingMaxAmmo=") {
				string s = line.substr(line.find("=") + 1);
				if (s == "true" || s == "TRUE" || s == "1")
					startingMaxAmmo = true;
				else
					startingMaxAmmo = false;
			}
			else if (slowo == "AdminPassword=") {
				string s = line.substr(line.find("=") + 1);
				adminPassword = md5(s + " gdfhr3tyswenxld5knoirhwlk6ns");
			}

			if (continueLoop) { //continue loop without getting new line
				continueLoop = false;
				continue;
			}
			if (!std::getline(stream, line)) //get new line
				loop = false;
		}
	}

	floatCfgs.clear();
	intCfgs.clear();
	charactersCfgs.clear();

	while (isTeamGameMode) { //game is loading (joining to server)
		Sleep(16);
		int var = *((int*)0x106D1C84);
		if (var == 1 || var == 2) {
			string s = "T2 kub's mod " + version + " (type /fov 90 to change field of view)";
			char * writable = new char[s.size() + 1];
			strcpy(writable, s.c_str());
			komunikat(writable);
			delete[] writable;

			break;
		}
	}

	if (czy_ServerBot) {
		string bigozz = " \x4/aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
		char * writable2 = new char[bigozz.size() + 1];
		strcpy(writable2, bigozz.c_str());
		WriteToMemory((LPVOID)0x00AD8384, writable2, strlen(writable2) + 1);
		delete[] writable2;

		if (czy_ServerBotRequired) {
			bigozz = "WAITING FOR SERVER BOT";
			char * writable = new char[bigozz.size() + 1];
			strcpy(writable, bigozz.c_str());
			WriteToMemory((LPVOID)0x0051B93C, writable, strlen(writable) + 1);
			delete[] writable;
		}


		Sleep(1200);
		//wysylaniehook = (int(__cdecl*)(char *text))DetourFunction((PBYTE)0x4C3250, (PBYTE)hookedFunction2); //4C3250 4C30E0


		if (myid == -1) sendJoin();

		/*while (true) {
			Sleep(1000);
			cout << "ilenasekunde: " << dec << ilenasekunde << endl;
			ilenasekunde = 0;
		}*/

		while (true) {
			Sleep(48000);
			if (!czy_sprawdzanie_voice && czyJoined) {
				czy_sprawdzanie_voice = true;
				czyHostVoice = false;
				ss.str("");
				ss << " \x4/99" << " gvoice " << myid;
				wyslij(ss.str());
				std::async(std::launch::async, sprawdzVoice);
			}
		}
	}

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
		startowaniehook = (int(__cdecl*)())DetourFunction((PBYTE)0x4C0310, (PBYTE)hookedStartowanie); //(char *text1, char *text2); //int (__cdecl* startowaniehook)(); //int sub_4C0310()
		SpectJoinHook = (int(__cdecl*)(int int1, int int2))DetourFunction((PBYTE)0x485B00, (PBYTE)hookedSpectJoin); //int(__cdecl* SpectJoinHook)(int int1, int int2); //int __cdecl sub_485B00(int, int)
		TeamChangeHook = (int(__cdecl*)(int int1))DetourFunction((PBYTE)0x485EB0, (PBYTE)hookedTeamChange); //int(__cdecl* TeamChangeHook)(int int1); //int __cdecl sub_485EB0(int)
		respawn = (int(__cdecl*)(int int1))DetourFunction((PBYTE)0x425F50, (PBYTE)hookedRespawn); //int(__cdecl* respawn)(int int1); //int __cdecl sub_425F50(int)
		changeChar = (int(__cdecl*)(int int1))DetourFunction((PBYTE)0x486040, (PBYTE)hookedChangeChar); //int(__cdecl* changeChar)(int int1); //int sub_4246B0(void); //int __cdecl sub_4245E0(int); //int __cdecl sub_4195D0(int); int __cdecl sub_486040(int);
		//zmiananickuHook = (int(__cdecl*)())DetourFunction((PBYTE)0x482220, (PBYTE)hookedZmiananicku); //int(__cdecl* zmiananicku)(); //int sub_482220()
		//zmianaKoloru = (int(__cdecl*)(int int1))DetourFunction((PBYTE)0x486100, (PBYTE)hookedZmianaKoloru); //int(__cdecl* zmianaKoloru)(int int1); //int __cdecl sub_486100(int)
		//preZmianaKoloru = (int(__cdecl*)(int int1, int int2))DetourFunction((PBYTE)0x47FE00, (PBYTE)hookedPreZmianaKoloru);//int(__cdecl* preZmianaKoloru)(int int1); //int __cdecl sub_47FE00(int, int)
		wydropienieBroniHook = (int(__cdecl*)(int var1, int var2, float var3))DetourFunction((PBYTE)0x4261F0, (PBYTE)hookedWydropienieBroni);
		podniesienieBroniHook = (int(__cdecl*)(int int1, int int2))DetourFunction((PBYTE)0x480D80, (PBYTE)hookedPodniesienieBroni); //int(__cdecl* podniesienieBroniHook)(int int1, int int2); //int __cdecl sub_480D80(int, int)
		strzal = (int(__cdecl*)(int var1, int var2))DetourFunction((PBYTE)0x419260, (PBYTE)hookedStrzal); //int(__cdecl* zmianaAmmoHook)(float var1, float var2);//int(__cdecl* strzal)(float var1, float var2); //int __cdecl sub_419260(float, float)
		damage = (int(__cdecl*)(int var1, int var2, int *var3, int *var4, int *var5))DetourFunction((PBYTE)0x488000, (PBYTE)hookedDamage); //int(__cdecl* damage)(int var1, int var2, int var3, int var4, int var5); //int __cdecl sub_488000(int, int, int, int, int) damage
		indamage1 = (int(__cdecl*)(int var1, int var2, int var3))DetourFunction((PBYTE)0x419220, (PBYTE)hookedIndamage1); //int(__cdecl* indamage1)(int var1, int var2, int var3); //int __cdecl sub_419220(int, int, int) indamage1
		//sfx = (int(__cdecl*)(__int16 var1))DetourFunction((PBYTE)0x431FD0, (PBYTE)hookedsfx);  //int(__cdecl* realDzwiekczatu)(__int16 var1); //int __cdecl sub_431FD0(__int16) realDzwiekCzatu
		CreateThread(0, 0x1000, &Main_thread, 0, 0, NULL);
		CreateThread(0, 0, &wykonywanie_polecen, 0, 0, NULL);
		CreateThread(0, 0, &custom_weapons, 0, 0, NULL);
	}
	return TRUE;
}
