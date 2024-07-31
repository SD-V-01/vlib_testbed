////////////////////////////////////////////////////////////////////////////
//
//  VLiB Source File.
//  Copyright (C), V Studio, 2018-2024.
// -------------------------------------------------------------------------
//  File name:   main.cpp
//  Version:     v1.00
//  Created:     03/05/24 by Serial Designation V-X1.
//  Description: 
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#include "v.h"
#include "system.h"
#include "mdvk.h"
#include "mdio.h"
#include "mdos.h"
#include "vhash.h"
#include "mdhud.h"

//#define REMOVE_USRCODE

void vrt_preInitUsr(){
	#ifndef REMOVE_USRCODE

	#endif

}

#ifndef REMOVE_USRCODE
static void testMemExtras() {
	VDLOG("Test", "Machine has {u64} bytes of free memory", vGetTotalRam());
	VDLOG("Test", "Machine has {u64} bytes of free mdSystemInfo memory", mdsysFreeRam());
	VDLOG("Test", "Machine has {u64} bytes of buffer mdSystemInfo memory", mdsysBufferRam());
	VDLOG("Test", "Machine has {u64} bytes of shared mdSystemInfo memory", mdsysSharedRam());
	VDLOG("Test", "Machine has {u64} bytes of free swap mdSystemInfo memory", mdsysFreeSwap());
	VDLOG("Test", "Machine has {u64} bytes of total swap mdSystemInfo memory", mdsysTotalSwap());
	VDLOG("Test", "Machine has {u64} uptime", mdsysUptime());
	VDLOG("Test", "Machine has {u64} processes running", mdsysTotalProcesses());

}

static void testMdhud() {
	vsys_writeConsoleNullStr("##########    Testing mdHud\n");
	mdHudCommandBuffer CmdBuffer;
	mdHudCreateCommandBuffer(&CmdBuffer, MD_HUD_COMMAND_BUFFER_DEFAULT_SIZE);
	mdHudDumpToStdoutCommandBuffer(&CmdBuffer);
	mdHudCheckSizeCommandBuffer(&CmdBuffer, 1024);
	//mdHudPopLastCommandBuffer(&CmdBuffer);
	mdHudDumpToStdoutCommandBuffer(&CmdBuffer);

	mdHudDestroyCommandBuffer(&CmdBuffer);

}

static void testConsole() {
	vsys_writeConsoleNullStr("##########    Testing console\n");

	mdConState TestState;
	mdConStateCreate(&TestState, "VLIB Test");
	mdConVar TestVar;
	TestVar.Var.VarInt = 70;
	TestVar.Flags = mdConVarFlags_CHEAT | mdConVarFlags_SAVE;
	TestVar.Type = mdConVarType_Int;
	TestVar.Name = "md_testVarInt0";
	TestVar.Help = "Test integer variable";
	TestVar.StatePtr = &TestState;
	mdConStateSet(&TestState, &TestVar);
	mdConStateSet(&TestState, &TestVar);
	TestVar.Var.VarInt = 69;
	//mdConStateDumpToStdout(&TestState);
	mdConStateSet(&TestState, &TestVar);
	//mdConStateDumpToStdout(&TestState);
	//TestState.HtSize = MD_CON_STATE_DEFAULT_CAPACITY;
	mdConStateResize(&TestState);
	mdConVar* TestSearch = mdConStateSearchVar(&TestState, "md_testVarInt0");
	if (TestSearch != NULL) {
		vsys_writeConsoleNullStr("Found md_testVarInt0 in hashmap found with val \"");
		vsys_writeConsoleInteger(TestSearch->Var.VarInt);
		vsys_writeConsoleNullStr("\" with name \"");
		vsys_writeConsoleNullStr(TestSearch->Name);
		vsys_writeConsoleNullStr("\"\n");
		char ConVarToStr[1024];
		mdConVarToStr(TestSearch, ConVarToStr, 1024);
		vsys_writeConsoleNullStr(ConVarToStr);
		vsys_writeConsoleNullStr("\n");

	}
	else {
		vsys_writeConsoleNullStr("Could not find md_testVarInt0\n");

	}

	mdConStateFmt(&TestState, "Testing", "Testing standalone console {u64}", mdConSeverity_none, 70);

	mdConStateDumpDbToSelfe(&TestState);

	mdConStateDestroy(&TestState);

}

