// OledlgVAX.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "OledlgVAX.h"
#include "Common/xstring.hpp"
#include "Common/VisualAssistCryptoConfig.hpp"
#include "VisualAssistKeygen.hpp"

#include "Common/hooker/MinHook.h"
//#pragma comment(lib,"LibMinHook.lib")

#ifndef MAX_STRING
#define MAX_STRING 1024
#endif

#ifndef InvokePtrAs
#define InvokePtrAs(t,...) ((decltype(t)*)(G_##t))(__VA_ARGS__)
#endif
const char* oPublicKeyX = "4065234961,2221233238252903594850812155620126,3175203956977476891557515669668792";
const char* oPublicKeyY = "1329115615,9626603984703850283064885442292035,3463780848057510008753765087591958";
const char* cPublicKeyX = "2127088620,2558213661223504372788100802238141,2694097057723490910395353919176313";
const char* cPublicKeyY = "2127088620,8809976404932220599325753072055172,1929719295914332726580392022338415";

#ifdef _WIN64
#define HIJACKED_DLL_NAME "msenv_r"    //<--- modify

/* gcc does't support this. */
#pragma comment(linker, "/EXPORT:DllCanUnloadNow=" HIJACKED_DLL_NAME ".#1,@1")
#pragma comment(linker, "/EXPORT:DllGetClassObject=" HIJACKED_DLL_NAME ".#2,@2")
#pragma comment(linker, "/EXPORT:DllMain=" HIJACKED_DLL_NAME ".#3,@3")
#pragma comment(linker, "/EXPORT:IsSystemFontAvailable=" HIJACKED_DLL_NAME ".#4,@4")
#pragma comment(linker, "/EXPORT:VStudioComposeMEF=" HIJACKED_DLL_NAME ".#5,@5")
#pragma comment(linker, "/EXPORT:VStudioMain=" HIJACKED_DLL_NAME ".#6,@6")
#pragma comment(linker, "/EXPORT:VStudioTerm=" HIJACKED_DLL_NAME ".#7,@7")
#pragma comment(linker, "/EXPORT:VStudioValidateCmds=" HIJACKED_DLL_NAME ".#8,@8")
#else
#define HIJACKED_DLL_NAME "vcruntime140_r"    //<--- modify

