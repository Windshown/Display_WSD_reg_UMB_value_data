#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <windows.h>
#include <tchar.h>

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

#define REG_SOFTWARE_MS         TEXT("SOFTWARE\\Microsoft")
//#define REG_PATH_WSD_DEVICE_UMB TEXT("SYSTEM\\CurrentControlSet\\Enum\\Device Parameters\\IPBusEnumRoot\\UMB")
#define REG_PATH_WSD_DEVICE_UMB TEXT("SYSTEM\\CurrentControlSet\\Enum\\IPBusEnumRoot\\UMB")
#define REG_SOFTWARE_7ZIP       TEXT("SOFTWARE\\7-Zip\\Compression")

void QueryKey_All_WSD_Subkey_List(HKEY hKey);
void QueryValue_Single_WSD_Value_List(HKEY hKey);

#if 1
int main()
{
   HKEY hTestKey;

   if( RegOpenKeyEx( HKEY_LOCAL_MACHINE,
        REG_PATH_WSD_DEVICE_UMB,
        0,
        KEY_READ,
        &hTestKey) == ERROR_SUCCESS
      )
   {
      QueryKey_All_WSD_Subkey_List(hTestKey);
   }

   RegCloseKey(hTestKey);

   system("pause");

   return 0;
}
#endif

void QueryKey_All_WSD_Subkey_List(HKEY hKey)
{
    TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
    DWORD    cbName;                   // size of name string
    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name
    DWORD    cchClassName = MAX_PATH;  // size of class string
    DWORD    cSubKeys=0;               // number of subkeys
    DWORD    cbMaxSubKey;              // longest subkey size
    DWORD    cchMaxClass;              // longest class string
    DWORD    cValues;              // number of values for key
    DWORD    cchMaxValue;          // longest value name
    DWORD    cbMaxValueData;       // longest value data
    DWORD    cbSecurityDescriptor; // size of security descriptor
    FILETIME ftLastWriteTime;      // last write time

    DWORD i, retCode;

    TCHAR  /*achValue[MAX_VALUE_NAME],*/ achValue_single_WSD[MAX_VALUE_NAME];
    //DWORD cchValue = MAX_VALUE_NAME;

    //BYTE  achValue_content[MAX_VALUE_NAME];
    //DWORD  achValue_content;
    //DWORD  dwType, dwSize = MAX_KEY_LENGTH;
    HKEY hKey_WSD_Subkey_List;

    // Get the class name and the value count.
    retCode = RegQueryInfoKey(
        hKey,                    // key handle
        achClass,                // buffer for class name
        &cchClassName,           // size of class string
        NULL,                    // reserved
        &cSubKeys,               // number of subkeys
        &cbMaxSubKey,            // longest subkey size
        &cchMaxClass,            // longest class string
        &cValues,                // number of values for this key
        &cchMaxValue,            // longest value name
        &cbMaxValueData,         // longest value data
        &cbSecurityDescriptor,   // security descriptor
        &ftLastWriteTime);       // last write time

    // Enumerate the subkeys, until RegEnumKeyEx fails.

    if (cSubKeys)
    {
        printf( "\nNumber of subkeys: %d\n", (int)cSubKeys);

        for (i=0; i<cSubKeys; i++)
        {
            cbName = MAX_KEY_LENGTH;
            retCode = RegEnumKeyEx(hKey, i,
                     achKey,
                     &cbName,
                     NULL,
                     NULL,
                     NULL,
                     &ftLastWriteTime);

            //Get single key string
            _tcscpy(achValue_single_WSD, REG_PATH_WSD_DEVICE_UMB);
            _tcscat(achValue_single_WSD, TEXT("\\"));
            _tcscat(achValue_single_WSD, achKey);

            if (retCode == ERROR_SUCCESS)
            {
                _tprintf(TEXT("(%d) %s\n"), (int)(i+1), achKey);

                if ( RegOpenKeyEx( HKEY_LOCAL_MACHINE,
                    achValue_single_WSD,
                    0,
                    KEY_READ,
                    &hKey_WSD_Subkey_List) == ERROR_SUCCESS
                    )
                {
                    QueryValue_Single_WSD_Value_List(hKey_WSD_Subkey_List);
                }
            }
        }
    }

#if 0
    // Enumerate the key values.

    if (cValues)
    {
        printf( "\nNumber of values: %d\n", (int)cValues);

        for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++)
        {
            cchValue = MAX_VALUE_NAME;
            achValue[0] = '\0';
            retCode = RegEnumValue(hKey, i,
                achValue,
                &cchValue,
                NULL,
                NULL,
                NULL,
                NULL);

            if (retCode == ERROR_SUCCESS )
            {
                _tprintf(TEXT("(%d) %s\n"), (int)(i+1), achValue);

                retCode = RegQueryValueEx(hKey, achValue, NULL, &dwType, achValue_content, &dwSize);

                if (dwType == REG_DWORD)
                {
                    //itoa((int)achValue_content, achValue_content, 16);
                    _tprintf(TEXT("The content of value is %s\n"), achValue_content);
                }
                //else if (dwType == REG_SZ)
                //    _tprintf(TEXT("The content of value is %s\n"), achValue_content);
                else
                    _tprintf(TEXT("The content of value is %s\n"), achValue_content);
            }
        }
    }