static void testHash() {
	const char* TestStr = "MKey://windy_city";
	vsys_writeConsoleNullStr("##########   Testing hash\n");
	vsys_writeConsoleNullStr("Testing murmurHash3 custom impl \"");
	vsys_writeConsoleInteger(vmh332((void*)TestStr, vstrlen8(TestStr), 70));
	vsys_writeConsoleNullStr("\" For str \"");
	vsys_writeConsoleNullStr(TestStr);
	vsys_writeConsoleNullStr("\"\n");

}

static void testTime() {
	vsys_writeConsoleNullStr("##########   Testing mdos time\n");
	vsys_writeConsoleNullStr("Got \"");
	vsys_writeConsoleInteger(mdTimeGetMsSystemTime());
	vsys_writeConsoleNullStr("\" from getMsSystemTime()\n");

	vsys_writeConsoleNullStr("Got \"");
	vsys_writeConsoleInteger(mdTimeGetMicroSystemTime());
	vsys_writeConsoleNullStr("\" from getMicroSystemTime()\n");

	vsys_writeConsoleNullStr("Got \"");
	vsys_writeConsoleInteger(mdTimeGetUnixTime());
	vsys_writeConsoleNullStr("\" from mdTimeGetUnixTime()\n");

}

static void testFsUtil() {
	vsys_writeConsoleNullStr("##########   Testing filesys utils\nisDirSeparator / \"");
	bool isDirSpeResult = mdioIsDirectorySeparator('/');
	vsys_writeConsoleInteger(isDirSpeResult);
	vsys_writeConsoleNullStr("\"\n");

	char TestPath[MDIO_MAX_PATH] = "/home/_V/vlib_testbed/v/testing_path/V/test.c";
	vsys_writeConsoleNullStr("TestPath\"");
	vsys_writeConsoleNullStr(TestPath);
	vsys_writeConsoleNullStr("\"\n");

	char PathExtenionOut[MDIO_MAX_PATH] = { 0 };
	vsys_writeConsoleNullStr("Testing mdioReplacePathExtension with cpp \"");
	mdioReplacePathExtension(TestPath, "cpp", PathExtenionOut, MDIO_MAX_PATH);
	vsys_writeConsoleNullStr(PathExtenionOut);
	vsys_writeConsoleNullStr("\"\n");

	char ParentPath[MDIO_MAX_PATH] = { 0 };
	vsys_writeConsoleNullStr("Testing mdioGetParentPath \"");
	mdioGetParentPath(TestPath, ParentPath, MDIO_MAX_PATH);
	vsys_writeConsoleNullStr(ParentPath);
	vsys_writeConsoleNullStr("\"\n");

	char PathFilename[MDIO_MAX_PATH] = { 0 };
	vsys_writeConsoleNullStr("Testing mdioGetPathFilename \"");
	mdioGetPathFilename(TestPath, PathFilename, MDIO_MAX_PATH);
	vsys_writeConsoleNullStr(PathFilename);
	vsys_writeConsoleNullStr("\"\n");

	char PathExtension[MDIO_MAX_PATH] = { 0 };
	vsys_writeConsoleNullStr("Testing mdioGetPathExtension\"");
	mdioGetPathExtension(TestPath, PathExtension, MDIO_MAX_PATH);
	vsys_writeConsoleNullStr(PathExtension);
	vsys_writeConsoleNullStr("\"\n");

	char MergeDirAndFilename[MDIO_MAX_PATH] = { 0 };
	vsys_writeConsoleNullStr("Testing mdioMergeDirAndFilename\"");
	st MergeDirAndFilenameSize = mdioMergeDirAndFilename("/home/_V/", "music70.flac", '/', MergeDirAndFilename, MDIO_MAX_PATH);
	vsys_writeConsoleNullStr(MergeDirAndFilename);
	vsys_writeConsoleNullStr("\" with size \"");
	vsys_writeConsoleInteger(MergeDirAndFilenameSize);
	vsys_writeConsoleNullStr("\"\n");

	char NormalizePathContinue[MDIO_MAX_PATH] = { 0 };
	vsys_writeConsoleNullStr("Testing mdioNormalizePathContinue\"");
	st NormalizePathSize = mdioNormalizePathContinue("/home/V/testingNormalizedPath/", '\\', NormalizePathContinue, NormalizePathContinue, NormalizePathContinue + MDIO_MAX_PATH);
	vsys_writeConsole(NormalizePathContinue, NormalizePathSize);
	vsys_writeConsoleNullStr("\" with size \"");
	vsys_writeConsoleInteger(NormalizePathSize);
	vsys_writeConsoleNullStr("\"\n");


}