/* gcc does't support this. */
#pragma comment(linker, "/EXPORT:__CreateFrameInfo=" HIJACKED_DLL_NAME ".#1,@1")
#pragma comment(linker, "/EXPORT:__CxxThrowException=" HIJACKED_DLL_NAME ".#2,@2")
#pragma comment(linker, "/EXPORT:__EH_prolog=" HIJACKED_DLL_NAME ".#3,@3")
#pragma comment(linker, "/EXPORT:__FindAndUnlinkFrame=" HIJACKED_DLL_NAME ".#4,@4")
#pragma comment(linker, "/EXPORT:__IsExceptionObjectToBeDestroyed=" HIJACKED_DLL_NAME ".#5,@5")
#pragma comment(linker, "/EXPORT:__NLG_Dispatch2=" HIJACKED_DLL_NAME ".#6,@6")
#pragma comment(linker, "/EXPORT:__NLG_Return=" HIJACKED_DLL_NAME ".#7,@7")
#pragma comment(linker, "/EXPORT:__NLG_Return2=" HIJACKED_DLL_NAME ".#8,@8")
#pragma comment(linker, "/EXPORT:__SetWinRTOutOfMemoryExceptionCallback=" HIJACKED_DLL_NAME ".#9,@9")
#pragma comment(linker, "/EXPORT:___AdjustPointer=" HIJACKED_DLL_NAME ".#10,@10")
#pragma comment(linker, "/EXPORT:___BuildCatchObject=" HIJACKED_DLL_NAME ".#11,@11")
#pragma comment(linker, "/EXPORT:___BuildCatchObjectHelper=" HIJACKED_DLL_NAME ".#12,@12")
#pragma comment(linker, "/EXPORT:___CxxDetectRethrow=" HIJACKED_DLL_NAME ".#13,@13")
#pragma comment(linker, "/EXPORT:___CxxExceptionFilter=" HIJACKED_DLL_NAME ".#14,@14")
#pragma comment(linker, "/EXPORT:___CxxFrameHandler=" HIJACKED_DLL_NAME ".#15,@15")
#pragma comment(linker, "/EXPORT:___CxxFrameHandler2=" HIJACKED_DLL_NAME ".#16,@16")
#pragma comment(linker, "/EXPORT:___CxxFrameHandler3=" HIJACKED_DLL_NAME ".#17,@17")
#pragma comment(linker, "/EXPORT:___CxxLongjmpUnwind=" HIJACKED_DLL_NAME ".#18,@18")
#pragma comment(linker, "/EXPORT:___CxxQueryExceptionSize=" HIJACKED_DLL_NAME ".#19,@19")
#pragma comment(linker, "/EXPORT:___CxxRegisterExceptionObject=" HIJACKED_DLL_NAME ".#20,@20")
#pragma comment(linker, "/EXPORT:___CxxUnregisterExceptionObject=" HIJACKED_DLL_NAME ".#21,@21")
#pragma comment(linker, "/EXPORT:___DestructExceptionObject=" HIJACKED_DLL_NAME ".#22,@22")
#pragma comment(linker, "/EXPORT:___FrameUnwindFilter=" HIJACKED_DLL_NAME ".#23,@23")
#pragma comment(linker, "/EXPORT:___GetPlatformExceptionInfo=" HIJACKED_DLL_NAME ".#24,@24")
#pragma comment(linker, "/EXPORT:___RTCastToVoid=" HIJACKED_DLL_NAME ".#25,@25")
#pragma comment(linker, "/EXPORT:___RTDynamicCast=" HIJACKED_DLL_NAME ".#26,@26")
#pragma comment(linker, "/EXPORT:___RTtypeid=" HIJACKED_DLL_NAME ".#27,@27")
#pragma comment(linker, "/EXPORT:___TypeMatch=" HIJACKED_DLL_NAME ".#28,@28")
#pragma comment(linker, "/EXPORT:___current_exception=" HIJACKED_DLL_NAME ".#29,@29")
#pragma comment(linker, "/EXPORT:___current_exception_context=" HIJACKED_DLL_NAME ".#30,@30")
#pragma comment(linker, "/EXPORT:___intrinsic_setjmp=" HIJACKED_DLL_NAME ".#31,@31")
#pragma comment(linker, "/EXPORT:___processing_throw=" HIJACKED_DLL_NAME ".#32,@32")
#pragma comment(linker, "/EXPORT:___report_gsfailure=" HIJACKED_DLL_NAME ".#33,@33")
#pragma comment(linker, "/EXPORT:___std_exception_copy=" HIJACKED_DLL_NAME ".#34,@34")
#pragma comment(linker, "/EXPORT:___std_exception_destroy=" HIJACKED_DLL_NAME ".#35,@35")
#pragma comment(linker, "/EXPORT:___std_terminate=" HIJACKED_DLL_NAME ".#36,@36")
#pragma comment(linker, "/EXPORT:___std_type_info_compare=" HIJACKED_DLL_NAME ".#37,@37")
#pragma comment(linker, "/EXPORT:___std_type_info_destroy_list=" HIJACKED_DLL_NAME ".#38,@38")
#pragma comment(linker, "/EXPORT:___std_type_info_hash=" HIJACKED_DLL_NAME ".#39,@39")
#pragma comment(linker, "/EXPORT:___std_type_info_name=" HIJACKED_DLL_NAME ".#40,@40")
#pragma comment(linker, "/EXPORT:___telemetry_main_invoke_trigger=" HIJACKED_DLL_NAME ".#41,@41")
#pragma comment(linker, "/EXPORT:___telemetry_main_return_trigger=" HIJACKED_DLL_NAME ".#42,@42")
#pragma comment(linker, "/EXPORT:___unDName=" HIJACKED_DLL_NAME ".#43,@43")
#pragma comment(linker, "/EXPORT:___unDNameEx=" HIJACKED_DLL_NAME ".#44,@44")
#pragma comment(linker, "/EXPORT:___uncaught_exception=" HIJACKED_DLL_NAME ".#45,@45")
#pragma comment(linker, "/EXPORT:___uncaught_exceptions=" HIJACKED_DLL_NAME ".#46,@46")
#pragma comment(linker, "/EXPORT:___vcrt_GetModuleFileNameW=" HIJACKED_DLL_NAME ".#47,@47")
#pragma comment(linker, "/EXPORT:___vcrt_GetModuleHandleW=" HIJACKED_DLL_NAME ".#48,@48")
#pragma comment(linker, "/EXPORT:___vcrt_InitializeCriticalSectionEx=" HIJACKED_DLL_NAME ".#49,@49")
#pragma comment(linker, "/EXPORT:___vcrt_LoadLibraryExW=" HIJACKED_DLL_NAME ".#50,@50")
#pragma comment(linker, "/EXPORT:__chkesp=" HIJACKED_DLL_NAME ".#51,@51")
#pragma comment(linker, "/EXPORT:__except_handler2=" HIJACKED_DLL_NAME ".#52,@52")
#pragma comment(linker, "/EXPORT:__except_handler3=" HIJACKED_DLL_NAME ".#53,@53")
#pragma comment(linker, "/EXPORT:__except_handler4_common=" HIJACKED_DLL_NAME ".#54,@54")
#pragma comment(linker, "/EXPORT:__get_purecall_handler=" HIJACKED_DLL_NAME ".#55,@55")
#pragma comment(linker, "/EXPORT:__get_unexpected=" HIJACKED_DLL_NAME ".#56,@56")
#pragma comment(linker, "/EXPORT:__global_unwind2=" HIJACKED_DLL_NAME ".#57,@57")
#pragma comment(linker, "/EXPORT:__is_exception_typeof=" HIJACKED_DLL_NAME ".#58,@58")
#pragma comment(linker, "/EXPORT:__local_unwind2=" HIJACKED_DLL_NAME ".#59,@59")
#pragma comment(linker, "/EXPORT:__local_unwind4=" HIJACKED_DLL_NAME ".#60,@60")
#pragma comment(linker, "/EXPORT:__longjmpex=" HIJACKED_DLL_NAME ".#61,@61")
#pragma comment(linker, "/EXPORT:__purecall=" HIJACKED_DLL_NAME ".#62,@62")
#pragma comment(linker, "/EXPORT:__seh_longjmp_unwind=" HIJACKED_DLL_NAME ".#64,@64")
#pragma comment(linker, "/EXPORT:__seh_longjmp_unwind4=" HIJACKED_DLL_NAME ".#63,@63")
#pragma comment(linker, "/EXPORT:__set_purecall_handler=" HIJACKED_DLL_NAME ".#65,@65")
#pragma comment(linker, "/EXPORT:__set_se_translator=" HIJACKED_DLL_NAME ".#66,@66")
#pragma comment(linker, "/EXPORT:__setjmp3=" HIJACKED_DLL_NAME ".#67,@67")
#pragma comment(linker, "/EXPORT:longjmp=" HIJACKED_DLL_NAME ".#68,@68")
#pragma comment(linker, "/EXPORT:memchr=" HIJACKED_DLL_NAME ".#69,@69")
#pragma comment(linker, "/EXPORT:memcmp=" HIJACKED_DLL_NAME ".#70,@70")
#pragma comment(linker, "/EXPORT:memcpy=" HIJACKED_DLL_NAME ".#71,@71")
#pragma comment(linker, "/EXPORT:memmove=" HIJACKED_DLL_NAME ".#72,@72")
#pragma comment(linker, "/EXPORT:memset=" HIJACKED_DLL_NAME ".#73,@73")
#pragma comment(linker, "/EXPORT:set_unexpected=" HIJACKED_DLL_NAME ".#74,@74")
#pragma comment(linker, "/EXPORT:strchr=" HIJACKED_DLL_NAME ".#75,@75")
#pragma comment(linker, "/EXPORT:strrchr=" HIJACKED_DLL_NAME ".#76,@76")
#pragma comment(linker, "/EXPORT:strstr=" HIJACKED_DLL_NAME ".#77,@77")
#pragma comment(linker, "/EXPORT:unexpected=" HIJACKED_DLL_NAME ".#78,@78")
#pragma comment(linker, "/EXPORT:wcschr=" HIJACKED_DLL_NAME ".#79,@79")
#pragma comment(linker, "/EXPORT:wcsrchr=" HIJACKED_DLL_NAME ".#80,@80")
#pragma comment(linker, "/EXPORT:wcsstr=" HIJACKED_DLL_NAME ".#81,@81")
#endif


