//#define DEBUG_CONSOLE // Uncomment this if you want a debug console

// Mod Name. Make sure it matches the mod folder's name
#define MOD_NAME "69420"
#define MOD_VER "6.9"

#include <Windows.h>
#include <cstdio>
#include <4dm.h>
using namespace fdm;

unsigned int __fastcall MaterialItem_getStackLimit_H(Item* self)
{
	return 69420;
}

unsigned int __fastcall ToolItem_getStackLimit_H(Item* self)
{
	if (self->getName() != "Stick")
		return 1;
	else
		return 69420;
}

DWORD WINAPI Main_Thread(void* hModule)
{
	// Create console window if DEBUG_CONSOLE is defined
#ifdef DEBUG_CONSOLE
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
#endif
	
	glfwInit();
	glewInit();

	// Hook to the MaterialItem::getStackLimit function
	Hook(reinterpret_cast<void*>(base + idaOffsetFix(0x16900)), reinterpret_cast<void*>(&MaterialItem_getStackLimit_H), NULL);
	// Hook to the ToolItem::getStackLimit function
	Hook(reinterpret_cast<void*>(base + idaOffsetFix(0x9C3A0)), reinterpret_cast<void*>(&ToolItem_getStackLimit_H), NULL);

	EnableHook(0);
	return true;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD _reason, LPVOID lpReserved)
{
	if (_reason == DLL_PROCESS_ATTACH)
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Main_Thread, hModule, 0, NULL);
	return TRUE;
}