static void testVulkan() {
	vsys_writeConsoleNullStr("##########   Testing VULKAN !!!\n");
	vsys_writeConsoleNullStr("Initializing loader\n");
	mdvkInitLoader();

//    NOTE(V): Instance search
	{
		MDVK_ERROR GetSurfaceErr = MDVK_ERROR_UNKNOWN;
		u32 SurfaceSpecVer = 0;
		bool GetSurface = mdvkIsInstanceExtensionPresent("VK_KHR_surface", &GetSurfaceErr, &SurfaceSpecVer);
		if (GetSurface) {
			vsys_writeConsoleNullStr("Found instance ext \"VK_KHR_surface\" !!\n");

		}
		else {
			vsys_writeConsoleNullStr("Could not find instance ext \"VK_KHR_surface\" !!\n");

		}

		if (mdvkIsInstanceLayerPresent("VK_LAYER_VALVE_steam_overlay_64", NULL, NULL, NULL)) {
			vsys_writeConsoleNullStr("Found instance layer \"VK_LAYER_VALVE_steam_overlay_64\" !!!\n");

		}
		else {
			vsys_writeConsoleNullStr("Could not find instance layer \"VK_LAYER_VALVE_steam_overlay_64\" !!!\n");

		}
	}

	//    NOTE(V): Testing instance info dumping
	{
		mdvkDumpAllInstanceLayerToStdout();
	
		vsys_writeConsoleNullStr("Checking instance extensions\n");
		MDVK_ERROR DumpInstanceExt = mdvkDumpAllInstanceExtToStdout();
		vsys_writeConsoleInteger(DumpInstanceExt);
		vsys_writeConsoleNullStr(" error code for dump all instance extensions\n");

	}

	//    NOTE(V): Creating instance
	VkInstance TestInstance;
	{
		vsys_writeConsoleNullStr("Creating instance\n");

		MDVK_ERROR InstanceErr = mdvkCreateInstance(NULL, 0, NULL, 0,
													"VLIB Vulkan",
													VK_API_VERSION_1_3,
													NULL,
													&TestInstance);
		vsys_writeConsoleInteger(InstanceErr);
		vsys_writeConsoleNullStr(" Error got for instance creation\n");

	}

	//    NOTE(V): Physical device
	VkPhysicalDevice PhysDevice;
	{
		vsys_writeConsoleNullStr("Getting physical device\n");
	
		MDVK_ERROR PhysDeviceErr = mdvkGetBestPhysicalDevice(VK_API_VERSION_1_3, &TestInstance, &PhysDevice);

		vsys_writeConsoleNullStr("Got code \"");
		vsys_writeConsoleInteger(PhysDeviceErr);
		vsys_writeConsoleNullStr("\" For physical device \"");
		vsys_writeConsoleInteger((unsigned long int)PhysDevice);
		vsys_writeConsoleNullStr("\"\n");

	}

//    NOTE(V): Device dump
	MDVK_ERROR DeviceExtEnumErr = mdvkDumpAllDeviceExtToStdout(&PhysDevice);
	MDVK_ERROR DeviceLayerEnumErr = mdvkDumpAllDeviceLayerToStdout(&PhysDevice);

	//    NOTE(V): Creating device
	VkDevice Device;
	{
		vsys_writeConsoleNullStr("Creating Vulkan device !!!!!!!!\n");

		MDVK_ERROR DeviceErr = mdvkCreateDevice(NULL, 0, NULL, 0, NULL, 0, &PhysDevice, NULL, &Device);
		vsys_writeConsoleNullStr("Got error code \"");
		vsys_writeConsoleInteger(DeviceErr);
		vsys_writeConsoleNullStr("\" From device creation !!\n");

		vsys_writeConsoleInteger((unsigned long int)Device);
		vsys_writeConsoleNullStr(" Is ptr to vulkan device\n");

	}

}