int __cdecl PrintA(const char* fmt, ...)
{
	int nRet = 0;
	va_list arg_ptr;
	va_start(arg_ptr, fmt);
	int length = MAX_STRING * 4 *sizeof(char);
	char * text = (char*)alloca(length);
	if (text)
	{
		int len = (int)strlen(fmt) + 8;
		char *nfmt = (char*)alloca(len*sizeof(char));
		if (nfmt)
		{
			_snprintf_s(nfmt,len,len-1,"[>Dbg<]%s",fmt);
			nRet = _vsnprintf_s(text, length/sizeof(char), length / sizeof(char) - 1, nfmt, arg_ptr);
			OutputDebugStringA(text);
		}
	}
	va_end(arg_ptr);
	return nRet;
}

int __cdecl PrintW(const wchar_t* fmt, ...)
{
	int nRet = 0;
	va_list arg_ptr;
	va_start(arg_ptr, fmt);
	int length = MAX_STRING * 4 * sizeof(WCHAR);
	WCHAR * text = (WCHAR*)alloca( length);
	if (text)
	{
		int len = (int)wcslen(fmt) + 8;
		WCHAR *nfmt = (WCHAR*)alloca( len * sizeof(WCHAR));
		if (nfmt)
		{
			_snwprintf_s(nfmt,len,len-1,L"[>Dbg<]%s",fmt);
			nRet = _vsnwprintf_s(text, length / sizeof(WCHAR), length / sizeof(WCHAR) - 1, nfmt, arg_ptr);
			OutputDebugStringW(text);
		}
	}
	va_end(arg_ptr);
	return nRet;
}


