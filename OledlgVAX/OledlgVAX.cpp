// OledlgVAX.cpp : 定义 DLL 应用程序的导出函数。
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
#pragma comment(linker,"/EXPORT:__CxxFrameHandler4=vcruntime140_1r.__CxxFrameHandler4")
#pragma comment(linker,"/EXPORT:__NLG_Dispatch2=vcruntime140_1r.__NLG_Dispatch2")
#pragma comment(linker,"/EXPORT:__NLG_Return2=vcruntime140_1r.__NLG_Return2")
#else
#pragma comment(linker,"/EXPORT:OleUIAddVerbMenuA=Oledlg_r.OleUIAddVerbMenuA")
#pragma comment(linker,"/EXPORT:OleUICanConvertOrActivateAs=Oledlg_r.OleUICanConvertOrActivateAs")
#pragma comment(linker,"/EXPORT:OleUIInsertObjectA=Oledlg_r.OleUIInsertObjectA")
#pragma comment(linker,"/EXPORT:OleUIPasteSpecialA=Oledlg_r.OleUIPasteSpecialA")
#pragma comment(linker,"/EXPORT:OleUIEditLinksA=Oledlg_r.OleUIEditLinksA")
#pragma comment(linker,"/EXPORT:OleUIChangeIconA=Oledlg_r.OleUIChangeIconA")
#pragma comment(linker,"/EXPORT:OleUIConvertA=Oledlg_r.OleUIConvertA")
#pragma comment(linker,"/EXPORT:OleUIBusyA=Oledlg_r.OleUIBusyA")
#pragma comment(linker,"/EXPORT:OleUIUpdateLinksA=Oledlg_r.OleUIUpdateLinksA")
#pragma comment(linker,"/EXPORT:OleUIPromptUserA=Oledlg_r.OleUIPromptUserA")
#pragma comment(linker,"/EXPORT:OleUIObjectPropertiesA=Oledlg_r.OleUIObjectPropertiesA")
#pragma comment(linker,"/EXPORT:OleUIChangeSourceA=Oledlg_r.OleUIChangeSourceA")
#pragma comment(linker,"/EXPORT:OleUIAddVerbMenuW=Oledlg_r.OleUIAddVerbMenuW")
#pragma comment(linker,"/EXPORT:OleUIBusyW=Oledlg_r.OleUIBusyW")
#pragma comment(linker,"/EXPORT:OleUIChangeIconW=Oledlg_r.OleUIChangeIconW")
#pragma comment(linker,"/EXPORT:OleUIChangeSourceW=Oledlg_r.OleUIChangeSourceW")
#pragma comment(linker,"/EXPORT:OleUIConvertW=Oledlg_r.OleUIConvertW")
#pragma comment(linker,"/EXPORT:OleUIEditLinksW=Oledlg_r.OleUIEditLinksW")
#pragma comment(linker,"/EXPORT:OleUIInsertObjectW=Oledlg_r.OleUIInsertObjectW")
#pragma comment(linker,"/EXPORT:OleUIObjectPropertiesW=Oledlg_r.OleUIObjectPropertiesW")
#pragma comment(linker,"/EXPORT:OleUIPasteSpecialW=Oledlg_r.OleUIPasteSpecialW")
#pragma comment(linker,"/EXPORT:OleUIPromptUserW=Oledlg_r.OleUIPromptUserW")
#pragma comment(linker,"/EXPORT:OleUIUpdateLinksW=Oledlg_r.OleUIUpdateLinksW")
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