static void testMem(u32 Length) {
	char* TestPtr = (char*)vsys_allocSmallPageGeneric(Length);

	vsys_writeConsoleNullStr("Testing \"");
	vsys_writeConsoleInteger(Length);
	vsys_writeConsoleNullStr("\" Bytes of memory alloc with ptr \"");
	vsys_writeConsoleInteger((u64)TestPtr);
	vsys_writeConsoleNullStr("\"\n");

	const char TestChar = 'V';

	for (u32 i = 0; i < Length; i++) {
		TestPtr[i] = TestChar;

	}

	for (u32 i = 0; i < Length; i++) {
		//vsys_writeConsole(&(TestPtr[i]), 1);
		if (TestPtr[i] != TestChar) {
			vsys_writeConsoleNullStr("Failed on offset \"");
			vsys_writeConsoleInteger(i);
			vsys_writeConsoleNullStr("\"\n");

		}

	}

	vsys_freeSmallPageGeneric((void*)TestPtr);

}

static void testVMem(u32 Length) {
	char* TestPtr = (char*)valloc(Length);

	vsys_writeConsoleNullStr("Testing \"");
	vsys_writeConsoleInteger(Length);
	vsys_writeConsoleNullStr("\" Bytes of memory VAlloc with ptr \"");
	vsys_writeConsoleInteger((u64)TestPtr);
	vsys_writeConsoleNullStr("\"\n");

	const char TestChar = 'V';

	for (u32 i = 0; i < Length; i++) {
		TestPtr[i] = TestChar;

	}

	for (u32 i = 0; i < Length; i++) {
		//vsys_writeConsole(&(TestPtr[i]), 1);
		if (TestPtr[i] != TestChar) {
			vsys_writeConsoleNullStr("Failed on offset \"");
			vsys_writeConsoleInteger(i);
			vsys_writeConsoleNullStr("\"\n");

		}

	}

	vfree(TestPtr);

}

static void testIntegers() {
	vsys_writeConsoleNullStr("##########   Testing integers\n");
	vsys_writeConsoleInteger(sizeof(u64));
	vsys_writeConsoleNullStr(" Bytes for u64\n");
	vsys_writeConsoleInteger(sizeof(u32));
	vsys_writeConsoleNullStr(" Bytes for u32\n");
	vsys_writeConsoleInteger(sizeof(u16));
	vsys_writeConsoleNullStr(" Bytes for u16\n");
	vsys_writeConsoleInteger(sizeof(u8));
	vsys_writeConsoleNullStr(" Bytes for u8\n");

	vsys_writeConsoleInteger(sizeof(i64));
	vsys_writeConsoleNullStr(" Bytes for i64\n");
	vsys_writeConsoleInteger(sizeof(i32));
	vsys_writeConsoleNullStr(" Bytes for i32\n");
	vsys_writeConsoleInteger(sizeof(i16));
	vsys_writeConsoleNullStr(" Bytes for i16\n");
	vsys_writeConsoleInteger(sizeof(i8));
	vsys_writeConsoleNullStr(" Bytes for i8\n");

}