#endif
}

void QueryValue_Single_WSD_Value_List(HKEY hKey)
{
    //TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
    //DWORD    cbName;                   // size of name string
    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name
    DWORD    cchClassName = MAX_PATH;  // size of class string
    DWORD    cSubKeys=0;               // number of subkeys
    DWORD    cbMaxSubKey;              // longest subkey size
    DWORD    cchMaxClass;              // longest class string
    DWORD    cValues;              // number of values for key
    DWORD    cchMaxValue;          // longest value name
    DWORD    cbMaxValueData;       // longest value data
    DWORD    cbSecurityDescriptor; // size of security descriptor
    FILETIME ftLastWriteTime;      // last write time

    DWORD i, retCode;

    TCHAR  achValue[MAX_VALUE_NAME];//, achValue_single_WSD[MAX_VALUE_NAME];
    DWORD cchValue = MAX_VALUE_NAME;

    TCHAR  achValue_content[MAX_KEY_LENGTH];
    //DWORD  achValue_content;
    DWORD  dwType, dwSize = MAX_KEY_LENGTH;
    //HKEY hKey_WSD_Subkey_List;

    // Get the class name and the value count.
    retCode = RegQueryInfoKey(
        hKey,                    // key handle
        achClass,                // buffer for class name
        &cchClassName,           // size of class string
        NULL,                    // reserved
        &cSubKeys,               // number of subkeys
        &cbMaxSubKey,            // longest subkey size
        &cchMaxClass,            // longest class string
        &cValues,                // number of values for this key
        &cchMaxValue,            // longest value name
        &cbMaxValueData,         // longest value data
        &cbSecurityDescriptor,   // security descriptor
        &ftLastWriteTime);       // last write time

    // Enumerate the key values.

    if (cValues)
    {
        printf( "\nNumber of values: %d\n", (int)cValues);

        for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++)
        {
            cchValue = MAX_VALUE_NAME;
            achValue[0] = '\0';
            retCode = RegEnumValue(hKey, i,
                achValue,
                &cchValue,
                NULL,
                NULL,
                NULL,
                NULL);

            if (retCode == ERROR_SUCCESS )
            {
                _tprintf(TEXT("(%d) %s\n"), (int)(i+1), achValue);

                //reset the cb buffer size to default
                dwSize = MAX_KEY_LENGTH;

                retCode = RegQueryValueEx(hKey, achValue, NULL, &dwType, (LPBYTE)achValue_content, &dwSize);

                if (dwType == REG_DWORD)
                {
                    //itoa((int)achValue_content, achValue_content, 16);
                    _tprintf(TEXT("The content of value is %s\n"), achValue_content);
                }
                //else if (dwType == REG_SZ)
                //    _tprintf(TEXT("The content of value is %s\n"), achValue_content);
                else
                {
                    _tprintf(TEXT("The content of value is %s\n"), achValue_content);
                }
            }
        }
    }
}