const byte* MemFind(const byte* lpMem,WORD wSize, const byte* lpSubMem ,WORD wSubSize)
{
	wSize -= wSubSize;
	for (WORD i = 0; i <= wSize; i++)
	{
		if (0 == memcmp(lpMem+i, lpSubMem, wSubSize))
		{
			return (const byte*)(lpMem + i);
		}
	}
	return nullptr;
}

CRITICAL_SECTION G_CS;
PVOID G_Memory = nullptr;
void TryReplaceKey()
{
    EnterCriticalSection(&G_CS);
    try
    {
//#ifdef _AMD64_
		int range = 0x2000;
//#else
//		int range = 0x50;
//#endif
        char* str1 = (char*)MemFind((const byte*)G_Memory, range, (const byte*)oPublicKeyX, (WORD)strlen(oPublicKeyX));
        char* str2 = (char*)MemFind((const byte*)G_Memory, range, (const byte*)oPublicKeyY, (WORD)strlen(oPublicKeyY));
		if (nullptr != str1 && nullptr != str2)
		{
			CopyMemory(str1, cPublicKeyX, strlen(cPublicKeyX));
			CopyMemory(str2, cPublicKeyY, strlen(cPublicKeyY));
            OutputDebugStringA("Path finished!");
			MH_DisableHook(MH_ALL_HOOKS);
			//MH_RemoveHook(MH_ALL_HOOKS);
			//MH_Uninitialize();
		}
    }
    catch (...) {}
    LeaveCriticalSection(&G_CS);
}

PVOID G_HeapAlloc = nullptr;
LPVOID WINAPI fHeapAlloc(__in HANDLE hHeap, __in DWORD dwFlags, __in SIZE_T dwBytes)
{
	PVOID Result = InvokePtrAs(HeapAlloc, hHeap, dwFlags, dwBytes);
	if (dwBytes == 0xFFFF)
	{
		G_Memory = Result;
	}
	return Result;
}

PVOID G_HeapFree = nullptr;
BOOL WINAPI fHeapFree(__inout HANDLE hHeap, __in DWORD dwFlags, __drv_freesMem(Mem) __post __notvalid __deref LPVOID lpMem)
{
    if (G_Memory && lpMem)
    {
        if (*(UCHAR*)lpMem == 'x')
        {
            TryReplaceKey();
        }
    }
	return InvokePtrAs(HeapFree, hHeap, dwFlags, lpMem);
}

VOID WINAPI Entry(HMODULE hModule)
{
    //MessageBoxA(NULL, "test", "test", 0);
	do 
	{
        InitializeCriticalSection(&G_CS);

        MH_STATUS sts = MH_Initialize();
        PrintA("MH_Initialize res:%d", sts);
		if(S_OK != sts) break;

        sts = MH_CreateHook(HeapAlloc, fHeapAlloc, &G_HeapAlloc);
        PrintA("MH_CreateHook res:%d", sts);
        if (S_OK != sts) break;

        sts = MH_CreateHook(HeapFree, fHeapFree, &G_HeapFree);
        PrintA("MH_CreateHook res:%d", sts);
        if (S_OK != sts) break;

        sts = MH_EnableHook(MH_ALL_HOOKS);
        PrintA("MH_EnableHook res: %d ", sts);
        if (S_OK != sts) break;

	} while (FALSE);
	return;
}

void Help() {
    _putts(TEXT("Usage:"));
    _putts(TEXT("    rundll32.exe ThisFile.dll,GenerateKey [-renew] <username> <license count> <expire date>"));
    _putts(TEXT(""));
    _putts(TEXT("        [-renew]           Generate renew-key."));
    _putts(TEXT("                           This parameter is optional."));
    _putts(TEXT(""));
    _putts(TEXT("        <username>         The username licensed to."));
    _putts(TEXT("                           This parameter must be specified."));
    _putts(TEXT(""));
    _putts(TEXT("        <license count>    The maximum number of copies that can be run under the newly-generated license."));
    _putts(TEXT("                           The value should be in 1 ~ 65536."));
    _putts(TEXT("                           This parameter must be specified."));
    _putts(TEXT(""));
    _putts(TEXT("        <expire date>      The date when the newly-generated license expires."));
    _putts(TEXT("                           The format must be one of the following:"));
    _putts(TEXT("                               1. \"yyyy/mm/dd\""));
    _putts(TEXT("                               2. \"yyyy-mm-dd\""));
    _putts(TEXT("                               3. \"yyyy.mm.dd\""));
    _putts(TEXT("                           This parameter must be specified."));
    _putts(TEXT("        eg:  rundll32.exe Oledlg.dll,GenerateKey -renew * 255 2099/12/12"));
    _putts(TEXT(""));
}

