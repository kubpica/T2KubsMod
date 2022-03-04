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

int myid = -1;
map<int, int> frezeI;
map<int, float> frezeF;
map<int, string> frezeS;
map<int, float> observe;
map<int, float> observef;
map<int, float> customDamages;
map<int, float> customNodes;
map<string, list<pair<int, int>>> customDrop;
map<int, list<pair<int, int>>> customPickup;
map<int, int> customPchance;
map<int, int> extraAmmo;
bool wasJoinSent = false;
map<int, int>::iterator it;
list<string> msgToSend;
list<string> customCommands;
list<string> serverCommands;
vector<string> presetCommands; // Commands set in launcherConfig.txt with "Cmd=..."

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
vector<string> adminWeapons; // Weapons recieved from admin
map<string,vector<string>> customStartingWeapons;
int killstreak = 0;
bool killstreaksEnabled = true;

map<int, string> charMotd;
map<string, string> customMotd;

map<string, string> localConfigPresets; // PresetName - URL
map<string, string> adminConfigPresets;
map<string, string> configPresetsDescriptions;
map<string, string> cachedConfigs;
string onRespawnConfig;
string onFragConfig;
string onDeathConfig;
string onCharacterChangeConfig;
string onWeaponDropConfig;
string onWeaponPickupConfig;
string onWeaponChangeConfig;
string onShotFiredConfig;

vector<string> tids;
std::list<string>::iterator iter;
char * writable;
byte dataz[] = { 0x00, 0x10, 0xFF, 0xFF };
DWORD hackOffsets[] = { 0x3d };
HMODULE hModule = GetModuleHandle(NULL);
DWORD baseAddress = (DWORD)hModule + 0x00778550;
bool hasStarted = false;
bool hideUnkCommandText = false;
bool hasJoined = false;
bool isHostVoice = false;
bool doCheckVoice = false;
bool blockInSpectMode = true;
bool isUnfreezeAll = false;
bool isUnobserveAll = false;
bool isSpectAllowed = true;
bool isSpectateEnabled = true;
bool isSetColorEnabled = false;
bool isPasswordConfirmation = false;
bool isLoggedIn = false;
bool areCustomDropsEnabled = false;
bool isArenaGamemode = false;
bool isServerBotRequired = false;
bool isServerBot = false;
bool isCustomDamageEnabled = false;
bool isCustomDropsConfig = false;
bool isCustomPickupsConfig = false;
bool isCustomPickupsEnabled = false;
bool areCustomWeaponsEnabled = false;
bool isUserBlackOil = true;
bool czyInfoOil = false;
int dchance = 25;
//int pchance = 25;
int commandCounter = 0;
std::string login;
std::string password;
int status = 0; //0-observator 1-waiting4game 2-inGame
bool pfmlayer = false;
bool sunfirepod = false;
bool chargeDart = false;
bool fireRidingGun = false;
bool fireRazor = false;
bool fireExtraNuke = false;
bool fireTranquilizer = false;
bool fireBlackOil = false;
bool fireAirStrike = false;
bool fireFlare = false;
bool fireCrossbow = false;
bool fireRespawnFlare = false;
bool blockPickups = false;
bool blockDrops = false;

bool razor = false;
bool tranquilizer = false;
bool nuke = false;
bool pistol = false;
bool bow = false;
bool tekbow = false;
bool shotgun = false;
bool flare = false;
bool plasma = false;
bool assault = false;
bool crossbow = false;
bool singleRocket = false;
bool betaGrenade = false;
bool betaCharge = false;
bool betaPlasma = false;
bool betaFirestorm = false;
bool betaCbore = false;
bool betaHarpoon = false;
bool betaTorpedo = false;
bool raptorClaws = false;

int indmg1var2 = 0;
int indmg1var3 = 0;
bool bUseWeaponsEverywhere;
bool ridingGunSide = false;
bool isLastAmmo = false;
bool wasInfoZoom = false;
bool wasInfoAmmo = false;
bool wasInfoSunfire = false;
bool wasInfoPfm = false;
bool wasInfoRazor = false;
int wasInfoAirStrike = 0;
int customWeaponId = 0;
int airStrikeWith = 16; //torpedo
int dinoRidingWith = 4; //chargeDart
int blackOilWith = 5; //pistol
int flareToFire = 95;
int cosmeticFlareToFire;
bool isTorpedoDisabledOnGround = false;
int airStrikeDelay = 0;
int airStrikeAmmoId = 18; //torpedo
int customAirStrikeAmmoId = 18; //torpedo
int airStrikeAmmoCost = 6;
int howManyExtraNukeExplosions = 2;
bool czyUserRazors = true;
bool forceSpectOnStart = false;
bool areSettingsDownloaded = false;
bool startingMaxAmmo = false;
bool isTeamGameMode = false;
string nickname;
string tid;
float currentFov = 0;
string cfgurl = "null";
string globalCfgurl = "null";
string adminPassword = "fe13c6045b5e31a4333585715e66636d";
string passedPassword;
float fixedF = 0.004;
float weaponsize = -10.23999977;
float weaponsize2 = 0.1000000015;
string motd = "";
int safeMode = 0;
string cheatsInfection = "";
vector<string> configInfections;
string weaponsInfection = "";
vector<string> cfgCmdInfections;
int flareInfection = -1;
string borrowedPassword = "";
bool isTempAdmin;

float defaultDamage = -1;
float defaultNode = -1;
float customDamage = -1;
float customNode = -1;

float originalDamage;
float originalNode;
int originalFragLimit;
int originalTimeLimit;
int originalPointLimit;

bool disableHostMode = false;
bool reloadModelsNeeded = false;
bool reloadWeaponsNeeded = false;
bool bDisableEnterCheat = false;
bool reloadWeaponsOnFrag = false;
bool allowSfxCommand = true;
int lastSfx;
int muteSfxTaunts;
int muteLector;
bool playLectorOnRemap = false;

vector<int> fragFlares;
vector<int> fragSfx;
int fragEffectsEnabled = 1;
vector<int> deathFlares;
vector<int> deathSfx;
int deathEffectsEnabled = 1;
vector<int> respawnFlares;
vector<int> respawnSfx;
int respawnEffectsEnabled = 1;

vector<int> deathAnims;
map<int, int> replacedAnims;
int logAnims;
bool reversedAnim17Attack;
bool resetToAnim2;
bool playingDead;

int lastTauntSfxReceived = -1;
int lastTauntLectorReceived = -1;

float respawnCooldown = 0;
float respawnCooldownTimer = 0;
int forceSpectOnRespawn = 0;
int forceSpectOnDeath = 0;
bool delayedForceSpect;
string delayedSpectText;

float changeDamageDelayTimer = 0;

int pfmProjectile = 12;
int sunfirepodProjectile = 10;
int assaultProjectile = 305;
int betaGrenadeProjectile = 302;
int betaHarpoonProjectile = 306;
int betaTorpedoProjectile = 0;
int betaPlasmaProjectile = 303;
int betaFirestormProjectile = 0;
int betaCboreProjectile = 459;
int betaChargeProjectile = 4;
int tranquilizerProjectile = 3;
int bowProjectile = 86;
int singleRocketProjectile = 295;
int crossbowProjectile = 298;

double myElo;

bool delayedRespawn;
bool remapOnRespawn;

bool delayedHello;

int superhot;
bool logSuperhot;
int superhotMovement = 1;
int superhotQuake = 1;
float superhotAdjustUpTime = 0.2;
float superhotAdjustDownTime = 0.1;
float superhotInitialSpeed = 1;
float superhotMinMovement = 0.5;
float superhotMaxMovement = 1;
float superhotMidSpeed = 0.01;
float superhotMinSpeed = 0.001;
float superhotMaxSpeed = 1;
float superhotMaxBulletSpeed = 1;
float superhotMidThreshold = 0.5;
float superhotAdjustTime; // current
float superhotTimer;
float superhotSpeed;
float superhotTargetSpeed;
map<int, int> playersState;
int superhotMoving;
int superhotStanding;
int superhotInactive;
float superhotTextTimer;
int superhotTextLvl;

vector<string> chatNews;
float timeBetweenChatNews = 90;
float chatNewsTimer;

float countdownTimer;
int countdownIntTimer;
string countdownCmd = "";

int(__cdecl* print)(const char *text); //Pointer to the function we are going to hook, must be declared same as original
int(__cdecl* sendingHook)(char *text); //int __cdecl sub_4C3250(char *);
int(__cdecl* sendingHook2)(int text1, int text2); //int __cdecl sub_48FC40(int, int)
int(__cdecl* SpectJoinHook)(int int1, int int2); //int __cdecl sub_485B00(int, int)
int(__cdecl* startingHook)(); //int sub_4C0310()
int(__cdecl* DropWeapon)(int var1, int var2, float var3); //int __cdecl sub_4261F0(float, int, float);
int(__cdecl* PickupWeapon)(int int1, int int2); //int __cdecl sub_480D80(int, int)
int(__cdecl* Fire)(int var1, int var2); //int __cdecl sub_419260(float, float)
int(__cdecl* damage)(int var1, int var2, int *var3, int *var4, int *var5); //int __cdecl sub_488000(int, int, int, int, int) damage
int(__cdecl* indamage1)(int var1, int var2, int var3); //int __cdecl sub_419220(int, int, int) indamage1
int(__cdecl* TeamChangeHook)(int int1); //int __cdecl sub_485EB0(int)
int(__cdecl* respawn)(int int1); //int __cdecl sub_425F50(int)
int(__cdecl* changeChar)(int int1);

//hit or miss fps things:
typedef int(__cdecl* int_1int_)(int i1);
typedef int(__cdecl* int_void_)(void);
int_1int_ hitOrMiss1; //= (int_1int_)0x41FD20;	//int __cdecl sub_41FD20(int);
int_1int_ hitOrMiss2; //= (int_1int_)0x461420;	//int __cdecl sub_461420(int);

typedef int(__cdecl* int_3int_)(int i1, int i2, int i3);
int_3int_ remap = (int_3int_)0x468260;

int_3int_ characterAnimation = (int_3int_)0x41FE50;

int_1int_ hitOrMiss3; //int __cdecl sub_45B060(int);
int_1int_ hit; //int __cdecl sub_45C9E0(int);
int_1int_ miss; //int __cdecl sub_45D140(int);
int_1int_ hitOrMiss4; //int __cdecl sub_45B350(int);

int_1int_ reloadCharacters = (int_1int_)0x484D30;

typedef void(__cdecl* fcstr_)(char *text);
//fcstr_ sending = (fcstr_)0x4C3250; //0x4A4C30 

typedef void(__cdecl* f1int_)(int int1);
f1int_ colorChange = (f1int_)0x486100;

typedef void(__cdecl* f2ints_)(int int1, int int2);
f2ints_ precolorChange = (f2ints_)0x47FE00;

//typedef void(__cdecl* SpectJoin_)(int int1, int int2);
f2ints_ SpectJoin = (f2ints_)0x485B00;

typedef void(__cdecl* f2ints1float_)(int var1, int var2, float var3);
f2ints1float_ dropWeapon = (f2ints1float_)0x4261F0;

typedef int(__cdecl* sfx_)(__int16 var1);
sfx_ sfx = (sfx_)0x431FD0;

typedef void(__cdecl* f1float_)(float float1);
typedef void(__cdecl* f2floats_)(float float1, float float2);
typedef void(__cdecl* fnoarg_)();

typedef int(__cdecl* int_2int_)(int i1, int i2);
int_2int_ levelEnd = (int_2int_)0x4858E0;

//int_2int_ incPlayerCount = (int_2int_)0x434AC0;
int_2int_ decPlayerCount = (int_2int_)0x434BE0;

int_1int_ lector = (int_1int_)0x4C82B0;

typedef int(__cdecl* int_)();
//int_ reloadMap = (int_)0x485290;
int_ changeNickname = (int_)0x482220;

/// <summary>
/// Calculates Elo rating change for "player X".
/// </summary>
/// <param name="playerRating"> Rating of player X.</param>
/// <param name="opponentRating"> Rating of his opponent.</param>
/// <param name="result"> 0 if lost; 0.5 if draw; 1 if won.</param>
/// <returns> The value by which the player's rating should be changed.</returns>
double calcEloChange(double playerRating, double opponentRating, double result)
{
	static int K = 24;

	double d = opponentRating - playerRating;
	if (d > 400) d = 400;
	else if (d < -400) d = -400;
	double we = 1 / (1 + pow(10, d / 400.0));
	double diff = result - we;
	return K * diff;
}

/// <summary>
/// Updates rating
/// </summary>
/// <param name="ratingX"> Rating of X</param>
/// <param name="ratingY"> Rating of Y</param>
/// <param name="didXWin"> 1 if X won; 0.5 if draw; 0 if Y won</param>
void updateRating(double ratingX, double ratingY, double didXWin)
{
	double change = calcEloChange(ratingX, ratingY, didXWin);
	ratingX += change;
	ratingY += change * -1;
}

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

void printString(string s) {
	char* writable = new char[s.size() + 1];
	strcpy(writable, s.c_str());
	print(writable);
	delete[] writable;
}

string getWeaponName(int weaponId) {
	// These are the weapon ids in the server config,
	// they are different from WeaponSlotId and AmmoId
	weaponId = abs(weaponId);
	switch (weaponId)
	{
	case 0:
	case 99:
		return "War Blade";
	case 1:
		return "Tek Bow";
	case 2:
		return "Pistol";
	case 3:
		return "Mag 60";
	case 4:
		return "Charge Dart Rifle";
	case 5:
		return "Shotgun";
	case 6:
		return "Shredder";
	case 7:
		return "Plasma Rifle";
	case 8:
		return "Firestorm Cannon";
	case 9:
		return "Cerebral Bore";
	case 10:
		return "Grenade Launcher";
	case 11:
		return "Scorpion Launcher";
	case 12:
		return "Flame Thrower";
	case 13:
		return "Nuke";
	case 14:
		return "Tranqulizer Gun";
	case 15:
		return "Sunfire Pod";
	case 16:
		return "PFM Layer";
	case 17:
		return "Harpoon Gun";
	case 18:
		return "Torpedo Launcher";
	case 19:
		return "Razor Wind";
	case 20:
		return "Single Rocket (Beta Scorpion)";
	case 21:
		return "Normal Bow";
	case 22:
		return "Assault Rifle";
	case 23:
		return "Crossbow";
	case 24:
		return "Flare";
	case 25:
		return "Charge Storm (Beta Charge)";
	case 26:
		return "Beta Plasma";
	case 27:
		return "Dino Riding Gun (Beta Firestorm)";
	case 28:
		return "Rockets From SP (Beta Cbore)";
	case 29:
		return "Beta Grenade";
	case 30:
		return "Beta Harpoon";
	case 31:
		return "Air Strike (Beta Torpedo)";
	case 32:
		return "Raptor Claws (Talon)";
	case 666:
		return "\"set 666\" effect";
	case 774:
		return "every beta custom weapon";
	case 775:
		return "every unique custom weapon";
	case 776:
		return "every standard weapon";
	case 777:
		return "all weapons";
	case 1337:
		return "sound effect";
	}
	stringstream ss("");
	ss << "?Unknown/Non-existing? Weapon" << weaponId;
	return ss.str();
}

string getSetWeaponNews(int weaponId, short ammo, string who, int asStartWeapon)
{
	stringstream news("");
	if (weaponId == -100) {
		news << " set " << getWeaponName(ammo);
		news << " as the only";
		if (asStartWeapon)
			news << " starting";
		news << " weapon for " << who << ".";
		return news.str();
	}
	else if (weaponId == 999) {
		news << " reset starting weapons to default server settings for " << who << ".";
		return news.str();
	}

	string what;
	if (weaponId < 0)
		what = " took away from ";
	else
		what = " gave ";
	news << what << who << " " << getWeaponName(weaponId);
	if (asStartWeapon)
		news << " as start weapon";
	if (weaponId != 666) 
	{
		if (weaponId < 0) {
			if (ammo >= 0)
				news << " and set its ammo to " << ammo;
		}
		else {
			news << " with ";
			if (ammo >= 0)
				news << ammo;
			else
				news << "default amount of";
			news << " ammo";
		}
	}
	news << ".";
	return news.str();
}

enum WeaponSlotId
{
	talonSlot = 0,
	warbladeSlot = 1, // 0 and 99 in startingWeapons config
	normalBowSlot = 2, // 21 in config
	tekbowSlot = 3, // 1 in config
	pistolSlot = 4, // 2 in config
	magnumSlot = 5, // 3 in config
	tranquilizerSlot = 6, // 14 in config
	chargeDartSlot = 7, // 4
	shotgunSlot = 8, // 5
	shredderSlot = 9, // 6
	plasmaSlot = 10, // 7
	firestormSlot = 11, // 8
	sunfirepodSlot = 12, // 15
	cboreSlot = 13, // 9
	pfmSlot = 14,  // 16
	grenadeSlot = 15, // 10
	scorpionSlot = 16,  // 11
	harpoonSlot = 17, // 17
	torpedoSlot = 18, // 18
	dinoRidingSlot = 19,
	flameSlot = 20, // 12
	razorSlot = 21, // 19
	nukeSlot = 22, // 13
	flareSlot = 23, // 24
	crossbowSlot = 24, // 23
	betaChargeSlot = 25, // 25
	assaultSlot = 26, // 22,
	betaPlasmaSlot = 27, // 26
	betaFirestormSlot = 28, // 27
	betaCboreSlot = 29, // 28
	betaGrenadeSlot = 30, // 29
	singleRocketSlot = 31, // 20
	betaHarpoonSlot = 32, // 30
	betaTorpedoSlot = 33, // 31 
	raptorClawsSlot = 34 // 32
};

enum AmmoId
{
	normalBowAmmo = 2,
	tekbowAmmo = 3,
	pistolAmmo = 4,
	magnumAmmo = 5,
	tranquilizerAmmo = 6,
	chargeDartAmmo = 7,
	greenShotgunAmmo = 8,
	redShotgunAmmo = 9,
	plasmaAmmo = 10,
	firestormAmmo = 11,
	sunfirepodAmmo = 12,
	cboreAmmo = 13,
	pfmAmmo = 14,
	grenadeAmmo = 15,
	scorpionAmmo = 16,
	harpoonAmmo = 17,
	torpedoAmmo = 18,
	flameAmmo = 19,
	singleRocketAmmo = 20,
	nukeAmmo = 21,
	assaultAmmo = 22,
	crossbowAmmo = 23, // crossbow ammo actually doesn't exist - it's included here only for customPickups feature
	flareAmmo = 24,
	betaChargeAmmo = 25,
	betaPlasmaAmmo = 26,
	betaFirestormAmmo = 27,
	betaCboreAmmo = 28,
	betaGrenadeAmmo = 29,
	betaHarpoonAmmo = 30, // actually doesn't exist - it's included here only for customPickups feature
	betaTorpedoAmmo = 31,
	raptorClawsAmmo = 32 // actually doesn't exist - it's included here only for customPickups feature
};

short* getAmmo(AmmoId ammoId) {
	switch (ammoId)
	{
	case normalBowAmmo:
		return (short*)0x106D1B84; //normal arrows
	case tekbowAmmo:
		return (short*)0x106D1B86; //explosive arrows
	case pistolAmmo:
		return (short*)0x106D1B88;
	case magnumAmmo:
		return (short*)0x106D1B88;
	case tranquilizerAmmo:
		return (short*)0x106D1B8C;
	case chargeDartAmmo:
		return (short*)0x106D1B8E;
	case greenShotgunAmmo:
		return (short*)0x106D1B90; //green
	case redShotgunAmmo:
		return (short*)0x106D1B92; //red
	case plasmaAmmo:
		return (short*)0x106D1B96;
	case firestormAmmo:
		return (short*)0x106D1B96;
	case sunfirepodAmmo:
		return (short*)0x106D1B98;
	case cboreAmmo:
		return (short*)0x106D1B9A;
	case pfmAmmo:
		return (short*)0x106D1B9C;
	case grenadeAmmo:
		return (short*)0x106D1B9E;
	case scorpionAmmo:
		return (short*)0x106D1BA0;
	case harpoonAmmo:
		return (short*)0x106D1BA2;
	case torpedoAmmo:
		return (short*)0x106D1BA4;
	case flameAmmo:
		return (short*)0x106D1BAC;
	case nukeAmmo:
		return (short*)0x106D1BB0;
	case assaultAmmo:
		return (short*)0x106D1BB6;
	case flareAmmo:
		return (short*)0x106D1BB2;
	case betaChargeAmmo:
		return (short*)0x106D1BB4;
	case betaPlasmaAmmo:
		return (short*)0x106D1BB8;
	case betaFirestormAmmo:
		return (short*)0x106D1BB8;
	case betaCboreAmmo:
		return (short*)0x106D1BBA;
	case betaGrenadeAmmo:
		return (short*)0x106D1BBC;
	case singleRocketAmmo:
		return (short*)0x106D1BBE;
	case betaTorpedoAmmo:
		return (short*)0x106D1BC0;
	default:
		break;
	}
}

void addAmmo(AmmoId ammoId, int ammo) {
	*(getAmmo(ammoId)) += ammo;
}

byte* getWeaponSlot(WeaponSlotId weaponSlotId) {
	switch (weaponSlotId)
	{
	case talonSlot:
	case raptorClawsSlot:
		return (byte*)0x106D1BC2;
	case warbladeSlot: // -99 = remove warblade
		return (byte*)0x106D1BC3;
	case normalBowSlot:
		return (byte*)0x106D1BC4;
	case tekbowSlot:
		return (byte*)0x106D1BC5;
	case pistolSlot:
		return (byte*)0x106D1BC6;
	case magnumSlot:
		return (byte*)0x106D1BC7;
	case chargeDartSlot:
		return (byte*)0x106D1BC9;
	case shotgunSlot:
		return (byte*)0x106D1BCA;
	case shredderSlot:
		return (byte*)0x106D1BCB;
	case plasmaSlot:
		return (byte*)0x106D1BCC;
	case firestormSlot:
		return (byte*)0x106D1BCD;
	case cboreSlot:
		return (byte*)0x106D1BCF;
	case grenadeSlot:
		return (byte*)0x106D1BD1;
	case scorpionSlot:
		return (byte*)0x106D1BD2;
	case flameSlot:
		return (byte*)0x106D1BD6;
	case nukeSlot:
		return (byte*)0x106D1BD8;
	case tranquilizerSlot:
		return (byte*)0x106D1BC8;
	case sunfirepodSlot:
		return (byte*)0x106D1BCE;
	case pfmSlot:
		return (byte*)0x106D1BD0;
	case harpoonSlot:
		return (byte*)0x106D1BD3;
	case torpedoSlot:
		return (byte*)0x106D1BD4;
	case razorSlot:
		return (byte*)0x106D1BD7;
	case singleRocketSlot:
		return (byte*)0x106D1BE1;
	case assaultSlot:
		return (byte*)0x106D1BDC;
	case crossbowSlot:
		return (byte*)0x106D1BDA;
	case flareSlot:
		return (byte*)0x106D1BD9;
	case betaChargeSlot:
		return (byte*)0x106D1BDB;
	case betaPlasmaSlot:
		return (byte*)0x106D1BDD;
	case betaFirestormSlot:
		return (byte*)0x106D1BDE;
	case betaCboreSlot:
		return (byte*)0x106D1BDF;
	case betaGrenadeSlot:
		return (byte*)0x106D1BE0;
	case betaHarpoonSlot:
		return (byte*)0x106D1BE2;
	case betaTorpedoSlot:
		return (byte*)0x106D1BE3;
	case dinoRidingSlot:
		return (byte*)0x106D1BD5;
	}
}

bool isEquiped(WeaponSlotId weaponSlotId) {
	return *(getWeaponSlot(weaponSlotId)) == 1;
}

bool isWaterWeapon(WeaponSlotId w) {
	if (w == torpedoSlot
		|| w == harpoonAmmo)
		return true;
	return false;
}

void equipWeapon(WeaponSlotId weaponSlotId, byte equip) {
	if (equip == 255)
		return;

	if (weaponSlotId == raptorClawsSlot)
		weaponSlotId = talonSlot;

	*(getWeaponSlot(weaponSlotId)) = equip;

	//cout << "equip " << (equip ? "1" : "0") << " customWeaponId " << customWeaponId << " weaponSlotId " << weaponSlotId << endl;
	// If removed from eq currently held weapon - change it.
	if (equip == 0 && customWeaponId == weaponSlotId) {
		short heldWeapon = *(short*)0x106D1D8C;
		for (int i = 1; i <= 33; i++) {
			short w = heldWeapon+i;
			//cout << "w: " << w << endl;
			w %= 34;
			if (isEquiped((WeaponSlotId)w) && (bUseWeaponsEverywhere || !isWaterWeapon((WeaponSlotId)w))) {
				//cout << "Changing to: " << w << endl;
				customWeaponId = w;
				*(short*)0x106D1D8C = w;
				return;
			}
		}
		// If the code reach here that means the eq is empty so let's add flare to prevent crash
		equipWeapon(flareSlot, 1);
		*getAmmo(flareAmmo) = 1;
		print("\x2 Your eq is empty!");
		customWeaponId = 23;
		*(short*)0x106D1D8C = 23;
	}
}

void setEffect(int effect, vector<int>& collection) {
	if (effect > 0) {
		// Add
		collection.push_back(effect);
	}
	else if (effect == 0) {
		// Remove all
		collection.clear();
	}
	else {
		// Remove
		effect *= -1;
		for (int i = collection.size() - 1; i >= 0; i--) {
			if (collection[i] == effect) {
				collection.erase(collection.begin() + i);
			}
		}
	}
}

void removeElementsStartingWith(string toRemove, vector<string>& collection) {
	for (int i = collection.size() - 1; i >= 0; i--) {
		if (collection[i].find(toRemove) == 0) {
			collection.erase(collection.begin() + i);
		}
	}
}

bool vectorContains(vector<string>& v, string s) {
	if (std::find(v.begin(), v.end(), s) != v.end()) {
		return true;
	}
	else {
		return false;
	}
}

void sendCmdToBot(string msg)
{
	if (msg.find(" \x4/") == 0 && msg.find("voice") == std::string::npos && msg.find("gvoice") == std::string::npos) //czy znaleziono komende
	{
		string msgHash = md5(msg + " salt");
		msgHash = " h;" + msgHash;
		msg += msgHash;
	}
	if (isServerBot) msgToSend.push_back(msg);
}

void sendCmdWithPassword(string msg, string pw = "")
{
	if (pw.empty())
		pw = passedPassword;

	if (msg.find(" \x4/") == 0)
	{
		if (msg.find("hello") != string::npos) {
			msgToSend.push_back(msg);
			return;
		}

		if (msg.find("tid:") == 3) {
			int i = stoi(msg.substr(7));
			std::stringstream ss;
			if (i == -1) {
				ss.str("");
				ss << " \x4/00" << msg.substr(msg.find("; ")+1);
				msg = ss.str();
			}
			else if (i < tids.size()) {
				ss.str("");
				ss << " \x4/" << tids[i] << msg.substr(msg.find("; "));
				msg = ss.str();
			}
			else {
				ss.str("");
				ss << "\x4 TID with shortcut id " << i << " not found.";
				printString(ss.str());
			}
		}

		string cleanPw = pw;
		for (int i = 0; i < pw.length(); i++)
			pw[i]++;

		msg += " p;" + pw;
		string hash = md5(msg + cleanPw + adminPassword);
		//cout << "beforeHash: " << msg + cleanPw + adminPassword << endl;
		msg += " h;" + hash;
		//cout << "cleanPw: " << cleanPw << endl;
		//cout << "pw: " << pw << endl;
		//cout << "hash: " << hash << endl;

		msgToSend.push_back(msg);
	}
	else {
		cout << "Wrong command syntax" << endl;
	}
}

void playLector(int i, bool sendToOthers, int verbose = 1, bool playForSelf = true) {
	if (muteLector) {
		if (verbose && sendToOthers) {
			print("\x4 You cannot send the voiceover line because you have muted it.");
			print("\x3 Type \"mute lector 0\" to unmute.");
		}
		return;
	}

	int ret = 1;
	if(playForSelf)
		ret = lector(i);

	stringstream ss;
	if (ret > 0) {
		if (sendToOthers) {
			ss.str("");
			ss << " \x4/00 tauntlector " << i << " " << verbose;
			sendCmdWithPassword(ss.str());

			if (verbose == 1) {
				ss.str("");
				ss << "\x4 You played lector " << i << " for everyone on the server (with kub's mod).";
				printString(ss.str());
				printString("\x3 Use the \"tlector\" command to play only for yourself.");
			}
		}
		else if (verbose) {
			ss.str("");
			ss << "\x4 You played lector " << i << " only for yourself.";
			printString(ss.str());
		}
	}
	else if (verbose) {
		ss.str();
		ss << "\x4 lector " << i << " not found :(" << endl;
		printString(ss.str());
	}
}

void playLector(int i) {
	playLector(i, false, 0);
}

void playSfx(int i, int search, bool sendToOthers, int verbose = 1) {
	int ret = sfx(i);
	if (search != 0) {
		while (ret < 0) {
			i = search > 0 ? i + 1 : i - 1;
			ret = sfx(i);
			if (i > 32767 || i < 0)
				break;
		}
	}
	if (verbose)
		lastSfx = i;

	stringstream ss;
	if (ret > 0) {
		if (sendToOthers) {
			ss.str("");
			ss << " \x4/00 tauntsfx " << i << " " << verbose;
			sendCmdWithPassword(ss.str());

			if (verbose == 1) {
				ss.str("");
				ss << "\x4 You played sfx " << i << " for everyone on the server (with kub's mod).";
				printString(ss.str());
				printString("\x3 Use the \"tsfx\" command to play only for yourself. Type \"next sfx\" to play the next one.");
			}
			else if (verbose == 2) {
				ss.str("");
				ss << "\x2 " << nickname << " respawned! (sfx " << i << ")";
				printString(ss.str());
			}
		}
		else if (verbose) {
			ss.str("");
			ss << "\x4 You played sfx " << i << " only for yourself.";
			printString(ss.str());
		}
	}
	else if (verbose && i > 32767 || i < 0) {
		ss.str();
		ss << "\x4 sfx " << i << " not found - no more sound effects :(" << endl;
		printString(ss.str());
	}
	else if (verbose) {
		ss.str();
		ss << "\x4 sfx " << i << " not found :(" << endl;
		printString(ss.str());
	}
}

void nextSfx(bool sendToOthers) {
	playSfx(lastSfx + 1, 1, sendToOthers);
}

void prevSfx(bool sendToOthers) {
	playSfx(lastSfx + 1, -1, sendToOthers);
}

void replaySfx(bool sendToOthers) {
	playSfx(lastSfx, 0, sendToOthers);
}

template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
	std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
	std::advance(start, dis(g));
	return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	return select_randomly(start, end, gen);
}

void animateCharacter(int animId) {
	characterAnimation(275583568, 275583568, animId);
}

void execRandomAnim(vector<int>& collection) {
	if (collection.size() > 0) {
		int i = *select_randomly(collection.begin(), collection.end());
		animateCharacter(i);
	}
}

void fireRandomFlare(vector<int>& collection, bool delayed = false) {
	if (collection.size() > 0) {
		int i = *select_randomly(collection.begin(), collection.end());
		cosmeticFlareToFire = i;
		if (delayed) {
			fireRespawnFlare = true;
		}
		else {
			Fire(0x106d1250, i);
		}
	}
}

void playRandomSfx(vector<int>& collection, int verbose = 0) {
	if (collection.size() > 0) {
		int i = *select_randomly(collection.begin(), collection.end());
		playSfx(i, 1, true, verbose);
	}
}

void playRandomLector(vector<int>& collection, bool sendToOthers, int verbose = 0, bool playForSelf = true) {
	if (collection.size() > 0) {
		int i = *select_randomly(collection.begin(), collection.end());
		playLector(i, sendToOthers, verbose, playForSelf);
	}
}

void playNumberLector(int number, bool sendToOthers = true) {
	switch (number)
	{
	case 1:
		playLector(12, sendToOthers, 0);
		break;
	case 2:
		playLector(13, sendToOthers, 0);
		break;
	case 3:
		playLector(14, sendToOthers, 0);
		break;
	case 4:
		playLector(15, sendToOthers, 0);
		break;
	case 5:
		playLector(16, sendToOthers, 0);
		break;
	case 6:
		playLector(17, sendToOthers, 0);
		break;
	case 7:
		playLector(18, sendToOthers, 0);
		break;
	case 8:
		playLector(19, sendToOthers, 0);
		break;
	case 9:
		playLector(20, sendToOthers, 0);
		break;
	case 10:
		playLector(21, sendToOthers, 0);
		break;
	}
}

void playBlueWinLector() {
	vector<int> v = { 62, 63, 64, 65, 66, 68, 69, 70 };
	playRandomLector(v, true);
}

void playRedWinLector() {
	vector<int> v = { 71, 72, 73, 74, 75, 77, 78, 79 };
	playRandomLector(v, true);
}

void playScoreFlagLector() {
	vector<int> v = { 80, 81 };
	playRandomLector(v, true);
}

void playNewPlayerLector(bool playForSelf) {
	vector<int> v = { 0, 1, 2, 3, 4, 5 };
	playRandomLector(v, true, 0, playForSelf);
}

void playWelcomeLector() {
	vector<int> v = { 6, 7, 8, 9, 10 };
	playRandomLector(v, false);
}

void playStartLector() {
	vector<int> v = { 26, 27, 28, 29, 30, 31, 32, 33, 35 };
	playRandomLector(v, false);
}

void playDrawLector() {
	vector<int> v = { 34, 45 };
	playRandomLector(v, true);
}

bool randomBool() {
	return rand() > (RAND_MAX / 2);
}

void playAceLector() {
	vector<int> v = { 11, 25, 36, 37, 38, 39, 40, 41, 42, 43, 44, 46, 47 };
	if (randomBool)
		v.push_back(48);
	else
		v.push_back(49);
	playRandomLector(v, true);
}

void playChooseTeamLector() {
	vector<int> v = { 50, 51 };
	playRandomLector(v, false);
}

void respawnProtection(bool activate) {
	if (activate) {
		WriteToMemory((void*)0x00419974, "\xC7\x86\x50\x0A\x00\x00\x00\x00\x70\x42", 10);
	}
	else {
		WriteToMemory((void*)0x00419974, "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90", 10);
	}
}

void useWeaponsEverywhere(bool activate) {
	if (activate) {
		bUseWeaponsEverywhere = true;
		WriteToMemory((void*)0x0041D0C6, "\xEB", 1);
	}
	else {
		bUseWeaponsEverywhere = false;
		WriteToMemory((void*)0x0041D0C6, "\x75", 1);
	}
}

void flamesInWater(bool activate) {
	if (activate)
		WriteToMemory((void*)0x0041D0B6, "\xEB", 1);
	else
		WriteToMemory((void*)0x0041D0B6, "\x74", 1);
}

void startingChar(bool);

int setWeapon(int weaponId, short ammo = -1, int asStartWeapon = 0) {
	if (asStartWeapon)
	{
		if (weaponId == 999) {
			adminWeapons.clear();
			setWeapon(-100, 2);
			startingChar(true);
			return -1;
		}
		stringstream ss("");
		
		if (weaponId == -100 || abs(weaponId) == 777)
			adminWeapons.clear();
		else {
			ss.str("");
			ss << abs(weaponId);
			removeElementsStartingWith(ss.str(), adminWeapons);
		}
		ss.str("");
		ss << weaponId << ";" << ammo;
		adminWeapons.push_back(ss.str());
	}

	// Negative value will remove weapon from eq
	byte equip = 1;
	if (weaponId < 0) {
		weaponId *= -1;
		equip = 0;
	}

	if (weaponId > 100 && weaponId < 200)
	{
		weaponId -= 100;
		equip = 255;
	}

	short* a;
	// These are the weapon ids in the server config,
	// they are different from WeaponSlotId and AmmoId
	switch (weaponId)
	{
	case 0:
	case 99: //remove warblade
		equipWeapon(warbladeSlot, equip);
		break;
	case 1: // Tek Bow
		equipWeapon(tekbowSlot, equip);
		if (ammo >= 0) {
			*getAmmo(normalBowAmmo) = ammo;
			*getAmmo(tekbowAmmo) = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo) {
				*getAmmo(normalBowAmmo) = 50;
				*getAmmo(tekbowAmmo) = 50;
			}
			else {
				*getAmmo(normalBowAmmo) = 10;
				*getAmmo(tekbowAmmo) = 10;
			}
		}
		return tekbowAmmo;
		break;
	case 2: // Pistol
		equipWeapon(pistolSlot, equip);
		a = getAmmo(pistolAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo)
				*a = 300;
			else
				*a = 50;
		}
		return pistolAmmo;
		break;
	case 3:
		equipWeapon(magnumSlot, equip);
		a = getAmmo(magnumAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo)
				*a = 300;
			else
				*a = 50;
		}
		return magnumAmmo;
		break;
	case 4:
		equipWeapon(chargeDartSlot, equip);
		a = getAmmo(chargeDartAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo)
				*a = 50;
			else
				*a = 15;
		}
		return chargeDartAmmo;
		break;
	case 5: //shotgun
		equipWeapon(shotgunSlot, equip);
		a = getAmmo(greenShotgunAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo)
				*a = 100;
			else
				*a = 20;
		}
		return greenShotgunAmmo;
		break;
	case 6:
		equipWeapon(shredderSlot, equip);
		a = getAmmo(redShotgunAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo)
				*a = 50;
			else
				*a = 15;
		}
		return redShotgunAmmo;
		break;
	case 7:
		equipWeapon(plasmaSlot, equip);
		a = getAmmo(plasmaAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo)
				*a = 300;
			else
				*a = 100;
		}
		return plasmaAmmo;
		break;
	case 8:
		equipWeapon(firestormSlot, equip);
		a = getAmmo(firestormAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo)
				*a = 300;
			else
				*a = 100;
		}
		return firestormAmmo;
		break;
	case 9:
		equipWeapon(cboreSlot, equip);
		a = getAmmo(cboreAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo)
				*a = 25;
			else
				*a = 5;
		}
		return cboreAmmo;
		break;
	case 10:
		equipWeapon(grenadeSlot, equip);
		a = getAmmo(grenadeAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo)
				*a = 100;
			else
				*a = 14;
		}
		return grenadeAmmo;
		break;
	case 11:
		equipWeapon(scorpionSlot, equip);
		a = getAmmo(scorpionAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo)
				*a = 50;
			else
				*a = 5;
		}
		return scorpionAmmo;
		break;
	case 12:
		equipWeapon(flameSlot, equip);
		a = getAmmo(flameAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo)
				*a = 300;
			else
				*a = 100;
		}
		return flameAmmo;
		break;
	case 13:
		equipWeapon(nukeSlot, equip);
		a = getAmmo(nukeAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo)
				*a = 10;
			else
				*a = 2;
		}
		return nukeAmmo;
		break;
	case 14: //tranquilizer
		equipWeapon(tranquilizerSlot, equip);
		a = getAmmo(tranquilizerAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo)
				*a = 50;
			else
				*a = 15;
		}
		return tranquilizerAmmo;
		break;
	case 15: //sunfirepod
		equipWeapon(sunfirepodSlot, equip);
		a = getAmmo(sunfirepodAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo)
				*a = 300;
			else
				*a = 50;
		}
		return sunfirepodAmmo;
		break;
	case 16: //pfm
		equipWeapon(pfmSlot, equip);
		a = getAmmo(pfmAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo)
				*a = 50;
			else
				*a = 15;
		}
		return pfmAmmo;
		break;
	case 17: //harpoon
		equipWeapon(harpoonSlot, equip);
		a = getAmmo(harpoonAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo)
				*a = 50;
			else
				*a = 12;
		}
		return harpoonAmmo;
		break;
	case 18: //torpedo
		equipWeapon(torpedoSlot, equip);
		a = getAmmo(torpedoAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo)
				*a = 100;
			else
				*a = 30;
		}
		return torpedoAmmo;
		break;
	case 19: //razor
		equipWeapon(razorSlot, equip);
		break;
	case 20: //singlerocket
		equipWeapon(singleRocketSlot, equip);
		a = getAmmo(singleRocketAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo)
				*a = 50;
			else
				*a = 5;
		}
		return singleRocketAmmo;
		break;
	case 21: //normal bow
		equipWeapon(normalBowSlot, equip);
		a = getAmmo(normalBowAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo) {
				*a = 50;
			}
			else {
				*a = 10;
			}
		}
		return normalBowAmmo;
		break;
	case 22: //assault
		equipWeapon(assaultSlot, equip);
		a = getAmmo(assaultAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo)
				*a = 300;
			else
				*a = 100;
		}
		return assaultAmmo;
		break;
	case 23: //crossbow
		equipWeapon(crossbowSlot, equip);
		a = getAmmo(tekbowAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo) {
				*a = 50;
			}
			else {
				*a = 10;
			}
		}
		return tekbowAmmo;
		break;
	case 24: //flare
		equipWeapon(flareSlot, equip);
		*getAmmo(flareAmmo) = 1;
		if (ammo > 0) {
			flareToFire = ammo;
		}
		else if (ammo == 0) {
			*getAmmo(flareAmmo) = 0;
		}
		break;
	case 25: //betaCharge
		equipWeapon(betaChargeSlot, equip);
		a = getAmmo(betaChargeAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo)
				*a = 50;
			else
				*a = 15;
		}
		return betaChargeAmmo;
		break;
	case 26: //betaPlasma
		equipWeapon(betaPlasmaSlot, equip);
		a = getAmmo(betaPlasmaAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo)
				*a = 300;
			else
				*a = 100;
		}
		return betaPlasmaAmmo;
		break;
	case 27: //betaFirestorm
		equipWeapon(betaFirestormSlot, equip);
		a = getAmmo(betaFirestormAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo)
				*a = 300;
			else
				*a = 100;
		}
		return betaFirestormAmmo;
		break;
	case 28: //betaCbore
		equipWeapon(betaCboreSlot, equip);
		a = getAmmo(betaCboreAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo)
				*a = 150;
			else
				*a = 15;
		}
		return betaCboreAmmo;
		break;
	case 29: //betaGrenade
		equipWeapon(betaGrenadeSlot, equip);
		a = getAmmo(betaGrenadeAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo)
				*a = 100;
			else
				*a = 15;
		}
		return betaGrenadeAmmo;
		break;
	case 30: //betaHarpoon
		equipWeapon(betaHarpoonSlot, equip);
		break;
	case 31: //airStrike (betaTorpedo)
		useWeaponsEverywhere(true);
		equipWeapon(betaTorpedoSlot, equip);
		a = getAmmo(betaTorpedoAmmo);
		if (ammo >= 0) {
			*a = ammo;
		}
		else if (equip) {
			if (startingMaxAmmo)
				*a = 100;
			else
				*a = 30;
		}
		return betaTorpedoAmmo;
		break;
	case 32: //raptorClaws
		equipWeapon(raptorClawsSlot, equip);
		break;
	case 100:
		if (equip) {
			//non-explosive arrows
			a = getAmmo(normalBowAmmo);
			if (ammo >= 0) {
				*a = ammo;
			}
			else if (startingMaxAmmo) {
				*a = 50;
			}
			else {
				*a = 10;
			}
		}
		else {
			// remove each weapon (but not warblade) unless its id is the same as the ammo value
			for (int i = 1; i <= 32; i++) {
				setWeapon(i == ammo ? i : i * -1);
			}
		}
		break;
	case 666: //it's not weapon but I added it here so you can set the '666' effect like weapons
		WriteToMemory((LPVOID)0x00AD02EC, &equip, 1);
		break;
	case 774: //every custom weapon without unique icon (beta weapons)
		for (int i = 25; i <= 31; i++) {
			setWeapon(equip ? i : i * -1, ammo);
		}
		break;
	case 775: //every custom weapon with unique icon
		for (int i = 14; i <= 24; i++) {
			if (i == 17 || i == 18) // Skip harpoon & torpedo
				continue;
			setWeapon(equip ? i : i * -1, ammo);
		}
		break;
	case 776: //every standard weapon (without custom ones)
		for (int i = 1; i <= 13; i++) {
			setWeapon(equip ? i : i * -1, ammo);
		}
		setWeapon(equip ? 17 : -17, ammo);
		setWeapon(equip ? 18 : -18, ammo);
		break;
	case 777: //all weapons (including custom ones)
		for (int i = 1; i <= 32; i++) {
			setWeapon(equip ? i : i * -1, ammo);
		}
		break;
	case 1337: //it's not weapon but this way you can play sfx on respawn/frag/killstreak
		playSfx(ammo, 0, equip, 0);
		break;
	case 2337: //not weapon - play lector
		playLector(ammo, equip, 0);
		break;
	}

	return -1;
}

void setStartingWeapons(vector<string>* v) {
	for (auto const& value : *v) {
		int ammoId = -1;
		int i;
		short ammo = -1;
		if (value.find(";") != std::string::npos) {
			i = stoi(value.substr(0, value.find(";")));
			ammo = stoi(value.substr(value.find(";") + 1));
		}
		else i = stoi(value);

		ammoId = setWeapon(i, ammo);

		if (!startingMaxAmmo && ammo < 0 && extraAmmo.find(ammoId) != extraAmmo.end()) {
			addAmmo((AmmoId)ammoId, extraAmmo[ammoId]);
		}
		if (ammoId == tekbowAmmo && areCustomWeaponsEnabled) addAmmo(normalBowAmmo, 30);
	}
}

void setCustomStartingWeapons(string key) {
	if (customStartingWeapons.count(key)) {
		setStartingWeapons(&customStartingWeapons[key]);
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
		v = &startingWeapons;
		break;
	default:
		stringstream ss("");
		ss << character;
		setCustomStartingWeapons(ss.str());
		return;
	}
	setStartingWeapons(v);
}

void printCustomMotd(string key) {
	if (customMotd.count(key)) {
		string s = customMotd[key];
		printString(s);
	}
}

void loadFragWeapons()
{
	short* frags = (short*)0x00AD0470;
	stringstream ss("");
	ss << "frags" << *frags;
	string fragsKey = ss.str();
	setCustomStartingWeapons(fragsKey);
	printCustomMotd(fragsKey);
}

void startingChar(bool onlyFragMotd = false) {
	// Startin weapons:
	int character = *((int*)0x106D1770);
	setStartingWeapons(-1);
	setStartingWeapons(character);

	short* team = (short*)0x00AD047A;
	stringstream ss("");
	ss << "team" << *team;
	string teamKey = ss.str();
	setCustomStartingWeapons(teamKey);

	loadFragWeapons();

	setStartingWeapons(&adminWeapons);

	// MOTDs:
	if (!onlyFragMotd) {
		if (charMotd.find(-1) != charMotd.end()) {
			string s = charMotd[-1];
			printString(s);
		}
		if (charMotd.find(character) != charMotd.end()) {
			string s = charMotd[character];
			printString(s);
		}
		printCustomMotd(teamKey);
	}
}

string toZerosFormat(int value, int digits = 2) { //const char *
	std::string result;
	while (digits-- > 0) {
		result += ('0' + value % 10);
		value /= 10;
	}
	std::reverse(result.begin(), result.end());
	return result;
}

void addCustomPickup(int main, int pick, int ammo) {
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
		wasJoinSent = true;
		
		std::mt19937 rnd(std::time(NULL));
		std::uniform_real_distribution < double > dist(100, 999); //range
		myid = dist(rnd);
		std::stringstream ss;
		ss.str("");
		ss << " \x4/99 join " << myid;
		sendCmdToBot(ss.str());
}

void checkNickname() {
	string nick = (char*)0x00AD045C;
	char chars[] = "/:;\\"; //remove these characters from the nickname
	for (unsigned int i = 0; i < strlen(chars); ++i) nick.erase(std::remove(nick.begin(), nick.end(), chars[i]), nick.end());
	cout << "Nick: " << nick << endl;

	char* writable = new char[nick.size() + 1];
	strcpy(writable, nick.c_str());
	WriteToMemory((LPVOID)0x00AD045C, writable, strlen(writable) + 1);
	delete[] writable;

	if (nick != nickname) {
		nickname = nick;

		if (hasJoined) {
			std::stringstream ss;
			ss.str("");
			ss << " \x4/99 cnick " << toZerosFormat(myid) << " " << nick;
			sendCmdToBot(ss.str());
		}

		changeNickname();
	}
}

void setSpectText(string s = "") {
	if (s.empty())
		s = "SPECTATOR   ESC FOR OPTIONS";

	char* writable = new char[s.size() + 1];
	strcpy(writable, s.c_str());
	WriteToMemory((LPVOID)0x0051B93C, writable, strlen(writable) + 1);
	delete[] writable;
} 

void setStatsText(string s = "") {
	if (s.empty())
		s = "PLAYER STATS";

	char* writable = new char[s.size() + 1];
	strcpy(writable, s.c_str());
	WriteToMemory((LPVOID)0x0051BA64, writable, strlen(writable) + 1);
	delete[] writable;
}

bool isDead()
{
	return *(int*)0x106D1394 == 0;
}

bool isF1Menu()
{
	return *(int*)0x00AD02A0;
}

void forceSpect(string spectText = "") {
	if (isDead())
		SpectJoin(1, 0); //respawn

	int adres = 0x00AD03D8;
	int var = 4198400;
	WriteToMemory((LPVOID)adres, &var, sizeof(var));
	SpectJoin(0, 1);
	setSpectText(spectText);
}

void animForceSpect(string spectText = "") {
	if (isDead() || *(int*)0x106D1C80 < 2) {
		forceSpect(spectText);
		return;
	}
	
	Fire(0x106d1250, 209);
	animateCharacter(26);
	
	delayedSpectText = spectText;
	delayedForceSpect = true;
}

void forceSpect(bool waiting4gameMode, bool isCustomSpectText, string spectText = "") {
	if (!isCustomSpectText) {
		if (waiting4gameMode)
			spectText = "WAITING FOR GAME TO JOIN";
		else
			spectText = "SPECTATOR   ESC FOR OPTIONS";
	}

	animForceSpect(spectText);

	std::stringstream ss;
	if (waiting4gameMode) {
		if (hasJoined) {
			ss.str("");
			ss << " \x4/99" << " wplay " << myid;
			sendCmdToBot(ss.str());
			ss.str("");
			ss << " \x4/99" << " cstatus " << status << " 1 " << myid;
			sendCmdToBot(ss.str());
		}
		status = 1;
	}
	else {
		if (hasJoined) {
			ss.str("");
			ss << " \x4/99" << " cstatus " << status << " 0 " << myid;
			sendCmdToBot(ss.str());
		}
		status = 0;
	}
}

void blockInSpect()
{
	blockInSpectMode = true;
	animForceSpect("RESPAWNS BLOCKED");
}

void forceRespawn()
{
	blockInSpectMode = false;
	SpectJoin(1, 0);
}

int commandExecution(std::string & text, std::string searchedPhrase)
{
	size_t znalezionaPozycja = text.find(searchedPhrase); //searching for the position on which the command is placed
	if (znalezionaPozycja == std::string::npos) //whether the command was found
	{
		if (text.find(": /login ") != std::string::npos || text.find(": /register ") != std::string::npos) return 1;
		if (text.find(": ") < 17) sfx(300);
		return 0; //if not then return
	}
	serverCommands.push_back(text);
	return 1;
}

string hashPassword(string pw){
	return md5(pw + " gdfhr3tyswenxld5knoirhwlk6ns");
}

bool isAdmin(bool verbose = true){
	string s = hashPassword(passedPassword);
	cout << "Passed: " << passedPassword << " Hashed: " << s << " Actual: " << adminPassword << " IsAdmin: " << (s == adminPassword) << endl;
	if (s == adminPassword) {
		return true;
	}

	if (verbose)
		print("\x4 You are not authorized. Log in with the command: pass 'password'");
	return false;
}

bool notTempAdmin() {
	if (isTempAdmin) {
		print("\x4 Temporary admin can't use this command.");
		return false;
	}
	return true;
}

enum Cheat
{
	invicibility = 1, // (X)It is not allowed by default in mp. (?)I don't know if it does anything in mp.
	infiniteLives = 2, // (?)
	allWeapons = 4, // (X)(?)
	unlimitedAmmo = 8, // (X)(?)
	allSpecialObjects = 16, // (?)
	bigHeadMode = 32, // (X)
	tinyMode = 64, // (?)
	stickMode = 128, // (!)It can be available by default
	bigHandsFeetMode = 256, // (X)
	blackScreen = 512, //???
	gouraudMode = 1024, // (!)
	juansCheat = 2048, // (?)
	zachAttackCheat = 4096, // (?)
	allMap = 8192, // (?)
	blackout = 16384, // (!)
	frootyStripes = 32768 // (!)
};

void disableEnterCheat()
{
	static bool done = false;
	if (done)
		return;
	done = true;

	WriteToMemory((void*)0x00474678, "\x90\x90\x90\x90\x90", 5);
}

void allowAllCheats()
{
	static bool done = false;
	if (done)
		return;
	done = true;

	WriteToMemory((void*)0x004829D2, "\x90\x90\x90\x90\x90\x90", 6);
	WriteToMemory((void*)0x00484E94, "\x90\x90\x90\x90\x90\x90", 6);
	WriteToMemory((void*)0x0048505F, "\x90\x90\x90\x90\x90\x90", 6);
	WriteToMemory((void*)0x004821A3, "\x90\x90\x90\x90\x90\x90", 6);
}

void unlockCheat(Cheat cheat)
{
	int* cheatLockFlags = (int*)0x005D5A64;
	*cheatLockFlags |= cheat;
}

void lockCheat(Cheat cheat)
{
	disableEnterCheat();

	int* cheatLockFlags = (int*)0x005D5A64;
	*cheatLockFlags &= ~cheat;
}

void activateCheat(Cheat cheat)
{
	if (cheat == invicibility
		|| cheat == unlimitedAmmo
		|| cheat == allWeapons
		|| cheat == bigHeadMode
		|| cheat == bigHandsFeetMode) 
	{
		allowAllCheats();
	}

	switch (cheat)
	{
	case blackout:
		sfx(781);
		break;
	case bigHandsFeetMode:
		sfx(621);
		break;
	case bigHeadMode:
		sfx(601);
		break;
	case blackScreen:
		sfx(641); //Pen and Ink Mode
		break;
	case gouraudMode:
		sfx(651);
		break;
	case frootyStripes:
		sfx(840);
		break;
	case juansCheat:
		sfx(15210);
		break;
	case stickMode:
		sfx(611);
		break;
	case tinyMode:
		sfx(631);
		break;
	case zachAttackCheat:
		sfx(722);
		break;
	default:
		sfx(15203);
		break;
	}

	int* cheatActivateFlags = (int*)0x005D5A60;
	*cheatActivateFlags |= cheat;
}

void deactivateCheat(Cheat cheat)
{
	int* cheatActivateFlags = (int*)0x005D5A60;
	*cheatActivateFlags &= ~cheat;
}

void setCheat(Cheat cheat, int i) {
	switch (i)
	{
	case -1:
		unlockCheat(cheat);
		deactivateCheat(cheat);
		break;
	case 0:
		lockCheat(cheat);
		deactivateCheat(cheat);
		break;
	case 1:
		lockCheat(cheat);
		activateCheat(cheat);
		break;
	case 2:
		unlockCheat(cheat);
		activateCheat(cheat);
		break;
	default:
		break;
	}
}

bool isSelfTarget(string target) {
	return target == nickname || target == tid || target == "tid:-1" || target == "tid:-2";
}

void sendSetCheat(string command, int modeIndex, Cheat cheat) {
	if (!isAdmin())
		return;

	int mode = atoi(command.substr(modeIndex).c_str());
	string target;
	stringstream ss;
	bool infect = false;
	if (command.length() > modeIndex+2) {
		// Specifed player
		target = command.substr(command.find(" ", modeIndex) + 1);

		if (isSelfTarget(target)) // if indicated self
			setCheat(cheat, mode);

		target += ";";
	}
	else {
		// To everyone
		target = "00";
		setCheat(cheat, mode); // also self

		ss.str("");
		ss << " \x4/00 news \x4 " << nickname << " set cheat " << cheat << " to mode " << mode
			<< " on everyone currently on the server.";
		sendCmdWithPassword(ss.str());

		ss.str("");
		ss << "\x4 You just set cheat " << cheat << " to mode " << mode
			<< " on everyone currently on the server (with kub's mod).";
		printString(ss.str());
	
		infect = true;
		//if(!infect) print("(If someone new joins, they will not have this mode! You will have to repeat this action on him.)");
	}

	ss.str("");
	ss << " \x4/" << target << " setcheat " << cheat << " " << mode;
	sendCmdWithPassword(ss.str());

	if (infect) {
		ss.str("");
		ss << *(unsigned int*)0x005D5A60 << " " << *(unsigned int*)0x005D5A64;
		cheatsInfection = ss.str();
		ss.str("");
		ss << " \x4/" << target << " infectcheats " << cheatsInfection;
		sendCmdWithPassword(ss.str());
	}
}

bool isSafeMode(int i) {
	bool b = false;
	if (i < 0) {
		if (safeMode <= i)
			b = true;
	}
	else if (safeMode >= i) {
		b = true;
	}

	if(b)
		cout << "SafeMode" << i << " blocked sth." << endl;

	return b;
}

static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param)
{
	std::string& text = *static_cast<std::string*>(param);
	size_t totalsize = size * nmemb;
	text.append(static_cast<char*>(buffer), totalsize);
	return totalsize;
}

bool readWebSite(string* result, string url) {
	CURL* curl;
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

string removeNewLineChar(string s) {
	if (!s.empty() && (s[s.length() - 1] == '\n' || s[s.length() - 1] == '\r')) {
		return s.erase(s.length() - 1);
	}
	return s;
}

void reloadCharModels()
{
	reloadCharacters(11338600);
}

void setFlare(int i, bool asStartingWeapon) {
	flareToFire = i;
	if (i > 0) {
		equipWeapon(flareSlot, 1);
		*getAmmo(flareAmmo) = 1;
	}
	else {
		equipWeapon(flareSlot, 0);
		*getAmmo(flareAmmo) = 0;
	}

	if(asStartingWeapon)
	{
		removeElementsStartingWith("24", startingWeapons);
		if(i > 0)
			startingWeapons.push_back("24");
	}
}

short stos(string str) {
	short s;
	sscanf(str.c_str(), "%hi", &s);
	return s;
}

void addStartingWeapons(string s, vector<string>* collection) {
	istringstream iss(s);
	vector<string> tokens{ istream_iterator<string>{iss},
		istream_iterator<string>{} };
	for (auto const& value : tokens) {
		if (value == "-100")
			(*collection).clear();
		else
			(*collection).push_back(value);
	}
}

bool cfgBool(string line) {
	string s = line.substr(line.find("=") + 1);
	if (s.find("true") != std::string::npos
		|| s.find("TRUE") != std::string::npos
		|| s.find("1") != std::string::npos)
		return true;
	return false;
}

string cfgString(string line) {
	string s = line.substr(line.find("=") + 1);
	s = removeNewLineChar(s);
	return s;
}

int cfgInt(string line) {
	return stoi(line.substr(line.find("=") + 1));
}

float cfgFloat(string line) {
	return stof(line.substr(line.find("=") + 1));
}

vector<string> splitString(string s, char c) {
	stringstream ss(s);
	string segment;
	vector<string> seglist;

	while (getline(ss, segment, c))
	{
		seglist.push_back(segment);
	}

	return seglist;
}

map<string, unsigned int> floatCfgs;
map<string, unsigned int> intCfgs;
map<string, unsigned int> charactersCfgs;

void setFloatCfg(string key, float f) {
	WriteToMemory((LPVOID)floatCfgs[key], &f, 4);
}

void setIntCfg(string key, int i) {
	WriteToMemory((LPVOID)intCfgs[key], &i, 4);
}

bool configLine(string, string);

void setConfigLine(string cmd, float value) {
	stringstream ss("");
	ss << cmd << value;
	configLine(ss.str(), "");
}

string getCharacterShortName(int character) {
	switch (character)
	{
	case -1:
		return "all";
	case 0: // Turok
		return "turok";
	case 1: // Adon
		return "adon";
	case 2: // Gant
		return "gant";
	case 3: // Flesh
		return "flesh";
	case 4: // Pur
		return "pur";
	case 5: // End
		return "end";
	case 6: // Fire
		return "fire";
	case 7: // Iggy
		return "iggy";
	case 8: // Camp
		return "camp";
	case 9: // Tel
		return "tel";
	case 10: // Raptor
		return "raptor";
	}
}

void setCharacterHP(int character, int hp) {
	if (character < 0) {
		for (int i = 0; i <= 10; i++)
			setCharacterHP(character, hp);
		return;
	}

	stringstream ss("");
	ss << getCharacterShortName(character) << "HP=";
	setIntCfg(ss.str(), hp);
}

void setCharacterSize(int character, float l, float h, float w, float camera = -99) {
	if (character < 0) {
		for (int i = 0; i <= 10; i++)
			setCharacterSize(character, l, h, w, camera);
		return;
	}

	string shortName = getCharacterShortName(character);
	setFloatCfg(shortName + "Length=", l);
	setFloatCfg(shortName + "Height=", h);
	setFloatCfg(shortName + "Width=", w);
	if (camera >= -1)
		setConfigLine(shortName + "Camera=", camera);

	reloadModelsNeeded = true;
}

bool setCharacterSize(string line, int character) {
	vector<string> params = splitString(line.substr(line.find("=") + 1), ';');
	if (params.size() > 4)
	{
		cout << "Wrong params for " << line << endl;
		return false;
	}

	float l;
	float h;
	float w;
	if (params.size() >= 3) {
		l = stof(params[0]);
		h = stof(params[1]);
		w = stof(params[2]);
	}
	else {
		float f = stof(params[0]);
		l = f;
		h = f;
		w = f;
	}

	float camera = -99;
	if (params.size() == 2 || params.size() == 4) {
		camera = stof(params[params.size()-1]);
	}

	cout << "setCharacterSize " << l << " " << h << " " << w << " " << camera << " ";

	setCharacterSize(character, l, h, w, camera);

	return true;
}

float cfgValueToFloat(string value) {
	// Check if the first char specifies type of the value
	char type;
	switch (value[0]) {
	case 'i':
	case 's':
	case 'b':
	case 'f':
	case 'd':
	case 'u':
		type = value[0];
		value = value.substr(1);
		break;
	default:
		type = 'i';
		break;
	}

	// If starts with 0x then it's address to value in the game memory
	if (value.find("0x") != 0) {
		switch (type) {
		case 'i':
		case 's':
		case 'b':
			return stoi(value);
		case 'f':
			return stof(value);
		case 'd':
			return (float)stod(value);
		case 'u':
			return (float)stoul(value);
		}
	}
	else
	{
		int a = stoi(value, 0, 16);
		switch (type) {
		case 'i':
			return *(int*)a;
		case 's':
			return *(short*)a;
		case 'b':
			return *(byte*)a;
		case 'f':
			return *(float*)a;
		case 'd':
			return (float)*(double*)a;
		case 'u':
			return (float)*(unsigned int*)a;
		}
	}
	return 0;
}

int cfgValueToInt(string value) {
	if (value.find("0x") == string::npos)
		return stoi(value);

	return (int)cfgValueToFloat(value);
}

short cfgValueToShort(string value) {
	if (value.find("0x") == string::npos)
		return stos(value);

	return (short)cfgValueToFloat(value);
}

void kick(string s) {
	WriteToMemory((void*)0x0051B958, s.c_str(), s.size());
	s = "\xA1\x84\x02\xAD\x00";
	WriteToMemory((void*)0x0046E195, s.c_str(), s.size());
	int i = 0;
	WriteToMemory((void*)0x00B74624, &i, 4);
}

void setBulletSpeed(float f = 1) {
	WriteToMemory((void*)0x0050B804, &f, sizeof(f));
}

void setCloudsSpeed(float f) {
	WriteToMemory((LPVOID)0x0050B808, &f, sizeof(f));
}

void setPickablesSpeed(float f) {
	f *= 0.08726646751;
	WriteToMemory((LPVOID)0x004F9724, &f, sizeof(f));
}

void setEffectsSize(float f) {
	f *= 0.001000000047;
	WriteToMemory((LPVOID)0x004F9CCC, &f, sizeof(f));
}

void setQuakeReductionSpeed(float f) {
	f *= 3;
	WriteToMemory((void*)0x004F94B0, &f, sizeof(f));
}

void activateMovementMultiplier(bool activate) {
	if (activate)
		WriteToMemory((void*)0x0041FF58, "\x90\x90", 2);
	else
		WriteToMemory((void*)0x0041FF58, "\x74\x0E", 2);
}

void setMovementSpeed(float f) {
	WriteToMemory((void*)0x005D5A7C, &f, sizeof(f)); // char speed
}

void setSuperSpeed(float f) {
	setBulletSpeed(f*superhotMaxBulletSpeed);
	setCloudsSpeed(f);
	setPickablesSpeed(f);
}

void setSuperhotSpeed(float f) {
	superhotSpeed = f;
	setSuperSpeed(f);

	if (superhotQuake) {
		if (f < 1)
		{
			setQuakeReductionSpeed(0.4 + 0.6 * f);
		}
		else
		{
			setQuakeReductionSpeed(f);
		}
	}

	if (superhotMovement) {
		if (f < 1)
		{
			setMovementSpeed(superhotMinMovement + (superhotMaxMovement-superhotMinMovement)*f);
		}
		else
		{
			setMovementSpeed(f*superhotMaxMovement);
		}
	}
}

void adjustSuperhotSpeed(float targetSpeed, float adjustmentTime) {
	if (adjustmentTime == 0) {
		setSuperhotSpeed(targetSpeed);
	}

	superhotInitialSpeed = superhotSpeed;
	superhotTargetSpeed = targetSpeed;
	superhotAdjustTime = adjustmentTime;
	superhotTimer = adjustmentTime;
}

void adjustSuperhotSpeed(float targetSpeed) {
	if (superhotSpeed > targetSpeed)
		adjustSuperhotSpeed(targetSpeed, superhotAdjustDownTime);
	else
		adjustSuperhotSpeed(targetSpeed, superhotAdjustUpTime);
}

enum SuperhotState {
	moving = 0,
	standing = 1,
	inactive = 2
};

SuperhotState toSuperhotState(int i) {
	if (i == 2 || i == 32)
		return standing;
	else if (i == 0 || i == 1 || i == 15)
		return inactive;
	else
		return moving;
}

void decSuperhotState(int playerId) {
	SuperhotState state = toSuperhotState(playersState[playerId]);
	switch (state)
	{
	case moving:
		superhotMoving--;
		break;
	case standing:
		superhotStanding--;
		break;
	case inactive:
		superhotInactive--;
		break;
	}
}

void incSuperhotState(int playerId) {
	SuperhotState state = toSuperhotState(playersState[playerId]);
	switch (state)
	{
	case moving:
		superhotMoving++;
		break;
	case standing:
		superhotStanding++;
		break;
	case inactive:
		superhotInactive++;
		break;
	}
}

void setSuperhotMovement(int mode) {
	superhotMovement = mode;
	activateMovementMultiplier(superhotMovement);
}

void setSuperhotMovement() {
	setSuperhotMovement(superhotMovement);
}

void setSuperhotMode(int mode) {
	if (superhot == 3 && mode != 3) {
		superhotMidThreshold = 0.5;
		if(isAdmin(false))
			print("superhotMidThreshold has been reset to 0.5");
	}

	superhot = mode;
	if (superhot)
	{
		superhotTextLvl = 0;
		superhotTextTimer = 0;
		superhotInitialSpeed = *(float*)0x0050B804;
		setSuperhotMovement();
	}
	else
	{
		setMovementSpeed(superhotMaxMovement);
		activateMovementMultiplier(superhotMaxMovement != 1);
		setStatsText();
		setSuperSpeed(superhotMaxSpeed);
		setQuakeReductionSpeed(1);
	}
}

int hookedDecPlayerCount(int i1, int i2) {
	static byte* playerCount = (byte*)0x005D4634;

	byte pre = *playerCount;
	int toRet = decPlayerCount(i1, i2);
	if (pre == *playerCount)
		return toRet;

	//stringstream ss("");
	//ss << "dec(" << i2 << ") " << (int)pre << " \x02 " << (int)*(byte*)0x005D4634;
	//printString(ss.str());
	if (playersState.count(i2)) {
		decSuperhotState(i2);
		playersState.erase(i2);
	}

	return toRet;
}

/*int hookedIncPlayerCount(int i1, int i2) {
	byte pre = *(byte*)0x005D4634;
	int toRet = incPlayerCount(i1, i2);
	if (pre == *(byte*)0x005D4634)
		return toRet;

	stringstream ss("");
	ss << "inc(" << i2 << ") " << (int)pre << " \x02 " << (int)*(byte*)0x005D4634;
	printString(ss.str());

	return toRet;
}*/

void setFragLimit(int i) {
	WriteToMemory((LPVOID)0x00AD44D0, &i, 4);
}

void setTimeLimit(int i) {
	WriteToMemory((LPVOID)0x00AD44D4, &i, 4);
}

void setPointLimit(int i) {
	WriteToMemory((LPVOID)0x00AD44D8, &i, 4);
}

void applyCustomDamage()
{
	if (customDamage != -1)
		WriteToMemory((LPVOID)0x00AD44EC, &customDamage, sizeof(customDamage));
	if (customNode != -1)
		WriteToMemory((LPVOID)0x00AD44F0, &customNode, sizeof(customNode));
}


void setCustomDamage(short weapon)
{
	if (customDamages.find(weapon) != customDamages.end())
		customDamage = customDamages[weapon];
	else if (defaultDamage != -1)
		customDamage = defaultDamage;

	if (customNodes.find(weapon) != customNodes.end())
		customNode = customNodes[weapon];
	else if (defaultNode != -1)
		customNode = defaultNode;

	float currentDamage = *((float*)0x00AD44EC);
	float currentNode = *((float*)0x00AD44F0);
	if (currentDamage < customDamage || currentNode < customNode)
	{
		changeDamageDelayTimer = 3;
		return;
	}
	applyCustomDamage();
}

void setCustomDamage() {
	setCustomDamage(*((short*)0x106D1BE6));
}

void setDamage(float f) {
	defaultDamage = f;
	setCustomDamage();
}

void setNode(float f) {
	defaultNode = f;
	setCustomDamage();
}

bool execCommand(string);
bool loadOnlineConfig(string);

void resetMod(bool reloadConfig = true)
{
	customDamages.clear();
	customNodes.clear();
	customDrop.clear();
	customPickup.clear();
	customPchance.clear();
	extraAmmo.clear();
	startingWeapons.clear();
	turokWeapons.clear();
	adonWeapons.clear();
	gantWeapons.clear();
	fleshWeapons.clear();
	purWeapons.clear();
	endWeapons.clear();
	fireWeapons.clear();
	iggyWeapons.clear();
	campWeapons.clear();
	telWeapons.clear();
	adminWeapons.clear();
	customStartingWeapons.clear();
	charMotd.clear();
	customMotd.clear();
	cachedConfigs.clear();
	onRespawnConfig.clear();
	onFragConfig.clear();
	onDeathConfig.clear();
	onCharacterChangeConfig.clear();
	onWeaponDropConfig.clear();
	onWeaponPickupConfig.clear();
	onWeaponChangeConfig.clear();
	onShotFiredConfig.clear();
	blockInSpectMode = false;
	cheatsInfection = "";
	configInfections.clear();
	weaponsInfection = "";
	cfgCmdInfections.clear();
	flareInfection = -1;
	fragFlares.clear();
	fragSfx.clear();
	deathFlares.clear();
	deathAnims.clear();
	replacedAnims.clear();
	deathSfx.clear();
	respawnFlares.clear();
	respawnSfx.clear();
	respawnCooldown = 0;
	forceSpectOnRespawn = 0;
	pfmProjectile = 12;
	sunfirepodProjectile = 10;
	assaultProjectile = 305;
	betaGrenadeProjectile = 302;
	betaHarpoonProjectile = 306;
	betaTorpedoProjectile = 0;
	betaPlasmaProjectile = 303;
	betaFirestormProjectile = 0;
	betaCboreProjectile = 459;
	betaChargeProjectile = 4;
	tranquilizerProjectile = 3;
	bowProjectile = 86;
	singleRocketProjectile = 295;
	crossbowProjectile = 298;
	airStrikeWith = 16; //torpedo
	dinoRidingWith = 4; //chargeDart
	blackOilWith = 5; //pistol
	flareToFire = 95;
	isTorpedoDisabledOnGround = false;
	airStrikeDelay = 0;
	airStrikeAmmoId = 18; //torpedo
	customAirStrikeAmmoId = 18; //torpedo
	airStrikeAmmoCost = 6;
	howManyExtraNukeExplosions = 2;
	bUseWeaponsEverywhere = false;
	blockPickups = false;
	blockDrops = false;
	useWeaponsEverywhere(false);
	chatNews.clear();

	setSuperhotMode(0);
	superhotMovement = 1;
	superhotQuake = 1;
	superhotAdjustUpTime = 0.2;
	superhotAdjustDownTime = 0.1;
	superhotInitialSpeed = 1;
	superhotMinMovement = 0.5;
	superhotMaxMovement = 1;
	superhotMidSpeed = 0.01;
	superhotMinSpeed = 0.001;
	superhotMaxSpeed = 1;
	superhotMaxBulletSpeed = 1;
	superhotMidThreshold = 0.5;
	setMovementSpeed(1);
	activateMovementMultiplier(false);
	setSuperSpeed(1);
	setEffectsSize(1);
	setQuakeReductionSpeed(1);

	setFragLimit(originalFragLimit);
	setTimeLimit(originalTimeLimit);
	setPointLimit(originalPointLimit);
	setDamage(originalDamage);
	setNode(originalNode);
	
	if (reloadConfig) {
		loadOnlineConfig(cfgurl);
		SpectJoin(1, 0); // respawn
	}
}

void prepareToOnlineConfig() {
	int offset = 0;
	string lvlSet = (char*)0x00B65DD9;
	if (lvlSet.find("Arena") != std::string::npos)
		offset = -17936;
	else if (lvlSet.find("CTF") != std::string::npos)
		offset = -13576;

	floatCfgs["fleshLength="] = 0x101424C0 + offset;
	floatCfgs["fleshHeight="] = 0x101424BC + offset;
	floatCfgs["fleshWidth="] = 0x101424B8 + offset;
	floatCfgs["fleshJump="] = 0x101424A0 + offset;
	floatCfgs["fleshSpeed="] = 0x1014249C + offset;
	floatCfgs["fleshCamera="] = 0x101424B0 + offset;
	floatCfgs["adonLength="] = 0x10142430 + offset;
	floatCfgs["adonHeight="] = 0x1014242C + offset;
	floatCfgs["adonWidth="] = 0x10142428 + offset;
	floatCfgs["adonJump="] = 0x10142410 + offset;
	floatCfgs["adonSpeed="] = 0x1014240C + offset;
	floatCfgs["adonCamera="] = 0x10142420 + offset;
	floatCfgs["turokLength="] = 0x101423E8 + offset;
	floatCfgs["turokHeight="] = 0x101423E4 + offset;
	floatCfgs["turokWidth="] = 0x101423E0 + offset;
	floatCfgs["turokJump="] = 0x101423C8 + offset;
	floatCfgs["turokSpeed="] = 0x101423C4 + offset;
	floatCfgs["turokCamera="] = 0x101423D8 + offset;
	floatCfgs["purLength="] = 0x10142508 + offset;
	floatCfgs["purHeight="] = 0x10142504 + offset;
	floatCfgs["purWidth="] = 0x10142500 + offset;
	floatCfgs["purJump="] = 0x101424E8 + offset;
	floatCfgs["purSpeed="] = 0x101424E4 + offset;
	floatCfgs["purCamera="] = 0x101424F8 + offset;
	floatCfgs["endLength="] = 0x10142550 + offset;
	floatCfgs["endHeight="] = 0x1014254C + offset;
	floatCfgs["endWidth="] = 0x10142548 + offset;
	floatCfgs["endJump="] = 0x10142530 + offset;
	floatCfgs["endSpeed="] = 0x1014252C + offset;
	floatCfgs["endCamera="] = 0x10142540 + offset;
	floatCfgs["fireLength="] = 0x10142598 + offset;
	floatCfgs["fireHeight="] = 0x10142594 + offset;
	floatCfgs["fireWidth="] = 0x10142590 + offset;
	floatCfgs["fireJump="] = 0x10142578 + offset;
	floatCfgs["fireSpeed="] = 0x10142574 + offset;
	floatCfgs["fireCamera="] = 0x10142588 + offset;
	floatCfgs["iggyLength="] = 0x101425E0 + offset;
	floatCfgs["iggyHeight="] = 0x101425DC + offset;
	floatCfgs["iggyWidth="] = 0x101425D8 + offset;
	floatCfgs["iggyJump="] = 0x101425C0 + offset;
	floatCfgs["iggySpeed="] = 0x101425BC + offset;
	floatCfgs["iggyCamera="] = 0x101425D0 + offset;
	floatCfgs["campLength="] = 0x10142628 + offset;
	floatCfgs["campHeight="] = 0x10142624 + offset;
	floatCfgs["campWidth="] = 0x10142620 + offset;
	floatCfgs["campJump="] = 0x10142608 + offset;
	floatCfgs["campSpeed="] = 0x10142604 + offset;
	floatCfgs["campCamera="] = 0x10142618 + offset;
	floatCfgs["telLength="] = 0x10142670 + offset;
	floatCfgs["telHeight="] = 0x1014266C + offset;
	floatCfgs["telWidth="] = 0x10142668 + offset;
	floatCfgs["telJump="] = 0x10142650 + offset;
	floatCfgs["telSpeed="] = 0x1014264C + offset;
	floatCfgs["telCamera="] = 0x10142660 + offset;
	floatCfgs["gantLength="] = 0x10142478 + offset;
	floatCfgs["gantHeight="] = 0x10142474 + offset;
	floatCfgs["gantWidth="] = 0x10142470 + offset;
	floatCfgs["gantJump="] = 0x10142458 + offset;
	floatCfgs["gantSpeed="] = 0x10142454 + offset;
	floatCfgs["gantCamera="] = 0x10142468 + offset;

	intCfgs["fleshHP="] = 0x10142498 + offset;
	intCfgs["adonHP="] = 0x10142408 + offset;
	intCfgs["turokHP="] = 0x101423C0 + offset;
	intCfgs["purHP="] = 0x101424E0 + offset;
	intCfgs["endHP="] = 0x10142528 + offset;
	intCfgs["fireHP="] = 0x10142570 + offset;
	intCfgs["iggyHP="] = 0x101425B8 + offset;
	intCfgs["campHP="] = 0x10142600 + offset;
	intCfgs["telHP="] = 0x10142648 + offset;
	intCfgs["gantHP="] = 0x10142450 + offset;

	if (lvlSet.find("Arena") != std::string::npos)
		offset = -22168;
	else if (lvlSet.find("CTF") != std::string::npos)
		offset = -1768;

	intCfgs["raptorHP="] = 0x10144640 + offset;
	floatCfgs["raptorLength="] = 0x10144668 + offset;
	floatCfgs["raptorHeight="] = 0x10144664 + offset;
	floatCfgs["raptorWidth="] = 0x10144660 + offset;
	floatCfgs["raptorJump="] = 0x10144648 + offset;
	floatCfgs["raptorSpeed="] = 0x10144644 + offset;
	floatCfgs["raptorCamera="] = 0x10144658 + offset;

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
	charactersCfgs["raptorMOTD="] = 10;
}

void addConfigPreset(map<string, string>& map, string cfgLine) {
	string s = cfgString(cfgLine);
	string presetId = s.substr(0, s.find(":"));
	string url = s.substr(s.find(":") + 1);
	map[presetId] = url;
	cout << "ConfigPreset added " << presetId << " " << url << endl;
}

void addConfigPresetDescription(string cfgLine) {
	string s = cfgString(cfgLine);
	string presetId = s.substr(0, s.find(":"));
	string desc = s.substr(s.find(":") + 1);
	configPresetsDescriptions[presetId] = desc;
}

void addCustomStartingWeapons(string line, string key) {
	string valueString = line.substr(line.find("=") + 1);
	valueString = valueString.substr(0, line.find(":"));
	int value = stoi(valueString);

	vector<string> collection;
	addStartingWeapons(line.substr(line.find(":") + 1), &collection);

	stringstream ss("");
	ss << key << value;
	customStartingWeapons[ss.str()] = collection;
	cout << line << endl;
	cout << key << ": " << value << " " << valueString << " weapons: " << line.substr(line.find(":") + 1) << endl;
}

void addCustomMotd(string line, string key) {
	string valueString = line.substr(line.find("=") + 1);
	valueString = valueString.substr(0, line.find(":"));
	int value = stoi(valueString);

	cout << key << "MOTD= " << value << " " << valueString << endl;

	stringstream ss("");
	ss << key << value;
	customMotd[ss.str()] = line.substr(line.find(":") + 1);
}

void callFunc(int address, string funcType, string msg) {
	if (safeMode > 2)
	{
		cout << "SafeMode3 blocked callFunc: " << address << " " << funcType << " " << msg << endl;
		return;
	}

	if (funcType.find("na") == 0) {
		fnoarg_ func = (fnoarg_)address;
		func();
	}
	else if (funcType.find("i1") == 0) {
		int var = 0;
		if (msg.find("(") != std::string::npos) {
			funcType = msg.substr(msg.find("(") + 1); //msg.substr(27);
			funcType = funcType.substr(0, msg.find(")"));
			var = atoi(funcType.c_str());
		}
		//cout << "callf i1 var: " << var << endl;
		f1int_ func = (f1int_)address;
		func(var);
	}
	else if (funcType.find("i2") == 0) {
		int var1 = 0;
		int var2 = 0;
		if (msg.find("(") != std::string::npos) {
			funcType = msg.substr(msg.find("(") + 1); //msg.substr(27);
			funcType = funcType.substr(0, msg.find(","));
			var1 = atoi(funcType.c_str());

			if (msg.find(",") != std::string::npos) {
				funcType = msg.substr(msg.find(",") + 1);
				funcType = funcType.substr(0, msg.find(")"));
				var2 = atoi(funcType.c_str());
			}
		}
		//cout << "callf i2 var1: " << var1 << " var2 : " << var2 << endl;
		f2ints_ func = (f2ints_)address;
		func(var1, var2);
	}
	else if (funcType.find("f1") == 0) {
		float var = 0;
		if (msg.find("(") != std::string::npos) {
			funcType = msg.substr(msg.find("(") + 1); //msg.substr(27);
			funcType = funcType.substr(0, msg.find(")"));
			var = atof(funcType.c_str());
		}
		f1float_ func = (f1float_)address;
		func(var);
	}
	else if (funcType.find("f2") == 0) {
		float var1 = 0;
		float var2 = 0;
		if (msg.find("(") != std::string::npos) {
			funcType = msg.substr(msg.find("(") + 1); //msg.substr(27);
			funcType = funcType.substr(0, msg.find(","));
			var1 = atof(funcType.c_str());

			if (msg.find(",") != std::string::npos) {
				funcType = msg.substr(msg.find(",") + 1);
				funcType = funcType.substr(0, msg.find(")"));
				var2 = atof(funcType.c_str());
			}
		}
		f2floats_ func = (f2floats_)address;
		func(var1, var2);
	}
	else if (funcType.find("cs") == 0) {
		int var = 0;
		if (msg.find("(") != std::string::npos) {
			funcType = msg.substr(msg.find("(") + 1); //msg.substr(27);
			funcType = funcType.substr(0, msg.find(")"));
		}
		char* writable = new char[funcType.size() + 1];
		strcpy(writable, funcType.c_str());
		fcstr_ func = (fcstr_)address;
		func(writable);
		delete[] writable;
	}
}

void softReloadMap() {
	if (delayedRespawn)
		return;

	int i = 0;
	WriteToMemory((void*)0x00B74624, &i, 4);

	remap(5773664, *(int*)0x005CA4D0, 0);
	delayedRespawn = true;

	i = 1;
	WriteToMemory((void*)0x00B74624, &i, 4);
}

int hookedLevelEnd(int i1, int i2)
{
	int toReturn = levelEnd(i1, i2);
	//stringstream ss("");
	//ss << "LevelEnd(" << i1 << ", " << i2 << ") " << toReturn;
	//printString(ss.str());
	playLectorOnRemap = true;
	return 1;
}

int hookedCharacterAnimation(int i1, int i2, int i3)
{
	int anim = i3;
	if (i1 == 275583568 && i2 == 275583568) {
		if (playingDead) {
			if (i3 == 15) {
				*(short*)0x106D1C80 = 36;
				print("Fake death animation reset - you can get up now.");
				return 0;
			}
			else {
				playingDead = false;
			}
		}
		
		if (replacedAnims.count(i3)) {
			anim = replacedAnims[i3];

			if (i3 == 36) {
				playingDead = true;
			}
		}		

		if (*(int*)0x106D1770 == 10) { // Is raptor?
			if (replacedAnims.count(i3+37)) {
				anim = replacedAnims[i3+37];

				if (i3 == 36) {
					playingDead = true;
				}
			}
		}

		if(superhot == 1) {
			if (anim == 2 || anim == 32)
				adjustSuperhotSpeed(superhotMidSpeed, superhotAdjustDownTime);
			else
				adjustSuperhotSpeed(superhotMaxSpeed, superhotAdjustUpTime);
		}
	}
	else {
		if (anim == 17) {
			if (!reversedAnim17Attack) {
				reversedAnim17Attack = true;
				animateCharacter(17);
				resetToAnim2 = true;
				print("[AntyHector] Blocked anim 17 attempt - attack reversed :)");
			}
			return 0;
		}
	}

	int toReturn = characterAnimation(i1, i2, anim);

	if (superhot >= 2 && toReturn == 1) {
		if (playersState.count(i1) == 0 || toSuperhotState(playersState[i1]) != toSuperhotState(anim)) {
			if (playersState.count(i1))
				decSuperhotState(i1);
			playersState[i1] = anim;
			incSuperhotState(i1);

			float targetSpeed;
			int active = superhotMoving + superhotStanding;
			if (superhot == 3 && active > 0)
				superhotMidThreshold = 1/(float)active;
			float threshold = active*superhotMidThreshold;
			if (superhotStanding <= threshold && threshold != 0) {
				float f = 1 - superhotStanding/threshold;
				targetSpeed = superhotMidSpeed + (superhotMaxSpeed-superhotMidSpeed)*f;
			}
			else {
				float reversedThreshold = active * (1 - superhotMidThreshold);
				float f = 1 - (superhotStanding - threshold) / reversedThreshold;
				targetSpeed = superhotMinSpeed + (superhotMidSpeed-superhotMinSpeed)*f;
			}
			adjustSuperhotSpeed(targetSpeed);

			if(logSuperhot) {	
				stringstream ss("");
				ss << "[SUPERHOT] " << superhotStanding << "/" << active;
				ss << " \x02 M" << superhotMoving << " S" << superhotStanding << " I" << superhotInactive;
				ss << " \x02 Speed: " << targetSpeed;
				//ss << " (" << superhotStanding/(float)active << ")";
				printString(ss.str());
			}
		}
	}
	
	if (logAnims == 1 || logAnims == 2 && i3 > 5) {
		stringstream ss("");
		ss << "[Anim] " << i1 << " " << i2 << " " << i3;
		if (i3 != anim)
			ss << " (replaced with " << anim << ")";
		ss << " returned: " << toReturn;
		printString(ss.str());
	}

	return toReturn;
}

void setFrags(short value) {
	WriteToMemory((void*)0x00AD0470, &value, 2);
}

void setPain(short value) {
	WriteToMemory((void*)0x00AD0472, &value, 2);
}

void setDeaths(short value) {
	WriteToMemory((void*)0x00AD0474, &value, 2);
}

void setTime(short value) {
	WriteToMemory((void*)0x00AD0476, &value, 2);
}

void setHP(short value) {
	WriteToMemory((void*)0x106D1775, &value, 2);
}

void resetStats() {
	setFrags(0);
	setPain(0);
	setDeaths(0);
	setTime(0);
	killstreak = 0;
}

void showEloInsteadTime(bool enable){
	if (enable)
	{
		WriteToMemory((void*)0x00482688, "\x90\x90\x90\x90\x90\x90\x90", 7); // Disable time
		WriteToMemory((void*)0x0051BA16, "Elo ", 4);
		WriteToMemory((void*)0x0051BA4E, "Elo ", 4);
		setTime(myElo);
	}
	else
	{
		WriteToMemory((void*)0x00482688, "\x66\x89\x85\xCE\x00\x00\x00", 7); // Enable time
		WriteToMemory((void*)0x0051BA16, "Time", 4);
		WriteToMemory((void*)0x0051BA4E, "Time", 4);
		setTime(0);
	}
}

void requestSoftReloadMap(bool restats = false) {
	remapOnRespawn = true;
	animateCharacter(26);

	if (restats)
		resetStats();
}

// Returns true if added/changed, false if removed.
bool replaceAnim(int oldAnim, int newAnim) {
	if (oldAnim < 0 || newAnim < 0) {
		oldAnim = abs(oldAnim);
		if (replacedAnims.count(oldAnim))
			replacedAnims.erase(oldAnim);
		return false;
	}

	replacedAnims[oldAnim] = newAnim;
	return true;
}

void setFixedF(float f = 0) {
	if (f <= 0)
	{
		int frameTime = *(int*)0x00B65F70;
		fixedF = 0.001 * frameTime;
		return;
	}

	fixedF = f;
}

void setFrameTime(int frameTime, bool adjustFixedF) {
	if (frameTime >= 0)
	{
		WriteToMemory((LPVOID)0x00B65F70, &frameTime, sizeof(frameTime));
		if (adjustFixedF)
			setFixedF();
	}
}

bool configLine(string line, string word = "") {
	if(word.empty())
		word = line.substr(0, line.find("=") + 1);

	if (charactersCfgs.count(word)) {
		if (word.find("Weapons") != std::string::npos) {
			vector<string>* v;
			switch (charactersCfgs[word])
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

			addStartingWeapons(cfgString(line), v);
			reloadWeaponsNeeded = true;
		}
		else { //motd
			charMotd[charactersCfgs[word]] = cfgString(line);
		}
		return true;
	} 
	if (word == "teamWeapons=") {
		addCustomStartingWeapons(line, "team");
		return true;
	}
	if (word == "teamMOTD=") {
		addCustomMotd(line, "team");
		return true;
	}
	if (word == "fragsWeapons=") {
		addCustomStartingWeapons(line, "frags");
		return true;
	}
	if (word == "fragsMOTD=") {
		addCustomMotd(line, "frags");
		return true;
	}
	if (word == "killstreakWeapons=") {
		addCustomStartingWeapons(line, "killstreak");
		return true;
	}
	if (word == "killstreakMOTD=") {
		addCustomMotd(line, "killstreak");
		return true;
	}
	if (word == "customWeapons=") {
		addCustomStartingWeapons(line, "");
		return true;
	}
	if (word == "customMOTD=") {
		addCustomMotd(line, "");
		return true;
	}
	if (word == "MOTD=") {
		printString(cfgString(line));
		return true;
	}
	if (word == "statsText=") {
		setStatsText(cfgString(line));
		return true;
	}
	if (word == "chatNews=") {
		string news = cfgString(line);
		if (news == "*clear*") {
			chatNews.clear();
			removeElementsStartingWith("chatNews=", cfgCmdInfections);
		}
		else
			chatNews.push_back(news);
		return true;
	}
	if (word == "timeBetweenChatNews=" || word == "chatNewsTime=") {
		timeBetweenChatNews = cfgFloat(line);
		return true;
	}
	if (word == "ban=") {
		stringstream ss("");
		ss << "BAN REASON: " << cfgString(line);
		printString(ss.str());

		kick("YOU HAVE BEEN BANED!");
		return true;
	}
	if (word == "adminMod=") {
		addConfigPreset(adminConfigPresets, line);
		return true;
	}
	if (word == "mod=") {
		addConfigPreset(localConfigPresets, line);
		return true;
	}
	if (word == "modDesc=") {
		addConfigPresetDescription(line);
		return true;
	}
	if (word == "removeAdminMod=") {
		string s = cfgString(line);
		if (adminConfigPresets.count(s))
			adminConfigPresets.erase(s);
		return true;
	}
	if (word == "removeMod=") {
		string s = cfgString(line);
		if (localConfigPresets.count(s))
			localConfigPresets.erase(s);
		return true;
	}
	if (word == "onRespawnConfig=") {
		onRespawnConfig = cfgString(line);
		return true;
	}
	if (word == "onFragConfig=") {
		onFragConfig = cfgString(line);
		return true;
	}
	if (word == "onDeathConfig=") {
		onDeathConfig = cfgString(line);
		return true;
	}
	if (word == "onCharacterChangeConfig=") {
		onCharacterChangeConfig = cfgString(line);
		return true;
	}
	if (word == "onWeaponDropConfig=") {
		onWeaponDropConfig = cfgString(line);
		return true;
	}
	if (word == "onWeaponPickupConfig=") {
		onWeaponPickupConfig = cfgString(line);
		return true;
	}
	if (word == "onWeaponChangeConfig=") {
		onWeaponChangeConfig = cfgString(line);
		return true;
	}
	if (word == "onShotFiredConfig=") {
		onShotFiredConfig = cfgString(line);
		return true;
	}
	if (word == "execConfig=") {
		loadOnlineConfig(cfgString(line));
		return true;
	}
	if (word == "fleshCamera=") {
		float f = cfgFloat(line);
		float* camsize = (float*)floatCfgs["fleshCamera="];
		if (f == -1)
			*camsize = *((float*)floatCfgs["fleshHeight="]) / 0.6875 * 168.9599915;
		else
			*camsize = f;
		return true;
	}
	if (word == "adonCamera=") {
		float f = cfgFloat(line);
		float* camsize = (float*)floatCfgs["adonCamera="];
		if (f == -1)
			*camsize = *((float*)floatCfgs["adonHeight="]) / 0.5625 * 138.2399902;
		else
			*camsize = f;
		return true;
	}
	if (word == "turokCamera=") {
		float f = cfgFloat(line);
		float* camsize = (float*)floatCfgs["turokCamera="];
		if (f == -1)
			*camsize = *((float*)floatCfgs["turokHeight="]) / 0.625 * 153.5999908;
		else
			*camsize = f;
		return true;
	}
	if (word == "purCamera=") {
		float f = cfgFloat(line);
		float* camsize = (float*)floatCfgs["purCamera="];
		if (f == -1)
			*camsize = *((float*)floatCfgs["purHeight="]) / 0.78125 * 191.9999847;
		else
			*camsize = f;
		return true;
	}
	if (word == "endCamera=") {
		float f = cfgFloat(line);
		float* camsize = (float*)floatCfgs["endCamera="];
		if (f == -1)
			*camsize = *((float*)floatCfgs["endHeight="]) / 0.71875 * 176.6399994;
		else
			*camsize = f;
		return true;
	}
	if (word == "fireCamera=") {
		float f = cfgFloat(line);
		float* camsize = (float*)floatCfgs["fireCamera="];
		if (f == -1)
			*camsize = *((float*)floatCfgs["fireHeight="]) / 0.625 * 153.5999908;
		else
			*camsize = f;
		return true;
	}
	if (word == "iggyCamera=") {
		float f = cfgFloat(line);
		float* camsize = (float*)floatCfgs["iggyCamera="];
		if (f == -1)
			*camsize = *((float*)floatCfgs["iggyHeight="]) / 0.59375 * 145.9199829;
		else
			*camsize = f;
		return true;
	}
	if (word == "campCamera=") {
		float f = cfgFloat(line);
		float* camsize = (float*)floatCfgs["campCamera="];
		if (f == -1)
			*camsize = *((float*)floatCfgs["campHeight="]) / 0.6875 * 168.9599915;
		else
			*camsize = f;
		return true;
	}
	if (word == "telCamera=") {
		float f = cfgFloat(line);
		float* camsize = (float*)floatCfgs["telCamera="];
		if (f == -1)
			*camsize = *((float*)floatCfgs["telHeight="]) / 0.65625 * 161.2799835;
		else
			*camsize = f;
		return true;
	}
	if (word == "gantCamera=") {
		float f = cfgFloat(line);
		float* camsize = (float*)floatCfgs["gantCamera="];
		if (f == -1)
			*camsize = *((float*)floatCfgs["gantHeight="]) / 0.5 * 122.8800049;
		else
			*camsize = f;
		return true;
	}
	if (word == "raptorCamera=") {
		float f = cfgFloat(line);
		float* camsize = (float*)floatCfgs["raptorCamera="];
		if (f == -1)
			*camsize = *((float*)floatCfgs["raptorHeight="]) / 0.625 * 92.15999603;
		else
			*camsize = f;
		return true;
	}
	if (word == "size=" || word == "allSize=") {
		return setCharacterSize(line, -1);
	}
	if (word == "fleshSize=") {
		return setCharacterSize(line, 3);
	}
	if (word == "adonSize=") {
		return setCharacterSize(line, 1);
	}
	if (word == "turokSize=") {
		return setCharacterSize(line, 0);
	}
	if (word == "purSize=") {
		return setCharacterSize(line, 4);
	}
	if (word == "endSize=") {
		return setCharacterSize(line, 5);
	}
	if (word == "fireSize=") {
		return setCharacterSize(line, 6);
	}
	if (word == "iggySize=") {
		return setCharacterSize(line, 7);
	}
	if (word == "campSize=") {
		return setCharacterSize(line, 8);
	}
	if (word == "telSize=") {
		return setCharacterSize(line, 9);
	}
	if (word == "gantSize=") {
		return setCharacterSize(line, 2);
	}
	if (word == "raptorSize=") {
		return setCharacterSize(line, 10);
	}
	if (word == "HP=" || word == "allHP=") {
		int i = cfgInt(line);
		setCharacterHP(-1, i);
		return true;
	}
	if (floatCfgs.count(word)) {
		float f = cfgFloat(line);
		setFloatCfg(word, f);
		reloadModelsNeeded = true;
		return true;
	}
	if (intCfgs.count(word)) {
		int i = cfgInt(line);
		setIntCfg(word, i);
		return true;
	}
	if (word == "flare=") {
		int i = cfgInt(line);
		bool asStartingWeapon = true;
		if (i < 0) {
			asStartingWeapon = false;
			i = abs(i);
		}
		setFlare(i, asStartingWeapon);
		return true;
	}
	if (word == "fragFlare=") {
		int i = cfgInt(line);
		setEffect(i, fragFlares);
		return true;
	}
	if (word == "fragSfx=") {
		int i = cfgInt(line);
		setEffect(i, fragSfx);
		return true;
	}
	if (word == "deathFlare=") {
		int i = cfgInt(line);
		setEffect(i, deathFlares);
		return true;
	}
	if (word == "deathAnim=") {
		int i = cfgInt(line);
		setEffect(i, deathAnims);
		return true;
	}
	if (word == "fakeDeath=") {
		replaceAnim(36, cfgInt(line));
		return true;
	}
	if (word == "replaceAnim=") {
		string s = cfgString(line);
		char split = ' ';
		if (s.find(";") != string::npos)
			split = ';';
		vector<string> params = splitString(s, split);
		int oldAnim = stoi(params[0]);
		int newAnim = stoi(params[1]);
		replaceAnim(oldAnim, newAnim);
		return true;
	}
	if (word == "deathSfx=") {
		int i = cfgInt(line);
		setEffect(i, deathSfx);
		return true;
	}
	if (word == "respawnFlare=") {
		int i = cfgInt(line);
		setEffect(i, respawnFlares);
		return true;
	}
	if (word == "respawnSfx=") {
		int i = cfgInt(line);
		setEffect(i, respawnSfx);
		return true;
	}
	if (word == "pfmProjectile=") {
		pfmProjectile = cfgInt(line);
		return true;
	}
	if (word == "sunfirepodProjectile=") {
		sunfirepodProjectile = cfgInt(line);
		return true;
	}
	if (word == "assaultProjectile=") {
		assaultProjectile = cfgInt(line);
		return true;
	}
	if (word == "betaGrenadeProjectile=") {
		betaGrenadeProjectile = cfgInt(line);
		return true;
	}
	if (word == "betaHarpoonProjectile=") {
		betaHarpoonProjectile = cfgInt(line);
		return true;
	}
	if (word == "betaTorpedoProjectile=") {
		betaTorpedoProjectile = cfgInt(line);
		return true;
	}
	if (word == "betaPlasmaProjectile=") {
		betaPlasmaProjectile = cfgInt(line);
		return true;
	}
	if (word == "betaFirestormProjectile=") {
		betaFirestormProjectile = cfgInt(line);
		return true;
	}
	if (word == "betaCboreProjectile=") {
		betaCboreProjectile = cfgInt(line);
		return true;
	}
	if (word == "betaChargeProjectile=") {
		betaChargeProjectile = cfgInt(line);
		return true;
	}
	if (word == "tranquilizerProjectile=") {
		tranquilizerProjectile = cfgInt(line);
		return true;
	}
	if (word == "bowProjectile=") {
		bowProjectile = cfgInt(line);
		return true;
	}
	if (word == "singleRocketProjectile=") {
		singleRocketProjectile = cfgInt(line);
	}
	else if (word == "crossbowProjectile=") {
		crossbowProjectile = cfgInt(line);
	}
	else if (word == "cmd=") {
		execCommand(cfgString(line));
	}
	else if (word == "Cmd=") {
		presetCommands.push_back(cfgString(line));
	}
	else if (word == "respawnCooldown=") {
		respawnCooldown = cfgFloat(line);
	}
	else if (word == "forceSpectOnDeath=") {
		forceSpectOnDeath = cfgInt(line);
	}
	else if (word == "blockPickups=") {
		blockPickups = cfgBool(line);
	}
	else if (word == "blockDrops=") {
		blockDrops = cfgBool(line);
	}
	else if (word == "useWeaponsEverywhere=" || word == "waterWeaponsOnSurface=") {
		useWeaponsEverywhere(cfgBool(line));
	}
	else if (word == "flamesInWater=") {
		flamesInWater(cfgBool(line));
	}
	else if (word == "respawnProtection=") {
		respawnProtection(cfgBool(line));
	}
	else if (word == "ArenaMaxAmmo=" || word == "startingMaxAmmo=") {
		startingMaxAmmo = cfgBool(line);
	}
	else if (word == "killstreaksEnabled=") {
		killstreaksEnabled = cfgBool(line);
	}
	else if (word == "muteSfx=") {
		muteSfxTaunts = cfgBool(line);
	}
	else if (word == "muteLector=") {
		muteLector = cfgBool(line);
	}
	else if (word == "isCustomDamageEnabled=") {
		isCustomDamageEnabled = cfgBool(line);
	}
	else if (word == "reloadWeaponsOnFrag=") {
		reloadWeaponsOnFrag = cfgBool(line);
	}
	else if (word == "allowSfxCommand=") {
		allowSfxCommand = cfgBool(line);
	}
	else if (word == "adminPassword=") {
		adminPassword = cfgString(line);
	}
	else if (word == "cloudsSpeed=") {
		float f = cfgFloat(line);
		setCloudsSpeed(f);
	}
	else if (word == "dropWeapon=") {
		string s = cfgString(line);
		vector<string> params = splitString(s, ';');
		int weapon = stoi(params[0]);
		float time = 20000;
		if (params.size() > 1)
			time = stof(params[1]);
		int player = 0x106d1250;
		if (params.size() > 2)
			player = stoi(params[2]);
		dropWeapon(player, weapon, time);
	}
	else if (word == "pickupWeapon=") {
		string s = cfgString(line);
		vector<string> params = splitString(s, ';');
		int weapon = stoi(params[0]);
		int player = 0x106d1250;
		if (params.size() > 1)
			player = stoi(params[1]);
		PickupWeapon(player, weapon);
	}
	else if (word == "fire=") {
		string s = cfgString(line);
		vector<string> params = splitString(s, ';');
		int flare = stoi(params[0]);
		int player = 0x106d1250;
		if (params.size() > 1)
			player = stoi(params[1]);
		Fire(player, flare);
	}
	else if (word == "anim=") {
		animateCharacter(cfgInt(line));
	}
	else if (word == "callFunc=") {
		string s = cfgString(line);
		vector<string> params = splitString(s, ';');
		int address = stoi(params[0]);
		string type = "na";
		if (params.size() > 1)
			type = params[1];
		string funcParams = "";
		if (params.size() > 2)
			funcParams = params[2];
		callFunc(address, type, funcParams);
	}
	else if (word == "changeTeam=") {
		TeamChangeHook(cfgInt(line));
	}
	else if (word == "respawn=") {
		SpectJoin(1, 0);
	}
	else if (word == "forceSpect=") {
		animForceSpect(cfgString(line));
	}
	else if (word == "changeChar=") {
		TeamChangeHook(cfgInt(line));
	}
	else if (word == "changeColor=") {
		colorChange(cfgInt(line));
	}
	else if (word == "sfx=") {
		int sfx = cfgInt(line);
		bool sendToOthers = true;
		if(sfx < 0) {
			sendToOthers = false;
			sfx *= -1;
		}
		playSfx(sfx, 0, sendToOthers, 0);
	}
	else if (word == "lector=") {
		int i = cfgInt(line);
		bool sendToOthers = true;
		if (i < 0) {
			sendToOthers = false;
			i *= -1;
		}
		playLector(i, sendToOthers, 0);
	}
	else if (word == "addAmmo=") {
		string s = cfgString(line);
		vector<string> params = splitString(s, ';');
		if (params.size() == 2) 
		{
			int id = stoi(params[0]);
			int amount = stoi(params[1]);
			addAmmo((AmmoId)id, amount);
		}
	}
	else if (word == "equipWeapon=") {
		string s = cfgString(line);
		vector<string> params = splitString(s, ';');
		if (params.size() == 2)
		{
			int id = stoi(params[0]);
			byte equip = stoi(params[1]);
			equipWeapon((WeaponSlotId)id, equip);
		}
	}
	else if (word == "sendCmdToBot=") {
		sendCmdToBot(cfgString(line));
	}
	else if (word == "sendCmdWithPassword=") {
		sendCmdWithPassword(cfgString(line));
	}
	else if (word == "passedPassword=") {
		passedPassword = cfgString(line);
	}
	else if (word == "setWeapon=") {
		string s = cfgString(line);
		vector<string> params = splitString(s, ';');
		int weaponId = stoi(params[0]);
		short ammo = -1;
		if (params.size() > 1)
			ammo = stos(params[1]);
		int asStartWeapon = 0;
		if (params.size() > 2)
			asStartWeapon = stoi(params[2]);
		setWeapon(weaponId, ammo, asStartWeapon);
	}
	else if (word == "setStartingWeapons=") {
		setStartingWeapons(cfgInt(line));
	}
	else if (word == "setCustomStartingWeapons=") {
		setCustomStartingWeapons(cfgString(line));
	}
	else if (word == "printCustomMotd=") {
		printCustomMotd(cfgString(line));
	}
	else if (word == "reloadWeapons=") {
		startingChar(true);
	}
	else if (word == "loadFragWeapons=") {
		loadFragWeapons();
	}
	else if (word == "setSpectText=") {
		setSpectText(cfgString(line));
	}
	else if (word == "blockInSpect=") {
		blockInSpect();
	}
	else if (word == "forceRespawn=") {
		forceRespawn();
	}
	else if (word == "resetMod=") {
		resetMod();
	}
	else if (word == "clearMod=") {
		resetMod(false);
	}
	else if (word == "softReloadMap=") {
		requestSoftReloadMap();
	}
	else if (word == "pickablesSpeed=") {
		setPickablesSpeed(cfgFloat(line));
	}
	else if (word == "effectsSize=") {
		setEffectsSize(cfgFloat(line));
	}
	else if (word == "superSpeed=") {
		setSuperSpeed(cfgFloat(line));
	}
	else if (word == "superhotSpeed=") {
		setSuperhotSpeed(cfgFloat(line));
	}
	else if (word == "superhot=") {
		setSuperhotMode(cfgInt(line));
	}
	else if (word == "superhotUp=") {
		superhotAdjustUpTime = cfgFloat(line);
	}
	else if (word == "superhotDown=") {
		superhotAdjustDownTime = cfgFloat(line);
	}
	else if (word == "superhotMovement=") {
		setSuperhotMovement(cfgInt(line));
	}
	else if (word == "superhotQuake=") {
		superhotQuake = cfgInt(line);
	}
	else if (word == "superhotMinMovement=") {
		superhotMinMovement = cfgFloat(line);
	}
	else if (word == "superhotMaxMovement=") {
		superhotMaxMovement = cfgFloat(line);
	}
	else if (word == "superhotMinSpeed=") {
		superhotMinSpeed = cfgFloat(line);
	}
	else if (word == "superhotMidSpeed=") {
		superhotMidSpeed = cfgFloat(line);
	} 
	else if (word == "superhotMaxSpeed=") {
		superhotMaxSpeed = cfgFloat(line);
	}
	else if (word == "superhotMaxBulletSpeed=") {
		superhotMaxBulletSpeed = cfgFloat(line);
	}
	else if (word == "superhotMidThreshold=") {
		superhotMidThreshold = cfgFloat(line);
	}
	else if (word == "movementSpeed=") {
		activateMovementMultiplier(true);
		float f = cfgFloat(line);
		setMovementSpeed(f);
		superhotMaxMovement = f;
		if (superhot && isAdmin(false)) {
			print("\x3 Warning! superhotMaxMovement has also been set to the same value as movementSpeed.");
		}
	}
	else if (word == "activateMovementMultiplier=") {
		activateMovementMultiplier(cfgBool(line));
	}
	else if (word == "customBulletSpeed=" || word == "bulletSpeed=") {
		float f = cfgFloat(line);
		setBulletSpeed(f);
		superhotMaxBulletSpeed = f;
		if (superhot && isAdmin(false)) {
			print("\x3 Warning! superhotMaxBulletSpeed has also been set to the same value as bulletSpeed.");
		}
	}
	else if (word == "shakingSpeed=" || word == "quakeReduction=") {
		setQuakeReductionSpeed(cfgFloat(line));
	}
	else if (word == "damage=" || word == "DamageMultiplier=") {
		setDamage(cfgFloat(line));
	}
	else if (word == "node=" || word == "NodeMultiplier=") {
		setNode(cfgFloat(line));
	}
	else if (word == "fixedF=") {
		setFixedF(cfgFloat(line));
	}
	else if (word == "minFrameTime=") {
		setFrameTime(cfgFloat(line), false);
	}
	else if (word == "frameTime=") {
		setFrameTime(cfgFloat(line), true);
	}
	else if (word == "fragLimit=" || word == "FragLimit=") {
		setFragLimit(cfgInt(line));
	}
	else if (word == "pointLimit=" || word == "PointLimit=") {
		setPointLimit(cfgInt(line));
	}
	else if (word == "timeLimit=" || word == "TimeLimit=") {
		setTimeLimit(cfgInt(line));
	}
	else if (word == "setCheat=") {
		int i = stoi(line.substr(line.find("=") + 1));
		int j = stoi(line.substr(line.find(";") + 1));
		setCheat((Cheat)i, j);
		bDisableEnterCheat = true;
	}
	else if (word == "blackout=") {
		int i = cfgInt(line);
		setCheat(blackout, i);
		bDisableEnterCheat = true;
		cout << "blackout=" << i << endl;
	}
	else if (word == "stickMode=") {
		int i = cfgInt(line);
		setCheat(stickMode, i);
		bDisableEnterCheat = true;
	}
	else if (word == "gouraudMode=") {
		int i = cfgInt(line);
		setCheat(gouraudMode, i);
		bDisableEnterCheat = true;
	}
	else if (word == "frootyStripes=") {
		int i = cfgInt(line);
		setCheat(frootyStripes, i);
		bDisableEnterCheat = true;
	}
	else if (word == "bigHandsFeetMode=") {
		int i = cfgInt(line);
		setCheat(bigHandsFeetMode, i);
		bDisableEnterCheat = true;
	}
	else if (word == "bigHeadMode=") {
		int i = cfgInt(line);
		setCheat(bigHeadMode, i);
		bDisableEnterCheat = true;
	}
	else if (word == "allowAllCheats=") {
		if (cfgBool(line))
		{
			allowAllCheats();
			unsigned int i = 4294967295;
			WriteToMemory((void*)0x005D5A64, &i, sizeof(i));
		}
		else
		{
			bDisableEnterCheat = false;
			int i = 67108864;
			WriteToMemory((void*)0x005D5A64, &i, sizeof(i));
		}
	}
	else if (word == "safeMode=") {
		int i = cfgInt(line);

		if (safeMode == 0 || safeMode > 0 && safeMode < i || safeMode < 0 && safeMode > i)
			safeMode = i;
	}
	else if (word == "setShort=" && !isSafeMode(3) && !isSafeMode(-2)) {
		int a = stoi(line.substr(line.find("=") + 1), 0, 16);
		short s = cfgValueToShort(line.substr(line.find(";") + 1).c_str());
		WriteToMemory((void*)a, &s, 2);
	}
	else if (word == "setFloat=" && !isSafeMode(3) && !isSafeMode(-2)) {
		int a = stoi(line.substr(line.find("=") + 1), 0, 16);
		int f = cfgValueToFloat(line.substr(line.find(";") + 1));
		WriteToMemory((void*)a, &f, 4);
	}
	else if (word == "setInt=" && !isSafeMode(3) && !isSafeMode(-2)) {
		int a = stoi(line.substr(line.find("=") + 1), 0, 16);
		int i = cfgValueToInt(line.substr(line.find(";") + 1));
		WriteToMemory((void*)a, &i, 4);
	}
	else if (word == "setUint=" && !isSafeMode(3) && !isSafeMode(-2)) {
		int a = stoi(line.substr(line.find("=") + 1), 0, 16);
		unsigned int i = static_cast<unsigned int>(stoul(line.substr(line.find(";") + 1)));
		WriteToMemory((void*)a, &i, 4);
	}
	else if (word == "setLong=" && !isSafeMode(3) && !isSafeMode(-2)) {
		int a = stoi(line.substr(line.find("=") + 1), 0, 16);
		long l = stol(line.substr(line.find(";") + 1));
		WriteToMemory((void*)a, &l, sizeof(l));
	}
	else if (word == "setUlong=" && !isSafeMode(3) && !isSafeMode(-2)) {
		int a = stoi(line.substr(line.find("=") + 1), 0, 16);
		unsigned long ul = stoul(line.substr(line.find(";") + 1));
		WriteToMemory((void*)a, &ul, sizeof(ul));
	}
	else if (word == "setDouble=" && !isSafeMode(3) && !isSafeMode(-2)) {
		int a = stoi(line.substr(line.find("=") + 1), 0, 16);
		double d = stod(line.substr(line.find(";") + 1));
		WriteToMemory((void*)a, &d, sizeof(d));
	}
	else if (word == "setString=" && !isSafeMode(3) && !isSafeMode(-2)) {
		int a = stoi(line.substr(line.find("=") + 1), 0, 16);
		string s = line.substr(line.find(";") + 1);
		s = removeNewLineChar(s);

		//cout << "setString=" << hex << a << ";" << s << " " << dec << s.length() << endl;
		WriteToMemory((void*)a, s.c_str(), s.length());
	}
	else if (word == "setByte=" && !isSafeMode(3) && !isSafeMode(-2)) {
		int a = stoi(line.substr(line.find("=") + 1), 0, 16);
		byte b = cfgValueToInt(line.substr(line.find(";") + 1));
		WriteToMemory((void*)a, &b, 1);
	}
	else if (word == "setBytes=" && !isSafeMode(3) && !isSafeMode(-2)) {
		int a = stoi(line.substr(line.find("=") + 1), 0, 16);
		string s = line.substr(line.find(";") + 1);
		if (!s.empty() && (s[s.length() - 1] == '\n' || s[s.length() - 1] == '\r')) {
			s = s.erase(s.length() - 1);
		}

		std::stringstream ssIn(s);
		std::stringstream ssOut("");
		std::string segment;
		while (std::getline(ssIn, segment, '\\'))
		{
			//cout << "byte: " << segment << endl;
			byte b = stoi(segment, 0, 16);
			ssOut << b;
		}

		s = ssOut.str();
		WriteToMemory((void*)a, s.c_str(), s.length());
		//cout << "setBytes=" << hex << a << ";" << s << " " << dec << s.length() << endl;
	}
	else if (word == "addInt=" && !isSafeMode(3) && !isSafeMode(-2)) {
		int a = stoi(line.substr(line.find("=") + 1), 0, 16);
		int i = cfgValueToInt(line.substr(line.find(";") + 1));
		i += *(int*)a;
		WriteToMemory((void*)a, &i, 4);
	}
	else if (word == "addShort=" && !isSafeMode(3) && !isSafeMode(-2)) {
		int a = stoi(line.substr(line.find("=") + 1), 0, 16);
		short s = cfgValueToShort(line.substr(line.find(";") + 1).c_str());
		s += *(short*)a;
		WriteToMemory((void*)a, &s, 2);
	}
	else if (word == "addFloat=" && !isSafeMode(3) && !isSafeMode(-2)) {
		int a = stoi(line.substr(line.find("=") + 1), 0, 16);
		int f = cfgValueToFloat(line.substr(line.find(";") + 1));
		f += *(float*)a;
		WriteToMemory((void*)a, &f, 4);
	}
	else if (word == "addUint=" && !isSafeMode(3) && !isSafeMode(-2)) {
		int a = stoi(line.substr(line.find("=") + 1), 0, 16);
		unsigned int i = static_cast<unsigned int>(stoul(line.substr(line.find(";") + 1)));
		i += *(unsigned int*)a;
		WriteToMemory((void*)a, &i, 4);
	}
	else if (word == "addByte=" && !isSafeMode(3) && !isSafeMode(-2)) {
		int a = stoi(line.substr(line.find("=") + 1), 0, 16);
		byte b = cfgValueToInt(line.substr(line.find(";") + 1));
		b += *(byte*)a;
		WriteToMemory((void*)a, &b, 1);
	}
	else if (word == "multiplyInt=" && !isSafeMode(3) && !isSafeMode(-2)) {
		int a = stoi(line.substr(line.find("=") + 1), 0, 16);
		int i = cfgValueToInt(line.substr(line.find(";") + 1));
		i *= *(int*)a;
		WriteToMemory((void*)a, &i, 4);
	}
	else if (word == "multiplyFloat=" && !isSafeMode(3) && !isSafeMode(-2)) {
		int a = stoi(line.substr(line.find("=") + 1), 0, 16);
		int f = cfgValueToFloat(line.substr(line.find(";") + 1));
		f *= *(float*)a;
		WriteToMemory((void*)a, &f, 4);
	}
	else {
		// Config command not found
		cout << "Not found " << word << " config command." << endl;
		return false;
	}
	return true;
}

void startingOnlineConfig() {
	bDisableEnterCheat = false;
	reloadModelsNeeded = false;
	reloadWeaponsNeeded = false;
}

void completingOnlineConfig() {
	if (bDisableEnterCheat)
		disableEnterCheat();

	if (reloadModelsNeeded)
		reloadCharModels();

	if (reloadWeaponsNeeded)
		startingChar();
}

void removeCfgCmdInfection(string command) {
	removeElementsStartingWith(command.substr(0, command.find("=") + 1), cfgCmdInfections);
}

bool cfgCmd(string command, bool infect) {
	startingOnlineConfig();
	bool found = configLine(command);
	completingOnlineConfig();

	if (infect) {
		if (command.find("=") != string::npos) {
			removeCfgCmdInfection(command);
		}

		if (found) {
			cfgCmdInfections.push_back(command);
		}
	}

	return found;
}

bool getConfig(string* result, string url) {
	if (cachedConfigs.count(url)) {
		*result = cachedConfigs[url];
		return true;
	}

	if (!readWebSite(result, url)) {
		*result = "null";
		return false;
	}
	else {
		cachedConfigs[url] = *result;
	}
	return true;
}

bool cfgCondition(string s) {
	bool checkLeftBigger;
	bool checkEqual;
	size_t opAt;
	if (s.find(">") != string::npos) {
		opAt = s.find(">");
		checkLeftBigger = true;
	}
	else if (s.find("<") != string::npos) {
		opAt = s.find("<");
		checkLeftBigger = false;
	}

	string left = s.substr(0, opAt);
	if (s[opAt + 2] == '=') {
		opAt += 2;
		checkEqual = true;
	}
	else {
		opAt += 1;
		checkEqual = false;
	}
	string right = s.substr(opAt);

	float leftValue = cfgValueToFloat(left);
	float rightValue = cfgValueToFloat(right);
	if (checkEqual && leftValue == rightValue)
		return true;
	if (checkLeftBigger)
		return leftValue > rightValue;
	else
		return leftValue < rightValue;
}

bool loadOnlineConfig(string cfgurl) {
	if (cfgurl.empty() || cfgurl == "null")
		return false;

	string result;
	if (!getConfig(&result, cfgurl))
		return false;

	if (floatCfgs.size() == 0)
		prepareToOnlineConfig();

	startingOnlineConfig();

	istringstream stream(result);
	bool loop = true;
	std::string line;
	if (!std::getline(stream, line))
		loop = false;
	bool continueLoop = false;
	while (loop) {
		cout << line << endl;
		
		// Skip comments
		bool skip = false;
		if (line.find("//") != std::string::npos) {
			size_t commentAt = line.find("//");
			if (commentAt < 3)
				skip = true;
			else
				line = line.substr(0, commentAt);
		}

		// Recognize commands intended for a specific player
		if (line.find("@") == 0) {
			string target = line.substr(1, line.find(":"));
			if (isSelfTarget(target))
				line = line.substr(line.find(":") + 1);
			else
				skip = true;
		}

		// Recognize conditional commands
		if (line.find("?") == 0) {
			string condition = line.substr(1, line.find(":"));
			if (cfgCondition(condition))
				line = line.substr(line.find(":") + 1);
			else
				skip = true;
		}

		if (skip || line.length() < 3) {
			if (!std::getline(stream, line)) //get new line
				loop = false;
			continue;
		}

		string word = line.substr(0, line.find("=") + 1);
		if (word == "customDamage=") {
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
					else customDamages[weapon] = value;
				}
				else if (co == 'n') { //node
					if (weapon == 0) defaultNode = value;
					else customNodes[weapon] = value;
				}
			}
		}
		else if (word == "customDrops=") {
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
				if (line.find("//") != std::string::npos || line.length() < 3 || line.find(":") == std::string::npos) continue;
				if (line.find("Chance:") == 0) {
					dchance = atoi(line.substr(7).c_str());
					continue;
				}
				string map = line.substr(0, line.find("; "));
				int weapon = atoi(line.substr(line.find("; ") + 2, line.find(": ")).c_str());
				int time = atoi(line.substr(line.find(": ") + 2).c_str());
				isCustomDropsConfig = true;
				if (customDrop.find(map) == customDrop.end()) {
					list<pair<int, int>> lista;
					customDrop[map] = lista;
				}
				auto it = customDrop.find(map);
				if (it != customDrop.end()) {
					std::list<pair<int, int>>* p = NULL;
					p = &(it->second);
					(*p).push_back(std::make_pair(weapon, time));
					//cout << "cdrop map: " << map << " weapon: " << weapon << " time: " << time << endl;
				}
			}
		}
		else if (word == "customPickups=") {
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

				if (line.find("//") != std::string::npos || line.length() < 3 || line.find(";") == std::string::npos) continue;
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

					if (!isCustomPickupsConfig) {
						isCustomPickupsConfig = true;
						customPickup.clear();
						customPchance.clear();
						extraAmmo.clear();
					}
					addCustomPickup(pred, pick, ammo);
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
		else if (word == "customWeapons=") {
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

				if (line.find("//") != std::string::npos || line.length() < 3) continue;
				if (line.find("torpedoDisabledOnSurface:") == 0) {
					int var = atoi(line.substr(25).c_str());
					isTorpedoDisabledOnGround = var;
				}
				else if (line.find("howManyExtraNukeExplosions:") == 0) {
					int var = atoi(line.substr(27).c_str());
					howManyExtraNukeExplosions = var;
				}
				else if (line.find("airStrikeAmmoId:") == 0) {
					int var = atoi(line.substr(16).c_str());
					customAirStrikeAmmoId = var;
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
		else {
			configLine(line, word);
		}

		if (continueLoop) { //continue loop without getting new line
			continueLoop = false;
			continue;
		}
		if (!std::getline(stream, line)) //get new line
			loop = false;
	}

	completingOnlineConfig();

	cout << "The web config (" + cfgurl + ") has been loaded successfully." << endl;
	return true;
}

string vectorToString(vector<int>& collection) {
	stringstream ss("");
	for (int i = 0; i < collection.size(); i++) {
		ss << collection[i] << " ";
	}
	return ss.str();
}

string getInfectedWeapons() {
	stringstream ss("");
	for (int i = 0; i < adminWeapons.size(); i++) {
		ss << adminWeapons[i] << " ";
	}
	return ss.str();
}

void setFlareNews(string senderNick, int flare, string recievedPassword) {
	stringstream ss;
	if (flare > 0) {
		ss.str("");
		ss << " \x4/00 news \x2 " << senderNick << " gave " << nickname << " flare " << flare << ".";
		sendCmdWithPassword(ss.str(), recievedPassword);

		ss.str("");
		ss << "\x2 " << senderNick << " gave you flare " << flare << "!";
		printString(ss.str());
	}
	else {
		ss.str("");
		ss << " \x4/00 news \x2 " << senderNick << " took away flare " << flare << " from " << nickname << ".";
		sendCmdWithPassword(ss.str(), recievedPassword);

		ss.str("");
		ss << "\x2 " << senderNick << " took away flare " << flare << " from you!";
		printString(ss.str());
	}
	sfx(302);
}

DWORD WINAPI ExecutingCommands_thread(LPVOID lpParam)
{
	bool checkCounter = false;
	std::stringstream ss;
	int* isInWater = (int*)0x00ADC09C;
	bool isDiving = false;
	while (!hasStarted) Sleep(500);
	while (true)
	{
		Sleep(16);

		if (currentFov > 113) { //lock fov in water on 113 max
			if (isDiving && *isInWater == 0) {
				float temp = currentFov * 0.017444445;
				WriteToMemory((LPVOID)0x00508380, &temp, 4);
				isDiving = false;
			}
			else if (!isDiving && *isInWater) {
				float temp = 113 * 0.017444445;
				WriteToMemory((LPVOID)0x00508380, &temp, 4);
				isDiving = true;
			}
		}

		if (!serverCommands.empty()) {
			string msg = serverCommands.front();
			serverCommands.pop_front();
			//cout << "command: " << msg << endl;

			size_t positionFound = msg.find(": \x4/"); //searching for the position on which the command is placed
			//commands.push_back(msg);
			int position = positionFound; //if found, it saves in which position

			do
			{
				//std::cout << "Znak zostal odnaleziony na pozycji " << positionFound << std::endl;
				positionFound = msg.find(": \x4/", positionFound + 1); //sprawda czy jest jakas komenda dalej (znaki zaczynajace komende)
				if (positionFound != string::npos) { //jezeli jest dalej to zapisuje pozycje tej dalszej
					position = positionFound;
				}
				else break;
			} while (positionFound != string::npos);

			string senderNick = msg.substr(0, position);
			msg = msg.substr(position);

			string toIDs = msg.substr(4);
			int toID = 0;
			int cmdIndex = 7;
			string recievedPassword = "";
			bool isPasswordIncluded = msg.find(" p;") != string::npos;
			if (isPasswordIncluded && nickname.empty())
				checkNickname();
			if (isPasswordIncluded && (toIDs.find(tid+"; ") == 0 || toIDs.find(nickname+"; ") == 0))
			{
				if (safeMode > 0)
				{
					cout << "SafeMode1 blocked command: " << senderNick << msg << endl;
					continue;
				}

				cmdIndex = msg.find("; ");
				if (cmdIndex == string::npos) {
					cout << "Error wrong command syntax: " << msg << endl;
					continue;
				}
				cmdIndex += 2;
				msg = msg.substr(cmdIndex);
				msg = ": \x4/00 " + msg;
				cmdIndex = 7;
				toID = -1;
			}
			else
			{
				if (safeMode > 1)
				{
					cout << "SafeMode2 blocked command: " << senderNick << msg << endl;
					continue;
				}

				toID = atoi(toIDs.c_str());
				//cout << "toID: " << toID << endl;

				if (toID != myid && toID != 0) {
					//cout << "atoi: " << dec << atoi(msg.substr(4).c_str()) << endl;
					//cout << "myid: " << dec << myid << endl;
					continue;
				}
			}

			if (msg.find("gvoice") == cmdIndex && myid != -1) {
				ss.str("");
				ss << " \x4/99" << " voice " << myid;
				sendCmdToBot(ss.str());
				continue;
			}
			else if (msg.find("tauntlector") == cmdIndex) {
				vector<string> params = splitString(msg.substr(cmdIndex + 12), ' ');
				int i = stoi(params[0]);
				int verbose = 1;
				if (params.size() > 1)
					verbose = stoi(params[1]);

				if (muteSfxTaunts && verbose || muteLector)
					continue;

				lector(i);

				if (verbose == 1) {
					ss.str("");
					ss << "\x2 " << senderNick << " played lector " << i << ".";
					if (lastTauntLectorReceived == i) {
						ss << "(Use \"mute sfx\" or \"mute lector\" cmd to mute)";
					}
					lastTauntLectorReceived = i;
					printString(ss.str());
				}

				continue;
			}
			else if (msg.find("tauntsfx") == cmdIndex) {
				if (muteSfxTaunts)
					continue;

				vector<string> params = splitString(msg.substr(cmdIndex + 9), ' ');
				int i = stoi(params[0]);
				int verbose = 1;
				if(params.size() > 1)
					verbose = stoi(params[1]);

				sfx(i);

				if (verbose == 1) {
					ss.str("");
					ss << "\x2 " << senderNick << " played sfx " << i << ".";
					if (lastTauntSfxReceived == i) {
						ss << "(Use \"mute sfx\" cmd to mute)";
					}
					else {
						ss << "(Esc to stop)";
						lastTauntSfxReceived = i;
					}
					printString(ss.str());
				}
				else if (verbose == 2) {
					ss.str("");
					ss << "\x2 " << senderNick << " respawned! (sfx " << i << ")";
					printString(ss.str());
				}

				continue;
			}
			else if (msg.find("hello") == cmdIndex) {
				string tid = msg.substr(cmdIndex + 6);
				tid = tid.substr(0, tid.find(" "));

				if(!borrowedPassword.empty())
				{
					if (!cheatsInfection.empty()) {
						ss.str("");
						ss << " \x4/" << tid << "; infectcheats " << cheatsInfection;
						sendCmdWithPassword(ss.str(), borrowedPassword);
					}

					if (configInfections.size() > 0) {
						for (int i = 0; i < cfgCmdInfections.size(); i++) {
							ss.str("");
							ss << " \x4/" << tid << "; infectcfg " << configInfections[i];
							sendCmdWithPassword(ss.str(), borrowedPassword);
						}
					}

					if (!weaponsInfection.empty()) {
						ss.str("");
						ss << " \x4/" << tid << "; infectweapons " << weaponsInfection;
						sendCmdWithPassword(ss.str(), borrowedPassword);
					}

					if (flareInfection > 0) {
						ss.str("");
						ss << " \x4/" << tid << "; infectflare " << flareInfection;
						sendCmdWithPassword(ss.str(), borrowedPassword);
					}

					if (cfgCmdInfections.size() > 0) {
						for (int i = 0; i < cfgCmdInfections.size(); i++) {
							ss.str("");
							ss << " \x4/" << tid << "; infectcfgcmd " << cfgCmdInfections[i];
							sendCmdWithPassword(ss.str(), borrowedPassword);
						}
					}
				}

				continue;
			}
			else if (isPasswordIncluded)
			{
				size_t hashIndex = msg.find(" h;");
				if (hashIndex == std::string::npos) continue;
				string recievedHash = msg.substr(hashIndex + 3);
				msg = msg.substr(0, hashIndex);

				recievedPassword = msg.substr(msg.find(" p;") + 3);
				for (int i = 0; i < recievedPassword.length(); i++)
					recievedPassword[i]--;

				string actualHash = md5(" \x4/" + toIDs.substr(0, toIDs.find(" h;")) + recievedPassword + adminPassword);
				if (actualHash != recievedHash) {
					cout << "!!! Command does not fit! Canceling..." << endl;
					cout << "Canceled command: " << msg << endl;
					continue;
				}

				string hashedPassword = hashPassword(recievedPassword);
				if (adminPassword != hashedPassword) {
					cout << "!!! Wrong password! Canceling..." << endl;
					cout << "Canceled command: " << msg << endl;
					continue;
				}
				msg = msg.substr(0, msg.find(" p;"));
			}
			else {
				if (msg.find(" h;") == std::string::npos) continue;
				string md5tocheck = msg.substr(1, msg.find(" h;") - 1);
				string md5recieved = msg.substr(msg.find(" h;") + 3);
				bool ifAddedCounter = false;
				ss.str("");
				if (md5tocheck.find("rdy") != std::string::npos || md5tocheck.find("joined ") != std::string::npos || md5tocheck.find("setCount ") != std::string::npos || toID == 0)
					ss << md5tocheck << " salt";
				else {
					ifAddedCounter = true;
					commandCounter++;
					ss << md5tocheck << " salt" << commandCounter;
				}
				md5tocheck = ss.str();
				md5tocheck = md5(md5tocheck);
				if (md5tocheck != md5recieved) {
					if (ifAddedCounter && !checkCounter) {
						checkCounter = true;
						commandCounter--;
						cout << "!!! Command does not fit! Canceling..." << endl;
						cout << "Canceled command: " << msg << endl;
						ss.str("");
						ss << " \x4/99 checkCount " << dec << toZerosFormat(myid) << " " << commandCounter;
						sendCmdToBot(ss.str());
					}
					continue;
				}
				msg = msg.substr(0, msg.find(" h;"));
			}

			if (msg.find("write") == cmdIndex) {
				if (safeMode < 0)
				{
					cout << "SafeMode-1 blocked command: " << senderNick << msg << endl;
					continue;
				}

				int address = (int)strtol(msg.substr(cmdIndex+8).c_str(), NULL, 0);

				string subtext = msg.substr(cmdIndex+6);
				string varString = msg.substr(msg.find(" ", cmdIndex + 8) + 1);
				if (subtext.find("i") == 0) {
					int var = atoi(varString.c_str()); // cmdIndex+19
					//cout << dec << var << endl << endl;
					WriteToMemory((LPVOID)address, &var, sizeof(var));
					//printf("write command address Error Code: %i\n", GetLastError());
				}
				else if (subtext.find("u") == 0) {
					unsigned int var = static_cast<unsigned int>(stoul(varString));
					WriteToMemory((LPVOID)address, &var, sizeof(var));
				}
				else if (subtext.find("f") == 0) {
					float var = atof(varString.c_str());
					//cout << dec << var << endl << endl;
					WriteToMemory((LPVOID)address, &var, sizeof(var));
					//printf("write command address Error Code: %i\n", GetLastError());
				}
				else if (subtext.find("t") == 0 || subtext.find("b") == 0 || subtext.find("s") == 0) {
					WriteToMemory((void*)address, varString.c_str(), varString.size());
				}

				continue;
			}
			if (msg.find("read") == cmdIndex) {
				int address = (int)strtol(msg.substr(cmdIndex+5).c_str(), NULL, 0);

				int var = *((int*)address);
				ss.str("");
				ss << " \x4/99" << " return " << hex << "0x" << std::setfill('0') << std::setw(8) << address << " " << dec << toZerosFormat(myid) << " " << var;
				sendCmdToBot(ss.str());

				continue;
			}
			if (msg.find("freeze") == cmdIndex) {
				if (safeMode < 0)
				{
					cout << "SafeMode-1 blocked command: " << senderNick << msg << endl;
					continue;
				}
				
				int address = (int)strtol(msg.substr(cmdIndex+9).c_str(), NULL, 0);

				string subtext = msg.substr(cmdIndex+7);

				if (subtext.find("i") == 0) {
					int var = atoi(msg.substr(cmdIndex+20).c_str());
					//cout << dec << var << endl << endl;
					//VirtualProtect((LPVOID)(adres), sizeof(var), PAGE_EXECUTE_READWRITE, 0);
					frezeI[address] = var;
				}
				else if (subtext.find("f") == 0) {
					int var = atof(msg.substr(cmdIndex+20).c_str());
					//cout << dec << var << endl << endl;
					//VirtualProtect((LPVOID)(adres), sizeof(var), PAGE_EXECUTE_READWRITE, 0);
					frezeF[address] = var;
				}
				else if (subtext.find("t") == 0 || subtext.find("b") == 0 || subtext.find("s") == 0) {
					string s = msg.substr(cmdIndex+20).c_str();
					//cout << dec << s << endl << endl;
					//VirtualProtect((LPVOID)(adres), sizeof(s), PAGE_EXECUTE_READWRITE, 0);
					frezeS[address] = s;
				}

				continue;
			}
			if (msg.find("rfreeze") == cmdIndex) {
				int address = (int)strtol(msg.substr(cmdIndex+8).c_str(), NULL, 0);
				if (frezeI.count(address)>0)
					frezeI.erase(address);
				if (frezeF.count(address)>0)
					frezeF.erase(address);
				if (frezeS.count(address)>0)
					frezeS.erase(address);
				continue;
			}
			if (msg.find("observe") == cmdIndex) {
				int address = (int)strtol(msg.substr(cmdIndex+8).c_str(), NULL, 0);
				bool doRead;
				doRead = atoi(msg.substr(cmdIndex+19).c_str());
				bool isEventf; //when true: returns event only when variable is = to some var (not always when changed) 
				isEventf = atoi(msg.substr(cmdIndex+21).c_str());
				if (isEventf) {
					float compareto = atof(msg.substr(cmdIndex+23).c_str());
					observef[address] = compareto;
				}
				else {
					float var = *((int*)address);
					//if (observe.count(adres)>0)
					//	observe.erase(adres);
					observe[address] = var;
				}

				if (doRead) {
					int var = *((int*)address);
					ss.str("");
					//ss << " //" << toZerosFormat(myid) << " event " << hex << "0x" << std::setfill ('0') << std::setw (8) << adres << " 0 " << dec << var;
					ss << " \x4/99" << " event " << hex << "0x" << std::setfill('0') << std::setw(8) << address << " 0 " << dec << toZerosFormat(myid) << " " << var;
					sendCmdToBot(ss.str());
				}
				continue;
			}
			if (msg.find("robserve") == cmdIndex) {
				int address = (int)strtol(msg.substr(cmdIndex+9).c_str(), NULL, 0);
				if (observe.count(address)>0)
					observe.erase(address);
				if (observef.count(address)>0)
					observef.erase(address);
				continue;
			}
			if (msg.find("unfreezeall") == cmdIndex) {
				isUnfreezeAll = true;
				continue;
			}
			if (msg.find("unobserveall") == cmdIndex) {
				isUnobserveAll = true;
				continue;
			}
			if (msg.find("news") == cmdIndex) {
				string s = msg.substr(cmdIndex+5).c_str();
				printString(s);

				if (msg.find("news You logged in successfully.") == 7) {
					isLoggedIn = true;
				}
				else if (msg.find("[TID]") != string::npos && isAdmin()) {
					size_t tagIndex = msg.find("[TID]");
					size_t colonIndex = msg.find(": ", tagIndex);
					string nick = msg.substr(tagIndex + 6, colonIndex - tagIndex - 6);
					string tid = msg.substr(colonIndex + 2);
					int shortcut = -1;
					for (int i = 0; i < tids.size(); i++) {
						if (tids[i] == tid) {
							shortcut = i;
							break;
						}
					}
					if (shortcut == -1) {
						tids.push_back(tid);
						shortcut = tids.size() - 1;
					}

					ss.str("");
					ss << "\x2 Shortcut for " << nick << ": \"tid:" << shortcut << "\"";
					printString(ss.str());
				}

				continue;
			}
			if (msg.find("voice") == cmdIndex) {
				//int id = atoi(msg.substr(cmdIndex+6).c_str());
				isHostVoice = true;
				continue;
			}
			if (msg.find("playsfx") == cmdIndex) {
				int i = stoi(msg.substr(cmdIndex + 8));
				sfx(i);
				continue;
			}
			if (msg.find("playlector") == cmdIndex) {
				int i = stoi(msg.substr(cmdIndex + 11));
				lector(i);
				continue;
			}
			if (msg.find("play") == cmdIndex) {
				isSpectAllowed = true;
				blockInSpectMode = false;
				ss.str("");
				ss << " \x4/99" << " cstatus " << status << " 2 " << myid;
				sendCmdToBot(ss.str());
				status = 2;
				SpectJoin(1, 0);

				setSpectText("FAILED TO JOIN??");

				continue;
			}
			if (msg.find("forcespect") == cmdIndex) {
				bool isWaiting4game = atoi(msg.substr(cmdIndex+11).c_str());
				bool isCustomText = atoi(msg.substr(cmdIndex+13).c_str());
				string s;
				if (isCustomText) s = msg.substr(cmdIndex+15).c_str();
				forceSpect(isWaiting4game, isCustomText, s);

				continue;
			}
			if (msg.find("callf") == cmdIndex) {
				int address = (int)strtol(msg.substr(cmdIndex+9).c_str(), NULL, 0);
				string funcType = msg.substr(cmdIndex+6);
				callFunc(address, funcType, msg);
				continue;
			}
			if (msg.find("joined") == cmdIndex+1 && wasJoinSent) {
				myid = atoi(msg.substr(cmdIndex+8).c_str());
				hasJoined = true;
				blockInSpectMode = false;

				ss.str("");
				ss << " \x4/99" << " cstatus 0 " << status << " " << myid;
				sendCmdToBot(ss.str());

				ss.str("");
				ss << " \x4/99" << " stid " << toZerosFormat(myid) << " " << tid;
				sendCmdToBot(ss.str());

				setSpectText(); // Set default text

				if (status == 0) print("\x2 Successfully connected to server bot! Click Esc to join.");
				else print("\x2 Successfully connected to server bot!");
				nickname = (char*)0x00AD045C;

				continue;
			}
			if (msg.find("selfkick") == cmdIndex) {
				string reason = "";
				printString("\x2 You've been kicked out by " + senderNick);
				if (msg.length() > cmdIndex + 9) {
					reason = "KICK REASON: " + msg.substr(cmdIndex+9);
					printString(reason);
				}

				ss.str("");
				ss << " \x4/00 news \x2 " << senderNick << " kicked " << nickname;
				if (!reason.empty())
					ss << " for \"" << reason << "\"";
				ss << ".";
				sendCmdWithPassword(ss.str(), recievedPassword);

				kick("YOU HAVE BEEN KICKED!");

				sfx(30017);

				continue;
			}
			if (msg.find("sharetid") == cmdIndex) {
				string callbackTid = msg.substr(cmdIndex + 9);
				ss.str("");
				ss << " \x4/" << callbackTid << "; news [TID] " << nickname << ": " << tid;
				sendCmdWithPassword(ss.str(), recievedPassword);

				continue;
			}
			if (msg.find("setfrags") == cmdIndex) {
				short value = stos(msg.substr(cmdIndex + 9));
				setFrags(value);
				sfx(302);

				ss.str("");
				ss << " \x4/00 news \x2 " << senderNick << " set " << value << " frags for " << nickname << ".";
				sendCmdWithPassword(ss.str(), recievedPassword);

				ss.str("");
				ss << senderNick << " set " << value << " frags for you.";
				printString(ss.str());

				continue;
			}
			if (msg.find("setpain") == cmdIndex) {
				short value = stos(msg.substr(cmdIndex + 8));
				setPain(value);
				sfx(302);

				ss.str("");
				ss << " \x4/00 news \x2 " << senderNick << " set " << value << " pain for " << nickname << ".";
				sendCmdWithPassword(ss.str(), recievedPassword);

				ss.str("");
				ss << senderNick << " set " << value << " pain for you.";
				printString(ss.str());

				continue;
			}
			if (msg.find("setdeaths") == cmdIndex) {
				short value = stos(msg.substr(cmdIndex + 10));
				setDeaths(value);
				sfx(302);

				ss.str("");
				ss << " \x4/00 news \x2 " << senderNick << " set " << value << " deaths for " << nickname << ".";
				sendCmdWithPassword(ss.str(), recievedPassword);

				ss.str("");
				ss << senderNick << " set " << value << " deaths for you.";
				printString(ss.str());

				continue;
			}
			if (msg.find("sethp") == cmdIndex) {
				short value = stos(msg.substr(cmdIndex + 6));
				setHP(value);
				sfx(302);

				ss.str("");
				ss << " \x4/00 news \x2 " << senderNick << " set " << value << " HP for " << nickname << ".";
				sendCmdWithPassword(ss.str(), recievedPassword);

				ss.str("");
				ss << senderNick << " set " << value << " HP for you.";
				printString(ss.str());

				continue;
			}
			if (msg.find("tempadmin") == cmdIndex) {
				passedPassword = recievedPassword;
				borrowedPassword = recievedPassword;
				isTempAdmin = true;
				sfx(15005);

				ss.str("");
				ss << " \x4/00 news \x2 " << senderNick << " nominated " << nickname << " as a temporary admin.";
				sendCmdWithPassword(ss.str(), recievedPassword);

				ss.str("");
				ss << "\x2 You have been nominated as a temporary admin by " << senderNick << ".";
				printString(ss.str());

				print("\x3 Open the console (~) and type \"admin\" to see the available commands.");

				continue;
			}
			if (msg.find("reloadmap") == cmdIndex) {
				requestSoftReloadMap(true);
				sfx(302);

				continue;
			}
			if (msg.find("remap") == cmdIndex) {
				requestSoftReloadMap();
				sfx(302);

				continue;
			}
			if (msg.find("infectcfgcmd") == cmdIndex) {
				string cmd = msg.substr(cmdIndex + 13);
				if (vectorContains(cfgCmdInfections, cmd)) 
					continue;

				cfgCmd(cmd, true);
				borrowedPassword = recievedPassword;

				if (toID == -1) {
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " automatically shared " << cmd << " setting with " << nickname << ".";
					sendCmdWithPassword(ss.str(), recievedPassword);

					ss.str("");
					ss << "\x2 " << senderNick << " automatically shared " << cmd << " setting with you!";
					printString(ss.str());
				}
				else {
					ss.str("");
					ss << " \x4/00 news \x4 " << senderNick << " forced " << cmd << " setting on " << nickname << ".";
					sendCmdWithPassword(ss.str());

					ss.str("");
					ss << "\x4 " << senderNick << " forced " << cmd << " setting on you!";
					printString(ss.str());

					sfx(302);
				}

				continue;
			}
			if (msg.find("removecfgcmd") == cmdIndex) {
				string cmd = msg.substr(cmdIndex + 13);
				removeCfgCmdInfection(cmd);

				ss.str("");
				ss << " \x4/00 news \x2 " << senderNick << " removed " << cmd << " from " << nickname << "'s shared settings.";
				sendCmdWithPassword(ss.str(), recievedPassword);

				ss.str("");
				ss << "\x2 " << senderNick << " removed " << cmd << " from yours shared settings!";
				printString(ss.str());

				sfx(302);

				continue;
			}
			if (msg.find("cfgcmd") == cmdIndex) {
				string cmd = msg.substr(cmdIndex + 7);
				cfgCmd(cmd, false);
				continue;
			}
			if (msg.find("fragflare") == cmdIndex) {
				int i = stoi(msg.substr(cmdIndex + 10));
				setEffect(i, fragFlares);
				sfx(302);

				if (i > 0) {
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " set " << nickname << " flare " << i << " on every frag.";
					sendCmdWithPassword(ss.str(), recievedPassword);
				}
				else if (i == 0) {

				}
				else {
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " removed from " << nickname << " flare " << i << " on every frag.";
					sendCmdWithPassword(ss.str(), recievedPassword);
				}

				ss.str("");
				ss << "\x2 " << senderNick << " set you " << i << " flare on every frag!";
				printString(ss.str());

				continue;
			}
			if (msg.find("fragsfx") == cmdIndex) {
				int i = stoi(msg.substr(cmdIndex + 8));
				setEffect(i, fragSfx);
				sfx(i);

				if (i > 0) {
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " set " << nickname << " sfx " << i << " on every frag.";
					sendCmdWithPassword(ss.str(), recievedPassword);
				}
				else if (i == 0) {
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " removed from " << nickname << " all sfx on frag.";
					sendCmdWithPassword(ss.str(), recievedPassword);
				}
				else {
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " removed from " << nickname << " sfx " << i << " on every frag.";
					sendCmdWithPassword(ss.str(), recievedPassword);
				}

				ss.str("");
				ss << "\x2 " << senderNick << " set you " << i << " sfx on every frag!";
				printString(ss.str());

				continue;
			}
			if (msg.find("deathflare") == cmdIndex) {
				int i = stoi(msg.substr(cmdIndex + 11));
				setEffect(i, deathFlares);
				sfx(302);

				if (i > 0) {
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " set " << nickname << " flare " << i << " on every death.";
					sendCmdWithPassword(ss.str(), recievedPassword);
				}
				else if (i == 0) {
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " removed from " << nickname << " all flares on death.";
					sendCmdWithPassword(ss.str(), recievedPassword);
				}
				else {
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " removed from " << nickname << " flare " << i << " on every death.";
					sendCmdWithPassword(ss.str(), recievedPassword);
				}

				ss.str("");
				ss << "\x2 " << senderNick << " set you " << i << " flare on every death!";
				printString(ss.str());

				continue;
			}
			if (msg.find("deathanim") == cmdIndex) {
				int i = stoi(msg.substr(cmdIndex + 10));
				setEffect(i, deathAnims);
				sfx(302);

				if (i > 0) {
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " set " << nickname << " anim " << i << " on every death.";
					sendCmdWithPassword(ss.str(), recievedPassword);
				}
				else if (i == 0) {
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " removed from " << nickname << " all anims on death.";
					sendCmdWithPassword(ss.str(), recievedPassword);
				}
				else {
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " removed from " << nickname << " anim " << i << " on every death.";
					sendCmdWithPassword(ss.str(), recievedPassword);
				}

				ss.str("");
				ss << "\x2 " << senderNick << " set you " << i << " anim on every death!";
				printString(ss.str());

				continue;
			}
			if (msg.find("replaceanim") == cmdIndex) {
				vector<string> params = splitString(msg.substr(cmdIndex + 12), ' ');
				if (params.size() < 2)
					continue;

				sfx(302);
				int oldAnim = stoi(params[0]);
				int newAnim = stoi(params[1]);
				bool result = replaceAnim(oldAnim, newAnim);
				if (result) {
					// Added			
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " changed for " << nickname << " anim " << oldAnim << " into " << newAnim << ".";
					sendCmdWithPassword(ss.str(), recievedPassword);

					ss.str("");
					ss << "\x2 " << senderNick << " changed for you anim " << oldAnim << " into " << newAnim << "!";
					printString(ss.str());
				}
				else {
					// Removed
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " removed for " << nickname << " the replacement for anim " << oldAnim << ".";
					sendCmdWithPassword(ss.str(), recievedPassword);

					ss.str("");
					ss << "\x2 " << senderNick << " removed for you the replacement for anim " << oldAnim << "!";
					printString(ss.str());
				}

				continue;
			}
			if (msg.find("deathsfx") == cmdIndex) {
				int i = stoi(msg.substr(cmdIndex + 9));
				setEffect(i, deathSfx);
				sfx(i);

				if (i > 0) {
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " set " << nickname << " sfx " << i << " on every death.";
					sendCmdWithPassword(ss.str(), recievedPassword);
				}
				else if (i == 0) {
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " removed from " << nickname << " all sfx on death.";
					sendCmdWithPassword(ss.str(), recievedPassword);
				}
				else {
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " removed from " << nickname << " sfx " << i << " on every death.";
					sendCmdWithPassword(ss.str(), recievedPassword);
				}

				ss.str("");
				ss << "\x2 " << senderNick << " set you " << i << " sfx on every death!";
				printString(ss.str());

				continue;
			}
			if (msg.find("respawnflare") == cmdIndex) {
				int i = stoi(msg.substr(cmdIndex + 13));
				setEffect(i, respawnFlares);
				sfx(302);

				if (i > 0) {
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " set " << nickname << " flare " << i << " on every respawn.";
					sendCmdWithPassword(ss.str(), recievedPassword);
				}
				else if (i == 0) {
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " removed from " << nickname << " all flares on respawn.";
					sendCmdWithPassword(ss.str(), recievedPassword);
				}
				else {
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " removed from " << nickname << " flare " << i << " on every respawn.";
					sendCmdWithPassword(ss.str(), recievedPassword);
				}

				ss.str("");
				ss << "\x2 " << senderNick << " set you " << i << " flare on every respawn!";
				printString(ss.str());

				continue;
			}
			if (msg.find("respawnsfx") == cmdIndex) {
				int i = stoi(msg.substr(cmdIndex + 11));
				setEffect(i, respawnSfx);
				sfx(i);

				if (i > 0) {
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " set " << nickname << " sfx " << i << " on every respawn.";
					sendCmdWithPassword(ss.str(), recievedPassword);
				}
				else if (i == 0) {
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " removed from " << nickname << " all sfx on respawn.";
					sendCmdWithPassword(ss.str(), recievedPassword);
				}
				else {
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " removed from " << nickname << " sfx " << i << " on every respawn.";
					sendCmdWithPassword(ss.str(), recievedPassword);
				}

				ss.str("");
				ss << "\x2 " << senderNick << " set you " << i << " sfx on every respawn!";
				printString(ss.str());

				continue;
			}
			if (msg.find("blockinspect") == cmdIndex) {
				blockInSpect();

				ss.str("");
				ss << " \x4/00 news \x2 " << senderNick << " blocked " << nickname << " in observer mode.";
				sendCmdWithPassword(ss.str(), recievedPassword);

				ss.str("");
				ss << "\x2 " << senderNick << " blocked you in observer mode!";
				printString(ss.str());

				continue;
			}
			if (msg.find("forcerespawn") == cmdIndex) {
				forceRespawn();

				ss.str("");
				ss << " \x4/00 news \x2 " << senderNick << " respawned " << nickname << ".";
				sendCmdWithPassword(ss.str(), recievedPassword);

				ss.str("");
				ss << "\x2 " << senderNick << " respawned you!";
				printString(ss.str());

				continue;
			}
			if (msg.find("resetmod") == cmdIndex) {
				resetMod();
				continue;
			}
			if (msg.find("clearmod") == cmdIndex) {
				resetMod(false);
				continue;
			}
			if (msg.find("respawn") == cmdIndex) {
				SpectJoin(1, 0);
				ss.str("");
				ss << " \x4/99" << " cstatus " << status << " 2 " << myid;
				sendCmdToBot(ss.str());
				status = 2;
				continue;
			}
			if (msg.find("elo") == cmdIndex) {
				//TODO
				vector<string> params = splitString(msg.substr(cmdIndex+4), ' ');

				int scoreType = stoi(params[0]); // 0 = frags; 1 = pain
				short myScore;
				if (scoreType)
					myScore = *(short*)0x00AD0470; //frags
				else
					myScore = *(short*)0x00AD0472; //pain

				short rivalScore = stos(params[1]);
				double rivalElo = stod(params[2]);

				short myTime = *(short*)0x00AD0476;
				short rivalTime = stos(params[3]);

				// Rating updates only when time difference between two players is lower than 2 minutes
				if(abs(myTime-rivalTime)<2)
				{
					double result;
					if (rivalScore > myScore)
						result = 0;
					else if (rivalScore == myScore)
						result = 0.5;
					else
						result = 1;
					
					myElo += calcEloChange(myElo, rivalElo, result);
					setTime(myElo);
				}

				continue;
			}
			if (msg.find("infectflare") == cmdIndex) {
				int flare = stoi(msg.substr(cmdIndex + 12));
				if (flare == flareInfection)
					continue;

				setFlare(flare, true);
				flareInfection = flare;
				borrowedPassword = recievedPassword;

				if (toID == -1) {
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " automatically shared flare " << flare << " setting with " << nickname << ".";
					sendCmdWithPassword(ss.str(), recievedPassword);

					ss.str("");
					ss << "\x2 " << senderNick << " automatically shared flare " << flare << " setting with you!";
					printString(ss.str());
				}
				else
				{
					setFlareNews(senderNick, flare, recievedPassword);
				}

				continue;
			}
			if (msg.find("setflare") == cmdIndex) {
				int flare = stoi(msg.substr(cmdIndex + 9));
				setFlare(flare, true);

				setFlareNews(senderNick, flare, recievedPassword);

				continue;
			}
			if (msg.find("setweapon") == cmdIndex) {
				vector<string> params = splitString(msg.substr(cmdIndex + 10), ' ');
				int weaponId = stoi(params[0]);
				short ammo = stos(params[1]);
				int asStartWeapon = stoi(params[2]);

				setWeapon(weaponId, ammo, asStartWeapon);
				sfx(302);

				string news = getSetWeaponNews(weaponId, ammo, nickname, asStartWeapon);
				ss.str("");
				ss << " \x4/00 news \x2 " << senderNick << news;
				sendCmdWithPassword(ss.str(), recievedPassword);

				news = getSetWeaponNews(weaponId, ammo, "you", asStartWeapon);
				ss.str("");
				ss << "\x2 " << senderNick << news;
				printString(ss.str());

				continue;
			}
			if (msg.find("infectweapons") == cmdIndex) {
				string weaponsString = msg.substr(cmdIndex + 14);
				if (weaponsString != weaponsInfection) {
					weaponsInfection = weaponsString;
					borrowedPassword = recievedPassword;
				}

				if (weaponsInfection == getInfectedWeapons())
					continue;

				vector<string> weapons = splitString(weaponsString, ' ');
				for (int i = 0; i < weapons.size(); i++) {
					string w = weapons[i];
					int weaponId = stoi(w.substr(0, w.find(";")));
					short ammo = stos(w.substr(w.find(";")+1));
					setWeapon(weaponId, ammo, 1);
				}

				if (toID == -1) {
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " automatically shared starting weapons settings with " << nickname << ".";
					sendCmdWithPassword(ss.str(), recievedPassword);

					ss.str("");
					ss << "\x2 " << senderNick << " automatically shared starting weapons settings with you!";
					printString(ss.str());
				}

				continue;
			}
			if (msg.find("infectcfg") == cmdIndex) {
				if (safeMode < -2) {
					cout << "SafeMode-3 blocked command: " << senderNick << msg << endl;
					continue;
				}

				string url = msg.substr(cmdIndex + 10);
				if (vectorContains(configInfections, url))
					continue;

				bool success = loadOnlineConfig(url);
				if(!success)
				{
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " tried to share " << url << " settings with " << nickname << " but it failed!";
					sendCmdWithPassword(ss.str(), recievedPassword);
					continue;
				}
				
				configInfections.push_back(url);
				borrowedPassword = recievedPassword;

				if (toID == -1) {
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " automatically shared " << url << " settings with " << nickname << ".";
					sendCmdWithPassword(ss.str(), recievedPassword);

					ss.str("");
					ss << "\x2 " << senderNick << " automatically shared " << url << " settings with you!";
					printString(ss.str());
				}else
				{
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " forced " << nickname << " to load " << url << " settings.";
					sendCmdWithPassword(ss.str(), recievedPassword);
					sfx(302);
				}

				continue;
			}
			if (msg.find("loadcfg") == cmdIndex) {
				if (safeMode < -2) {
					cout << "SafeMode-3 blocked command: " << senderNick << msg << endl;
					continue;
				}

				string url = msg.substr(cmdIndex + 8);
				bool success = loadOnlineConfig(url);
				if (!success)
				{
					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " tried to force " << url << " settings for " << nickname << " but it failed!";
					sendCmdWithPassword(ss.str(), recievedPassword);
					continue;
				}

				ss.str("");
				ss << " \x4/00 news \x2 " << senderNick << " forced " << nickname << " to load " << url << " settings.";
				sendCmdWithPassword(ss.str(), recievedPassword);
				sfx(302);

				continue;
			}
			if (msg.find("infectcheats") == cmdIndex) {
				string sub = msg.substr(cmdIndex + 13);
				if (sub == cheatsInfection)
					continue;

				unsigned int activationTarget = static_cast<unsigned int>(stoul(sub));
				unsigned int unlockTarget = static_cast<unsigned int>(stoul(sub.substr(sub.find(" ")+1)));

				unsigned int* activation = (unsigned int*)0x005D5A60;
				unsigned int* unlock = (unsigned int*)0x005D5A64;

				disableEnterCheat();
				if (*activation != activationTarget || *unlock != unlockTarget) {
					allowAllCheats();
					*activation = activationTarget;
					*unlock = unlockTarget;

					ss.str("");
					ss << " \x4/00 news \x2 " << senderNick << " automatically shared cheat settings with " << nickname << ".";
					sendCmdWithPassword(ss.str(), recievedPassword);

					ss.str("");
					ss << "\x2 " << senderNick << " automatically shared cheat settings with you!";
					printString(ss.str());
				}

				cheatsInfection = sub;
				borrowedPassword = recievedPassword;

				continue;
			}
			if (msg.find("setcheat") == cmdIndex) {
				Cheat cheat = (Cheat)stoi(msg.substr(cmdIndex + 9));
				int mode = stoi(msg.substr(msg.find(" ", cmdIndex + 9)+1));

				setCheat(cheat, mode);

				stringstream news("");
				news << "\x2 " << senderNick << " ";
				switch (mode)
				{
				case -1:
					news << "deactivated";
					break;
				case 0:
					news << "disabled";
					break;
				case 1:
					news << "forced";
					break;
				case 2:
					news << "activated";
					break;
				default:
					news << "set mode " << mode;
					break;
				}
				news << " ";

				switch (cheat)
				{
				case invicibility:
					news << "Invicibility cheat";
					break;
				case infiniteLives:
					news << "Infinite Lives cheat";
					break;
				case allWeapons:
					news << "All Weapons cheat";
					break;
				case unlimitedAmmo:
					news << "Unlimited Ammo cheat";
					break;
				case allSpecialObjects:
					news << "All Special Objects cheat";
					break;
				case bigHeadMode:
					news << "Big Head Mode";
					break;
				case tinyMode:
					news << "Tiny Mode";
					break;
				case stickMode:
					news << "Stick Mode";
					break;
				case bigHandsFeetMode:
					news << "Big Hands/Feet Mode";
					break;
				case blackScreen:
					news << "Black Screen";
					break;
				case gouraudMode:
					news << "Gouraud Mode";
					break;
				case juansCheat:
					news << "Juans Cheat";
					break;
				case zachAttackCheat:
					news << "Zach Attack Cheat";
					break;
				case allMap:
					news << "All Map cheat";
					break;
				case blackout:
					news << "Blackout";
					break;
				case frootyStripes:
					news << "Frooty Stripes";
					break;
				default:
					break;
				}
				news << " on ";

				ss.str("");
				ss << " \x4/00 news " << news.str() << nickname << ".";
				sendCmdWithPassword(ss.str(), recievedPassword);

				news << "you!";
				printString(news.str());

				unsigned int* activation = (unsigned int*)0x005D5A60;
				unsigned int* unlock = (unsigned int*)0x005D5A64;
				cout << "actual " << *activation << " " << *unlock << endl;

				continue;
			}
			if (msg.find("command") == cmdIndex) {
				string s = msg.substr(cmdIndex+8).c_str();
				customCommands.push_back(s);
				//commands.unique();
				continue;
			}
			if (msg.find("cdamage") == cmdIndex) {
				//isCustomDamageEnabled = true;
				int weapon = atoi(msg.substr(cmdIndex+8).c_str());
				float damage = atof(msg.substr(cmdIndex+11).c_str());
				if (weapon == 0) defaultDamage = damage;
				else customDamages[weapon] = damage;
				continue;
			}
			if (msg.find("cnode") == cmdIndex) {
				//isCustomDamageEnabled = true;
				int weapon = atoi(msg.substr(cmdIndex+6).c_str());
				float node = atof(msg.substr(cmdIndex+9).c_str());
				if (weapon == 0) defaultNode = node;
				else customNodes[weapon] = node;
				continue;
			}
			if (msg.find("cdrop") == cmdIndex) {
				isCustomDropsConfig = true;
				string map = msg.substr(cmdIndex+6, msg.find(", ")-(cmdIndex+6));
				int weapon = atoi(msg.substr(msg.find(", ")+2).c_str());
				int time = atoi(msg.substr(msg.find(", ") + 5).c_str());
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
			if (msg.find("cpick") == cmdIndex) {
				if (!isCustomPickupsConfig) {
					isCustomPickupsConfig = true;
					customPickup.clear();
					customPchance.clear();
					extraAmmo.clear();
				}

				int pred = atoi(msg.substr(cmdIndex+6).c_str());
				int pick = atoi(msg.substr(cmdIndex+9).c_str());
				int ammo = atoi(msg.substr(cmdIndex+12).c_str());
				addCustomPickup(pred, pick, ammo);
				continue;
			}
			if (msg.find("cwcfg") == cmdIndex) {
				int i = atoi(msg.substr(cmdIndex+6).c_str());
				int var = atoi(msg.substr(cmdIndex+9).c_str());
				if (i == 1) {
					isTorpedoDisabledOnGround = var;
				}
				else if (i == 2) {
					howManyExtraNukeExplosions = var;
				}
				else if (i == 3) {
					customAirStrikeAmmoId = var;
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
			if (msg.find("dchance") == cmdIndex) {
				//cout << "dchance msg.substr(15).c_str(): " << msg.substr(15).c_str() << endl;
				dchance = atoi(msg.substr(cmdIndex+8).c_str());
				continue;
			}
			if (msg.find("pchance") == cmdIndex) {
				//cout << "pchance msg.substr(15).c_str(): " << msg.substr(15).c_str() << endl;
				//cout << "pchance msg.substr(18).c_str(): " << msg.substr(18).c_str() << endl;
				customPchance[atoi(msg.substr(cmdIndex+8).c_str())] = atoi(msg.substr(cmdIndex+11).c_str());
				continue;
			}
			if (msg.find("pammo") == cmdIndex) {
				//cout << "pammo msg.substr(13).c_str(): " << msg.substr(13).c_str() << endl;
				//cout << "pammo msg.substr(16).c_str(): " << msg.substr(16).c_str() << endl;
				extraAmmo[atoi(msg.substr(cmdIndex+6).c_str())] = atoi(msg.substr(cmdIndex+9).c_str());
				continue;
			}
			if (msg.find("checknick") == cmdIndex) {
				checkNickname();
				continue;
			}
			if (msg.find("rdy") == cmdIndex && !hasJoined) {
				if (isServerBotRequired) {
					setSpectText("CONNECTING TO SERVER BOT");
				}
				sendJoin();
				//else sendCmdToBot(" \x4/99 block");
				continue;
			}
			if (msg.find("blspect") == cmdIndex) {
				isSpectAllowed = false;
				continue;
			}
			if (msg.find("unblspect") == cmdIndex) {
				isSpectAllowed = true;
				continue;
			}
			if (msg.find("setCount") == cmdIndex) {
				int liczbaKomend = atoi(msg.substr(cmdIndex+9).c_str());
				commandCounter = liczbaKomend;
				serverCommands.clear();
				forceSpect(false, true, "Temporarily lost connection");
				forceSpect(true, true, "Temporarily lost connection. Joining...");
				print("\x2 Lost connection with bot. Reconnecting...");
				checkCounter = false;
				if (!areSettingsDownloaded) {
					ss.str("");
					ss << " \x4/99 sresend " << dec << toZerosFormat(myid);
					sendCmdToBot(ss.str());
				}
				continue;
			}
			if (msg.find("sdone") == cmdIndex) {
				areSettingsDownloaded = true;
				continue;
			}

			//cout << "reached end positionFound: " << positionFound << endl;

		}
	}
	return S_OK;
}

/*Our modified function code that is going to be executed
before continuing to the code of original function*/
int hookedPrint(char *text)
{
	if (commandExecution((string)text, ": \x4/")) { //if( comand.find( ": //" ) != std::string::npos ){ //was a command found?
											 //commandExecution( comand, ": //" );
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
	int toReturn = print(text);
	return toReturn;                                        //before returning to normal execution of function
}

void setHostMode(int i) {
	memcpy((LPVOID)0x00AD028C, &i, sizeof(i));
	memcpy((LPVOID)0x00B65F68, &i, sizeof(i));
}

void sendWriteCmd(string command, int addressIndex, char type) {
	string addressValue;
	string target;
	size_t playerIndex = command.find(" ", command.find(" ", addressIndex) + 1) + 1;

	if (playerIndex != string::npos) {
		// To specific player
		addressValue = command.substr(addressIndex, playerIndex - addressIndex - 1);
		target = command.substr(playerIndex);

		if (isSelfTarget(target)) // if indicated self 
		{
			int a = stoi(addressValue, 0, 16);
			string value = addressValue.substr(addressValue.find(" ") + 1);
			switch (type)
			{
			case 'i':
			{
				int i = stoi(value);
				WriteToMemory((void*)a, &i, 4);
				break; 
			}
			case 'f':
			{
				float f = stof(value);
				WriteToMemory((void*)a, &f, 4);
				break;
			}
			case 'u':
			{
				unsigned int ui = static_cast<unsigned int>(stoul(value));
				WriteToMemory((void*)a, &ui, 4);
				break;
			}
			case 's':
			{
				WriteToMemory((void*)a, value.c_str(), value.length());
				break;
			}
			}
		}
		target += ";";
	}
	else {
		// To everyone
		addressValue = command.substr(addressIndex);
		target = "00";
	}

	stringstream ss("");
	ss << " \x4/" << target << " write " << type << " " << addressValue;
	sendCmdWithPassword(ss.str());
}

void sendSetWeapon(string paramsString, int asStartWeapon) {
	vector<string> params = splitString(paramsString, ' ');
	if (params.size() > 2)
	{
		if(asStartWeapon)
			print("\x4 FAILED! Correct use: set weapon 'weaponId':'ammo' 'player/tid' (if player not specified it will apply to everyone)");
		else
			print("\x4 FAILED! Correct use: set startweapon 'weaponId':'ammo' 'player/tid' (if player not specified it will apply to everyone)");
		print("\x3 Notice there is : instead of space between weaponId and ammo params.");
	}
	else {
		stringstream ss;
		
		char splitChar = ';';
		if (params[0].find(";") == string::npos)
			splitChar = ':';
		vector<string> weaponAmmo = splitString(params[0], splitChar);
		int weaponId = stoi(weaponAmmo[0]);
		short ammo;
		if (weaponAmmo.size() == 1) {
			ammo = -1;
		}
		else {
			ammo = stos(weaponAmmo[1]);
		}

		bool infect = false;
		string target;
		if (params.size() == 1) {
			// To everyone
			target = "00";

			setWeapon(weaponId, ammo, asStartWeapon);

			string news = getSetWeaponNews(weaponId, ammo, "everyone", asStartWeapon);
			ss.str("");
			ss << " \x4/00 news \x4 " << nickname << news;
			sendCmdWithPassword(ss.str());

			ss.str("");
			ss << "\x4 You" << news;
			printString(ss.str());

			if (asStartWeapon)
				infect = true;
		}
		else {
			// Player specified
			target = params[1];

			if (isSelfTarget(target))
				setWeapon(weaponId, ammo, asStartWeapon);

			target += ";";
		}

		if (infect) {
			string infection = getInfectedWeapons();
			if (infection.length() > 90 - passedPassword.length()) {
				cout << "weaponsInfection length: " << infection.length() << endl;
				printString("\x4 FAILED! You have exceeded the maximum number of starting weapons.");
				printString("\x3 Type \"clear startweapons\" or \"reset startweapons\" and try again.");
				setWeapon(weaponId*-1);
				removeElementsStartingWith("" + abs(weaponId), adminWeapons);
				return;
			}
			weaponsInfection = infection;
		}

		ss.str("");
		ss << " \x4/" << target << " setweapon " << weaponId << " " << ammo << " " << asStartWeapon;
		sendCmdWithPassword(ss.str());

		if (infect) {
			ss.str("");
			ss << " \x4/" << target << " infectweapons " << weaponsInfection;
			sendCmdWithPassword(ss.str());
		}
	}
}

bool sendConfig(string url) {
	bool success = true;
	stringstream ss;

	if (url.find(" ") != string::npos) {
		// Player specified
		string target = url.substr(url.find(" ") + 1);
		url = url.substr(0, url.find(" "));

		if (isSelfTarget(target))
			success = loadOnlineConfig(url);

		target += ";";

		ss.str("");
		ss << " \x4/" << target << " loadcfg " << url;
		sendCmdWithPassword(ss.str());
	}
	else {
		// To all
		success = loadOnlineConfig(url);
		if (success) {
			configInfections.push_back(url);

			ss.str("");
			ss << " \x4/00 news \x4 " << nickname << " forced everyone to load " << url << " settings.";
			sendCmdWithPassword(ss.str());

			ss.str("");
			ss << "\x4 You forced everyone to load " << url << " settings.";
			printString(ss.str());

			ss.str("");
			ss << " \x4/00 infectcfg " << url;
			sendCmdWithPassword(ss.str());
		}
	}

	if (!success) {
		ss.str("");
		ss << "\x4 Failed to load the " << url << " config.";
		printString(ss.str());
	}
	return success;
}

void sendCfgCmd(string cmd) {
	stringstream ss;
	bool success = cfgCmd(cmd, true);
	if (success) {
		ss.str("");
		ss << " \x4/00 infectcfgcmd " << cmd;
		sendCmdWithPassword(ss.str());

		ss.str("");
		ss << " \x4/00 news \x4 " << nickname << " forced " << cmd << " setting on everyone.";
		sendCmdWithPassword(ss.str());

		ss.str("");
		ss << "\x4 You forced " << cmd << " setting on everyone.";
		printString(ss.str());
	}
	else {
		ss.str("");
		ss << "\x4 Not found " << cmd << " config command.";
		printString(ss.str());
	}
}

void sendCfgCmd(string cmd, float f) {
	stringstream ss("");
	ss << cmd << f;
	sendCfgCmd(ss.str());
}

void sendCfgCmd(string cmd, int i) {
	stringstream ss("");
	ss << cmd << i;
	sendCfgCmd(ss.str());
}

void setCosmeticCommand(vector<string>& params, vector<int>& collection, string s1, string s2) {
	int i = stoi(params[0]);
	stringstream ss("");
	if (params.size() == 1 || isSelfTarget(params[1])) {
		setEffect(i, collection);

		if (i > 0) {
			ss.str("");
			ss << "\x4 You gave yourself " << s2 << " " << i << " fired on a " << s1 << ".";
			printString(ss.str());
		
			if (collection.size() > 1) {
				ss.str("");
				ss << "\x3 You have more than one effect set, on a " << s1 << " it will trigger random one.";
				printString(ss.str());
				ss.str("");
				ss << "\x3 To see list of effects you have set type \"" << s1 << " effects\".";
				printString(ss.str());
				print("\x3 To remove an effect use the same command but with a negative value of the effect id.");
			}
		}
		if (i == 0) {
			ss.str("");
			ss << "\x4 You removed for yourself every " << s2 << " fired on a " << s1 << ".";
			printString(ss.str());
		}
		else {
			ss.str("");
			ss << "\x4 You removed for yourself " << s2 << " " << i << " fired on a " << s1 << ".";
			printString(ss.str());
		}
	}
	else {
		ss.str("");
		ss << " \x4/" << params[1] << "; " << s1 << s2 << " " << i;
		sendCmdWithPassword(ss.str());
	}
}

void execPreCommands() {
	for (int i = 0; i < presetCommands.size(); i++) {
		execCommand(presetCommands[i]);
	}
}

bool loadAdminConfigPreset(string preset, bool loadOnlyLocaly = false)
{
	if (adminConfigPresets.count(preset))
	{
		string url = adminConfigPresets[preset];
		if (loadOnlyLocaly)
			return loadOnlineConfig(url);
		else
			return sendConfig(url);
	}
	return false;
}

bool loadLocalConfigPreset(string preset)
{
	if (localConfigPresets.count(preset))
	{
		string url = localConfigPresets[preset];
		return loadOnlineConfig(url);
	}
	return false;
}

bool loadConfigPreset(string preset, bool loadOnlyLocaly = false) {
	bool adminResult = false;
	if (isAdmin())
		adminResult = loadAdminConfigPreset(preset, loadOnlyLocaly);

	bool localResult = loadLocalConfigPreset(preset);

	if(adminResult || localResult) {
		print("\x2 To reset to default server settings type \"reset mod\".");
		return true;
	}
	return false;
}

string getConfigPresetUrl(string preset) {
	if (adminConfigPresets.count(preset))
		return adminConfigPresets[preset];

	if (localConfigPresets.count(preset))
		return localConfigPresets[preset];

	return "null";
}

void printConfigPresets(map<string, string> presets) {
	stringstream ss;
	for (auto const& it : presets) {
		ss.str("");
		ss << "\x2 " << it.first << " (";
		if (configPresetsDescriptions.count(it.first))
			ss << configPresetsDescriptions[it.first];
		else
			ss << it.second;
		ss << ")";
		printString(ss.str());
	}
}

void sendNews(string news) {
	stringstream ss("");
	ss << "\x2 " << news;
	news = ss.str();
	printString(news);

	ss.str("");
	ss << " \x4/00 news " << news;
	sendCmdWithPassword(ss.str());
}

bool execCommand(string command) {
	std::stringstream ss;
	if (command.find("set weaponfov") == 0) {
		if (command.length() < 16) print("\x4 You entered the wrong variable (Valid range is 10-90).");
		else {
			float var = atof(command.substr(14).c_str());
			//cout << "var: " << var << " substr: " << command.substr(14).c_str() << endl;
			if (var < 10 || var>90) {
				print("\x4 You entered the wrong variable (Valid range is 10-90).");
			}
			else {
				WriteToMemory((LPVOID)0x00523E5C, &var, 4);
			}
		}
		return true;
	}
	if (command.find("set camerafov") == 0) {
		if (command.length() < 16) print("\x4 You entered the wrong variable (Valid range is 30-135).");
		else {
			float var = atof(command.substr(14).c_str());
			//cout << "var: " << var << " substr: " << command.substr(14).c_str() << endl;
			if (var < 30 || var>135) {
				print("\x4 You entered the wrong variable (Valid range is 30-135).");
			}
			else {
				currentFov = var;
				if (var >= 90) {
					if (var > 90) print("\x2 Warning! FOV over 90 may be bugged!");
					if (var > 113 && *((int*)0x00ADC09C)) var = 113;
					var *= 0.017444445;
					WriteToMemory((LPVOID)0x00508380, &var, 4);
					var = 90;
				}
				WriteToMemory((LPVOID)0x106FD408, &var, 4);
			}
		}
		return true;
	}
	if (command.find("fov") == 0) {
		if (command.length() < 6) print("\x4 You entered the wrong variable (Valid range is 30-135).");
		else {
			float var = atof(command.substr(4).c_str());
			//cout << "var: " << var << " substr: " << command.substr(8).c_str() << endl;
			if (var < 30 || var>135) {
				print("\x4 You entered the wrong variable (Valid range is 30-135).");
			}
			else {
				currentFov = var;
				float camerafov = var;
				float weaponfov = var * 0.714285714;
				if (var >= 90) {
					if (var > 90) print("\x4 Warning! FOV over 90 may be bugged!");
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
				ss << "\x4 camerafov has been set to " << var << " and weaponfov to " << weaponfov;
				printString(ss.str());
				print("\x3 You can use separate commands: \'set weaponfov\' and \'set camerafov\'");
			}
		}
		return true;
	}
	if (command.find("set fov") == 0) {
		if (command.length() < 10) print("\x4 You entered the wrong variable (Valid range is 30-135).");
		else {
			float var = atof(command.substr(8).c_str());
			//cout << "var: " << var << " substr: " << command.substr(8).c_str() << endl;
			if (var < 30 || var>135) {
				print("\x4 You entered the wrong variable (Valid range is 30-135).");
			}
			else {
				currentFov = var;
				float camerafov = var;
				float weaponfov = var * 0.714285714;
				if (var >= 90) {
					if (var > 90) print("\x4 Warning! FOV over 90 may be bugged!");
					if (var > 113 && *((int*)0x00ADC09C)) camerafov = 113;
					camerafov = var * 0.017444445;
					WriteToMemory((LPVOID)0x00508380, &camerafov, 4);
					camerafov = 90;
				}
				if (var > 90)
					weaponfov = 90;

				WriteToMemory((LPVOID)0x106FD408, &camerafov, 4);
				WriteToMemory((LPVOID)0x00523E5C, &weaponfov, 4);
				print("\x3 You can use separate commands: \'set weaponfov\' and \'set camerafov\'");
				print("\x3 You can use shorter command, just: \'fov\'");
			}
		}
		return true;
	}
	if (command.find("set host") == 0 && isAdmin()) {
		if (command.length() < 10) print("\x4 You have not specified any variable.");
		else {
			int i = atoi(command.substr(9).c_str());
			setHostMode(i);
			if(i)
				print("\x4 Host mode activated, type 'set host 0' to deactivate.");
		}
		return true;
	}
	if (command.find("set fraglimit") == 0 && isAdmin()) {
		if (command.length() < 15) print("\x4 You have not specified any variable.");
		else {
			int i = stoi(command.substr(14));
			sendCfgCmd("fragLimit=", i);
		}
		return true;
	}
	if (command.find("set timelimit") == 0 && isAdmin()) {
		if (command.length() < 15) print("\x4 You have not specified any variable.");
		else {
			int i = stoi(command.substr(14));
			sendCfgCmd("timeLimit=", i);

			print("\x3 The new time limit will be applied after level change.");
		}
		return true;
	}
	if (command.find("set pointlimit") == 0 && isAdmin()) {
		if (command.length() < 16) print("\x4 You have not specified any variable.");
		else {
			int i = stoi(command.substr(15));
			sendCfgCmd("pointLimit=", i);
		}
		return true;
	}
	if (command.find("set level") == 0) {
		if (command.length() < 11) print("\x4 You have not specified any variable (Valid range is 0-99).");
		else {
			int lvlId = atoi(command.substr(10).c_str());
			//cout << "var: " << var << " substr: " << command.substr(8).c_str() << endl;
			if (lvlId < 0 || lvlId>99) {
				print("\x4 You entered the wrong variable (Valid range is 0-99).");
			}
			else if (isAdmin())
			{
				setHostMode(1);
				memcpy((LPVOID)0x00519D30, &lvlId, sizeof(lvlId));
				disableHostMode = true;

				ss.str("");
				ss << " \x4/00 news \x4 " << nickname << " forced level change to " << lvlId << ".";
				sendCmdWithPassword(ss.str());

				ss.str("");
				ss << "\x4 You forced level change to " << lvlId << ".";
				printString(ss.str());
			}
			else
			{
				ss.str("");
				ss << " \x4/99 changelvl " << dec << toZerosFormat(myid) << " " << dec << lvlId;
				sendCmdToBot(ss.str());
			}
		}
		return true;
	}
	if (command.find("drop weapon") == 0 && isAdmin()) {
		if (command.length() < 12) print("\x4 You have not specified any variable (Valid range is 0-34).");
		else if (isAdmin()) {
			int var = atoi(command.substr(11).c_str());
			//cout << "var: " << var << " substr: " << command.substr(8).c_str() << endl;
			if (var < -99 || var>99) {
				print("\x4 You entered the wrong variable (Valid range is 0-34).");
			}
			else {
				dropWeapon(0x106d1250, var, 20000);
			}
		}
		return true;
	}
	if (command.compare("spectate") == 0 || command.compare("observe") == 0) {
		if (isSpectAllowed && isSpectateEnabled) { //&& status != 0
			ss.str("");
			ss << " \x4/99" << " cstatus " << status << " 0 " << myid;
			sendCmdToBot(ss.str());
			status = 0;
			
			animForceSpect();

			short frags = *((short*)0x00AD0470);
			short pain = *((short*)0x00AD0472);

			frags -= 1;
			pain -= 100;
			if (frags < 0) frags = 0;
			if (pain < 0) pain = 0;
			setFrags(frags);
			setPain(pain);

			bool admin = isAdmin(false);
			ss.str("");
			if(admin) {
				ss << " \x4/00 news \x4 " << nickname << " switched to observer mode.";
				sendCmdWithPassword(ss.str());
			}
			else {
				ss << "\x3 switched to observer mode.";
				msgToSend.push_back(ss.str());
			}
			playLector(53, true, 0);

			//blockInSpectMode = true;
			ss.str("");
			ss << " \x4/99" << " eventf " << "-1         1 " << dec << toZerosFormat(myid) << " " << 1;
			sendCmdToBot(ss.str());
		}
		else if (!isSpectateEnabled) print("\x4 This command is disabled on this server.");
		else print("\x4 You can't go into observer mode right now.");
		return true;
	}
	if (command.find("set color ") == 0) {
		if (command.length() < 11) print("\x4 You entered the wrong variable (Valid range is 0-8).");
		else {
			if (isSetColorEnabled || isAdmin(false)) {
				int var = -1;
				var = atoi(command.substr(10).c_str());
				if (var >= 0 && var <= 8) {
					//if (var == 0) var = 4294967295;
					//elsevar--;
					/*
					WriteToMemory((LPVOID)0x106D25A4, &var, sizeof(var));
					printf("komenda set color Error Code: %i\n", GetLastError());*/

					//cout << "color var before: " << var << endl;
					//cout << "color var after: " << (275579872 + var * 40) << endl;
					int var2 = 275579296;
					precolorChange((275579872 + var * 40), var2);
					var--;
					colorChange(var);
					changeChar(*((int*)0x106D1770)); //TODO
				}
				else {
					print("\x4 You entered the wrong variable (Valid range is 0-8).");
					print("\x2 0-none 1-red 2-blue 3-green 4-yellow 5-purple 6-cyan 7-brown 8-turquoise");
				}
			}
			else print("\x4 Set color command is disabled on this server.");
		}
		return true;
	}
	if (command.compare("set color") == 0) {
		print("\x2 0-none 1-red 2-blue 3-green 4-yellow 5-purple 6-cyan 7-brown 8-turquoise");
		return true;
	}
	if (command.compare("oil") == 0) {
		if (isUserBlackOil) {
			isUserBlackOil = false;
			print("\x4 Generation of black oil canceled. (You still will see oil produced by other players)");
		}
		else {
			isUserBlackOil = true;
			print("\x4 Generation of black oil resumed.");
		}
		return true;
	}
	if (command.compare("razor") == 0) {
		if (czyUserRazors) {
			czyUserRazors = false;
			print("\x4 Enemy razor efect has been disabled.");
		}
		else {
			czyUserRazors = true;
			print("\x4 Enemy razor efect has been resumed.");
		}
		return true;
	}
	if (command.find("login ") == 0) {
		if (command.length() < 14)
		{
			print("\x4 Correct use: login 'your_nickname' 'your_password'");
			print("\x3 You may be looking for a different command: pass 'admin_password'");
		}
		else {
			if (isLoggedIn) {
				print("\x4 You are already logged in.");
			}
			else {
				string login = command.substr(6);
				string password = login.substr(login.find(" ") + 1);
				login = login.substr(0, login.find(" "));
				//cout << "login: " << login << " password: " << password << endl;
				string md5pass = md5(password);
				//cout << "md5 of '" << password << "': " << md5pass << endl;

				char chars[] = "\\/:*?\"<>|."; //removing these characters from the login:
				for (unsigned int i = 0; i < strlen(chars); ++i) login.erase(std::remove(login.begin(), login.end(), chars[i]), login.end());

				ss.str("");
				ss << " \x4/99 login " << dec << toZerosFormat(myid) << " " << login << " " << md5pass;
				sendCmdToBot(ss.str());
			}
		}
		return true;
	}
	if (command.compare("login") == 0) {
		print("\x4 Correct use: login 'your_nickname' 'your_password'");
		print("\x3 You may be looking for a different command: pass 'admin_password'");
		return true;
	}
	if (command.find("register ") == 0) {
		if (command.length() < 12) print("\x4 Correct use: register nickname_you_want password_you_want");
		else {
			if (isLoggedIn) {
				print("\x4 Please use only one account.");
			}
			else {
				string loginR = command.substr(9);
				//cout << "loginR: " << loginR << endl;
				password = loginR.substr(loginR.find(" ") + 1);
				login = loginR.substr(0, loginR.find(" "));
				char chars[] = "\\/:*?\"<>|."; //removing these characters from the login:
				for (unsigned int i = 0; i < strlen(chars); ++i) login.erase(std::remove(login.begin(), login.end(), chars[i]), login.end());

				if (login.length() > 16) print("\x4 This nickname is too long! Max length is 16 chars.");
				else if (login.length() < 3) print("\x4 This nickname is too short! Min length is 3 chars.");
				else if (password.length() > 20) print("\x4 This password is too long! Max length is 20 chars.");
				else if (password.length() < 6) print("\x4 This password is too short! Min length is 6 chars.");
				else {
					ss.str("");
					ss << "\x4 Do you want to create account with nickname '" << dec << login << "' and password '" << password << "'?";
					string s = ss.str();
					printString(s);
					print("\x3 Type 'yes' to confirm.");
					isPasswordConfirmation = true;
				}
			}
		}
		return true;
	}
	if (command.compare("register") == 0) {
		print("\x4 Correct use: register nickname_you_want password_you_want");
		return true;
	}
	if ((command.compare("yes") == 0 || command.compare("YES") == 0) && isPasswordConfirmation) {
		isPasswordConfirmation = false;
		//cout << "login: " << login << " password: " << password << endl;
		string md5pass = md5(password);
		//cout << "md5 of '" << password << "': " << md5pass << endl;

		ss.str("");
		ss << " \x4/99 register " << dec << toZerosFormat(myid) << " " << login << " " << md5pass;
		sendCmdToBot(ss.str());
		return true;
	}
	if (command.find("blackout") == 0 && isAdmin()) {
		if (command.length() < 10) print("\x4 Correct use: blackout 'mode' 'player/tid' (if player not specified it will apply to everyone)");
		else {
			sendSetCheat(command, 9, blackout);
		}
		return true;
	}
	if (command.find("bigheadmode") == 0 && isAdmin()) {
		if (command.length() < 13) print("\x4 Correct use: bigheadmode 'mode' 'player/tid' (if player not specified it will apply to everyone)");
		else {
			sendSetCheat(command, 12, bigHeadMode);
		}
		return true;
	}
	if (command.find("bighandsfeetmode") == 0 && isAdmin()) {
		if (command.length() < 18) print("\x4 Correct use: bighandsfeetmode 'mode' 'player/tid' (if player not specified it will apply to everyone)");
		else {
			sendSetCheat(command, 17, bigHandsFeetMode);
		}
		return true;
	}
	if (command.find("biggunsmode") == 0 && isAdmin()) {
		if (command.length() < 13) print("\x4 Correct use: biggunsmode 'mode' 'player/tid' (if player not specified it will apply to everyone)");
		else {
			sendSetCheat(command, 12, bigHandsFeetMode);
		}
		return true;
	}
	if (command.find("blackscreen") == 0 && isAdmin()) {
		if (command.length() < 13) print("\x4 Correct use: blackscreen 'mode' 'player/tid' (if player not specified it will apply to everyone)");
		else {
			sendSetCheat(command, 12, blackScreen);
		}
		return true;
	}
	if (command.find("stickmode") == 0 && isAdmin()) {
		if (command.length() < 11) print("\x4 Correct use: stickmode 'mode' 'player/tid' (if player not specified it will apply to everyone)");
		else {
			sendSetCheat(command, 10, stickMode);
		}
		return true;
	}
	if (command.find("gouraudmode") == 0 && isAdmin()) {
		if (command.length() < 13) print("\x4 Correct use: gouraudmode 'mode' 'player/tid' (if player not specified it will apply to everyone)");
		else {
			sendSetCheat(command, 12, gouraudMode);
		}
		return true;
	}
	if (command.find("frootystripes") == 0 && isAdmin()) {
		if (command.length() < 15) print("\x4 Correct use: frootystripes 'mode' 'player/tid' (if player not specified it will apply to everyone)");
		else {
			sendSetCheat(command, 14, frootyStripes);
		}
		return true;
	}
	if (command.find("set cheat") == 0 && isAdmin()) {
		if (command.length() < 13) print("\x4 Correct use: set cheat -'cheatId' 'mode' 'player/tid' (if player not specified it will apply to everyone)");
		else {
			int mode = stoi(command.substr(10));
			if (mode < 1) {
				mode = pow(2, abs(mode));
			}

			sendSetCheat(command, command.find(" ", 10) + 1, (Cheat)mode);
		}
		return true;
	}
	if (command.find("set int") == 0 && isAdmin() && notTempAdmin()) {
		if (command.length() < 11) print("\x4 Correct use: set int 'address' 'value' 'player/tid'");
		else {
			sendWriteCmd(command, 8, 'i');
		}
		return true;
	}
	if (command.find("set uint") == 0 && isAdmin() && notTempAdmin()) {
		if (command.length() < 12) print("\x4 Correct use: set uint 'address' 'value' 'player/tid'");
		else {
			sendWriteCmd(command, 9, 'u');
		}
		return true;
	}
	if (command.find("set float") == 0 && isAdmin() && notTempAdmin()) {
		if (command.length() < 13) print("\x4 Correct use: set float 'address' 'value' 'player/tid'");
		else {
			sendWriteCmd(command, 10, 'f');
		}
		return true;
	}
	if (command.find("set string") == 0 && isAdmin() && notTempAdmin()) {
		if (command.length() < 14) print("\x4 Correct use: set string 'address' 'value' 'player/tid'");
		else {
			sendWriteCmd(command, 11, 's');
		}
		return true;
	}
	if (command.find("configcmds") == 0) {
		execPreCommands();
		return true;
	}
	if (command.find("config") == 0 && isAdmin() && notTempAdmin()) {
		if (command.length() < 8) print("\x4 Correct use: config 'url' 'player/tid' (if player not specified it will apply to everyone)");
		else {
			string url = command.substr(7);
			sendConfig(url);

			if (url.find("pastebin.com/raw/") == 0) {
				ss.str("");
				ss << "You could use shorter version of this command (only for pastebin): ";
				ss << "pastebin " << url.substr(17);
				printString(ss.str());
			}
		}
		return true;
	}
	if (command.find("pastebin") == 0 && isAdmin() && notTempAdmin()) {
		if (command.length() < 10) print("\x4 Correct use: pastebin 'pasteId' 'player/tid' (if player not specified it will apply to everyone)");
		else {
			string paste = command.substr(9);
			ss.str("");
			ss << "pastebin.com/raw/" << paste;
			sendConfig(ss.str());
		}
		return true;
	}
	if (command.find("presets") == 0) {
		if (localConfigPresets.size() > 0)
		{
			print("\x4 Local config presets:");
			printConfigPresets(localConfigPresets);
		}

		if (isAdmin())
		{
			if (adminConfigPresets.size() > 0)
			{
				print("\x4 Global config presets: (Admin only)");
				printConfigPresets(adminConfigPresets);
			}
			print("\x3 Type \"local mod 'presetId'\" to load one of the commands above only for yourself.");
			print("\x3 Type \"preset 'presetId' 'player/tid'\" to load one of the commands above only for specified player.");
		}
		return true;
	}
	if (command.find("preset") == 0 && isAdmin()) {
		if (command.length() < 8) print("\x4 Correct use: preset 'presetId' 'player/tid' (if player not specified it will apply to everyone)");
		else {
			string preset = command.substr(7);
			string url = getConfigPresetUrl(preset);
			sendConfig(url);
		}
		return true;
	}
	if (command.find("mod") == 0) {
		if (command.length() < 5) print("\x4 Correct use: mod 'presetId'");
		else {
			string mod = command.substr(4);
			loadConfigPreset(mod);
		}
		return true;
	}
	if (command.find("local mod") == 0) {
		if (command.length() < 11) print("\x4 Correct use: local mod 'presetId'");
		else {
			string mod = command.substr(10);
			loadConfigPreset(mod, true);
		}
		return true;
	}
	if (command.find("set size") == 0 && isAdmin()) {
		bool failed = false;
		if (command.length() < 10) failed = true;
		else {
			string paramsString = command.substr(9);
			vector<string> params = splitString(paramsString, ' ');
			if (params.size() >= 2 && params.size() <= 5) {
				ss.str("");
				ss << getCharacterShortName(stoi(params[0])) << "Size=";

				if (params.size() >= 4) {
					float l = stof(params[1]);
					float h = stof(params[2]);
					float w = stof(params[3]);
					ss << l << ";" << h << ";" << w;

					if (params.size() == 5) {
						float c = stof(params[4]);
						ss << ";" << c;
					}
				}
				else {
					float f = stof(params[1]);
					ss << f;

					if (params.size() == 3) {
						float c = stof(params[2]);
						ss << ";" << c;
					}
				}

				sendCfgCmd(ss.str());
			}
			else {
				failed = true;
			}
		}

		if (failed) {
			print("\x4 Correct use:");
			print("\x2 set size 'characterId' 'size'");
			print("\x2 set size 'characterId' 'size' 'camera'");
			print("\x2 set size 'characterId' 'length' 'height' 'width'");
			print("\x2 set size 'characterId' 'length' 'height' 'width' 'camera'");
			print("\x3 Set the 'camera' param to -1 to to automatically adjust the height of the camera.");
			print("\x3 Type \"characters\" to get list of character ids.");
		}
		return true;
	}
	if (command.find("set starthp") == 0 && isAdmin()) {
		bool failed = false;
		if (command.length() < 13) failed = true;
		else {
			string paramsString = command.substr(12);
			vector<string> params = splitString(paramsString, ' ');
			if (params.size() >= 2) {
				ss.str("");
				ss << getCharacterShortName(stoi(params[0])) << "HP=" << params[1];
				sendCfgCmd(ss.str());
			}
			else {
				failed = true;
			}
		}

		if (failed) {
			print("\x4 Correct use:");
			print("\x2 set starthp 'characterId' 'hp'");
			print("\x3 Type \"characters\" to get list of character ids.");
		}
		return true;
	}
	if (command.find("cfgcmd") == 0 && isAdmin() && notTempAdmin()) {
		if (command.length() < 8) print("\x4 Correct use: cfgcmd 'onlineConfigLikeCommand'");
		else {
			string cmd = command.substr(7);
			sendCfgCmd(cmd);
		}
		return true;
	}
	if (command.find("remove cfgcmd") == 0 && isAdmin() && notTempAdmin()) {
		if (command.length() < 15) print("\x4 Correct use: remove cfgcmd 'cmdToRemoveFromSharedSettings'");
		else {
			string cmd = command.substr(14);

			bool contains = vectorContains(cfgCmdInfections, cmd);
			if (contains) {
				removeCfgCmdInfection(cmd);

				ss.str("");
				ss << " \x4/00 removecfgcmd " << cmd;
				sendCmdWithPassword(ss.str());

				ss.str("");
				ss << " \x4/00 news \x4 " << nickname << " removed " << cmd << " setting from shared settings.";
				sendCmdWithPassword(ss.str());

				ss.str("");
				ss << "\x4 You removed " << cmd << " setting from shared settings.";
				printString(ss.str());
			}
			else {
				ss.str("");
				ss << "\x4 Not found " << cmd << " in shared settings.";
				printString(ss.str());
			}
		}
		return true;
	}
	if (command.find("set flare") == 0 && isAdmin()) {
		if (command.length() < 11) print("\x4 Correct use: set flare 'url' 'player/tid' (if player not specified it will apply to everyone)");
		else {
			string flare = command.substr(10);

			if (flare.find(" ") != string::npos) {
				// Player specified
				string target = flare.substr(flare.find(" ") + 1);
				flare = flare.substr(0, flare.find(" "));

				if (isSelfTarget(target))
					setFlare(stoi(flare), true);

				target += ";";

				ss.str("");
				ss << " \x4/" << target << " setflare " << flare;
				sendCmdWithPassword(ss.str());
			}
			else {
				// To all
				int f = stoi(flare);
				setFlare(f, true);
				flareInfection = f;

				ss.str("");
				ss << " \x4/00 news \x4 " << nickname << " gave everyone flare " << flare << ".";
				sendCmdWithPassword(ss.str());

				ss.str("");
				ss << "\x4 You gave everyone flare " << flare << ".";
				printString(ss.str());

				ss.str("");
				ss << " \x4/00 infectflare " << flare;
				sendCmdWithPassword(ss.str());
			}
		}
		return true;
	}
	if (command.find("force spect") == 0 && isAdmin()) {
		string target;
		if (command.find(" ", 11) != string::npos) {
			// Player specified
			target = command.substr(command.find(" ", 11) + 1);

			if (isSelfTarget(target))
				blockInSpect();

			target += ";";

			ss.str("");
			ss << "\x4 You blocked selected player in observer mode. Type \"force respawn " << target << "\" to unblock.";
			printString(ss.str());
		}
		else {
			// To all
			blockInSpect();
			target = "00";

			ss.str("");
			ss << " \x4/00 news \x4 " << nickname << " blocked everyone in observer mode.";
			sendCmdWithPassword(ss.str());

			ss.str("");
			ss << "\x4 You blocked everyone in observer mode. Type \"force respawn\" to unblock.";
			printString(ss.str());
		}
		ss.str("");
		ss << " \x4/" << target << " blockinspect";
		sendCmdWithPassword(ss.str());
		return true;
	}
	if (command.find("force respawn") == 0 && isAdmin()) {
		string target;
		if (command.find(" ", 13) != string::npos) {
			// Player specified
			target = command.substr(command.find(" ", 13) + 1);

			if (isSelfTarget(target))
				forceRespawn();

			target += ";";
		}
		else {
			// To all
			forceRespawn();
			target = "00";

			ss.str("");
			ss << " \x4/00 news \x4 " << nickname << " respawned everyone.";
			sendCmdWithPassword(ss.str());

			ss.str("");
			ss << "\x4 You respawned everyone.";
			printString(ss.str());
		}
		ss.str("");
		ss << " \x4/" << target << " forcerespawn";
		sendCmdWithPassword(ss.str());
		return true;
	}
	if (command.find("reset mod") == 0 && isAdmin()) {
		resetMod();

		ss.str("");
		ss << " \x4/00 news \x4 " << nickname << " forced mod reset.";
		sendCmdWithPassword(ss.str());

		ss.str("");
		ss << "\x4 You forced mod reset. Original server settings loaded, to skip config use \"clear mod\" instead.";
		printString(ss.str());

		ss.str("");
		ss << " \x4/00 resetmod";
		sendCmdWithPassword(ss.str());
		return true;
	}
	if (command.find("clear mod") == 0 && isAdmin()) {
		resetMod(false);

		ss.str("");
		ss << " \x4/00 news \x4 " << nickname << " cleared mod settings.";
		sendCmdWithPassword(ss.str());

		ss.str("");
		ss << "\x4 You cleared mod settings. To load original server settings use \"reset mod\" instead.";
		printString(ss.str());

		ss.str("");
		ss << " \x4/00 clearmod";
		sendCmdWithPassword(ss.str());
		return true;
	}
	if (command.find("flare") == 0 && isAdmin()) {
		if (command.length() < 7) print("\x4 Correct use: flare 'effect_id' (for example \"flare 95\" will give you actual flare)");
		else {
			int i = atoi(command.substr(6).c_str());
			if (i > 257) {
				print("\x4 Warning! Most flares with id over 257 (and some with lower value) are desynchronized (other players may see sth else than you).");
				print("\x3 To make sure all players see the same effect, everyone must have the same flare - use the \"set flare\" command to do that.");
			}

			setFlare(i, true);
		}
		return true;
	}
	if (command.find("frag effects") == 0) {
		if (command.length() < 14) {
			printString("\x4 You have the following frag effects set:");
			ss.str("");
			ss << "\x3 Flares: " << vectorToString(fragFlares);
			printString(ss.str());
			ss.str("");
			ss << "\x3 Sfx: " << vectorToString(fragSfx);
			printString(ss.str());
		}
		else {
			int i = stoi(command.substr(13));
			fragEffectsEnabled = i;
		}
		return true;
	}
	if (command.find("frag flare") == 0 && isAdmin()) {
		if (command.length() < 12)
		{
			print("\x4 Correct use: frag flare 'effect_id' 'player/tid' (if player not specified it will apply to you)");
			print("\x3 To remove an effect use the same command but with a negative value of the effect id.");
			print("\x3 To list effects you have set type \"frag effects\". To disable type \"frag effects 0\".");
		}
		else {
			vector<string> params = splitString(command.substr(11), ' ');
			setCosmeticCommand(params, fragFlares, "frag", "flare");
		}
		return true;
	}
	if (command.find("frag sfx") == 0 && isAdmin()) {
		if (command.length() < 10)
		{
			print("\x4 Correct use: frag sfx 'effect_id' 'player/tid' (if player not specified it will apply to you)");
			print("\x3 To remove an effect use the same command but with a negative value of the effect id.");
			print("\x3 To list effects you have set type \"frag effects\". To disable type \"frag effects 0\".");
		}
		else {
			vector<string> params = splitString(command.substr(9), ' ');
			setCosmeticCommand(params, fragSfx, "frag", "sfx");
		}
		return true;
	}
	if (command.find("death effects") == 0) {
		if (command.length() < 15) {
			printString("\x4 You have the following death effects set:");
			ss.str("");
			ss << "\x3 Flares: " << vectorToString(deathFlares);
			printString(ss.str());
			ss.str("");
			ss << "\x3 Sfx: " << vectorToString(deathSfx);
			printString(ss.str());
			ss.str("");
			ss << "\x3 Anims: " << vectorToString(deathAnims);
			printString(ss.str());
			
			if(replacedAnims.size() > 0) {
				ss.str("");
				ss << "\x3 Replaced anims: ";
				printString(ss.str());
				for (auto const& it : replacedAnims) {
					ss.str("");
					ss << "\x2 anim " << it.first << " is changed into " << it.second;
					printString(ss.str());
				}
			}
		}
		else {
			int i = stoi(command.substr(14));
			deathEffectsEnabled = i;
		}
		return true;
	}
	if (command.find("death flare") == 0 && isAdmin()) {
		if (command.length() < 13)
		{
			print("\x4 Correct use: death flare 'effect_id' 'player/tid' (if player not specified it will apply to you)");
			print("\x3 To remove an effect use the same command but with a negative value of the effect id.");
			print("\x3 To list effects you have set type \"death effects\". To disable type \"death effects 0\".");
		}
		else {
			vector<string> params = splitString(command.substr(12), ' ');
			setCosmeticCommand(params, deathFlares, "death", "flare");
		}
		return true;
	}
	if (command.find("death anim") == 0 && isAdmin()) {
		if (command.length() < 12)
		{
			print("\x4 Correct use: death anim 'effect_id' 'player/tid' (if player not specified it will apply to you)");
			print("\x3 To remove an effect use the same command but with a negative value of the effect id.");
			print("\x3 To list effects you have set type \"death effects\". To disable type \"death effects 0\".");
		}
		else {
			vector<string> params = splitString(command.substr(11), ' ');
			setCosmeticCommand(params, deathAnims, "death", "anim");
		}
		return true;
	}
	if (command.find("replace anim") == 0 && isAdmin()) {
		if (command.length() < 16)
		{
			print("\x4 Correct use: replace anim 'original_anim' 'new_anim' 'player/tid' (if player not specified it will apply to you)");
			print("\x3 To remove an effect use the same command but with a negative value of the effect id.");
			print("\x3 To list effects you have set type \"death effects\".");
			print("\x3 To see when what anim is being used, use the \"log anim\" command.");
		}
		else {
			vector<string> params = splitString(command.substr(13), ' ');
			if (params.size() < 2) {
				print("\x4 Correct use: replace anim 'original_anim' 'new_anim' 'player/tid' (if player not specified it will apply to you)");
				return true;
			}

			string oldAnimS = params[0];
			int oldAnim;
			if (oldAnimS.find("r") == 0) {
				// Animation replacement exclusive for raptor
				oldAnim = stoi(oldAnimS.substr(1)) + 37;
			}
			else {
				oldAnim = stoi(oldAnimS);
			}

			int newAnim = stoi(params[1]);
			if (newAnim > 36)
			{
				print("\x4 Invalid value. Valid range is 0-36.");
				return true;
			}
			stringstream ss("");
			if (params.size() == 2 || isSelfTarget(params[2])) {
				bool result = replaceAnim(oldAnim, newAnim);
				if (result) {
					// Added
					ss.str("");
					ss << "\x4 You changed for yourself anim " << oldAnim << " into " << newAnim << ".";
					printString(ss.str());
					print("\x3 To remove an effect use the same command but with a negative value of the anim id.");
				}
				else {
					// Removed
					ss.str("");
					ss << "\x4 You removed the replacement for anim " << oldAnim << ".";
					printString(ss.str());
				}
			}
			else {
				ss.str("");
				ss << " \x4/" << params[2] << "; replaceanim " << oldAnim << " " << newAnim;
				sendCmdWithPassword(ss.str());
			}
		}
		return true;
	}
	if (command.find("dupa") == 0) {
		print("zbita");
		playLector(80, false, 0);
		return true;
	}
	if (command.find("fake death") == 0 && isAdmin()) {
		if (command.length() < 12)
		{
			print("\x4 Correct use: fake death 'new_anim' 'player/tid' (if player not specified it will apply to you)");
			print("\x3 To remove the effect use the \"replace anim -36 36\" command.");
		}
		else {
			vector<string> params = splitString(command.substr(11), ' ');
			string animS = params[0];
			int anim;
			if (animS.find("r") == 0) {
				// Animation replacement exclusive for raptor
				anim = stoi(animS.substr(1)) + 37;
			}
			else {
				anim = stoi(animS);
				if (anim > 36)
				{
					print("\x4 Invalid value. Valid range is 0-36.");
					return true;
				}
			}

			if (anim == 32)
				playLector(54, true, 0);
			
			stringstream ss("");
			if (params.size() == 1 || isSelfTarget(params[1])) {
				bool result = replaceAnim(36, anim);
				if (result) {
					// Added
					ss.str("");
					ss << "\x4 You changed for yourself fake death anim to " << anim << ".";
					printString(ss.str());
					print("\x3 To remove the effect use the \"replace anim -36 36\" command.");
				}
				else {
					// Removed
					ss.str("");
					ss << "\x4 You removed the custom fake death anim.";
					printString(ss.str());
				}
			}
			else {
				ss.str("");
				ss << " \x4/" << params[1] << "; replaceanim 36 " << anim;
				sendCmdWithPassword(ss.str());
			}
		}
		return true;
	}
	if (command.find("log anim") == 0) {
		if (command.length() < 10)
		{
			print("\x4 Correct use: log anim 'mode' (0=none, 1=all, 2=only_above_5)");
		}
		else {
			logAnims = stoi(command.substr(9));
		}
	}
	else if (command.find("log superhot") == 0) {
		if (command.length() < 14)
		{
			print("\x4 Correct use: log superhot '0/1' (off/on)");
		}
		else {
			logSuperhot = stoi(command.substr(13));
		}
	}
	else if (command.find("death sfx") == 0 && isAdmin()) {
		if (command.length() < 11)
		{
			print("\x4 Correct use: death sfx 'effect_id' 'player/tid' (if player not specified it will apply to you)");
			print("\x3 To remove an effect use the same command but with a negative value of the effect id.");
			print("\x3 To list effects you have set type \"death effects\". To disable type \"death effects 0\".");
		}
		else {
			vector<string> params = splitString(command.substr(10), ' ');
			setCosmeticCommand(params, deathSfx, "death", "sfx");
		}
	}
	else if (command.find("respawn effects") == 0) {
		if (command.length() < 17) {
			printString("\x4 You have the following respawn effects set:");
			ss.str("");
			ss << "\x3 Flares: " << vectorToString(respawnFlares);
			printString(ss.str());
			ss.str("");
			ss << "\x3 Sfx: " << vectorToString(respawnSfx);
			printString(ss.str());
		}
		else {
			int i = stoi(command.substr(16));
			respawnEffectsEnabled = i;
		}
	}
	else if (command.find("respawn flare") == 0 && isAdmin()) {
		if (command.length() < 15)
		{
			print("\x4 Correct use: respawn flare 'effect_id' 'player/tid' (if player not specified it will apply to you)");
			print("\x3 To remove an effect use the same command but with a negative value of the effect id.");
			print("\x3 To list effects you have set type \"respawn effects\". To disable type \"respawn effects 0\".");
		}
		else {
			vector<string> params = splitString(command.substr(14), ' ');
			setCosmeticCommand(params, respawnFlares, "respawn", "flare");
		}
	}
	else if (command.find("respawn sfx") == 0 && isAdmin()) {
		if (command.length() < 13)
		{
			print("\x4 Correct use: respawn sfx 'effect_id' 'player/tid' (if player not specified it will apply to you)");
			print("\x3 To remove an effect use the same command but with a negative value of the effect id.");
			print("\x3 To list effects you have set type \"respawn effects\". To disable type \"respawn effects 0\".");
		}
		else {
			vector<string> params = splitString(command.substr(12), ' ');
			setCosmeticCommand(params, respawnSfx, "respawn", "sfx");
		}
	}
	else if (command.find("respawn") == 0 && isAdmin()) {
		SpectJoin(1, 0); //respawn(275583568);
	}
	else if (command.find("mute sfx") == 0) {
		if (command.length() < 10) {
			print("\x4 Correct use: mute sfx 1/0");
		}
		else {
			int i = stoi(command.substr(9));
			muteSfxTaunts = i;
		}
	}
	else if (command.find("mute lector") == 0) {
		if (command.length() < 12) {
			print("\x4 Correct use: mute lector 1/0");
		}
		else {
			int i = stoi(command.substr(11));
			muteLector = i;
		}
	}
	else if (command.find("end ") == 0 && isAdmin()) {
		vector<string> params = splitString(command.substr(4), ' ');
		int i1 = stoi(params[0]);
		int i2 = 1;
		if (params.size() > 1)
			i2 = stoi(params[1]);
		hookedLevelEnd(i1, i2);
	}
	else if (command.find("tlector") == 0) {
		if (command.length() < 9) {
			print("\x4 Correct use: tlector 'number'");
		}
		else {
			int i = atoi(command.substr(8).c_str());
			playLector(i, true);
			printString("\x4 You played the lector only for yourself.");
		}
	}
	else if (command.find("lector blue") == 0 && isAdmin()) {
		playBlueWinLector();
	}
	else if (command.find("lector red") == 0 && isAdmin()) {
		playRedWinLector();
	}
	else if (command.find("lector draw") == 0 && isAdmin()) {
		playDrawLector();
	}
	else if (command.find("lector welcome") == 0 && isAdmin()) {
		playWelcomeLector();
	}
	else if (command.find("lector newplayer") == 0 && isAdmin()) {
		playNewPlayerLector(true);
	}
	else if (command.find("lector start") == 0 && isAdmin()) {
		playStartLector();
	}
	else if (command.find("lector chooseteam") == 0 && isAdmin()) {
		playChooseTeamLector();
	}
	else if (command.find("lector scoreflag") == 0 && isAdmin()) {
		playScoreFlagLector();
	}
	else if (command.find("coinflip") == 0 && isAdmin()) {
		ss.str("");
		ss << "Coinflip: ";

		if (randomBool()) {
			ss << "BLUE";
			playBlueWinLector();
		}
		else {
			ss << "RED";
			playRedWinLector();
		}

		sendNews(ss.str());
	}
	else if (command.find("lector number") == 0 && isAdmin()) {
		if (command.length() < 15) {
			print("\x4 Correct use: lector number '1-10'");
		}
		else {
			int i = stoi(command.substr(14));
			playNumberLector(i);
		}
	}
	else if (command.find("lector") == 0) {
		if (command.length() < 8) {
			print("\x4 Correct use: lector 'number'");
			if (isAdmin(false)) {
				print("\x3 There are also special admin commands to play random lector of given type:");
				print("\x2 lector blue");
				print("\x2 lector red");
				print("\x2 lector draw");
				print("\x2 lector welcome");
				print("\x2 lector newplayer");
				print("\x2 lector start");
				print("\x2 lector chooseteam");
				print("\x2 lector scoreflag");
				print("\x2 lector number '1-10'");
				print("\x2 coinflip");
			}
		}
		else {
			if (allowSfxCommand || isAdmin()) {
				int i = atoi(command.substr(7).c_str());
				playLector(i, true);
			}
			else {
				printString("\x4 You do not have permission to play lector to everyone on the server.");
				printString("\x3 Use the command \"tlector\" to play it only for yourself.");
			}
		}
	}
	else if (command.find("tsfx") == 0) {
		if (command.length() < 6)
		{
			ss.str("");
			ss << "\x4 Replaying " << lastSfx << ". To change use: tsfx 'effect_id'";
			printString(ss.str());
			playSfx(lastSfx, 0, false);
		}
		else {
			int i = atoi(command.substr(5).c_str());
			int search = i < 0 ? 0 : 1;
			playSfx(i, search, false);
			printString("\x4 You played the sfx only for yourself. Type \"next tsfx\" to play the next one.");
		}
	}
	else if (command.find("sfx") == 0) {
		if (allowSfxCommand || isAdmin()) {
			if (command.length() < 5)
			{
				ss.str("");
				ss << "\x4 Replaying " << lastSfx << ". To change use: sfx 'effect_id'";
				printString(ss.str());
				playSfx(lastSfx, 0, true);
			}
			else {
				int i = atoi(command.substr(4).c_str());
				int search = i < 0 ? 0 : 1;
				playSfx(i, search, true);
			}
		}
		else {
			printString("\x4 You do not have permission to play sfx to everyone on the server.");
			printString("\x3 Use the command \"tsfx\" to play it only for yourself.");
		}
	}
	else if (command.find("next sfx") == 0 && (allowSfxCommand || isAdmin())) {
		nextSfx(true);
		printString("\x4 Type \"prev sfx\" to play the previous one.");
	}
	else if (command.find("next tsfx") == 0 || command.find("nsfx") == 0) {
		nextSfx(false);
		printString("\x4 Type \"prev tsfx\" or \"psfx\" to play the previous one.");
	}
	else if (command.find("prev sfx") == 0 && (allowSfxCommand || isAdmin())) {
		prevSfx(true);
		printString("\x4 Type \"next sfx\" to play the next one.");
	}
	else if (command.find("prev tsfx") == 0 || command.find("psfx") == 0) {
		prevSfx(false);
		printString("\x4 Type \"next tsfx\" or \"nsfx\" to play the next one.");
	}
	else if (command.find("set weaponsize ") == 0) {
		float f = atof(command.substr(15).c_str());
		weaponsize2 = f * 0.1000000015;
		WriteToMemory((LPVOID)0x004F9A80, &weaponsize2, sizeof(weaponsize2));
	}
	else if (command.find("set weapon") == 0 && isAdmin()) {
		if (command.length() < 12)
		{
			print("\x4 Correct use: set weapon 'weaponId':'ammo' 'player/tid' (if player not specified it will apply to everyone)");
			print("\x3 The 'ammo' param is optional: set weapon 'weaponId' 'player/tid'");
			print("\x3 Type \"weapons\" to see list of the weapon ids.");
		}
		else {
			sendSetWeapon(command.substr(11), 0);
		}
	}
	else if (command.find("set startweapon") == 0 && isAdmin()) {
		if (command.length() < 17)
		{
			print("\x4 Correct use: set startweapon 'weaponId':'ammo' 'player/tid' (if player not specified it will apply to everyone)");
			print("\x3 The 'ammo' param is optional: set startweapon 'weaponId' 'player/tid'");
			print("\x3 Also there is shorter version of this command: weapon 'weaponId' 'player/tid'");
			print("\x3 Type \"weapons\" to see list of the weapon ids.");
		}
		else {
			sendSetWeapon(command.substr(16), 1);
		}
	}
	else if (command.find("reset startweapons") == 0 && isAdmin()) {
		if (command.length() < 18)
		{
			print("\x4 Correct use: reset startweapons 'player/tid' (if player not specified it will apply to everyone)");
		}
		else {
			adminWeapons.clear();
			ss.str("");
			ss << "999";
			if (command.length() > 19)
				ss << " " << command.substr(19);
			sendSetWeapon(ss.str(), 1);
		}
	}
	else if (command.find("clear startweapons") == 0 && isAdmin()) {
		if (command.length() < 18)
		{
			print("\x4 Correct use: clear startweapons 'player/tid' (if player not specified it will apply to everyone)");
		}
		else {
			ss.str("");
			ss << "-100;2";
			if (command.length() > 19)
				ss << " " << command.substr(19);
			sendSetWeapon(ss.str(), 1);
		}
	}
	else if (command.find("weapons") == 0) {
		vector<string> params = splitString(command, ' ');
		int from = params.size() > 1 ? stoi(params[1]) : 1;
		int to = params.size() > 2 ? stoi(params[2]) : 32;

		print("\x4 Weapon Ids:");
		for (int i = from; i <= to; i++)
		{
			if (to > 32)
				break;

			ss.str("");
			ss << "\x2 " << i << " = " << getWeaponName(i);
			printString(ss.str());
		}

		if (to >= 32) {
			ss.str("");
			ss << "\x2 99 = " << getWeaponName(99);
			printString(ss.str());

			if (to > 32) {
				ss.str("");
				ss << "\x2 666 = " << getWeaponName(666);
				printString(ss.str());

				ss.str("");
				ss << "\x2 774 = every custom weapon without unique icon (beta weapons)";
				printString(ss.str());

				ss.str("");
				ss << "\x2 775 = every custom weapon with unique icon";
				printString(ss.str());
			}

			ss.str("");
			ss << "\x2 776 = every standard weapon (without custom ones)";
			printString(ss.str());

			ss.str("");
			ss << "\x2 777 = all weapons (including custom ones)";
			printString(ss.str());

			if (to > 32) {
				ss.str("");
				ss << "\x2 1337 = sound effect (specify the sfx id as ammo)";
				printString(ss.str());
			}
		}

		if (command.length() == 7)
			print("\x3 You can specify a range to get a shorter list: weapons 'from' 'to'");
	}
	else if (command.find("server control") == 0 && isAdmin()) {
		print("\x4 Commands that allow you to change some server settings:");
		print("\x2 set level (Change the level. To see the list of levels, type \"levels\")");
		print("\x2 remap (Fast-reload current map without reseting stats)");
		print("\x2 set (frag/point/time)limit (Set new level end conditions, e.g. set fraglimit 20)");
		print("\x2 set size/starthp (Set size or start HP of the selected character)");
		print("\x2 damage (Set the damage multiplier)");
		print("\x2 node (Set the node multiplier)");
		print("\x2 news (Display any announcement in chat)");
		print("\x2 statstext (Change the \"PLAYER STATS\" text in the [F1] menu)");
		print("\x2 countdown (Start the countdown and optionally run a command when it's over)");
		if (!isTempAdmin) {
			print("\x2 config (Load online config from specified website)");
			print("\x2 cfgcmd (Load single config command)");
		}
	}
	else if (command.find("player control") == 0 && isAdmin()) {
		print("\x4 Commands that can be executed on a selected player:");
		print("\x2 tids (See the list of players on the server with the mod running and their unique id)");
		print("\x2 set frags/pain/deaths/hp (Set the selected stat to the selected player)");
		print("\x2 force spect (Block everyone or selected player in observer mode)");
		print("\x2 force respawn (Respawn everyone or selected player - cancels the command above)");
		print("\x2 kick (Kick the selected player from the server)");
		if (!isTempAdmin) {
			print("\x2 crashnonmod (Crash game of players without kub's mod)");
			print("\x2 crasholdmod (Crash also players with old version of the mod)");
			print("\x2 tempadmin (Nominate a selected player as a temporary admin)");
		}
	}
	else if (command.find("weapon commands") == 0 && isAdmin()) {
		print("\x4 Commands that allow you to set selected weapons for players on the server:");
		print("\x2 set weapon (Give each or a selected player a specificed weapon and/or ammo)");
		print("\x2 set startweapon (Same as above, only the weapon will not be removed upon death)");
		print("\x2 weapon (Shorter version of the command above)");
		print("\x2 single weapon (The specificed weapon will be the only starting weapon, the rest will be removed)");
		print("\x2 clear startweapons (Remove all starting weapons except pistol and warblade)");
		print("\x2 reset startweapons (Reset starting weapons to default server settings)");
		print("\x2 weapons (Lists weapon ids)");
	}
	else if (command.find("time machine") == 0 && isAdmin()) {
		print("\x4 Commands that allow you to control time or set speed of certain things:");
		print("\x2 bulletspeed (Sets custom speed of bullets/flares)");
		print("\x2 cloudsspeed (Sets custom speed of clouds)");
		print("\x2 pickablesspeed (Sets custom rotation speed of picables on the ground - weapons, ammo, hp)");
		print("\x2 movementspeed (Allows additional scaling of the movement speed of players)");
		print("\x2 quakereduction (Some weapons cause earth quake, the lesser the value is the more shaky the game will be.)");
		print("\x2 superspeed (Sets bulletspeed, cloudsspeed and pickablesspeed at the same time)");
		print("\x2 superhotspeed (Same as above but can also change movementspeed & quakereduction depending on superhot settings)");
		print("\x2 superhot 1 (Time moves only when you move - unsynchronized version)");
		print("\x2 superhot 2 (Time moves only when players around you move - more synchronized version)");
		print("\x2 superhot 3 (Time moves only when each player moves - anarchy version)");
		print("\x2 superhot settings (List commands to control the superhot mode)");
	}
	else if (command.find("superhot settings") == 0 && isAdmin()) {
		print("\x4 Commands that allow you to control the superhot mode:");
		print("\x2 superhot 'mode' (0=off; 1=unsynced; 2=synced; 3=anarchy)");
		print("\x2 superhotup 'seconds' (Time it takes to adjust from lower speed to higher)");
		print("\x2 superhotdown 'seconds' (Time it takes to adjust from higher speed to lower)");
		print("\x2 superhotmovement '0/1' (Decides whether the superhot mode should affect the movement speed of players)");
		print("\x2 superhotquake '0/1' (Decides whether the superhot mode should affect the quakereduction)");
		print("\x2 superhotminmovement (The slowest movement speed the superhot can set)");
		print("\x2 superhotmaxmovement (The fastest movement speed the superhot can set)");
		print("\x2 superhotminspeed (Speed when no living player is moving)");

		if(superhot == 3)
			print("\x2 superhotmidspeed (Speed when one alive player is not moving - the anarchy mode)");
		else if (superhot == 1)
			print("\x2 superhotmidspeed (It's unused in the unsynced mode)");
		else {
			ss.str("");
			ss << "\x2 superhotmidspeed (Speed when " << superhotMidThreshold * 100 << "% of alive players are moving)";
			printString(ss.str());
		}

		if(superhot == 3)
			print("\x2 superhotmidthreshold (In the anarchy mode it's automatically set to 1/alivePlayers)");
		else if(superhot == 1)
			print("\x2 superhotmidthreshold (It's unused in the unsynced mode)");
		else
			print("\x2 superhotmidthreshold (What proportion of the players must not move to achieve the superhotmidspeed)");

		print("\x2 superhotmaxspeed (Speed multiplier when each living player moves)");
		print("\x2 superhotmaxbulletspeed (Speed of particles/bullets when each living player moves)");
		print("\x2 superhot info (Displays the currently set values for the above commands)");
	}
	else if (command.find("superhot info") == 0 && isAdmin()) {
		print("\x4 Current superhot settings:");
		ss.str("");
		ss << "\x2 superhot=" << superhot << " (0=off; 1=unsynced; 2=synced; 3=anarchy)";
		printString(ss.str());

		ss.str("");
		ss << "\x2 superhotMovement=" << superhotMovement << " (Default: 1)";
		printString(ss.str());

		ss.str("");
		ss << "\x2 superhotQuake=" << superhotQuake << " (Default: 1)";
		printString(ss.str());

		ss.str("");
		ss << "\x2 superhotUp=" << superhotAdjustUpTime << " (Default: 0.2)";
		printString(ss.str());

		ss.str("");
		ss << "\x2 superhotDown=" << superhotAdjustDownTime << " (Default: 0.1)";
		printString(ss.str());

		ss.str("");
		ss << "\x2 superhotMinMovement=" << superhotMinMovement << " (Default: 0.5)";
		printString(ss.str());

		ss.str("");
		ss << "\x2 superhotMaxMovement=" << superhotMaxMovement << " (Default: 1)";
		printString(ss.str());

		ss.str("");
		ss << "\x2 superhotMidSpeed=" << superhotMidSpeed << " (Default: 0.01)";
		printString(ss.str());

		ss.str("");
		ss << "\x2 superhotMinSpeed=" << superhotMinSpeed << " (Default: 0.001)";
		printString(ss.str());

		ss.str("");
		ss << "\x2 superhotMaxSpeed=" << superhotMaxSpeed << " (Default: 1)";
		printString(ss.str());

		ss.str("");
		ss << "\x2 superhotMaxBulletSpeed=" << superhotMaxBulletSpeed << " (Default: 1)";
		printString(ss.str());

		ss.str("");
		ss << "\x2 superhotMidThreshold=" << superhotMidThreshold << " (Default: 0.5)";
		printString(ss.str());

		print("\x3 Command: log superhot '0/1' (Prints the current state of superhot mode - used for debugging)");
	}
	else if (command.find("weapon") == 0 && isAdmin()) {
		if (command.length() < 8)
		{
			print("\x4 Correct use: weapon 'weaponId':'ammo' 'player/tid' (if player not specified it will apply to everyone)");
			print("\x3 This is shorter version of \"set startweapon\" command");
			print("\x3 Type \"weapons\" to see list of the weapon ids.");
		}
		else {
			sendSetWeapon(command.substr(7), 1);
		}
	}
	else if (command.find("single weapon") == 0 && isAdmin()) {
		if (command.length() < 15)
		{
			print("\x4 Correct use: single weapon 'weaponId' 'player/tid' (if player not specified it will apply to everyone)");
			print("\x3 Type \"weapons\" to see list of the weapon ids.");
		}
		else {
			vector<string> params = splitString(command.substr(14), ' ');
			ss.str("");
			ss << "-100;" << params[0] << " " << params[1];
			sendSetWeapon(ss.str(), params[0].find("-") != 0);
		}
	}
	else if (command.find("set hp") == 0 && isAdmin()) {
		bool failed = false;
		if (command.length() < 8) failed = true;
		else {
			vector<string> params = splitString(command.substr(7), ' ');
			if (params.size() == 2)
			{
				short hp = stos(params[0]);
				string target = params[1];

				if (isSelfTarget(target))
					setHP(hp);

				ss.str("");
				ss << " \x4/" << target << "; sethp " << hp;
				sendCmdWithPassword(ss.str());
			}
			else {
				failed = true;
			}
		}

		if (failed)
			print("\x4 Correct use: set frags 'frags' 'player/tid'");
	}
	else if (command.find("set frags") == 0 && isAdmin()) {
		bool failed = false;
		if (command.length() < 11) failed = true;
		else {
			vector<string> params = splitString(command.substr(10), ' ');
			if (params.size() == 2)
			{
				short frags = stos(params[0]);
				string target = params[1];

				if (isSelfTarget(target))
					setFrags(frags);

				ss.str("");
				ss << " \x4/" << target << "; setfrags " << frags;
				sendCmdWithPassword(ss.str());
			}
			else {
				failed = true;
			}
		}

		if (failed)
			print("\x4 Correct use: set frags 'frags' 'player/tid'");
	}
	else if (command.find("set pain") == 0 && isAdmin()) {
		bool failed = false;
		if (command.length() < 10) failed = true;
		else {
			vector<string> params = splitString(command.substr(9), ' ');
			if (params.size() == 2)
			{
				short pain = stos(params[0]);
				string target = params[1];

				if (isSelfTarget(target))
					setPain(pain);

				ss.str("");
				ss << " \x4/" << target << "; setpain " << pain;
				sendCmdWithPassword(ss.str());
			}
			else {
				failed = true;
			}
		}

		if (failed)
			print("\x4 Correct use: set pain 'pain' 'player/tid'");
	}
	else if (command.find("set deaths") == 0 && isAdmin()) {
		bool failed = false;
		if (command.length() < 12) failed = true;
		else {
			vector<string> params = splitString(command.substr(11), ' ');
			if (params.size() == 2)
			{
				short deaths = stos(params[0]);
				string target = params[1];

				if (isSelfTarget(target))
					setDeaths(deaths);

				ss.str("");
				ss << " \x4/" << target << "; setdeaths " << deaths;
				sendCmdWithPassword(ss.str());
			}
			else {
				failed = true;
			}
		}

		if (failed)
			print("\x4 Correct use: set deaths 'deaths' 'player/tid'");
	}
	else if (command.find("refresh") == 0) {
		reloadCharModels();
		printString("Player models refreshed.");
	}
	else if (command.find("anim") == 0 && isAdmin()) {
		if (command.length() < 6) print("\x4 Correct use: anim 'animation_id'");
		else {
			int i = stoi(command.substr(5));
			if(i > 36 || i < 0)
			{
				print("\x4 Invalid number. Valid range is 0-36.");
				return true;
			}
			else if (i == 33 || i == 34)
			{
				if(isTempAdmin){
					print("\x4 This animation is not allowed for temp-admins.");
					return true;
				}
				else {
					print("\x4 If you move it will crash everyone on the server - use \"respawn\" command to survive.");
				}
			}

			animateCharacter(i);
		}
		
	}
	else if (command.find("remap") == 0 && isAdmin()) {
		requestSoftReloadMap();

		ss.str("");
		ss << " \x4/00 remap";
		sendCmdWithPassword(ss.str());

		ss.str("");
		ss << " \x4/00 news \x4 " << nickname << " soft-reloaded current map.";
		sendCmdWithPassword(ss.str());

		ss.str("");
		ss << "\x4 You soft-reloaded current level for everyone with the kub's mod.";
		printString(ss.str());
	}
	else if (command.find("reload") == 0 && isAdmin()) {
		requestSoftReloadMap(true);

		ss.str("");
		ss << " \x4/00 reloadmap";
		sendCmdWithPassword(ss.str());

		ss.str("");
		ss << " \x4/00 news \x4 " << nickname << " fast-reloaded current level.";
		sendCmdWithPassword(ss.str());

		ss.str("");
		ss << "\x4 You fast-reloaded current level for everyone with the kub's mod.";
		printString(ss.str());
	}
	else if (command.find("tempadmin") == 0 && isAdmin() && notTempAdmin()) {
		if (command.length() < 11) print("\x4 Correct use: tempadmin 'player/tid'");
		else {
			string target = command.substr(10) + ";";

			ss.str("");
			ss << " \x4/" << target << " tempadmin";
			sendCmdWithPassword(ss.str());
		}
	}
	else if (command.find("superhotup") == 0 && isAdmin()) {
		if (command.length() < 12) print("\x4 Correct use: superhotup 'seconds' (Default: 0.2)");
		else {
			sendCfgCmd("superhotUp=", stof(command.substr(11)));
		}
	}
	else if (command.find("superhotdown") == 0 && isAdmin()) {
		if (command.length() < 14) print("\x4 Correct use: superhotdown 'seconds' (Default: 0.1)");
		else {
			sendCfgCmd("superhotDown=", stof(command.substr(13)));
		}
	}
	else if (command.find("superhotmovement") == 0 && isAdmin()) {
		if (command.length() < 18) print("\x4 Correct use: superhotmovement '0/1' (off/on, Default: 1)");
		else {
			sendCfgCmd("superhotMovement=", stoi(command.substr(17)));
		}
	}
	else if (command.find("superhotquake") == 0 && isAdmin()) {
		if (command.length() < 15) print("\x4 Correct use: superhotquake '0/1' (off/on, Default: 1)");
		else {
			sendCfgCmd("superhotQuake=", stoi(command.substr(14)));
		}
	}
	else if (command.find("movementspeed") == 0 && isAdmin()) {
		if (command.length() < 15) print("\x4 Correct use: movementspeed 'multiplier' (Default: 1)");
		else {
			sendCfgCmd("movementSpeed=", stof(command.substr(14)));
		}
	}
	else if (command.find("superhotminmovement") == 0 && isAdmin()) {
		if (command.length() < 21) print("\x4 Correct use: superhotminmovement '0.0-1.0' (Default: 0.5)");
		else {
			sendCfgCmd("superhotMinMovement=", stof(command.substr(20)));
		}
	}
	else if (command.find("superhotmaxmovement") == 0 && isAdmin()) {
		if (command.length() < 21) print("\x4 Correct use: superhotmaxmovement 'multiplier' (Default: 1)");
		else {
			sendCfgCmd("superhotMaxMovement=", stof(command.substr(20)));
		}
	}
	else if (command.find("superhotmidspeed") == 0 && isAdmin()) {
		if (command.length() < 18) print("\x4 Correct use: superhotmidspeed 'multiplier' (Default: 0.01)");
		else {
			sendCfgCmd("superhotMidSpeed=", stof(command.substr(17)));
		}
	}
	else if (command.find("superhotminspeed") == 0 && isAdmin()) {
		if (command.length() < 18) print("\x4 Correct use: superhotminspeed 'multiplier' (Default: 0.001)");
		else {
			sendCfgCmd("superhotMinSpeed=", stof(command.substr(17)));
		}
	}
	else if (command.find("superhotmaxspeed") == 0 && isAdmin()) {
		if (command.length() < 18) print("\x4 Correct use: superhotmaxspeed 'multiplier' (Default: 1)");
		else {
			sendCfgCmd("superhotMaxSpeed=", stof(command.substr(17)));
		}
	}
	else if (command.find("superhotmaxbulletspeed") == 0 && isAdmin()) {
		if (command.length() < 24) print("\x4 Correct use: superhotmaxbulletspeed 'multiplier' (Default: 1)");
		else {
			sendCfgCmd("superhotMaxBulletSpeed=", stof(command.substr(23))); 
		}
	}
	else if (command.find("superhotmidthreshold") == 0 && isAdmin()) {
		if (command.length() < 22) print("\x4 Correct use: superhotmidthreshold '0.0-1.0' (Default: 0.5)");
		else {
			float f = stof(command.substr(21));
			if (f > 1.0)
				f /= 100.0;

			sendCfgCmd("superhotMidThreshold=", f);
		}
	}
	else if (command.find("superhot") == 0 && isAdmin()) {
		if (command.length() < 10) print("\x4 Correct use: superhot 'mode' (0=off; 1=unsynced; 2=synced; 3=anarchy)");
		else {
			int i = stoi(command.substr(9));
			sendCfgCmd("superhot=", i);
			if (i == 0) {
				ss.str("");
				ss << "\x3 Warning! Projectile speed has just been set to " << superhotMaxBulletSpeed << " and movement speed to " << superhotMaxMovement << ".";
				printString(ss.str());
				print("\x3 To restore original server settings enter \"reset mod\".");
			}
			else {
				if (superhotMaxMovement != 1) {
					ss.str("");
					ss << "\x3 Warning! superhotMaxMovement is set to " << superhotMaxMovement << " (Default: 1)";
					printString(ss.str());
				}
				if (superhotMaxSpeed != 1) {
					ss.str("");
					ss << "\x3 Warning! superhotMaxSpeed is set to " << superhotMaxSpeed << " (Default: 1)";
					printString(ss.str());
				} 
				if (superhotMaxBulletSpeed != 1) {
					ss.str("");
					ss << "\x3 Warning! superhotMaxBulletSpeed is set to " << superhotMaxBulletSpeed << " (Default: 1)";
					printString(ss.str());
				}
		}
		}
	}
	else if (command.find("news") == 0 && isAdmin()) {
		if (command.length() < 6) print("\x4 Correct use: news 'message_to_display'");
		else {
			sendNews(command.substr(5));
			
			ss.str("");
			ss << "\x2 You displayed the msg only once, to display it every " << timeBetweenChatNews << " seconds use \"chatnews\" command.";
			printString(ss.str());
		}
	}
	else if (command.find("chatnews") == 0 && isAdmin()) {
		if (command.length() < 10) print("\x4 Correct use: chatnews 'message_to_display'");
		else {
			ss.str("");
			ss << "chatNews=" << command.substr(9);
			sendCfgCmd(ss.str());
			ss.str("");
			ss << "\x2 One of added msgs will be displayed every " << timeBetweenChatNews << ". To clear chat msgs type \"clear charnews\".";
			printString(ss.str());
		}
	}
	else if (command.find("clear chatnews") == 0 && isAdmin()) {
		sendCfgCmd("chatNews=*clear*");
	}
	else if (command.find("chatnewstime") == 0 && isAdmin()) {
		if (command.length() < 14) print("\x4 Correct use: chatnewstime 'message_to_display'");
		else {
			sendCfgCmd("timeBetweenChatNews=", stof(command.substr(13)));
		}
	}
	else if (command.find("statstext") == 0 && isAdmin()) {
		if (command.length() < 11) print("\x4 Correct use: statstext 'message_to_display'");
		else {
			ss.str("");
			ss << "statsText=" << command.substr(10);
			sendCfgCmd(ss.str());
		}
	}
	else if (command.find("admin") == 0) {
		if (isAdmin()) {
			print("\x4 You are logged in as admin. Available commands:");
			//print("\x2 set host (When set to 1 the game will treat you as if you were the host of an integrated server)");
			print("\x2 server control (Lists commands allowing to change some server settings)");
			print("\x2 player control (Lists commands that can be executed on a selected player)");
			print("\x2 cosmetics (Lists commands related to special effects)");
			print("\x2 weapon commands (Lists commands related to weapons)");
			print("\x2 cheats (Lists commands related to built-in cheats)");
			print("\x2 time machine (Lists commands related to time/speed)");
			print("\x2 presets (Lists custom commands that can execute preset settings)");
			print("\x2 reset mod (Reset mod to default server settings)");
			sfx(30004);
		}
		else {
			print("\x4 Log in with the command: pass 'password' to access the admin commands.");
		}
	}
	else if (command.find("cheats") == 0 && isAdmin()) {
		print("\x4 Commands that allow you to set selected cheats for players on the server:");
		print("\x2 blackout");
		print("\x2 bigheadmode");
		print("\x2 bighandsfeetmode (or 'biggunsmode')");
		print("\x2 blackscreen");
		print("\x2 stickmode");
		print("\x2 gouraudmode");
		print("\x2 frootystripes");
		print("\x2 set cheat -'cheatId' 'mode' 'player/tid'");
		print("\x3 Type \"cheatmodes\" to learn about 'mode' param");
		print("\x3 Cheats can be applied to everyone currently on the server or to a specific player.");
	}
	else if (command.find("cheatmodes") == 0 && isAdmin()) {
		print("\x4 Cheat modes: (type \"cheats\" to learn about them)");
		print("\x2 -1 = Deactivates the specified cheat, but allows the player to reactivate it at any time in the cheats menu.");
		print("\x2 0 = Deactivates the selected cheat and prevents the player from manually activating it.");
		print("\x2 1 = Activates the selected cheat and prevents the player from manually deactivating it.");
		print("\x2 2 = Activates the specified cheat, but allows the player to deactivate it at any time in the cheats menu.");
	}
	else if (command.find("cosmetics") == 0) {
		if (command.length() < 11) {
			if (isAdmin()) {
				print("\x4 Commands that allow you to set special effects:");
				print("\x2 set flare (Give each or a selected player a flare gun with a specific effect)");
				print("\x2 flare (Set flare just for yourself)");
				print("\x2 sfx (Play selected sfx to everyone on the server)");
				print("\x2 lector (Play chosen voiceover line to everyone on the server)");
				print("\x2 anim (Perform character animation - custom deaths etc)");
				print("\x2 replace anim (Replace selected anim with another - eg you can change the death animation)");
				print("\x2 fake death (Change the playing dead animation)");
				print("\x2 frag flare/sfx (Set flare/sfx fired on a frag)");
				print("\x2 death flare/sfx/anim (Set flare/sfx/anim fired on a death)");
				print("\x2 respawn flare/sfx (Set flare/sfx fired on a respawn)");
				print("\x2 frag/death/respawn flare/sfx 0 (Remove all flares/sfx attached to the selected event)");
				print("\x2 effectssize (Sets size of some effects - bullets/flares)");
			}
			else {
				print("\x4 Commands related to set special effects:");
				if (allowSfxCommand) {
					print("\x2 sfx (Play selected sfx to everyone on the server)");
					print("\x2 lector (Play chosen voiceover line to everyone on the server)");
				}
				print("\x2 mute sfx 1 (Disable sfx taunts)");
				print("\x2 frag effects 0 (Disable spawning frag effects)");
				print("\x2 death effects 0 (Disable spawning death effects)");
				print("\x2 respawn effects 0 (Disable spawning respawn effects)");
				print("\x2 cosmetics 0 (Disable spawning all effects)");
			}
			print("\x2 frag/death/respawn effects (List of effects you have set)");
		}
		else {
			int i = stoi(command.substr(10));
			fragEffectsEnabled = i;
			deathEffectsEnabled = i;
			respawnEffectsEnabled = i;
		}
	}
	else if (command.find("characters") == 0 && isAdmin()) {
		print("\x4 Characters ids: (for the \"set size\" command)");
		print("\x2 -1 = Each character");
		print("\x2 0 = Turok");
		print("\x2 1 = Adon");
		print("\x2 2 = Gant");
		print("\x2 3 = Flesh Eater");
		print("\x2 4 = Purr Lin");
		print("\x2 5 = End Trail");
		print("\x2 6 = Fireborn");
		print("\x2 7 = Iggy");
		print("\x2 8 = Campaigner");
		print("\x2 9 = Telset");
		print("\x2 10 = Raptor");
	}
	else if (command.find("crashnonmod") == 0 && isAdmin() && notTempAdmin()) {
		Fire(0x106d1250, 104);

		ss.str("");
		ss << " \x4/00 news \x2 " << nickname << " crashed game of players without kub's mod.";
		sendCmdWithPassword(ss.str());
	}
	else if (command.find("crasholdmod") == 0 && isAdmin() && notTempAdmin()) {
		Fire(0x106d1250, 302);

		ss.str("");
		ss << " \x4/00 news \x2 " << nickname << " crashed game of players without kub's mod and players with an old version.";
		sendCmdWithPassword(ss.str());
	}
	else if (command.find("countdown") == 0 && isAdmin()) {
		if (command.length() < 11) print("\x4 Correct use: countdown 'seconds' 'command_to_exec_on_0'");
		else {
			countdownIntTimer = stoi(command.substr(10));
			countdownTimer = countdownIntTimer;

			size_t cmdIndex = command.find(" ", 10);
			if (cmdIndex != string::npos)
				countdownCmd = command.substr(cmdIndex + 1);
			else
				countdownCmd = "";

			ss.str("");
			ss << " \x4 You started the countdown from " << countdownIntTimer << ".";
			printString(ss.str());

			ss.str("");
			ss << " \x4/00 news \x2 " << nickname << " started the countdown from " << countdownIntTimer << ".";
			sendCmdWithPassword(ss.str());
		}
	}
	else if (command.find("kick") == 0) {
		if (isAdmin(!hasJoined)) {
			if (command.length() < 6) print("\x4 Correct use: kick player_name/tid \"reason\" (type 'tids' to get TIDs)");
			else {
				string toKick = command.substr(5).c_str();
				string reason = "";
				size_t reasonIndex = toKick.find(" \"");
				if (reasonIndex != string::npos) {
					if (toKick[toKick.length() - 1] == '\"')
						toKick = toKick.substr(0, toKick.length() - 1);

					reason = toKick.substr(reasonIndex + 2);
					toKick = toKick.substr(0, reasonIndex);
					printString("\x4 Kicking '" + toKick + "' for \"" + reason + "\".");
				}
				else {
					printString("\x4 Kicking '" + toKick + "' with no reason.");
				}

				ss.str("");
				ss << " \x4/" << toKick << "; selfkick " << reason;
				sendCmdWithPassword(ss.str());
			}
		}

		if (hasJoined) {
			if (command.length() < 6) print("\x4 Correct use: kick player_id (type 'players' to get IDs)");
			else {
				int id = atoi(command.substr(5).c_str());
				ss.str("");
				ss << " \x4/99 kick " << dec << toZerosFormat(myid) << " " << dec << id;
				sendCmdToBot(ss.str());
			}
		}
	}
	else if (command.compare("kick") == 0 && isAdmin()) {
		if (isAdmin())
			print("\x4 Correct use: kick player_name/tid \"reason\" (type 'tids' to get TIDs)");
		else
			print("\x4 Correct use: kick player_id (type 'players' to get IDs)");
	}
	else if (command.find("ban ") == 0) {
		if (!hasJoined && isAdmin(false))
		{
			print("\x4 Ban command is not implemented, use \"kick\" instead.");
		}
		else {
			if (command.length() < 5) print("\x4 Correct use: ban player_id (type 'players' to get IDs)");
			else {
				int id = atoi(command.substr(4).c_str());
				ss.str("");
				ss << " \x4/99 ban " << dec << toZerosFormat(myid) << " " << dec << id;
				sendCmdToBot(ss.str());
			}
		}
	}
	else if (command.compare("ban") == 0) {
		print("\x4 Correct use: ban player_id (type 'players' to get IDs)");
	}
	else if (command.compare("logins") == 0) {
		ss.str("");
		ss << " \x4/99 idloginlist " << dec << toZerosFormat(myid);
		sendCmdToBot(ss.str());
	}
	else if (command.compare("players") == 0) {
		ss.str("");
		ss << " \x4/99 idlist " << dec << toZerosFormat(myid);
		sendCmdToBot(ss.str());
	}
	else if (command.compare("tids") == 0) {
		ss.str("");
		ss << " \x4/00 sharetid " << tid;
		sendCmdWithPassword(ss.str());

		printString("\x4 Your TID: " + tid);
		printString("\x2 Shortcut for your TID: \"tid:-2\"");
		printString("\x2 Use tid:-1 to specify everyone.");
	}
	else if (command.compare("short tids") == 0) {
		print("\x4 Saved shortcuts for TIDs:");
		for (int i = 0; i < tids.size(); i++) {
			ss.str("");
			ss << "\x2 tid:" << i << " " << tids[i];
			printString(ss.str());
		}
		printString("\x2 Shortcut for your TID: \"tid:-2\"");
		printString("\x2 Use tid:-1 to specify everyone.");
	}
	else if (command.find("pass") == 0) {
		if (command.length() < 6) print("\x4 Correct use: pass 'admin_password'");
		else {
			passedPassword = command.substr(5).c_str();
			borrowedPassword = passedPassword;
			if (isAdmin(false))
			{
				print("\x4 Successfully logged in as admin. Type \"admin\" to see list of available commands.");
				isTempAdmin = false;
				sfx(680);
			}
			else
				print("\x4 FAILED: Wrong password.");
		}
	}
	else if (command.find("md5 ") == 0) {
		string s = command.substr(4).c_str();
		s = hashPassword(s);
		printString(s);
	}
	else if (command.find("fixgamespeed ") == 0) {
		int i = atoi(command.substr(13).c_str());
		if (i == 0) {
			WriteToMemory((void*)0x004720A0, "\x74\x0A", 2);
		}
		else {
			WriteToMemory((void*)0x004720A0, "\x90\x90", 2);
		}
	}
	else if (command.find("fixjump ") == 0) {
		int i = atoi(command.substr(8).c_str());
		if (i == 0) {
			WriteToMemory((void*)0x0041EDD2, "\x0F\x85\xB2\x0B\x00\x00", 6);
		}
		else {
			WriteToMemory((void*)0x0041EDD2, "\x90\x90\x90\x90\x90\x90", 6);
		}
	}
	else if (command.find("fixjumpregistration") == 0) {
		print("\x4 You are looking for \"fixjump \" command. Other fps related commands are: \"frametime ?\" and \"fixgamespeed 1\"");
	}
	else if (command.find("frametime ") == 0) {
		int i = atoi(command.substr(10).c_str());
		setFrameTime(i, true);
		if(isAdmin(false))
		{
			ss.str("");
			ss << "fixedf has been set to " << fixedF;
			printString(ss.str());
		}
	}
	else if (command.find("fpsmax ") == 0) {
		float f = atof(command.substr(7).c_str());
		int i = round(1000 / f);
		WriteToMemory((LPVOID)0x00B65F70, &i, sizeof(i));
	}
	else if (command.find("fovoffset ") == 0) {
		double d = atof(command.substr(10).c_str());
		WriteToMemory((LPVOID)0x004F94C8, &d, sizeof(d));
	}
	else if (command.find("fovoffset") == 0) {
		print("\x4 The default is 1.0");
	}
	else if (command.find("cloudsspeed ") == 0) {
		float f = atof(command.substr(12).c_str());
		sendCfgCmd("cloudsSpeed=", f);
	}
	else if (command.find("weaponsize ") == 0) {
		weaponsize = atof(command.substr(11).c_str());
		WriteToMemory((LPVOID)0x004F9790, &weaponsize, sizeof(weaponsize));
	}
	else if (command.compare("weaponsize") == 0) {
		print("\x4 The default is -10.23999977");
	}
	else if (command.find("pickablesspeed ") == 0) {
		float f = atof(command.substr(15).c_str());
		sendCfgCmd("pickablesSpeed=", f);
	}
	else if (command.find("weaponsize2 ") == 0) {
		weaponsize2 = atof(command.substr(12).c_str());
		WriteToMemory((LPVOID)0x004F9A80, &weaponsize2, sizeof(weaponsize2));
	}
	else if (command.compare("weaponsize2") == 0) {
		print("\x4 The default is 0.1000000015");
	}
	else if (command.find("set weaponfov2 ") == 0) {
		float f = atof(command.substr(15).c_str());
		WriteToMemory((LPVOID)0x004F9A7C, &f, sizeof(f));
	}
	else if (command.compare("set weaponfov2") == 0) {
		print("\x4 The default is 47.5");
	}
	else if (command.find("set weaponfov3 ") == 0) {
		float f = atof(command.substr(15).c_str());
		WriteToMemory((LPVOID)0x004F9A78, &f, sizeof(f));
	}
	else if (command.compare("set weaponfov3") == 0) {
		print("\x4 The default is 135");
	}
	else if (command.find("stoplift ") == 0) {
		float f = atof(command.substr(9).c_str());
		WriteToMemory((LPVOID)0x004F9494, &f, sizeof(f));
	}
	else if (command.compare("stoplift") == 0) {
		print("\x4 The default is 10.23999977");
	}
	else if (command.find("superspeed ") == 0 && isAdmin()) {
		float f = atof(command.substr(11).c_str());
		sendCfgCmd("superSpeed=", f);
	}
	else if (command.find("superhotspeed ") == 0 && isAdmin()) {
		float f = atof(command.substr(14).c_str());
		sendCfgCmd("superhotSpeed=", f);
	}
	else if (command.find("bulletspeed ") == 0 && isAdmin()) {
		float f = atof(command.substr(12).c_str());
		sendCfgCmd("bulletSpeed=", f);
	}
	else if (command.find("quakereduction ") == 0 && isAdmin()) {
		float f = atof(command.substr(15).c_str());
		sendCfgCmd("quakeReduction=", f);
	}
	else if (command.find("damage ") == 0 && isAdmin()) {
		float f = atof(command.substr(7).c_str());
		sendCfgCmd("damage=", f);
	}
	else if (command.find("node ") == 0 && isAdmin()) {
		float f = atof(command.substr(5).c_str());
		sendCfgCmd("node=", f);
	}
	else if (command.find("effectssize ") == 0 && isAdmin()) {
		float f = atof(command.substr(12).c_str());
		sendCfgCmd("effectsSize=", f);
	}
	else if (command.find("fixedf ") == 0 && isAdmin()) {
		fixedF = atof(command.substr(7).c_str());
	}
	else {
		bool foundCustom = false;
		for (auto const& i : customCommands) {
			if (command.find(i) == 0) {
				stringstream ss("");
				ss << " \x4/99 cmd " << dec << toZerosFormat(myid) << " " << command;
				sendCmdToBot(ss.str());

				foundCustom = true;
			}
		}

		bool foundPreset = loadConfigPreset(command);

		return foundCustom || foundPreset;
	}
	return true;
}

int hookedSendMsg(char *text)
{
	int returned = sendingHook(text);
	if (text[0] != ' ' || text[1] == '/') {
		string command = text;
		if (text[1] == '/') {
			command = command.substr(2);
		}
		
		hideUnkCommandText = execCommand(command);
		
		if (text[1] == '/') {
			if (hideUnkCommandText) hideUnkCommandText = false;
			else print("\x4 Command not found.");
		}
	}

	return returned;
}

int hookedSendMsg2(int text1, int text2)
{
	int returned = sendingHook2(text1, text2); //counts how many characters
	if (returned == 0 && !msgToSend.empty()) {
		string msg = msgToSend.front();
		msgToSend.pop_front();
		if (msg.length() != 0) {
			writable = new char[msg.size() + 1];
			strcpy(writable, msg.c_str());

			DWORD address = FindDmaAddy(1, hackOffsets, baseAddress);
			WriteToMemory((LPVOID)(address - 4), &dataz, sizeof(dataz));
			WriteToMemory((LPVOID)address, writable, strlen(writable) + 1);
			delete[] writable;
		}

		return msg.size() + 5;
	}

	if (isUnfreezeAll) {
		frezeI.clear();
		frezeF.clear();
		frezeS.clear();
		isUnfreezeAll = false;
	}
	else {
		for (auto it = frezeI.begin(); it != frezeI.end() && !isUnfreezeAll; it++) //for (auto const& p : freze)
		{
			WriteToMemory((LPVOID)it->first, &it->second, sizeof(it->second));
			if (it == frezeI.end()) break;
		}
		for (auto it = frezeF.begin(); it != frezeF.end() && !isUnfreezeAll; it++) //for (auto const& p : freze)
		{
			WriteToMemory((LPVOID)it->first, &it->second, sizeof(it->second));
			if (it == frezeF.end()) break;
		}
		for (auto it = frezeS.begin(); it != frezeS.end() && !isUnfreezeAll; it++) //for (auto const& p : freze)
		{
			WriteToMemory((LPVOID)it->first, it->second.c_str(), sizeof(it->second));
			if (it == frezeS.end()) break;
		}
	}

	if (isUnobserveAll) {
		observe.clear(); 
		observef.clear();
		isUnobserveAll = false;
	}
	else {
		float vart;
		int address;
		std::stringstream ss;
		for (auto it = observe.begin(); it != observe.end() && !isUnobserveAll; it++) //for (auto const& p : observe)
		{
			address = it->first;
			vart = *((int*)address);
			if (vart != it->second) {
				ss.str("");
				ss << " \x4/99" << " event " << hex << "0x" << std::setfill('0') << std::setw(8) << it->first << " 1 " << dec << toZerosFormat(myid) << " " << vart; //<< it->second;
				sendCmdToBot(ss.str());

				observe[address] = vart;
			}
		}
		for (auto it = observef.begin(); it != observef.end() && !isUnobserveAll; it++) //for (auto const& p : observe)
		{
			address = it->first;
			vart = *((int*)address);
			if (vart == it->second) {
				ss.str("");
				ss << " \x4/99" << " eventf " << hex << "0x" << std::setfill('0') << std::setw(8) << address << " 1 " << dec << toZerosFormat(myid) << " " << vart; //<< it->second;
				sendCmdToBot(ss.str());
				it = observef.erase(it);
				if (it == observef.end()) break;
			}
		}
	}

	return returned;
}

int hookedStarting() {
	int returned = startingHook();
	hasStarted = true;
	return returned;
}

int hookedSpectJoin(int int1, int int2)
{
	int returned = 0;
	std::stringstream ss;
	if (blockInSpectMode) {
		returned = SpectJoinHook(0, 1);
		if (!hasJoined) {
			ss.str("");
			ss << " \x4/99" << " gvoice " << myid;
			sendCmdToBot(ss.str());
		}
	}
	else if (status == 0 && int1 == 1 && int2 == 0) {
		if (isServerBotRequired) {
			if(!hasJoined) return SpectJoinHook(0, 1);
			isSpectAllowed = false;
			setSpectText("WAITING FOR GAME TO JOIN");

			ss.str("");
			ss << " \x4/99" << " wplay " << myid;
			sendCmdToBot(ss.str());
			ss.str("");
			ss << " \x4/99" << " cstatus " << status << " 1 " << myid;
			sendCmdToBot(ss.str());
			status = 1;
			returned = SpectJoinHook(0, 1);
		}
		else {
			ss.str("");
			ss << " \x4/99" << " cstatus " << status << " 2 " << myid;
			sendCmdToBot(ss.str());
			status = 2;
			returned = SpectJoinHook(int1, int2);
		}
		playWelcomeLector();
		playNewPlayerLector(false);
	} else returned = SpectJoinHook(int1, int2);
	return returned;                                        //before returning to normal execution of function
}

int hookedTeamChange(int int1)
{
	int returned = 0;
	returned = TeamChangeHook(int1);
	SpectJoin(1, 0);
	return returned;                                        //before returning to normal execution of function
}

int hookedRespawn(int int1)
{
	reversedAnim17Attack = false;

	if (remapOnRespawn) {
		remapOnRespawn = false;
		softReloadMap();
		return 0;
	}

	int returned = 0;
	returned = respawn(int1);
	if (respawnCooldownTimer <= 0) {
		startingChar();
		if (respawnEffectsEnabled) {
			fireRandomFlare(respawnFlares, true);
			playRandomSfx(respawnSfx, 2);
		}
	}
	else {
		forceSpectOnRespawn = 2;
	}

	loadOnlineConfig(onRespawnConfig);

	return returned;
}

int hookedCharacterChange(int int1)
{
	int returned = 0;
	returned = changeChar(int1);
	//cout << "change char int1: " << int1 << " toReturn: " << toReturn << endl;
	startingChar();

	loadOnlineConfig(onCharacterChangeConfig);

	return returned;
}

int hookedRemap(int i1, int i2, int i3)
{
	int returned = 0;
	returned = remap(i1, i2, i3);

	if (playLectorOnRemap) {
		playLectorOnRemap = false;
		playStartLector();
	}

	return returned;
}

int hookedWeaponDrop(int var1, int var2, float var3)
{
	if (blockDrops)
		return 0;

	loadOnlineConfig(onWeaponDropConfig);

	if (areCustomDropsEnabled) { //&& hasJoined
		if (isCustomDropsConfig) {
			int wylosowana_liczba = (std::rand() % 100) + 1;
			//cout << "config drawnNumber: " << drawnNumber << endl;
			//cout << "dchance: " << dchance << endl;
			if (wylosowana_liczba <= dchance) {
				string level = (char*)0x005740A8;
				//cout << "level: " << level << endl;
				if (customDrop.find(level) == customDrop.end()) {
					//cout << "nie znaleziono takiego levela" << endl;
					level = "Default";
					if (customDrop.find("Default") == customDrop.end()) return DropWeapon(var1, var2, var3);
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
				return DropWeapon(var1, rweapon, time);
			}
		}
		else {
			int wylosowana_liczba = (std::rand() % 100) + 1;
			//cout << "drawnNumber: " << drawnNumber << endl;
			if (wylosowana_liczba <= dchance) {
				int weapon = 19;
				if(isCustomPickupsEnabled && !isCustomPickupsConfig) weapon = (std::rand() % 19);
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
				return DropWeapon(var1, weapon, var3);
			}
		}
	}

	return DropWeapon(var1, var2, var3);
}

int who = 0x106d1250;
int who2 = 0x106d1250;

int hookedShotFired(int var1, int var2)
{
	/*cout << "hookedShotFired" << endl;
	std::cout << "Strzal var1 hex: " << hex << var1 << " dec: " << dec << var1 << std::endl; //we can access arguments passed to original function
	std::cout << "Strzal var2 hex: " << hex << var2 << " dec: " << dec << var2 << std::endl << endl;*/

	loadOnlineConfig(onShotFiredConfig);

	if (var2 == 46) { // 46=crash
		return Fire(var1, 302); // betaGrenade
	}

	if (var1 != 0x106d1250) {
		if (var2 == 10) {
			who2 = var1;
			var1 = 0x106d1250;
			Fire(who2, var2);
			return Fire(var1, var2);
		}
		else if (var2 == 3) {
			/*Fire(var1, var2);
			return Fire(0x106d1250, 10);*/
			who2 = var1;
			var1 = 0x106d1250;
			Fire(who2, var2);
			return Fire(var1, 10);
		}
		else if (flareToFire > 257 && var2 == (flareToFire - 256)) {
			// When flare id is over 257 every player needs the same flareToFire to see the same effect
			return Fire(var1, flareToFire);
		}
		else if (var2 == 104) {
			who = var1;
			var1 = 0x106d1250;
			if (!wasInfoRazor) {
				wasInfoRazor = true;
				print("\x2 Razor winds are just visual effect. Enemy razors always go to you but don't make damage (arrows do).");
				print("\x3 You can disable razor winds typing /razor");
			}
			if (!czyUserRazors) return Fire(var1, 0);
		}
		else if (var2 == 203 && flareToFire != 203) {
			return Fire(var1, 459); // singleplayer rocket
		}
		else if (var2 == 47 && flareToFire != 47) {
			return Fire(var1, 303); // betaPlasma
		}
		else if (var2 == 40 && flareToFire != 40) {
			return Fire(var1, 296); // betaChargeDart
		}
		else if (var2 == 42 && flareToFire != 42) {
			return Fire(var1, 298); // crossbow
		}
		else if (var2 == 49 && flareToFire != 49) {
			return Fire(var1, 305); // assault
		}
		else if (var2 == 39 && flareToFire != 39) {
			return Fire(var1, 295); // betaScorpion
		}
		else if (var2 == 50 && flareToFire != 50) {
			return Fire(var1, 306); // betaHarpoon
		}
		else if (var2 == 51 && flareToFire != 51) {
			return Fire(var1, 307); // left betaTorpedo
		}
		else if (var2 == 52 && flareToFire != 52) {
			return Fire(var1, 308); // right betaTorpedo
		}
		else if (var2 == 81 && flareToFire != 81) { // flame of fire
			return Fire(var1, 337); // black balls
		}
		else if (var2 == 83 && flareToFire != 83) { // a blue explosion shaking the camera
			return Fire(var1, 339); // drop a few glowing orbs
		}
		else if (var2 == 84 && flareToFire != 84) { // blue wheels
			return Fire(var1, 340); // drop a few glowing orbs
		}
		else if (var2 == 98 && flareToFire != 98) { // splash of water
			return Fire(var1, 354); // a blue bubble comes and goes
		}
		else if (var2 == 102 && flareToFire != 102) { // circle on the water
			return Fire(var1, 358); // green bubble comes and goes
		}
		else if (var2 == 126 && flareToFire != 126) { // circle on the water
			return Fire(var1, 382); // npc balls
		}
		else if (var2 == 165 && flareToFire != 165) { //?
			return Fire(var1, 421); // lightning
		}
		else if (var2 == 166 && flareToFire != 166) { //?
			return Fire(var1, 422); // large light
		}
		else if (var2 == 161 && flareToFire != 161) { //?
			return Fire(var1, 417); // lizards sth
		}
		else if (var2 == 168 && flareToFire != 168) { //?
			return Fire(var1, 424); // vertical pole high
		}
		else if (var2 == 175 && flareToFire != 175) { // faint red lights
			return Fire(var1, 431); // the long lingering cloud after nuke
		}
		else if (var2 == 176 && flareToFire != 176) { // some strange red something (lines? smoke ??) shows up on the walls as the burst is shot
			return Fire(var1, 432); // large black spot, lasts a long time
		}
		else if (var2 == 120 && flareToFire != 120) { // purple circles
			return Fire(var1, 376); // glowing orbs
		}
		return Fire(var1, var2);
	}

	int returned = 0;
	//if (wdamage != -1) toReturn = strzal(var1, wdamage); else {
		if (pfmlayer) returned = Fire(var1, pfmProjectile); //12
		else if (sunfirepod) {
			returned = Fire(var1, sunfirepodProjectile); //10
		}
		else if (assault) {
			short* ammo = getAmmo(assaultAmmo);
			if (*ammo > 0)
				returned = Fire(var1, assaultProjectile); //305 assault
		}
		else if (betaGrenade) {
			short* ammo = getAmmo(betaGrenadeAmmo);
			if (*ammo > 0)
				returned = Fire(var1, betaGrenadeProjectile); //302
		}
		else if (betaHarpoon) {
			returned = Fire(var1, betaHarpoonProjectile); //306
		}
		else if (betaTorpedo && var2 == 16) {
			airStrikeAmmoId = betaTorpedoAmmo;
			if(betaTorpedoProjectile > 0)
				Fire(var1, betaTorpedoProjectile);
			else
				fireAirStrike = true;
		}
		else if (betaPlasma) {
			short* ammo = getAmmo(betaPlasmaAmmo);
			if (*ammo > 0)
				returned = Fire(var1, betaPlasmaProjectile); //303
		}
		else if (betaFirestorm) {
			short* ammo = getAmmo(betaFirestormAmmo);
			if (*ammo > 0) {

				if (betaFirestormProjectile > 0)
					Fire(var1, betaFirestormProjectile);
				else
					fireRidingGun = true;
				
				if(*ammo <= 5)
					*ammo = 0;
				else
					*ammo -= 5;
			}
		}
		else if (betaCbore) {
			short* ammo = getAmmo(betaCboreAmmo);
			if (*ammo > 0) {
				returned = Fire(var1, betaCboreProjectile); //459 singleplayer rocket
				*ammo -= 1;
			}
		}
		else if (betaCharge) {
			short* ammo = getAmmo(betaChargeAmmo);
			if (*ammo > 0) {
				returned = Fire(var1, betaChargeProjectile); //4
				*ammo -= 1;
			}
		}
		else if (razor) {
			Fire(0x106d1250, 205);
			Fire(0x106d1250, 205);
			Fire(0x106d1250, 205);
			Fire(0x106d1250, 205);
			Fire(0x106d1250, 205);
			Fire(0x106d1250, 205);
			Fire(0x106d1250, 205);
			Fire(0x106d1250, 205);
			fireRazor = true;
			return Fire(0x106d1250, 205);

			//toReturn = Fire(var1, 104);
		}
		else if (nuke && var2 == 21) {
			if (areCustomWeaponsEnabled) fireExtraNuke = true;
			returned = Fire(var1, var2);
		}
		else if (tranquilizer) {
			fireTranquilizer = true;
			returned = Fire(var1, tranquilizerProjectile); //3
		}
		else if (bow) {
			returned = Fire(var1, bowProjectile); //86
		}
		else if (crossbow) {
			fireCrossbow = true;
		}
		else if (singleRocket) {
			returned = Fire(var1, singleRocketProjectile); //295
		} 
		else if (flare && var2 == 5) {
			fireFlare = true;
		}
		else if ((var2 == 16 || var2 == 231) && (isTorpedoDisabledOnGround || betaTorpedo)) {
			int isInWater = *((int*)0x00ADC09C);
			if (isInWater == 0) returned = Fire(var1, 0);
			else returned = Fire(var1, var2);
		}
		else returned = Fire(var1, var2);
		
		if (dinoRidingWith == var2 && areCustomWeaponsEnabled) {
			fireRidingGun = true;
		}
		if (blackOilWith == var2 && areCustomWeaponsEnabled && !flare && !crossbow) {
			if(isUserBlackOil) fireBlackOil = true;
		}
		if (airStrikeWith == var2 && areCustomWeaponsEnabled && !betaTorpedo && !betaCbore) {
			int isInWater = *((int*)0x00ADC09C);
			if (isInWater == 0){
				airStrikeAmmoId = customAirStrikeAmmoId;
				short* ammo = getAmmo((AmmoId)airStrikeAmmoId);

				int tempvar = 1;
				if (var2 == 16 && isTorpedoDisabledOnGround) tempvar = 0;
				if (*ammo - tempvar <= 0) {
					*ammo = 1;
					isLastAmmo = true;
				}
				fireAirStrike = true;
			}
		}

	//}
	//cout << "Fire toReturn: " << hex << returned << dec << endl << endl;
	return returned;                                        //before returning to normal execution of function
}

int hookedDamage(int var1, int var2, int *var3, int *var4, int *var5)
{
	/*cout << "hookedDamage" << endl;
	std::cout << "Damage var1: " << hex << var1 << dec << endl; //" adress: " << hex << var1 << dec << std::endl; //we can access arguments passed to original function
	std::cout << "Damage var2: " << var2 << std::endl;
	std::cout << "Damage var3: " << *var3 << " adress: " << hex << var3 << dec << std::endl; //location on the map
	std::cout << "Damage var4: " << *var4 << " adress: " << hex << var4 << dec << std::endl; //aiming direction (flight?)
	std::cout << "Damage var5: " << *var5 << " adress: " << hex << var5 << dec << std::endl << endl;*/
	
	if (var2 == 104 && who != 0x106d1250) {
		var1 = who;
		who = 0x106d1250;
	}
	else if ((var2 == 10 || var2 == 3) && who2 != 0x106d1250 && var1 == 0x106d1250) {
		var1 = who2;
		who2 = 0x106d1250;
	}

	int ret = damage(var1, var2, var3, var4, var5);

	//cout << "Damage ret: " << ret << endl << endl;
	return ret;
}

int hookedIndamage1(int var1, int var2, int var3)
{
	/*cout << "hookedIndamage1" << endl;
	std::cout << "Indamage1 var1: " << hex << var1 << dec << endl; //" adress: " << hex << var1 << dec << std::endl; //we can access arguments passed to original function
	std::cout << "Indamage1 var2: " << var2 << std::endl; //the id of the weapon
	std::cout << "Indamage1 var3: " << var3 << std::endl << endl; //projectile/effect*/
	int returned = 0;
	if (var3 == 104) returned = indamage1(var1, 21, 104);
	if (var1 != 0x106d1250) {
		if (var3 == 104) returned = indamage1(var1, 21, 104);
		else if (var3 == 10) returned = indamage1(var1, 12, 10);
		else if (var3 == 14) returned = indamage1(var1, 16, 14);
		else if (var3 == 16 || var3 == 231) returned = indamage1(var1, 18, 16);
		else if (var3 == 15) returned = indamage1(var1, 17, 15);
		else if (var3 == 4) returned = indamage1(var1, 7, 4);
		else if (var3 == 108 || var3 == 110 || var3 == 117) returned = indamage1(var1, 15, 13);
		else if (var3 == 12) returned = indamage1(var1, 14, 12);
		else if (var3 == 10) returned = indamage1(var1, 12, 10);
		else if (var3 == 205) returned = indamage1(var1, 21, 104);
		else if (var3 == 335) returned = indamage1(var1, 22, 21);
		else if (var3 == 3 || var3 == 111) returned = indamage1(var1, 6, 3);
		else if (var3 == 164) returned = indamage1(var1, 7, 4);
		else if (var3 == 5 || var3 == 54 || var3 == 150 || var3 == 209 || var3 == 210 || var3 == 203) returned = indamage1(var1, 4, 5);
		else if (var3 == 11) { returned = indamage1(var1, cboreSlot, 11); returned = 1; }
		else if (var3 == 21) returned = indamage1(var1, 22, 21);
		else if (var3 == 459) returned = indamage1(var1, 16, 14);
		else if (var3 == 305) returned = indamage1(var1, 26, 305);
		else if (var3 == 302) returned = indamage1(var1, 30, 302);
		else if (var3 == 295) returned = indamage1(var1, singleRocketSlot, 295); //toReturn = indamage1(var1, 13, 11); 
		else if (var3 == 86) returned = indamage1(var1, 3, 86);
		else if (var2 == 16 && var3 == 13) returned = indamage1(var1, 15, 13);
		else if (var3 == 303) returned = indamage1(var1, betaPlasmaSlot, 303);
		else if (var3 == 314 || var3 == 9) { returned = indamage1(var1, plasmaSlot, 9); returned = 1; }
		else if (var3 == 8) { returned = indamage1(var1, shotgunSlot, 8); returned = 1; }
		else if (var3 == 7) { returned = indamage1(var1, shotgunSlot, 7); returned = 1; }
		else if (var3 == 298) returned = indamage1(var1, tekbowSlot, 2);
		else if (var3 == 296) returned = indamage1(var1, betaChargeSlot, 296);
		else if (var3 == 305) returned = indamage1(var1, assaultSlot, 305);
		else if (var3 == 306) returned = indamage1(var1, harpoonSlot, 15);
		else if (var3 == 307) returned = indamage1(var1, betaTorpedoSlot, 307);
		else if (var3 == 308) returned = indamage1(var1, betaTorpedoSlot, 308);
		else if (var3 == flareToFire) returned = indamage1(var1, 4, 5);
		else if (var3 == cosmeticFlareToFire) returned = indamage1(var1, 4, 5);
		else returned = indamage1(var1, var2, var3);

		//cout << "Recieved Indamage1 toReturn: " << returned << endl << endl;
		return returned;
	}
	//if (wdamage != -1) toReturn = indamage1(var1, 10, 9);else {
		//if (var3 == 10) toReturn = indamage1(var1, 12, 10);
		if (var3 == 117 || var3 == 108 || var3 == 110) returned = indamage1(var1, 15, 13);
		else if (pfmlayer || sunfirepod || razor || tranquilizer || singleRocket || assault || crossbow
			|| betaCharge || betaGrenade || betaPlasma || betaFirestorm || betaCbore || betaHarpoon || betaTorpedo
			|| flare )
		{
			returned = indamage1(var1, indmg1var2, indmg1var3);
			if (crossbow)
				returned = 1;
		}
		else if (var3 == 5 || var3 == 54 || var3 == 150 || var3 == 209 || var3 == 210 
			|| var3 == flareToFire || var3 == cosmeticFlareToFire) returned = indamage1(var1, 4, 5);
		else {
			returned = indamage1(var1, var2, var3);
			if (var3 == 9 || var3 == 8)
				returned = 1;
		} 
	//}
	
	//cout << "Indamage1 toReturn: " << returned << endl << endl;
	return returned;                                        //before returning to normal execution of function
}

int hookedWeaponPickup(int int1, int int2)
{
	if (blockPickups)
		return 0;

	//std::cout << "WeaponPickup int1: " << hex << int1 << std::endl; //we can access arguments passed to original function
	//std::cout << "WeaponPickup int2: " << dec << int2 << std::endl;
	int returned = 0;
	//if (weaponId != -1) int2 = 5320896 + 24 * weaponId;
	int weaponId = (int2 - 5320896) / 24; // Corresponds to AmmoId

	if (isCustomPickupsEnabled) { //&& hasJoined
		//if (isCustomPickupsConfig) {
			int drawnNumber = (std::rand() % 100) + 1;
			//cout << "config drawnNumber: " << drawnNumber << endl;
			//map<int, list<int>> customPickup;
			//map<int, int> customPchance;
			int pchance = 0;
				if (customPchance.find(weaponId) != customPchance.end()) pchance = customPchance[weaponId];

			//cout << "pchance: " << pchance << endl;
			if (drawnNumber <= pchance) {
				
				//cout << "customPickup[weaponId].size(): " << customPickup[weaponId].size() << endl;
				int rweapon = (std::rand() % customPickup[weaponId].size()) + 1;
				//cout << "rweapon: " << rweapon << endl;
				int i = 1;
				int ammo = 0;
				for (auto it = customPickup[weaponId].begin(); it != customPickup[weaponId].end(); it++) {
					if (i == rweapon) {
						rweapon = std::get<0>(*it);
						ammo = std::get<1>(*it);
						break;
					}
					i++;
				}
				//cout << "rweapon: " << rweapon << " ammo: " << ammo << endl;
				addAmmo((AmmoId)rweapon, ammo);

				if (rweapon == (int)singleRocketAmmo) {
					equipWeapon(singleRocketSlot, 1);
					rweapon = 1;
				}
				else if (rweapon == (int)assaultAmmo) {
					equipWeapon(assaultSlot, 1);
					rweapon = 1;
				}
				else if (rweapon == (int)crossbowAmmo) {
					equipWeapon(crossbowSlot, 1);
					rweapon = 1;
				}
				else if (rweapon == (int)betaGrenadeAmmo) {
					equipWeapon(betaGrenadeSlot, 1);
					rweapon = 1;
				}
				else if (rweapon == (int)flareAmmo) {
					equipWeapon(flareSlot, 1);
					rweapon = 1;
				}
				else if (rweapon == (int)betaChargeAmmo) {
					equipWeapon(betaChargeSlot, 1);
					rweapon = 1;
				}
				else if (rweapon == (int)betaPlasmaAmmo) {
					equipWeapon(betaPlasmaSlot, 1);
					rweapon = 1;
				}
				else if (rweapon == (int)betaFirestormAmmo) {
					equipWeapon(betaFirestormSlot, 1);
					rweapon = 1;
				}
				else if (rweapon == (int)betaCboreAmmo) {
					equipWeapon(betaCboreSlot, 1);
					rweapon = 1;
				}
				else if (rweapon == (int)betaHarpoonAmmo) {
					equipWeapon(betaHarpoonSlot, 1);
					rweapon = 1;
				}
				else if (rweapon == (int)betaTorpedoAmmo) {
					equipWeapon(betaTorpedoSlot, 1);
					rweapon = 1;
				}
				else if (rweapon == (int)raptorClawsAmmo) {
					equipWeapon(raptorClawsSlot, 1);
					rweapon = 1;
				}

				loadOnlineConfig(onWeaponPickupConfig);

				int2 = 5320896 + 24 * rweapon;
				return PickupWeapon(int1, int2);
			}
			else {
				if (extraAmmo.find(weaponId) != extraAmmo.end()) {
					addAmmo((AmmoId)weaponId, extraAmmo[weaponId]);
				}
				if(weaponId == (int)tekbowAmmo && areCustomWeaponsEnabled) addAmmo(normalBowAmmo, 30);
				else if (weaponId == (int)greenShotgunAmmo && areCustomWeaponsEnabled) addAmmo(redShotgunAmmo, 3);
			}
		//}
	}

	returned = PickupWeapon(int1, int2);

	loadOnlineConfig(onWeaponPickupConfig);

	//cout << "PickupWeapon returned: " << returned << endl;
	return returned;                                        //before returning to normal execution of function
}

void checkVoice() {
	std::stringstream ss;
	std::this_thread::sleep_for(std::chrono::seconds{ 10 });
	if (isHostVoice == false) {
		ss.str("");
		ss << " \x4/99" << " gvoice " << myid;
		sendCmdToBot(ss.str());
		std::this_thread::sleep_for(std::chrono::seconds{ 10 });
	}
	if (isHostVoice == false) {
		ss.str("");
		ss << " \x4/99" << " gvoice " << myid;
		sendCmdToBot(ss.str());
		std::this_thread::sleep_for(std::chrono::seconds{ 5 });
	}
	if (isHostVoice == false) {
		cout << "DISCONNECTED WITH BOT! or lost connection." << endl;

		if (isServerBotRequired) {
			setSpectText("DISCONNECTED WITH BOT!");

			//wrzuc na specta
			int adres = 0x00AD03D8;
			int var = 4198400;
			WriteToMemory((LPVOID)adres, &var, sizeof(var));
			//printf("komenda write adres Error Code: %i\n", GetLastError());
			ss.str("");
			ss << " \x4/99" << " cstatus " << status << " 0 " << myid;
			sendCmdToBot(ss.str());
			status = 0;
			SpectJoin(0, 1);
			blockInSpectMode = true;
		}

		customCommands.clear();
		myid = -1;
		wasJoinSent = false;
		hasJoined = false;
		isUnfreezeAll = true;
		isUnobserveAll = true;
		isLoggedIn = false;
	}
	doCheckVoice = false;
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
	isServerBot = false;
	isServerBotRequired = false;
	isSpectateEnabled = true;
	isSetColorEnabled = false;
	areCustomDropsEnabled = false;
	isCustomDamageEnabled = false;
	isCustomPickupsEnabled = false;
	areCustomWeaponsEnabled = false;
	forceSpectOnStart = false;

	if (rules.find("\\ServerBot\\") != std::string::npos) {
		string subString = rules.substr(rules.find("\\ServerBot\\") + 11);
		//cout << "ServerBotRequiredsubString1: " << subString << endl;
		subString = subString.substr(0, subString.find("\\") - 1);
		//cout << "ServerBot: " << subString << endl;
		if (subString.find("TRUE") == 0 || subString.find("REQUIRED") == 0) {
			isServerBotRequired = true;
			isServerBot = true;
		}
		else if (subString.find("NOTREQUIRED") == 0) {
			isServerBotRequired = false;
			isServerBot = true;
		}
	}

	string lvlSet = (char*)0x00B65DD9;
	//cout << "levelSet: " << lvlSet << endl;
	if (isServerBot 
		&& lvlSet.find("beta09.lsm") == std::string::npos
		&& lvlSet.find("beta10.lsm") == std::string::npos
		&& lvlSet.find("mod10.lsm") == std::string::npos)
	{
		WriteToMemory((void*)0x00B65DD4, "You probably have an old or different version of mod than required", 67);
		ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);
		cout << "\n!!!!" << endl;
		cout << "Error! You probably have an old or different version of mod than required." << endl;
		string required = "";
		if (lvlSet.find("beta") != std::string::npos)
		{
			required = lvlSet.substr(lvlSet.find("beta"), lvlSet.find(".lsm") - lvlSet.find("beta"));
		}
		else 
		{
			required = lvlSet.substr(lvlSet.find("mod"), lvlSet.find(".lsm") - lvlSet.find("mod"));
		}
		cout << "Your version: beta09 Required: " << required << endl;
		cout << "Get new version at http://rebrand.ly/t2mod or contact me (kubpicapf@gmail.com)." << endl;
		cout << "!!!!\n" << endl;
	}
	else {
		if (rules.find("\\LvlSet\\") != std::string::npos) {
			string subString = rules.substr(rules.find("\\LvlSet\\") + 8);
			subString = subString.substr(0, subString.find("\\") - 1);
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
			if (subString[0] == '0') isSpectateEnabled = false;
			if (subString[1] == '1') isSetColorEnabled = true;
			if (subString[2] == '1') areCustomDropsEnabled = true; 
			if (subString[3] == '1') isCustomDamageEnabled = true;
			if (subString[4] == '1') useWeaponsEverywhere(true);
			if (subString[5] == '1') flamesInWater(true);
			if (subString[6] == '1') isCustomPickupsEnabled = true;
			if (subString[7] == '1') {
				areCustomWeaponsEnabled = true;
				isTorpedoDisabledOnGround = true;
			}
		}

		if (rules.find("\\GameType\\") != std::string::npos) {
			string subString = rules.substr(rules.find("\\GameType\\") + 10);
			//cout << "GameTypesubString1: " << subString << endl;
			subString = subString.substr(0, subString.find("\\"));
			//cout << "GameType: " << subString << endl;
			if (subString.find("Team Arena") == 0 || subString.find("Arena") == 0)
			{
				isArenaGamemode = true;
				isServerBotRequired = false;
			}
			else if (subString.find("Rok Match") == 0 || subString.find("AWR Match") == 0) {
				if(!isServerBot) isSetColorEnabled = true;
				forceSpectOnStart = true;
			}
			//else if (subString.find("Team Rok Match") == 0 || subString.find("Team AWR Match") == 0) forceSpectOnStart = false;
			if (subString.find("Team") != std::string::npos || subString.find("CTF") != std::string::npos)
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

void onFrag() {
	//cout << "on frag" << endl;

	if (reloadWeaponsOnFrag)
		startingChar(true);
	else
		loadFragWeapons();

	if (fragEffectsEnabled) {
		fireRandomFlare(fragFlares);
		playRandomSfx(fragSfx);
	}

	killstreak++;
	if (killstreak > 1 && killstreaksEnabled) {
		stringstream ss("");
		ss << "\x3 KILLSTREAK " << killstreak << " ";
		for (int i = 0; i < killstreak; i++)
			ss << "\x2";
		printString(ss.str());
		msgToSend.push_back(ss.str());

		if (killstreak % 5 == 0)
			playAceLector();
	}

	// Set killstreak bonus weapons & motd
	stringstream ss("");
	ss << "killstreak" << killstreak;
	string killstreakKey = ss.str();
	setCustomStartingWeapons(killstreakKey);
	printCustomMotd(killstreakKey);

	loadOnlineConfig(onFragConfig);
}

DWORD retFragHook = 0x0048AF22;

__declspec(naked) void midFragHook() // __declspec(naked) says to the compiler that we will worry about the prolog/epilog/return of the function
{
	__asm inc word ptr[edi + 0x000000C8]

	//if you want to do any other calls to other functions, etc and don't need the registers/stack anymore push it //for example:
	__asm pushad // push all general registers
	__asm pushfd // push all flags

	onFrag();

	//restore stack/registers, so we don't corrupt any data and program flow continues as it should
	__asm popfd
	__asm popad

	// return where we left off
	__asm jmp[retFragHook]
}

void onDeath() {
	//cout << "on death" << endl;

	if (deathEffectsEnabled) {
		execRandomAnim(deathAnims);
		fireRandomFlare(deathFlares);
		playRandomSfx(deathSfx);
	}

	if (respawnCooldown > 0)
		respawnCooldownTimer = respawnCooldown;

	if (forceSpectOnDeath)
		forceSpectOnRespawn = forceSpectOnDeath;

	loadOnlineConfig(onDeathConfig);

	if (killstreak > 1 && killstreaksEnabled) {
		stringstream ss("");
		ss << "\x3 Ended killstreak with " << killstreak << "\x2 frags.";
		printString(ss.str());
		msgToSend.push_back(ss.str());
	}
	killstreak = 0;
}

DWORD retDeathHook = 0x0048FD91;

__declspec(naked) void midDeathHook() // __declspec(naked) says to the compiler that we will worry about the prolog/epilog/return of the function
{
	__asm inc word ptr[ebx + 0x000000CC]

	//if you want to do any other calls to other functions, etc and don't need the registers/stack anymore push it //for example:
	__asm pushad // push all general registers
	__asm pushfd // push all flags

	onDeath();

	//restore stack/registers, so we don't corrupt any data and program flow continues as it should
	__asm popfd
	__asm popad

	// return where we left off
	__asm jmp[retDeathHook]
}

DWORD retJMP2 = 0x0048297E;

__declspec(naked) void MidChangeNameHook() // __declspec(naked) says to the compiler that we will worry about the prolog/epilog/return of the function
{
	__asm and ecx, 03 // do what we overwrote
	__asm repe movsb

	__asm pushad // push all general registers
	__asm pushfd // push all flags

	//cout << "MidChangeNameHook" << endl;
	checkNickname();

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

void applyCustomFirestorm() {
	// Firestorm works only when you have plasma ammo
	short* plasma = getAmmo(firestormAmmo);
	if (*plasma == 0)
		*plasma = 1;

	short var2 = firestormSlot;
	WriteToMemory((LPVOID)0x106D1D8C, &var2, sizeof(var2));
}

void onWeaponChange() {
	static bool customFirestorm;
	static bool weaponSizeChanged;
	static int hidenWeapon;

	short var = *((short*)0x106D1BE6);
	//cout << "onWeaponChange var: " << var << endl;

	if (var == grenadeSlot && pfmlayer
		|| var == magnumSlot && sunfirepod
		|| var == plasmaSlot && razor
		|| var == chargeDartSlot && chargeDart
		|| var == shredderSlot && tranquilizer
		|| var == nukeSlot && nuke
		|| var == pistolSlot && pistol
		|| var == scorpionSlot && crossbow
		|| var == tekbowSlot && bow
		|| var == tekbowSlot && tekbow
		|| var == pistolSlot && flare
		|| var == shotgunSlot && shotgun
		|| var == plasmaSlot && plasma
		|| var == shredderSlot && singleRocket
		|| var == firestormSlot && assault
		|| var == scorpionSlot && betaGrenade
		|| var == firestormSlot && betaCharge
		|| var == firestormSlot && betaPlasma
		|| var == shredderSlot && betaFirestorm
		|| var == scorpionSlot && betaCbore
		|| var == firestormSlot && betaHarpoon
		|| var == torpedoSlot && betaTorpedo
		|| var == raptorClawsSlot && raptorClaws) {
		return;
	}

	if (hidenWeapon > 0) {
		equipWeapon((WeaponSlotId)hidenWeapon, 1);
		hidenWeapon = -1;
	}

	//WriteToMemory((LPVOID)0x00AD4538, &var, sizeof(var));
	//WriteToMemory((LPVOID)0x00AD453B, &var, sizeof(var));
	customWeaponId = var;
	//cout << "customWeaponId: " << customWeaponId << endl;
	sunfirepod = false;
	chargeDart = false;
	razor = false;
	pfmlayer = false;
	tranquilizer = false;
	nuke = false;
	pistol = false;
	bow = false;
	tekbow = false;
	shotgun = false;
	flare = false;
	plasma = false;
	singleRocket = false;
	assault = false;
	crossbow = false;
	betaGrenade = false;
	betaCharge = false;
	betaPlasma = false;
	betaFirestorm = false;
	betaCbore = false;
	betaTorpedo = false;
	raptorClaws = false;
	betaHarpoon = false;
	if (customFirestorm) {
		customFirestorm = false;
		// Firestorm works only when you have plasma ammo
		// so remove the temporarly added one
		short* plasma = getAmmo(firestormAmmo);
		if (*plasma == 1)
			*plasma = 0;
	}

	if (var == pfmSlot) {
		pfmlayer = true;
		if (!wasInfoPfm) {
			wasInfoPfm = true;
			print("\x2 Mines will spawn only for players in your rendering distance.");
			print("\x3 Players far from you may not see some mines.");
		}
		indmg1var2 = pfmSlot;
		indmg1var3 = 12;

		short var2 = grenadeSlot;
		WriteToMemory((LPVOID)0x106D1D8C, &var2, sizeof(var2));

		if (isEquiped(grenadeSlot)) {
			hidenWeapon = grenadeSlot;
			equipWeapon((WeaponSlotId)hidenWeapon, 0);
		}
	}
	else if (var == plasmaSlot) {
		plasma = true;
	}
	else if (var == talonSlot) {
		raptorClaws = true;

		short var2 = raptorClawsSlot;
		WriteToMemory((LPVOID)0x106D1D8C, &var2, sizeof(var2));
	}
	else if (var == sunfirepodSlot) {
		sunfirepod = true;
		indmg1var2 = sunfirepodSlot;
		indmg1var3 = 10;

		short var2 = magnumSlot;
		WriteToMemory((LPVOID)0x106D1D8C, &var2, sizeof(var2));
	}
	else if (var == crossbowSlot) {
		crossbow = true;
		indmg1var2 = crossbowSlot;
		indmg1var3 = 298;

		short var2 = scorpionSlot;
		WriteToMemory((LPVOID)0x106D1D8C, &var2, sizeof(var2));
	}
	else if (var == assaultSlot) {
		assault = true;
		indmg1var2 = assaultSlot;
		indmg1var3 = 305;

		applyCustomFirestorm();
		customFirestorm = true;
	}
	else if (var == betaGrenadeSlot) {
		betaGrenade = true;
		indmg1var2 = grenadeSlot; //30;
		indmg1var3 = 13; //302;

		short var2 = scorpionSlot;
		WriteToMemory((LPVOID)0x106D1D8C, &var2, sizeof(var2));
		print("[BetaGrenade]");
	}
	else if (var == betaTorpedoSlot) {
		betaTorpedo = true;
		indmg1var2 = betaTorpedoSlot;
		indmg1var3 = 307;

		short var2 = torpedoSlot;
		WriteToMemory((LPVOID)0x106D1D8C, &var2, sizeof(var2));
		print("[AirStrike]");
	}
	else if (var == betaHarpoonSlot) {
		betaHarpoon = true;
		indmg1var2 = 17; //betaHarpoonSlot;
		indmg1var3 = 15; //306;

		applyCustomFirestorm();
		customFirestorm = true;
		print("[BetaHarpoon]");
	}
	else if (var == betaCboreSlot) {
		betaCbore = true;
		indmg1var2 = 16; //cboreSlot; //betaCboreSlot;
		indmg1var3 = 14; //11; //297;

		short var2 = scorpionSlot;
		WriteToMemory((LPVOID)0x106D1D8C, &var2, sizeof(var2));
		print("[RocketsFromSP]");
	}
	else if (var == betaPlasmaSlot) {
		betaPlasma = true;
		indmg1var2 = betaPlasmaSlot;
		indmg1var3 = 303;

		applyCustomFirestorm();
		customFirestorm = true;
		print("[BetaPlasma]");
	}
	else if (var == betaFirestormSlot) {
		betaFirestorm = true;
		indmg1var2 = 16; //assaultSlot;
		indmg1var3 = 14; //305;

		short var2 = shredderSlot;
		WriteToMemory((LPVOID)0x106D1D8C, &var2, sizeof(var2));
		print("[DinoRidingGun]");
	}
	else if (var == betaChargeSlot) {
		betaCharge = true;
		indmg1var2 = betaChargeSlot;
		indmg1var3 = 296;

		applyCustomFirestorm();
		customFirestorm = true;
		print("[ChargeStorm]");
	}
	else if (var == razorSlot) {
		razor = true;
		indmg1var2 = razorSlot;
		indmg1var3 = 104;

		short var2 = plasmaSlot;
		WriteToMemory((LPVOID)0x106D1D8C, &var2, sizeof(var2));
	}
	else if (var == chargeDartSlot) {
		chargeDart = true;
	}
	else if (var == normalBowSlot) {
		bow = true;
		if (!wasInfoZoom) {
			wasInfoZoom = true;
			print("\x2 Use zoom to shoot faster. [Shift]");
		}

		short var2 = tekbowSlot;
		WriteToMemory((LPVOID)0x106D1D8C, &var2, sizeof(var2));

		if (isEquiped(tekbowSlot)) {
			hidenWeapon = tekbowSlot;
			equipWeapon((WeaponSlotId)hidenWeapon, 0);
		}
	}
	else if (var == tekbowSlot) {
		tekbow = true;
		if (!wasInfoZoom) {
			wasInfoZoom = true;
			print("\x2 Use zoom to shoot faster. [Shift]");
		}
	}
	else if (var == shotgunSlot) {
		shotgun = true;
		if (!wasInfoAmmo) {
			wasInfoAmmo = true;
			print("\x2 [H] to change ammo type.");
		}
	}
	else if (var == pistolSlot) {
		pistol = true;
	}
	else if (var == tranquilizerSlot) {
		tranquilizer = true;
		if (!wasInfoSunfire) {
			wasInfoSunfire = true;
			print("\x2 Every shot will throw SunfirePod visible only for other players (to blind them for awhile).");
		}
		indmg1var2 = tranquilizerSlot;
		indmg1var3 = 3;

		short var2 = shredderSlot;
		WriteToMemory((LPVOID)0x106D1D8C, &var2, sizeof(var2));

		if (isEquiped(shredderSlot)) {
			hidenWeapon = shredderSlot;
			equipWeapon((WeaponSlotId)hidenWeapon, 0);
		}
	}
	else if (var == nukeSlot) {
		nuke = true;
	}
	else if (var == flareSlot) {
		flare = true;
		indmg1var2 = pistolSlot;
		indmg1var3 = 5;

		short var2 = pistolSlot;
		WriteToMemory((LPVOID)0x106D1D8C, &var2, sizeof(var2));
	}
	else if (var == singleRocketSlot) {
		singleRocket = true;
		indmg1var2 = singleRocketSlot; //16;
		indmg1var3 = 295; //14;

		short var2 = shredderSlot;
		WriteToMemory((LPVOID)0x106D1D8C, &var2, sizeof(var2));
	}
	
	if (weaponSizeChanged && var != warbladeSlot && var != raptorClawsSlot && var != talonSlot) {
		weaponSizeChanged = false;
		WriteToMemory((LPVOID)0x004F9790, &weaponsize, 4);
		WriteToMemory((LPVOID)0x004F9A80, &weaponsize2, 4);
	}
	else if (var == warbladeSlot || var == raptorClawsSlot || var == talonSlot) {
		//warblade or raptorclaws
		float weaponsize = -10.23999977;
		float weaponsize2 = 0.1000000015;
		WriteToMemory((LPVOID)0x004F9790, &weaponsize, 4);
		WriteToMemory((LPVOID)0x004F9A80, &weaponsize2, 4);
		weaponSizeChanged = true;
	} 

	if (isCustomDamageEnabled)
		setCustomDamage(var);

	loadOnlineConfig(onWeaponChangeConfig);
}

DWORD retJMP4 = 0x0042693F;

__declspec(naked) void midWeaponChange() // __declspec(naked) says to the compiler that we will worry about the prolog/epilog/return of the function
{
	__asm mov eax, [edx + 0x48] // do what we overwrote
		__asm mov[edi + 0x2C], eax

	
	__asm pushad // push all general registers
	__asm pushfd // push all flags

	onWeaponChange();

	//restore stack/registers, so we don't corrupt any data and program flow continues as it should
	__asm popfd
	__asm popad

	// return where we left off
	__asm jmp[retJMP4]
}

float* f = (float*)(0x0050B7FC);
void checkF2() {
	if (*f == 0)
		*f = fixedF;
}

void checkF2Fixed() {
	if (*f == 0)
	{
		*f = 0.01;
		//print("f == 0");
	}
}

void checkF6() {
	if(*f==fixedF)
		*f = 0;
}

DWORD retJMP5 = 0x004614FF;

__declspec(naked) void checkF() // __declspec(naked) says to the compiler that we will worry about the prolog/epilog/return of the function
{
	__asm mov cx, [esi + 0x0000012C] // do what we overwrote


		__asm pushad // push all general registers
	__asm pushfd // push all flags

	checkF2Fixed();

	//restore stack/registers, so we don't corrupt any data and program flow continues as it should
	__asm popfd
	__asm popad

	// return where we left off
	__asm jmp[retJMP5]
}

DWORD retJMP6 = 0x0041EDC2;

__declspec(naked) void checkF3() // __declspec(naked) says to the compiler that we will worry about the prolog/epilog/return of the function
{
	__asm lea esi, [ebp + 0x00000A68] // do what we overwrote


		__asm pushad // push all general registers
	__asm pushfd // push all flags

	checkF2();

	//restore stack/registers, so we don't corrupt any data and program flow continues as it should
	__asm popfd
	__asm popad

	// return where we left off
	__asm jmp[retJMP6]
}

DWORD retJMP7 = 0x0041F6C8;

__declspec(naked) void checkF4() // __declspec(naked) says to the compiler that we will worry about the prolog/epilog/return of the function
{
	__asm mov[ebp + 0x000000D4], eax // do what we overwrote

		__asm pushad // push all general registers
	__asm pushfd // push all flags

	checkF2();

	//restore stack/registers, so we don't corrupt any data and program flow continues as it should
	__asm popfd
	__asm popad

	// return where we left off
	__asm jmp[retJMP7]
}

DWORD retJMP8 = 0x0041F5CA;

__declspec(naked) void checkF5() // __declspec(naked) says to the compiler that we will worry about the prolog/epilog/return of the function
{
	__asm mov ax, [ebp + 0x00000A30] // do what we overwrote


	__asm pushad // push all general registers
	__asm pushfd // push all flags

	checkF6();

	//restore stack/registers, so we don't corrupt any data and program flow continues as it should
	__asm popfd
	__asm popad

	// return where we left off
	__asm jmp[retJMP8]
}

void sayHello() {
	execPreCommands();

	stringstream ss("");
	ss << " \x4/00 hello " << tid << " Download kub's mod: rebrand.ly/t2mod";
	sendCmdWithPassword(ss.str());
}

DWORD WINAPI CustomWeapons_thread(LPVOID lpParam) {
	while (1) {
		if (disableHostMode) {
			disableHostMode = false;
			Sleep(32);
			setHostMode(0);
		}

		if (delayedForceSpect) {
			delayedForceSpect = false;
			Sleep(32);
			forceSpect(delayedSpectText);
		}

		if (delayedRespawn) {
			delayedRespawn = false;

			Sleep(100);
			SpectJoin(1, 0);
		}

		if (delayedHello) {
			delayedHello = false;

			Sleep(1000);
			sayHello();
		}

		if (resetToAnim2) {
			resetToAnim2 = false;

			Sleep(100);
			animateCharacter(2);
		}

		if (forceSpectOnRespawn) {
			if (forceSpectOnRespawn == 2) {
				if (forceSpectOnDeath == 2 || respawnCooldownTimer > 0) {
					blockInSpectMode = true;
					forceSpect("RESPAWNS BLOCKED");
				}
			}
			else {
				printString("\x2 According to the server settings, you have been placed in observer mode after death.");
				forceSpect();
			}
			forceSpectOnRespawn = 0;
		}

		// Respawn cooldown
		if (respawnCooldownTimer > 0) {
			if (blockInSpectMode) {
				stringstream ss("");
				ss << "RESPAWN COOLDOWN: ";
				if (respawnCooldownTimer > 1.3)
					ss << (int)respawnCooldownTimer+1;
				else
					ss << std::fixed << std::setprecision(2) << respawnCooldownTimer;
				setSpectText(ss.str());
			}

			respawnCooldownTimer -= 16.0/1000.0;

			if (blockInSpectMode && respawnCooldownTimer <= 0) {
				blockInSpectMode = false;
				SpectJoin(1, 0); // Respawn
				setSpectText(); // Set default text
			}
		}

		// Change damage/node delay
		if (changeDamageDelayTimer > 0)
		{
			changeDamageDelayTimer -= 16.0 / 1000.0;
			if (changeDamageDelayTimer <= 0) {
				changeDamageDelayTimer = 0;
				applyCustomDamage();
			}
		}

		// Countdown
		if (countdownTimer > 0)
		{
			countdownTimer -= 16.0 / 1000.0;

			if (countdownTimer <= 0) {
				countdownTimer = 0;

				if (countdownCmd.empty()) {
					playLector(26, true, 0);
					sendNews("Go!");
				}
				else {
					if (countdownCmd == "force respawn") {
						playLector(29, true, 0);
						sendNews("Let's Rok!");
					}
					else if (countdownCmd.find("round1") == 0) {
						playLector(22, true, 0);
						sendNews("Round 1.");
						if (countdownCmd.size() > 7)
							countdownCmd = countdownCmd.substr(7);
					}
					else if (countdownCmd.find("round2") == 0) {
						playLector(23, true, 0);
						sendNews("Round 2.");
						if (countdownCmd.size() > 7)
							countdownCmd = countdownCmd.substr(7);
					}
					else if (countdownCmd.find("round3") == 0) {
						playLector(24, true, 0);
						sendNews("Round 3.");
						if (countdownCmd.size() > 7)
							countdownCmd = countdownCmd.substr(7);
					}
					else if (countdownCmd.find("timelimit") == 0) {
						playLector(57, true, 0);
						sendNews("Time limit hit.");
						if (countdownCmd.size() > 10)
							countdownCmd = countdownCmd.substr(10);
					}
					else if (countdownCmd.find("powerup") == 0) {
						playLector(52, true, 0);
						sendNews("Power-up.");
						if (countdownCmd.size() > 8)
							countdownCmd = countdownCmd.substr(8);
					}
					else if (countdownCmd.find("lector") == 0) {
						if(countdownCmd.size() > 9)
							sendNews(countdownCmd.substr(7));
						else
							sendNews(countdownCmd);
					}
					else if (countdownCmd.find("coinflip") != 0) {
						playLector(32, true, 0);
						sendNews(countdownCmd);
					}
					execCommand(countdownCmd);
				}
			}
			else if (countdownTimer <= countdownIntTimer) {
				playNumberLector(countdownIntTimer);

				stringstream ss("");
				ss << countdownIntTimer;
				sendNews(ss.str());

				countdownIntTimer--;
			}
		}

		// Change damage/node delay
		if (superhot) {
			if (superhotTimer > 0)
			{
				superhotTimer -= 16.0 / 1000.0;
				if (superhotTimer <= 0)
					superhotTimer = 0;

				float f = (superhotAdjustTime - superhotTimer) / superhotAdjustTime;
				float speed = (superhotTargetSpeed - superhotInitialSpeed) * f + superhotInitialSpeed;
				setSuperhotSpeed(speed);
			}

			superhotTextTimer += 16.0 / 1000.0;
			if (superhotTextTimer >= 0.5) {
				superhotTextTimer -= 0.5;
				superhotTextLvl++;
				if(superhotTextLvl < 8) {
					if (superhotTextLvl == 2)
						print("\x02 : SUPER : \x2 Time");
					else if (superhotTextLvl == 3)
						print("\x02 :  HOT  : \x2 moves");
					else if (superhotTextLvl == 4)
						print("\x02 : SUPER : \x2 only");
					else if (superhotTextLvl == 5)
						print("\x02 :  HOT  : \x2 when");
					else if (superhotTextLvl == 6) {
						if(superhot == 1)
							print("\x02 : SUPER : \x2 you");
						else if(superhot == 2)
							print("\x02 : SUPER : \x2 players");
						else
							print("\x02 : SUPER : \x2 everyone");
					}
					else if (superhotTextLvl == 7)
					{
						if(superhot == 3)
							print("\x02 :  HOT  : \x2 moves.");
						else
							print("\x02 :  HOT  : \x2 move.");
					}
				}
				else {
					if (superhotTextLvl == 8) {
						setStatsText("\x02 SUPER \x2");
						if (isDead()) //&& isF1Menu()
							lector(39);
					}
					else if (superhotTextLvl == 10) {
						setStatsText("\x02  HOT  \x2");
						if (isDead()) //&& isF1Menu()
							lector(35);
					}
					else if (superhotTextLvl == 11)
						superhotTextLvl = 7;
				}
			}
		}

		if (!chatNews.empty()) {
			chatNewsTimer += 16.0 / 1000.0;
			if (chatNewsTimer >= timeBetweenChatNews) {
				chatNewsTimer -= timeBetweenChatNews;
				string news = *select_randomly(chatNews.begin(), chatNews.end());
				printString(news);
			}
		}

		// Fire custom weapons
		Sleep(16);
		if (fireRidingGun) {
			fireRidingGun = false;
			Sleep(80);
			if (ridingGunSide) {
				ridingGunSide = false;
				Fire(0x106d1250, 110); //riding gun prawe
			}
			else {
				ridingGunSide = true;
				Fire(0x106d1250, 108); //riding gun lewe
			}
		}
		else if (fireRazor) {
			fireRazor = false;
			Fire(0x106d1250, 104);
			Sleep(26); //Sleep(35); //70 2 5
			Fire(0x106d1250, 205);
			Fire(0x106d1250, 205);
			Fire(0x106d1250, 205);
			Sleep(26);
			Fire(0x106d1250, 205);
			Fire(0x106d1250, 205);
			Fire(0x106d1250, 205);
			Sleep(25);
			Fire(0x106d1250, 205);
			Fire(0x106d1250, 205);
			Fire(0x106d1250, 205);
		}
		else if (fireExtraNuke && howManyExtraNukeExplosions) {
			fireExtraNuke = false;
			Sleep(35);
			for (int i = 0; i < howManyExtraNukeExplosions; i++) {
				short* var = (short*)0x106D1BB0;
				*var += 1;
				Fire(0x106d1250, 21);
				Sleep(35);
			}
		}
		else if (fireAirStrike) {
			fireAirStrike = false;
			//strzal(0x106d1250, 335);
			if (airStrikeDelay >= 500 && wasInfoAirStrike < 3) {
				print("\x2 Move to open space or else Katyusha rockets will kill you! (Change weapon to cancel)");
				wasInfoAirStrike++;
			}
			else if (wasInfoAirStrike < 2) {
				print("\x2 Katyusha launched! Move to open space or else rockets will kill you! (Air-strike)");
				wasInfoAirStrike++;
			}
			Sleep(airStrikeDelay);
			short var = *((short*)0x106D1D8C);
			if (var == airStrikeAmmoId || betaTorpedo) {
				short* ammo = getAmmo((AmmoId)airStrikeAmmoId);
				short tempammo = *ammo;
				tempammo -= airStrikeAmmoCost;
				if (tempammo < 0) tempammo = 0;
				*ammo = tempammo;
				if (airStrikeDelay >= 400) print("\x2 Katyusha launched! (Air-strike)");
				Fire(0x106d1250, 117);
				Sleep(35);
				Fire(0x106d1250, 117);
				Sleep(35);
				Fire(0x106d1250, 117);
				Sleep(35);
				Fire(0x106d1250, 117);
				Sleep(35);
				Fire(0x106d1250, 117);
				Sleep(35);
				Fire(0x106d1250, 117);
				Sleep(35);
				Fire(0x106d1250, 117);
			}
			else {
				print("\x2 You changed weapon - Airstrike canceled.");
			}
			if (isLastAmmo) {
				isLastAmmo = false;
				short* ammo = getAmmo((AmmoId)airStrikeAmmoId);
				if(*ammo > 0)
					*ammo -= 1;
			}
		}
		else if (fireTranquilizer) {
			fireTranquilizer = false;
			Fire(0x106d1250, 5);
			Sleep(35);
			Fire(0x106d1250, 111);
			Sleep(35);
			Fire(0x106d1250, 111);
			Sleep(35);
			Fire(0x106d1250, 111);
			Sleep(35);
			Fire(0x106d1250, 111);
			Sleep(35);
			Fire(0x106d1250, 111);
			Sleep(35);
			Fire(0x106d1250, 111);
			Sleep(35);
			Fire(0x106d1250, 111);
			Sleep(35);
			Fire(0x106d1250, 111);
			Sleep(35);
			Fire(0x106d1250, 111);
			Sleep(35);
			Fire(0x106d1250, 111);
		}
		else if (fireBlackOil) {
			if (!czyInfoOil) {
				czyInfoOil = true;
				print("\x2 Type /oil to disable generation of black oil.");
			}
			fireBlackOil = false;
			Fire(0x106d1250, 54);
			Sleep(35);
			Fire(0x106d1250, 150);
		}
		else if (fireCrossbow) {
			fireCrossbow = false;
			Fire(0x106d1250, crossbowProjectile); //298
		}
		else if (fireFlare) {
			fireFlare = false;
			Fire(0x106d1250, flareToFire);
		}
		else if (fireRespawnFlare) {
			fireRespawnFlare = false;
			Sleep(35);
			Fire(0x106d1250, cosmeticFlareToFire);
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
			char randomChar = 'a' + (std::rand() % 26);
			seed += randomChar;
		}
	}
	else {
		string word;
		string line;
		while (getline(config, line)) {
			word = line.substr(0, line.find("=") + 1);
			//cout << word << endl;
			if (word == "Names=" || word == "Names_0=" || word == "Names_1=" || word == "Names_2=" || word == "Names_3=" || word == "Names_4=") {
				string temp = line.substr(line.find("=") + 1);
				seed += temp;
			}
			char randomChar = 'a' + (std::rand() % 26);
			seed += randomChar;
			word.clear();
			line.clear();
		}
		config.close();
	}
	//cout << "seed: " << seed << endl;
	tid = md5(seed);
	for (int i = 0; i < 5; i++) {
		char randomChar = 'a' + (std::rand() % 26);
		tid += randomChar;
	}
}

void readModsCfg(string version, bool hideconsole)
{
	string result;
	readWebSite(&result, "https://pastebin.com/raw/sSwzQisM");
	//cout << "curl: " << result << "\n\n";

	bool isUptodate = false;
	string v;
	istringstream stream(result);
	for (string line; std::getline(stream, line); ) {
		cout << "readModsCfg: " << line << endl;
		string word = line.substr(0, line.find("=") + 1);
		if (word == "Version=") {
			v = line.substr(line.find("=") + 1);
			if (v != version) {
				cout << "Your version: " << version << " Other up-to-date: " << v << endl;
			}
			else {
				isUptodate = true;
			}
		}
		else if (word == "MOTD=") {
			cout << line.substr(line.find("=") + 1) << endl;
		}
		else if (word == "IngameMOTD=") {
			motd = line.substr(line.find("=") + 1);
		}
		else if (word == "ChatNews=") {
			chatNews.push_back(cfgString(line));
		}
		else if (word == "AdminMod=") {
			addConfigPreset(adminConfigPresets, line);
		}
		else if (word == "Mod=") {
			addConfigPreset(localConfigPresets, line);
		}
		else if (word == "ModDesc=") {
			addConfigPresetDescription(line);
		}
		else if (word == "SafeMode=") {
			int i = stoi(line.substr(line.find("=") + 1));

			if (safeMode == 0 || safeMode > 0 && safeMode < i || safeMode < 0 && safeMode > i)
				safeMode = i;
		}
	}
	if (!isUptodate && !v.empty()) {
		ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);
		cout << "\n!!!!" << endl;
		cout << "New version of mod is available!!!" << endl;
		cout << "Your version: " << version << " Newest: " << v << endl;
		cout << "Get new version at http://rebrand.ly/t2mod or contact me (kubpicapf@gmail.com)." << endl;
		hideconsole = false;
		cout << "!!!!\n" << endl;
	}

	cout << "Mod loaded successfully." << endl;
	cout << "Do NOT close this window!!!" << endl;

	if (hideconsole)
		ShowWindow(GetConsoleWindow(), SW_HIDE);
}

//void readServersCfg(string cfgurl) {
DWORD WINAPI readServersCfg(LPVOID lpParam) {
	if (cfgurl == "null") 
		return S_OK;

	loadOnlineConfig(globalCfgurl);
	loadOnlineConfig(cfgurl);
	delayedHello = true;

	return S_OK;
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
	string version = "B0.9";
	cout << "T2 kub's mod " << version << ".3 (wip) 1.0 PRE-RELEASE25" << endl;
	cout << "Mod\'s website: http://rebrand.ly/t2mod" << endl;
	cout << "Loading... Wait..." << endl;

	placeJMP((BYTE*)0x00426939, (DWORD)myMidfuncHook, 6);
	WriteToMemory((void*)0x0041D0D8, "\xEB", 1); 

	std::stringstream ss;
	ss.str("");
	ss << &customWeaponId;
	//cout << "&customWeaponId = 0: " << ss.str() << endl;
	char addressInBytes[4];
	addressInBytes[0] = strtol(ss.str().substr(6).c_str(), NULL, 16);
	addressInBytes[1] = strtol(ss.str().substr(4, 2).c_str(), NULL, 16);
	addressInBytes[2] = strtol(ss.str().substr(2, 2).c_str(), NULL, 16);
	addressInBytes[3] = strtol(ss.str().substr(0, 2).c_str(), NULL, 16);
	//cout << "addressInBytes: " << hex << (int)addressInBytes[0] << " " << (int)addressInBytes[1] << " " << (int)addressInBytes[2] << " " << (int)addressInBytes[3] << dec << endl;

	ss.str("");
	ss << "\x0F\xBF\x0D" << addressInBytes;
	WriteToMemory((void*)0x0041928D, ss.str().c_str(), 7);
	ss.str("");
	ss << "\x0F\xBF\x15" << addressInBytes;
	WriteToMemory((void*)0x004192B2, ss.str().c_str(), 7);
	ss.str("");
	ss << "\x0F\xBF\x3D" << addressInBytes;
	WriteToMemory((void*)0x0041D8CA, ss.str().c_str(), 7);
	ss.str("");
	ss << "\x0F\xBF\x0D" << addressInBytes;
	WriteToMemory((void*)0x00426C8B, ss.str().c_str(), 7);
	ss.str("");
	ss << "\x0F\xBF\x05" << addressInBytes;
	WriteToMemory((void*)0x00426AE8, ss.str().c_str(), 7);
	ss.str("");
	ss << "\x0F\xBF\x05" << addressInBytes;
	WriteToMemory((void*)0x0041DD5A, ss.str().c_str(), 7);
	ss.str("");
	ss << "\x0F\xBF\x05" << addressInBytes;
	WriteToMemory((void*)0x0041DDF2, ss.str().c_str(), 7);
	ss.str("");
	ss << "\x0F\xBF\x15" << addressInBytes;
	WriteToMemory((void*)0x00426981, ss.str().c_str(), 7);
	ss.str("");
	ss << "\x0F\xBF\x0D" << addressInBytes;
	WriteToMemory((void*)0x00426ECA, ss.str().c_str(), 7);
	WriteToMemory((LPVOID)0x00B723CC, "\x01", 1);

	customPchance[18] = 86;
	//addCustomPickup(18, 2, 30);
	addCustomPickup(18, 6, 12);
	addCustomPickup(18, 12, 200);
	addCustomPickup(18, 14, 22);
	addCustomPickup(18, 20, 0);
	addCustomPickup(18, 31, 10);
	addCustomPickup(18, 26, 100);
	customPchance[5] = 20;
	addCustomPickup(5, 12, 200);
	//customPchance[3] = 20;
	//addCustomPickup(3, 2, 30);
	customPchance[9] = 20;
	addCustomPickup(9, 6, 12);
	customPchance[15] = 20;
	addCustomPickup(15, 14, 22);
	customPchance[10] = 15;
	addCustomPickup(10, 20, 0);
	customPchance[8] = 15;
	addCustomPickup(8, 21, 1);
	customPchance[7] = 15;
	addCustomPickup(7, 17, 0);
	customPchance[13] = 15;
	addCustomPickup(13, 18, 0);
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
	bool autoFixedF = true;
	float maxpan = 4000;
	int minFrameTime = -1;
	bool hideconsole = true;

	char pathc[MAX_PATH];
	GetModuleFileNameA(hModule, pathc, sizeof(pathc));
	//cout << "pathc: " << pathc << endl;
	string path = pathc;
	path = path.substr(0, path.find_last_of("/\\"));

	path = path + "\\launcherConfig.txt";
	//cout << "path: " << path << endl;
	fstream config;
	config.open(path, std::fstream::in | std::fstream::out);

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
		config << "DllName=kubs_mod_client.dll" << endl; 
		config << "StartupParameters=-maxframerate 64 -soundthread -AverageMouse 0 -exclusivemouse -enableHardwareMixing -exclusivesound -output44k -lan" << endl; //-quickmouse
		config << "//It's better to have MaxFrameRate set to stable reachable value - so maxfps 250 is probably better than 1000." << endl;
		config << "MaxFrameRate=250" << endl;
		config << "CameraFOV=73.74" << endl; 
		config << "WeaponFOV=52.6714" << endl;  
		config << "SetWeaponSize=0.9" << endl;
		config << "//MaxPan is about directional (\"3D\") sound (600 is default, 10000 is best for competitive gameplay but may be annoying) - you can test it in game with 'set maxpan' command." << endl;
		config << "MaxPan=4000" << endl;
		config << "ShowModConsole=0" << endl;
		config.close();
	}
	else {
		string word;
		string line;
		bool fixGameSpeed = true;
		bool fixJumpReg = true;
		bool fHooks = true;
		while (getline(config, line)) {
			word = line.substr(0, line.find("=") + 1);
			//cout << word << endl;
			if (word == "WeaponFOV=") {
				string num = line.substr(line.find("=") + 1);
				weaponfov1 = ::atof(num.c_str());
				//cout << "weaponfov1: " << weaponfov1 << endl;
			}
			else if (word == "CameraFOV=") {
				string num = line.substr(line.find("=") + 1);
				camerafov1 = ::atof(num.c_str());
				//cout << "camerafov1: " << camerafov1 << endl;
			}
			else if (word == "MaxPan=") {
				string num = line.substr(line.find("=") + 1);
				maxpan = ::atof(num.c_str());
				//cout << "maxpan: " << maxpan << endl;
			}
			else if (word == "ShowModConsole=") {
				string num = line.substr(line.find("=") + 1);
				int show = ::atoi(num.c_str());
				if (show > 0)
					hideconsole = false;
			}
			else if (word == "KillstreaksEnabled=") {
				killstreaksEnabled = cfgBool(line);
			}
			else if (word == "MuteSfx=") {
				muteSfxTaunts = cfgBool(line);
			}
			else if (word == "MuteLector=") {
				muteLector = cfgBool(line);
			}
			else if (word == "MinFrameTime=") {
				string num = line.substr(line.find("=") + 1);
				minFrameTime = ::atoi(num.c_str());
			}
			else if (word == "MaxFrameRate=") {
				string num = line.substr(line.find("=") + 1);
				float f = ::atof(num.c_str());
				minFrameTime = round(1000/f);
			}
			else if (word == "FixGameSpeed=") {
				string num = line.substr(line.find("=") + 1);
				if (::atoi(num.c_str()) == 0) {
					fixGameSpeed = false;
				}
			}
			else if (word == "FixJumpRegistration=") {
				string num = line.substr(line.find("=") + 1);
				if (::atoi(num.c_str()) == 0) {
					fixJumpReg = false;
				}
			}
			else if (word == "FovOffset=") {
				string num = line.substr(line.find("=") + 1);
				double d = ::atof(num.c_str());
				WriteToMemory((LPVOID)0x004F94C8, &d, sizeof(d));
			}
			else if (word == "WeaponSize=") {
				string num = line.substr(line.find("=") + 1);
				weaponsize = ::atof(num.c_str());
				WriteToMemory((LPVOID)0x004F9790, &weaponsize, sizeof(weaponsize));
			}
			else if (word == "WeaponSize2=") {
				string num = line.substr(line.find("=") + 1);
				weaponsize2 = ::atof(num.c_str());
				if (weaponsize2 == 0)
					weaponsize2 = 0.001;
				WriteToMemory((LPVOID)0x004F9A80, &weaponsize2, sizeof(weaponsize2));
			}
			else if (word == "SetWeaponSize=") {
				string num = line.substr(line.find("=") + 1);
				float f = ::atof(num.c_str());
				weaponsize2 = f*0.1000000015;
			}
			else if (word == "WeaponFOV2=") {
				string num = line.substr(line.find("=") + 1);
				float f = ::atof(num.c_str());
				WriteToMemory((LPVOID)0x004F9A7C, &f, sizeof(f));
			}
			else if (word == "WeaponFOV3=") {
				string num = line.substr(line.find("=") + 1);
				float f = ::atof(num.c_str());
				WriteToMemory((LPVOID)0x004F9A78, &f, sizeof(f));
			} 
			else if (word == "FixedF=") {
				string num = line.substr(line.find("=") + 1);
				setFixedF(::atof(num.c_str()));
				autoFixedF = false;
			}
			else if (word == "FHooks=") {
				string num = line.substr(line.find("=") + 1);
				if (::atoi(num.c_str()) == 0) {
					fHooks = false;
				}
			}
			else if (word == "SafeMode=") {
				string num = line.substr(line.find("=") + 1);
				safeMode = ::atoi(num.c_str());
			}
			else if (word == "AdminMod=") {
				addConfigPreset(adminConfigPresets, line);
			}
			else if (word == "Mod=") {
				addConfigPreset(localConfigPresets, line);
			}
			else if (word == "ModDesc=") {
				addConfigPresetDescription(line);
			}
			else if (word == "GlobalConfig=") {
				globalCfgurl = cfgString(line);
			}
			else if (word == "Cmd=") {
				string cmd = line.substr(line.find("=") + 1);
				presetCommands.push_back(cmd);
			}

			word.clear();
			line.clear();
		}

		if (fixJumpReg) {
			WriteToMemory((void*)0x0041EDD2, "\x90\x90\x90\x90\x90\x90", 6);  //originally: 0F 85 B2 0B 00 00
		}
		if (fixGameSpeed) {
			WriteToMemory((void*)0x004720A0, "\x90\x90", 2); //originally: 74 0A
		}
		if (fHooks) {
			placeJMP((BYTE*)0x004614F9, (DWORD)checkF, 6);
			placeJMP((BYTE*)0x0041EDBC, (DWORD)checkF3, 6);
			placeJMP((BYTE*)0x0041F6C2, (DWORD)checkF4, 6);
			placeJMP((BYTE*)0x0041F5C3, (DWORD)checkF5, 7);
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

		generateTID(pathc);
		ftid << "//do NOT remove or change this file!" << endl;
		ftid << "system=" << tid << endl;
	}
	else {
		string word;
		string line;
		while (getline(ftid, line)) {
			word = line.substr(0, line.find("=") + 1);
			//cout << word << endl;
			if (word == "system=") {
				tid = line.substr(line.find("=") + 1);
			}
			word.clear();
			line.clear();
		}
		if (tid.length() != 37) {
			//cout << "wrong length of tid" << endl;
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
	placeJMP((BYTE*)0x00426939, (DWORD)midWeaponChange, 6);
	placeJMP((BYTE*)0x0048AF1B, (DWORD)midFragHook, 7);
	placeJMP((BYTE*)0x0048FD8A, (DWORD)midDeathHook, 7);

	//read web cfg of mod
	std::thread modCfg(readModsCfg, version, hideconsole);

	//while(*((int*)0x00AD0280)!=1);
	while (!hasStarted) Sleep(500);
	WriteToMemory((void*)address, "\xD9\x1D\x56\xBD\xAC", 5);
	if (!isServerBotRequired) {
		blockInSpectMode = false;
	}
	Sleep(400);
	if (isTeamGameMode && *((int*)0x106D1770) == 0) {
		int temp = -1;
		WriteToMemory((LPVOID)0x106D1770, &temp, sizeof(temp));
	}
	int spect = 4198400;
	while (true) { //game is loading (joining to server)
		Sleep(16);
		if(forceSpectOnStart) WriteToMemory((LPVOID)0x00AD03D8, &spect, sizeof(spect)); //if (isServerBotRequired)
		int var = *((int*)0x106D1C84);
		int var2 = *((int*)0x106D1770);
		if (var == 1 || var == 2 || (isTeamGameMode && var2) ) {
			break;
		}
	}

	Sleep(30);
	defaultDamage = *((float*)0x00AD44EC);
	defaultNode = *((float*)0x00AD44F0);
	originalDamage = defaultDamage;
	originalNode = defaultNode;
	originalFragLimit = *(int*)0x00AD44D0;
	originalTimeLimit = *(int*)0x00AD44D4;
	originalPointLimit = *(int*)0x00AD44D8;

	unlockCheat(stickMode);
	unlockCheat(gouraudMode);
	unlockCheat(blackout);
	unlockCheat(frootyStripes);

	byte bicik = *((byte*)0x0051A00F);
	if (bicik == 0x3F) { //if allCharsSame==TRUE then fix raptor's speed
		float turokspeed = *((float*)0x101423C4);
		//set raptor speed to be 1.25 times faster than turok:
		turokspeed *= 1.25;
		WriteToMemory((LPVOID)0x10144644, &turokspeed, sizeof(turokspeed));
		*((float*)0x10144648) = 1.6;
	}
	
	WriteToMemory((LPVOID)0x00523E5C, &weaponfov1, sizeof(weaponfov1));
	WriteToMemory((LPVOID)0x00528824, &maxpan, sizeof(maxpan));
	setFrameTime(minFrameTime, autoFixedF);
	if (camerafov1 >= 90) {
		camerafov1 *= 0.017444445;
		WriteToMemory((LPVOID)0x00508380, &camerafov1, 4);
		camerafov1 = 90;
		if (camerafov1 > 90) print("\x4 Warning! FOV over 90 may be bugged!");
	}
	WriteToMemory((LPVOID)0x106FD408, &camerafov1, 4);

	while (isTeamGameMode) { //game is loading (joining to server)
		Sleep(16);
		int var = *((int*)0x106D1C84);
		if (var == 1 || var == 2) {
			break;
		}
		else if (*(int*)0x00AD02C8) {
			playChooseTeamLector();
			break;
		}
	}

	WriteToMemory((LPVOID)0x004F9A80, &weaponsize2, sizeof(weaponsize2));

	CreateThread(0, 0, &readServersCfg, 0, 0, NULL);

	string s = "T2 kub's mod " + version + "++ (1.0 PRE-RELEASE) (type /fov 90 to change field of view)";
	printString(s);
	if (motd != "") {
		printString(motd);
	}

	Sleep(16);
	if (reloadModelsNeeded)
		reloadCharModels();

	checkNickname();

	if (isServerBot) {
		string temp = " \x4/aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
		char * writable2 = new char[temp.size() + 1];
		strcpy(writable2, temp.c_str());
		WriteToMemory((LPVOID)0x00AD8384, writable2, strlen(writable2) + 1);
		delete[] writable2;

		if (isServerBotRequired) {
			temp = "WAITING FOR SERVER BOT";
			char * writable = new char[temp.size() + 1];
			strcpy(writable, temp.c_str());
			WriteToMemory((LPVOID)0x0051B93C, writable, strlen(writable) + 1);
			delete[] writable;
		}

		Sleep(1200);

		if (myid == -1)
			sendJoin();

		if (cfgurl == "null")
			sayHello();

		while (true) {
			Sleep(48000);
			if (!doCheckVoice && hasJoined) {
				doCheckVoice = true;
				isHostVoice = false;
				ss.str("");
				ss << " \x4/99" << " gvoice " << myid;
				sendCmdToBot(ss.str());
				std::async(std::launch::async, checkVoice);
			}
		}
	}
	else if (cfgurl == "null") {
		sayHello();
	}

	modCfg.join();

	return S_OK;
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		print = (int(__cdecl*)(const char *text))DetourFunction((PBYTE)0x48A7A0, (PBYTE)hookedPrint); //Magic
		sendingHook = (int(__cdecl*)(char *text))DetourFunction((PBYTE)0x4C3250, (PBYTE)hookedSendMsg); 
		sendingHook2 = (int(__cdecl*)(int text1, int text2))DetourFunction((PBYTE)0x48FC40, (PBYTE)hookedSendMsg2); 
		startingHook = (int(__cdecl*)())DetourFunction((PBYTE)0x4C0310, (PBYTE)hookedStarting); 
		SpectJoinHook = (int(__cdecl*)(int int1, int int2))DetourFunction((PBYTE)0x485B00, (PBYTE)hookedSpectJoin); 
		TeamChangeHook = (int_1int_)DetourFunction((PBYTE)0x485EB0, (PBYTE)hookedTeamChange); 
		respawn = (int_1int_)DetourFunction((PBYTE)0x425F50, (PBYTE)hookedRespawn); 
		changeChar = (int_1int_)DetourFunction((PBYTE)0x486040, (PBYTE)hookedCharacterChange);
		remap = (int_3int_)DetourFunction((PBYTE)0x468260, (PBYTE)hookedRemap);
		characterAnimation = (int_3int_)DetourFunction((PBYTE)0x41FE50, (PBYTE)hookedCharacterAnimation);
		//incPlayerCount = (int_2int_)DetourFunction((PBYTE)0x434AC0, (PBYTE)hookedIncPlayerCount);
		decPlayerCount = (int_2int_)DetourFunction((PBYTE)0x434BE0, (PBYTE)hookedDecPlayerCount);
		levelEnd = (int_2int_)DetourFunction((PBYTE)0x4858E0, (PBYTE)hookedLevelEnd);
		DropWeapon = (int(__cdecl*)(int var1, int var2, float var3))DetourFunction((PBYTE)0x4261F0, (PBYTE)hookedWeaponDrop);
		PickupWeapon = (int(__cdecl*)(int int1, int int2))DetourFunction((PBYTE)0x480D80, (PBYTE)hookedWeaponPickup);
		Fire = (int(__cdecl*)(int var1, int var2))DetourFunction((PBYTE)0x419260, (PBYTE)hookedShotFired); 
		damage = (int(__cdecl*)(int var1, int var2, int *var3, int *var4, int *var5))DetourFunction((PBYTE)0x488000, (PBYTE)hookedDamage); 
		indamage1 = (int(__cdecl*)(int var1, int var2, int var3))DetourFunction((PBYTE)0x419220, (PBYTE)hookedIndamage1); 
		CreateThread(0, 0x1000, &Main_thread, 0, 0, NULL);
		CreateThread(0, 0, &ExecutingCommands_thread, 0, 0, NULL);
		CreateThread(0, 0, &CustomWeapons_thread, 0, 0, NULL); 
	}
	return TRUE;
}
