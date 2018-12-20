#include <iostream>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <iostream>
#include <tlhelp32.h>
#include <fstream>
//#include <sstream>
using namespace std;

/*DWORD getPid(string procName){
       HANDLE hsnap;
       PROCESSENTRY32 pt;
       PROCESSENTRY32 pt_;
	   bool bzyt = false;
       hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
       pt.dwSize = sizeof(PROCESSENTRY32);
       int counter = 0;
       do{
		   //std::wstring ws(pt.szExeFile);
		   //std::string s((const char*)&ws[0], sizeof(wchar_t)/sizeof(char)*ws.size());
		   //if(s.compare(procName)){  //if(pt.szExeFile == procName){
		    if(pt.szExeFile == procName){
                DWORD pid = pt.th32ProcessID;
                CloseHandle(hsnap);
                return pid;
            }
            if(bzyt && pt.th32ProcessID == pt_.th32ProcessID){
                if(counter<3){
                    hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
                    pt.dwSize = sizeof(PROCESSENTRY32);
                    cout << "!" << endl;
                }else if (counter>100){
                    return 0;
                }
                counter++;
            }
            pt_ = pt;
			bzyt = true;
            //if(pt.th32ProcessID == pt_.th32ProcessID) cout << "Tak" << endl;
        } while(Process32Next(hsnap, &pt));
        CloseHandle(hsnap);
        return 0;   //if nothing is found return 0;

        }*/

DWORD getPid(string name)
{
    DWORD pid = 0;

    // Create toolhelp snapshot.
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 process;
    ZeroMemory(&process, sizeof(process));
    process.dwSize = sizeof(process);

    // Walkthrough all processes.
    if (Process32First(snapshot, &process))
    {
        do
        {
            // Compare process.szExeFile based on format of name, i.e., trim file path
            // trim .exe if necessary, etc.
            if (string(process.szExeFile) == string(name))
            {
               pid = process.th32ProcessID;
               break;
            }
        } while (Process32Next(snapshot, &process));
    }

    CloseHandle(snapshot);

    return pid;
}

BOOL InjectLibrary(HANDLE hProcess, char *fnDll) {

    BOOL success = FALSE;
    HANDLE hThread = NULL;
    char *fnRemote = NULL;
    FARPROC procLoadLibraryA = NULL;

    size_t lenFilename = strlen(fnDll) + 1;

    /* Allocate space in the remote process */
    fnRemote = (char *)VirtualAllocEx(hProcess, NULL, lenFilename, MEM_COMMIT, PAGE_READWRITE);

    if (fnRemote) {

        /* Write the filename to the remote process. */
        if (WriteProcessMemory(hProcess, fnRemote, fnDll, lenFilename, NULL)) {

            /* Get the address of the LoadLibraryA function */
            procLoadLibraryA = GetProcAddress(GetModuleHandle("Kernel32"), "LoadLibraryA");
            hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)procLoadLibraryA, fnRemote, 0, NULL);

            if (hThread) {
                WaitForSingleObject(hThread, INFINITE);
                success = TRUE;
            }
        }

        VirtualFreeEx(hProcess, fnRemote, 0, MEM_RELEASE);
    }

    return success;
}

HANDLE proc;

int main()
{
    string ip;
    string exe;
    string dll = "kubs_mod_client.dll";
    exe = "Turok2MP.exe";
    ip = "-maxframerate 64 -quickmouse -exclusivemouse";
    float camerafov1 = 70;
    float weaponfov1 = 50;
    float maxpan = 3000;
    bool showGUI = true;
    ifstream config;
    config.open("launcherConfig.txt", std::fstream::in);
    if( !config.good() ){
        cout << "Config not found. Creating new one." << endl;
        config.close();
        ofstream newconfig;
        newconfig.open("launcherConfig.txt", std::fstream::trunc | std::fstream::out);
        newconfig << "ExeName=Turok2MP.exe" << endl;
        newconfig << "StartupParameters=-maxframerate 64 -quickmouse -exclusivemouse" << endl;
        newconfig << "CameraFOV=70" << endl;
        newconfig << "WeaponFOV=50" << endl;
        //newconfig << "ShowGUI=1" << endl;
        newconfig << "//MaxPan is about \"3D sound\" (600 is default, 10000 is best for competitive gameplay but may be annoying) - you can test it in game with 'set maxpan' command." << endl;
        newconfig << "MaxPan=3000" << endl;
        newconfig.close();
    }else{
        string slowo;
        string wiersz;
        //std::stringstream ss;
        while(getline( config, wiersz )){
            //ss.str( std::string() ); ss.clear();
            //ss << wiersz;
            //ss >> slowo; //while(ss >> slowo){
            slowo = wiersz.substr(0,wiersz.find("=")+1);
            //cout << slowo << endl;
                if(slowo == "StartupParameters="){
                    ip = wiersz.substr(wiersz.find("=")+1);
                }else if(slowo == "ExeName="){
                    exe = wiersz.substr(wiersz.find("=")+1);
                }else if(slowo == "DllName="){
                    dll = wiersz.substr(wiersz.find("=")+1);
                    //cout << "dll: " << dll << endl;
                }
                slowo.clear();
                wiersz.clear();
        }
    }
    config.close();

    cout << "T2 Multiplayer mod launcher by kubpica 1.1" << endl;
    cout << "kubpicapf@gmail.com" << endl;
    cout << "Tested with 1.03 exe (Basber's mod exe v1.27) - probably works also with clean 1.03" << endl;

    DWORD pid = getPid(exe.c_str());
    if (pid!=0){
        cout << "Game is already running." << endl;
        cin.get();
        return 1;
    }

    int h = (int) ShellExecute( NULL, NULL, exe.c_str(), ip.c_str(), NULL, SW_SHOW );
    if ( !(h>32) ){
        cout << "Could not open game." << endl;
        cout << "Make sure you have " << exe << " and this launcher in your turok2 main folder" << endl;
        cin.get();
        return 1;
    }

    Sleep(1000);

    pid = getPid(exe.c_str());
    if (pid==0){
        cout << "Game not found in processes. Make sure you have " << exe << " and this launcher in your turok2 main folder" << endl;
        cin.get();
        return 1;
    }

    proc = OpenProcess(PROCESS_ALL_ACCESS,false,pid);
    if (proc==NULL){
        cout << "Could not open game process." << endl;
        cin.get();
        return 1;
    }

    cout << "Game found." << endl;
    char * writable = new char[dll.size() + 1];
	strcpy(writable, dll.c_str());
    if(InjectLibrary(proc, writable)){
        //cout << "Mod (dll) injected successfully" << endl;
        cout << "Injecting " << dll << endl;
        //system("pause");
    }
    else{
        cout << "Failed to inject dll (mod)." << endl;
        cin.get();
    }
    delete[] writable;
}