int split(std::xstring str, std::vector<std::xstring>& ret, const TCHAR* const delimiter, int countDelimiters, bool ignoreEmptyTokens, bool keepSeparators)
{
    if (!delimiter)
        return 0;

    const size_t oldSize = ret.size();

    size_t tokenStartIdx = 0;
    for (size_t i = 0; i < str.size(); ++i)
    {
        for (int j = 0; j < countDelimiters; ++j)
        {
            if (str[i] == delimiter[j])
            {
                if (keepSeparators)
                {
                    ret.push_back(str.substr(tokenStartIdx, i + 1 - tokenStartIdx));
                }
                else
                {
                    if (i - tokenStartIdx > 0)
                        ret.push_back(str.substr(tokenStartIdx, i - tokenStartIdx));
                    else if (!ignoreEmptyTokens)
                        ret.push_back(std::xstring());
                }
                tokenStartIdx = i + 1;
                break;
            }
        }
    }
    if ((str.size()) > tokenStartIdx)
        ret.push_back(str.substr(tokenStartIdx, (str.size()) - tokenStartIdx));

    return (int)(ret.size() - oldSize);
}

extern "C" __declspec(dllexport) VOID WINAPI GenerateKey(HWND hwnd, HINSTANCE hinst, LPCSTR lpszCmdLine, int nCmdShow)
{
    int argc = 0;
    AllocConsole();

    FILE* m_new_stdout_file = nullptr;
    freopen_s(&m_new_stdout_file, "CONOUT$", "w+t", stdout);
    std::vector<std::xstring> argv;
	if (lpszCmdLine != nullptr && (argc = split(CA2W(lpszCmdLine).m_psz, argv, TEXT(" "),1,true,false))>=3)
	{
        try
        {
            uint32_t Year;
            uint32_t Month;
            uint32_t Day;
            if (_stscanf_s(argv[argc - 1].c_str(), TEXT("%u/%u/%u"), &Year, &Month, &Day) != 3)
            {
                if (_stscanf_s(argv[argc - 1].c_str(), TEXT("%u-%u-%u"), &Year, &Month, &Day) != 3)
                {
                    if (_stscanf_s(argv[argc - 1].c_str(), TEXT("%u.%u.%u"), &Year, &Month, &Day) != 3)
                    {
                        throw std::invalid_argument("Please specify a date with correct format.");
                    }
                }
            }

            uint32_t LicenseCount;
            if (_stscanf_s(argv[argc - 2].c_str(), TEXT("%u"), &LicenseCount) != 1)
            {
                throw std::invalid_argument("Please specify a valid license count.");
            }

            std::xstring Username = argv[argc - 3];

            if (argc ==3)
            {
                auto Info = VisualAssistKeygen<VisualAssistCryptoConfig, 0>::GenerateRegisterInfo(
                    Username.explicit_string().c_str(),
                    LicenseCount,
                    Year,
                    Month,
                    Day
                );

                _tprintf_s(TEXT("%hs\n"), Info.KeyName.c_str());
                _tprintf_s(TEXT("%hs\n"), Info.KeyCode.c_str());

            }
            else if (argc == 4 && _tcsicmp(argv[0].c_str(), TEXT("-renew")) == 0)
            {
                auto Info = VisualAssistKeygen<VisualAssistCryptoConfig, 1>::GenerateRegisterInfo(
                    Username.explicit_string().c_str(),
                    LicenseCount,
                    Year,
                    Month,
                    Day
                );

                _tprintf_s(TEXT("%hs\n"), Info.KeyName.c_str());
                _tprintf_s(TEXT("%hs\n"), Info.KeyCode.c_str());
                //system("pause");
                Sleep(10);
            }
            else
            {
                Help();
            }
        }
        catch (std::exception& e)
        {
            _tprintf_s(TEXT("Internal Error: %hs\n"), e.what());
        }
	}
    else
    {
        Help();
    }
    fclose(m_new_stdout_file);
}
