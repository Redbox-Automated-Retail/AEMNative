#include "main.h"

HANDLE g_hMutex = nullptr;
void* g_loggingService = nullptr;
bool g_isConnected = false; // temp

void DummyLog(const char* format, ...)
{
    char buffer[2048];
    va_list args;
    va_start(args, format);
	vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, format, args);

    OutputDebugStringA(buffer);
    OutputDebugStringA("\n");
}


static const char* GetResultString(int result)
{
	std::string output;

    switch (result)
    {
	    case DPEC_RESULT_SUCCESS:
            output = "Success";
			break;
        case DPEC_RESULT_FAILED:
			output = "Failed";
            break;
	    case DPEC_RESULT_ABORTED:
			output = "Aborted";
	        break;
	    case DPEC_RESULT_UNKNOWN:
			output = "Unknown";
	        break;
	    case DPEC_RESULT_TIMEOUT:
	        output = "Timeout";
	        break;
	    case DPEC_RESULT_NO_CONNECT:
	        output = "NoConnect";
	        break;
	    case DPEC_RESULT_CONNECTED:
	        output = "Connected";
	        break;
	    case DPEC_RESULT_NO_RESOURCE:
	        output = "NoResource";
	        break;
	    case DPEC_RESULT_CANT_COMPLETE:
	        output = "CantComplete";
	        break;
	    case DPEC_RESULT_SRC_EMPTY:
	        output = "SrcEmpty";
	        break;
	    case DPEC_RESULT_DST_OCCUPIED:
	        output = "DstOccupied";
	        break;
	    case DPEC_RESULT_SLOT_EMPTY:
	        output = "SlotEmpty";
	        break;
	    case DPEC_RESULT_SLOT_FULL:
	        output = "SlotFull";
	        break;
	    case DPEC_RESULT_BAD_VALUE:
	        output = "BadValue";
	        break;
	    case DPEC_RESULT_INVALID_SLOT:
	        output = "InvalidSlot";
	        break;
	    case DPEC_RESULT_INVALID_OP:
	        output = "InvalidOp";
	        break;
	    case DPEC_RESULT_WRONG_MODE:
	        output = "WrongMode";
	        break;
	    case DPEC_RESULT_WRONG_STATE:
	        output = "WrongState";
	        break;
	    case DPEC_RESULT_WRONG_MODEL:
	        output = "WrongModel";
	        break;
	    case DPEC_RESULT_CASE_REJECTED:
	        output = "CaseRejected";
	        break;
	    case DPEC_RESULT_CASE_JAMMED:
	        output = "CaseJammed";
	        break;
	    case DPEC_RESULT_CASE_RESEATED:
	        output = "CaseReseated";
	        break;
	    case DPEC_RESULT_CASE_YANKED_OUT:
	        output = "CaseYankedOut";
	        break;
	    case DPEC_RESULT_CASE_SHOVED_IN:
	        output = "CaseShovedIn";
	        break;
	    default:
			output = "?";
			break;
    }
	return output.c_str();
}

static const char* GetModeString(int mode)
{
	std::string output;

	switch (mode)
	{
	case DPEC_MODE_UNKNOWN:
		output = "Unknown";
		break;
	case DPEC_MODE_TRANSITION:
		output = "Transition";
		break;
	case DPEC_MODE_OPERATIONAL:
		output = "Operational";
		break;
	case DPEC_MODE_DIAGNOSTIC:
		output = "Diagnostic";
		break;
	default:
		output = "?";
		break;
	}

	return output.c_str();
}

extern "C" int DPEC_AbortOperation(int id)
{
    int result = DPEC_RESULT_SUCCESS;

	// TODO: LogEnter
    DummyLog("DPEC_AbortOperation(ID=$%X)", id);

    // TODO: call op manager abort with id

	const char* resultStr = GetResultString(result);
	// TODO: LogExit
    DummyLog("DPEC_AbortOperation(ID=$%X) returning DPEC_Result %u (%s)", id, result, resultStr);

	return result;
}

extern "C" void DPEC_AddLineToLog(char* format)
{
	if (!format) return;
	if (!g_loggingService) return;

	// TODO: LogMsg
	DummyLog(format);
}