static void testVstr32() {
	vsys_writeConsoleNullStr("##########   Testing vstr32 implementation\n");
	char IntToStrTest[32];
	st IntToStrSize = vinttostr8(1234567, IntToStrTest, 8);
	vsys_writeConsoleNullStr("String got for vinttostr8 of 1234567\"");
	vsys_writeConsoleNullStr(IntToStrTest);
	vsys_writeConsoleNullStr("\" With size \"");
	vsys_writeConsoleInteger(IntToStrSize);
	vsys_writeConsoleNullStr("\"\n");
	
	char IntToHexTest[32];
	st IntToHexSize = vinttohex8(1736725348, IntToHexTest, 20);
	vsys_writeConsoleNullStr("String got for vinttohex8 of 1736725348\"");
	vsys_writeConsoleNullStr(IntToHexTest);
	vsys_writeConsoleNullStr("\" with size \"");
	vsys_writeConsoleInteger(IntToHexSize);
	vsys_writeConsoleNullStr("\"\n");

	vsys_writeConsoleNullStr("Testing formatting\n");
	#define FORMAT_BUF_SIZE 256
	char FormatBuf[FORMAT_BUF_SIZE];
	const char* FormatInTest = "Testing {cstr} formarring";
	st FormatResult = vformat8("Testing formatting {u64} u64\"{u64:}\" u32\"{u32}\" bool {bool} {bool} with {eol}{i32} V{p}_{u64}"
							   "hex {u32:hex}{u32:hex} str {cstr}{eol}",
							   FormatBuf, FORMAT_BUF_SIZE, 18446744073709551615U, 70, 42, true, false,
							   -70, 18446744073709551615U, 18446744073709551615U,
							   4294967295, 1, FormatInTest);
	vsys_writeConsoleNullStr("\"");
	vsys_writeConsoleNullStr(FormatBuf);
	vsys_writeConsoleNullStr("\" with size \"");
	vsys_writeConsoleInteger(FormatResult);
	vsys_writeConsoleNullStr("\" strlen \"");
	vsys_writeConsoleInteger(vstrlen8(FormatBuf));
	vsys_writeConsoleNullStr("\"\n");

}

#endif

void vrt_usrCode() {
	#ifndef REMOVE_USRCODE
	vsys_writeConsoleNullStr("##########   Testing runtime\n");
	char TestArray[20];
	vsys_intToStr(321564687, TestArray);
	vsys_writeConsoleNullStr(TestArray);
	vsys_writeConsoleNullStr("#\n");

	vsys_writeConsoleNullStr("##########   Testing memory alloc syscall\n");

	#if 0
	testMem(4096);
	testMem(32768);
	testMem(4096000);
	testMem(16384000);
	testMem(262144000);
	//testMem(2621440000);
	//testMem(3686400000);

	#endif

	testVMem(4096);
	testVMem(32768);
	testVMem(4096000);
	testVMem(16384000);
	testVMem(262144000);
	testMemExtras();

	testIntegers();

	//vsys_breakpoint();

	testVulkan();

	vsys_writeConsoleNullStr("##########   Testing vsys_getOsVar\n");
	#define OSVAR_SIZE 64
	char Var[OSVAR_SIZE];
	vsys_getOsVar("XDG_SESSION_TYPE", Var, OSVAR_SIZE);
	vsys_writeConsoleNullStr("\"");
	vsys_writeConsoleNullStr(Var);
	vsys_writeConsoleNullStr("\" Is the result from getOsVar\n");

	//testVstr32();
	//testFsUtil();
	//testTime();
	//testHash();
	//testConsole();
	//testMdhud();

	#endif

}
