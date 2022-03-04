# T2 kub's mod
Mod for original T2 PC multiplayer (1998).
Description of the modification: https://www.turokforums.com/index.php?topic=526.0

Sorry for uploading so much trash to this repo the actuall code is one .cpp file here: https://github.com/kubpica/T2KubsMod/blob/master/t2_dll_hook_client/dll_czitin_hook/main_10_prerelease25.cpp

# How do you mod Turok?
I use Cheat Engine to find intresting (addresses of) variables and functions, then I go to Ida just to check what it says about function I found (what type of function it is, how many arguments and of what type it thinks it is), then I code: I detour function using detours library, so I can add my own code before/after/instead-of function execution, I can read and change it's parameters and what it returns. Sometimes I make "mid function hook" when I can't detour function for some reason or I need to do some code in a specific place in the middle of the function execution. I also edited some functions by overwriting its assembler code byte by byte (some minor changes eg. to make some "if"/jmp always or never execute). I compile my code to .dll file and my Turok launcher injects it into game's memory.

Debuggers and disassemblers can help you find function you are interested in but you need also some luck and patience. Very often it's guessing and testing over and over - trial and error method ;p But tbh maybe there is a better way to do that - I am not hacking/reverse engineering expert, I'm just passionate about Turok and programming :)
And Yes I know the code looks terrifying. I was a novice programmer when I wrote this so it's not easy to read.

# Tips if you want to develop it further
Some things in the code are very low level like changing single bytes in the game's memory to change how frame rates behave etc The code isn't well described, and I can't remember what most of these things do. Some things were achieved by trial and error, so I didn't really know what exactly I was doing even at the time of coding this xD - This mainly applies when I was unlocking fps. I uploaded My Cheat Tables.7z - the cheat tables should explain some hex values.

# Polish
Modyfikacja do gry Turok2. Jest to gra z 1998 i nie ma żadnego API więc wszystko zostało zrobione na zasadzie edytowania pamięci gry i wstrzykiwania do niej własnego kodu (dll injection, function hooking, function detouring).

Od razu mówię, że nie jestem dumny z tego jak ten kod wygląda :P Dzisiaj napisałbym to przejrzyściej i prawdopodobnie obiektowo.