extern "C" int DPEC_Connect()
{
	int result;

	// TODO: LogEnter
	DummyLog("DPEC_Connect()");

	// TODO: get lock and connect

	if (!g_isConnected) // used to somewhat simulate the lock, if it fails to get a lock, it returns already connected
	{
		g_isConnected = true;
		result = DPEC_RESULT_SUCCESS;
	}
	else
	{
		result = DPEC_RESULT_CONNECTED;
	}

	const char* resultStr = GetResultString(result);
	// TODO: LogExit
	DummyLog("DPEC_Connect() returning DPEC_Result %u (%s)", result, resultStr);
	return result;
}

extern "C" int DPEC_Disconnect()
{
	int result;

	// TODO: LogEnter
	DummyLog("DPEC_Disconnect()");

	// TODO: acquire lock and disconnect

	if (g_isConnected) // simulate lock
	{
		g_isConnected = false;
		result = DPEC_RESULT_SUCCESS;
	}
	else
	{
		result = DPEC_RESULT_NO_CONNECT;
	}

	const char* resultStr = GetResultString(result);
	// TODO: LogExit
	DummyLog("DPEC_Disconnect() returning DPEC_Result %u (%s)", result, resultStr);
	return result;
}

extern "C" int DPEC_GetLibraryVersion(DPEC_VERSION* pVersion, char* pVersionString)
{
	char versionBuffer[80];

	// TODO: LogEnter
	DummyLog("DPEC_GetLibraryVersion(pVers=@%X,pVerStr=@%X)", pVersion, pVersionString);

	wsprintfA(versionBuffer, "DPEC_API.dll Version %u.%u Build %04u", 1, 1, 31);
	if (pVersion)
	{
		pVersion->major = 1;
		pVersion->minor = 1;
		pVersion->build = 31;
	}

	if (pVersionString)
	{
		strcpy(pVersionString, versionBuffer);
	}

	// TODO: LogExit
	DummyLog("DPEC_GetLibraryVersion(Vers={maj:%u,min:%u,bld:%04u},VerStr=\"%s\")", 1, 1, 31, versionBuffer);

	return DPEC_RESULT_SUCCESS;
}

extern "C" int DPEC_GetMode()
{
	int mode = DPEC_MODE_UNKNOWN;
	// TODO: LogEnter
	DummyLog("DPEC_GetMode()");

	// TODO: acquire lock and get mode from op manager?

	const char* modeStr = GetModeString(mode);
	// TODO: LogExit
	DummyLog("DPEC_GetMode() returning DPEC_Mode %u (%s)", mode, modeStr);

	return mode;
}

extern "C" int DPEC_GetOpState(int id, int* pState)
{
	int result = DPEC_RESULT_SUCCESS;
	int state = DPEC_STATE_UNKNOWN;
}

extern "C" int DPEC_StartLoggingService()
{
    if (g_loggingService)
    {
        // TODO: LogMsg
        DummyLog("DPEC_StartLoggingService() called, Logger already running!");
        return DPEC_RESULT_SUCCESS;
    }

    // TODO: create logging service class
	g_loggingService = (void*)1; // dummy non-null value

    // TODO: LogMsg
    DummyLog("DPEC_StartLoggingService() called, Logger started!");
    return DPEC_RESULT_SUCCESS;
}

extern "C" int DPEC_KillLoggingService()
{
    if (!g_loggingService)
    {
        DummyLog("DPEC_KillLoggingService() called, Logger already stopped!");
        return DPEC_RESULT_SUCCESS;
    }

	// TODO: LogMsg
	DummyLog("DPEC_KillLoggingService() called, stopping Logger!");
    Sleep(1);
	//if (g_loggingService)
        // TODO: call first function in vtable with arg 1
	g_loggingService = nullptr;
    return DPEC_RESULT_SUCCESS;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  dwReason,
                       LPVOID lpReserved
                     )
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
	    {
			g_hMutex = CreateMutexA(nullptr, FALSE, "DPEC-API-DLL-DllMain-Mutex");
            if (!g_hMutex) {
                return FALSE;
			}

            if (GetLastError() == ERROR_ALREADY_EXISTS)
            {
                CloseHandle(g_hMutex);
                g_hMutex = nullptr;
                return FALSE;
            }

            // Temp
            AllocConsole();
            freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
            freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);
            freopen_s((FILE**)stdin, "CONIN$", "r", stdin);

            break;
	    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

