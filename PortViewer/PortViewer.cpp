#include "PortViewer.h"


/************************************************************************/
/* ���ݶ˿ں�����򿪸ö˿ںŵĽ��� ID(֧�� XP��Server 2003��Vista��Win7)
/************************************************************************/
DWORD GetProcessIdByPort(TcpOrUdp type, DWORD dwPort)
{
	HMODULE hModule = LoadLibraryW(L"iphlpapi.dll");
	if (hModule == NULL)
	{
		return 0;
	}

	if(type == TcpType)
	{
		// ������ѯ���� TCP ��Ϣ
		PFNAllocateAndGetTcpExTableFromStack pAllocateAndGetTcpExTableFromStack;
		pAllocateAndGetTcpExTableFromStack = 
			(PFNAllocateAndGetTcpExTableFromStack)GetProcAddress(hModule, "AllocateAndGetTcpExTableFromStack");
		if (pAllocateAndGetTcpExTableFromStack != NULL)
		{
			// ����Ϊ XP ���� Server 2003 ����ϵͳ
			PMIB_TCPEXTABLE pTcpExTable = NULL;
			if (pAllocateAndGetTcpExTableFromStack(&pTcpExTable, TRUE, GetProcessHeap(), 0, AF_INET) != 0)
			{
				if (pTcpExTable)
				{
					HeapFree(GetProcessHeap(), 0, pTcpExTable);
				}

				FreeLibrary(hModule);
				hModule = NULL;

				return 0;
			}

			for (UINT i = 0; i < pTcpExTable->dwNumEntries; i++)
			{
				// ���˵����ݣ�ֻ��ѯ������Ҫ�Ľ�������
				if(dwPort == ntohs(0x0000FFFF & pTcpExTable->table[i].dwLocalPort))
				{
					DWORD dwProcessId = pTcpExTable->table[i].dwProcessId;
					if (pTcpExTable)
					{
						HeapFree(GetProcessHeap(), 0, pTcpExTable);
					}

					FreeLibrary(hModule);
					hModule = NULL;

					return dwProcessId;
				}
			}

			if (pTcpExTable)
			{
				HeapFree(GetProcessHeap(), 0, pTcpExTable);
			}

			FreeLibrary(hModule);
			hModule = NULL;

			return 0;
		}
		else
		{
			// ����Ϊ Vista ���� 7 ����ϵͳ
			PMIB_TCPEXTABLE_VISTA pTcpExTable = NULL;
			PFNInternalGetTcpTable2 pInternalGetTcpTable2 = 
				(PFNInternalGetTcpTable2)GetProcAddress(hModule, "InternalGetTcpTable2");
			if (pInternalGetTcpTable2 == NULL)
			{
				if (pTcpExTable)
				{
					HeapFree(GetProcessHeap(), 0, pTcpExTable);
				}

				FreeLibrary(hModule);
				hModule = NULL;

				return 0;
			}

			if (pInternalGetTcpTable2(&pTcpExTable, GetProcessHeap(), 1))
			{
				if (pTcpExTable)
				{
					HeapFree(GetProcessHeap(), 0, pTcpExTable);
				}

				FreeLibrary(hModule);
				hModule = NULL;

				return 0;
			}

			for (UINT i = 0;i < pTcpExTable->dwNumEntries; i++)
			{
				// ���˵����ݣ�ֻ��ѯ������Ҫ�Ľ�������
				if(dwPort == ntohs(0x0000FFFF & pTcpExTable->table[i].dwLocalPort))
				{
					DWORD dwProcessId = pTcpExTable->table[i].dwProcessId;
					if (pTcpExTable)
					{
						HeapFree(GetProcessHeap(), 0, pTcpExTable);
					}

					FreeLibrary(hModule);
					hModule = NULL;

					return dwProcessId;
				}
			}

			if (pTcpExTable)
			{
				HeapFree(GetProcessHeap(), 0, pTcpExTable);
			}

			FreeLibrary(hModule);
			hModule = NULL;

			return 0;
		}
	}
	else if(type == UdpType)
	{
		// ������ѯ���� UDP ��Ϣ
		PMIB_UDPEXTABLE pUdpExTable = NULL;
		PFNAllocateAndGetUdpExTableFromStack pAllocateAndGetUdpExTableFromStack;
		pAllocateAndGetUdpExTableFromStack = 
			(PFNAllocateAndGetUdpExTableFromStack)GetProcAddress(hModule,"AllocateAndGetUdpExTableFromStack");
		if (pAllocateAndGetUdpExTableFromStack != NULL)
		{
			// ����Ϊ XP ���� Server 2003 ����ϵͳ
			if (pAllocateAndGetUdpExTableFromStack(&pUdpExTable, TRUE, GetProcessHeap(), 0, AF_INET) != 0)
			{
				if (pUdpExTable)
				{
					HeapFree(GetProcessHeap(), 0, pUdpExTable);
				}

				FreeLibrary(hModule);
				hModule = NULL;

				return 0;
			}

			for (UINT i = 0; i < pUdpExTable->dwNumEntries; i++)
			{
				// ���˵����ݣ�ֻ��ѯ������Ҫ�Ľ�������
				if (dwPort == ntohs(0x0000FFFF & pUdpExTable->table[i].dwLocalPort))
				{
					DWORD dwProcessId = pUdpExTable->table[i].dwProcessId;
					if (pUdpExTable)
					{
						HeapFree(GetProcessHeap(), 0, pUdpExTable);
					}

					FreeLibrary(hModule);
					hModule = NULL;

					return dwProcessId;
				}
			}

			if (pUdpExTable)
			{
				HeapFree(GetProcessHeap(), 0, pUdpExTable);
			}

			FreeLibrary(hModule);
			hModule = NULL;

			return 0;
		}
		else
		{
			// ����Ϊ Vista ���� 7 ����ϵͳ
			PFNInternalGetUdpTableWithOwnerPid pInternalGetUdpTableWithOwnerPid;
			pInternalGetUdpTableWithOwnerPid = 
				(PFNInternalGetUdpTableWithOwnerPid)GetProcAddress(hModule, "InternalGetUdpTableWithOwnerPid");
			if (pInternalGetUdpTableWithOwnerPid != NULL)
			{
				if (pInternalGetUdpTableWithOwnerPid(&pUdpExTable, GetProcessHeap(), 1))
				{
					if (pUdpExTable)
					{
						HeapFree(GetProcessHeap(), 0, pUdpExTable);
					}

					FreeLibrary(hModule);
					hModule = NULL;

					return 0;
				}

				for (UINT i = 0; i < pUdpExTable->dwNumEntries; i++)
				{
					// ���˵����ݣ�ֻ��ѯ������Ҫ�Ľ�������
					if (dwPort == ntohs(0x0000FFFF & pUdpExTable->table[i].dwLocalPort))
					{
						DWORD dwProcessId = pUdpExTable->table[i].dwProcessId;
						if (pUdpExTable)
						{
							HeapFree(GetProcessHeap(), 0, pUdpExTable);
						}

						FreeLibrary(hModule);
						hModule = NULL;

						return dwProcessId;
					}
				}
			}

			if (pUdpExTable)
			{
				HeapFree(GetProcessHeap(), 0, pUdpExTable);
			}

			FreeLibrary(hModule);
			hModule = NULL;

			return 0;
		}
	}
	else
	{
		FreeLibrary(hModule);
		hModule = NULL;

		return -1;
	}
}


/************************************************************************/
/* ���ݽ��� ID ������ý������򿪵����еĶ˿ںţ������� dwAllPort �����з������ж˿ں�
/* ���� dwMaxLen Ϊ����ĳ��ȣ������ķ���ֵΪ�������򿪵Ķ˿ڵ���Ŀ
/* (֧�� XP��Server 2003��Vista��Win7)
/************************************************************************/
DWORD GetAllPortByProcessId(TcpOrUdp type, DWORD dwProcessId, DWORD * dwAllPort, DWORD dwMaxLen)
{
	DWORD dwPortCount = 0;
	HMODULE hModule = LoadLibraryW(L"iphlpapi.dll");
	if (hModule == NULL)
	{
		return dwPortCount;
	}

	if(type == TcpType)
	{
		// ������ѯ���� UDP ��Ϣ
		PFNAllocateAndGetTcpExTableFromStack pAllocateAndGetTcpExTableFromStack;
		pAllocateAndGetTcpExTableFromStack = (PFNAllocateAndGetTcpExTableFromStack)GetProcAddress(hModule, "AllocateAndGetTcpExTableFromStack");
		if (pAllocateAndGetTcpExTableFromStack != NULL)
		{
			// ����Ϊ XP ���� Server 2003 ����ϵͳ
			PMIB_TCPEXTABLE pTcpExTable = NULL;
			if (pAllocateAndGetTcpExTableFromStack(&pTcpExTable, TRUE, GetProcessHeap(), 0, AF_INET) != 0)
			{
				if (pTcpExTable)
				{
					HeapFree(GetProcessHeap(), 0, pTcpExTable);
				}

				FreeLibrary(hModule);
				hModule = NULL;

				return dwPortCount;
			}

			for (UINT i = 0; i < pTcpExTable->dwNumEntries; i++)
			{
				// ���˵����ݣ�ֻ��ȡ����Ҫ��ѯ�Ľ��̵� Port ��Ϣ
				if(dwProcessId == pTcpExTable->table[i].dwProcessId)
				{
					if(dwPortCount < dwMaxLen)
					{
						dwAllPort[dwPortCount] = ntohs(0x0000FFFF & pTcpExTable->table[i].dwLocalPort);
						dwPortCount++;
					}
				}
			}

			if (pTcpExTable)
			{
				HeapFree(GetProcessHeap(), 0, pTcpExTable);
			}

			FreeLibrary(hModule);
			hModule = NULL;

			return dwPortCount;
		}
		else
		{
			// ����Ϊ Vista ���� 7 ����ϵͳ
			PMIB_TCPEXTABLE_VISTA pTcpExTable = NULL;
			PFNInternalGetTcpTable2 pInternalGetTcpTable2 = (PFNInternalGetTcpTable2)GetProcAddress(hModule, "InternalGetTcpTable2");
			if (pInternalGetTcpTable2 == NULL)
			{
				if (pTcpExTable)
				{
					HeapFree(GetProcessHeap(), 0, pTcpExTable);
				}

				FreeLibrary(hModule);
				hModule = NULL;

				return dwPortCount;
			}

			if (pInternalGetTcpTable2(&pTcpExTable, GetProcessHeap(), 1))
			{
				if (pTcpExTable)
				{
					HeapFree(GetProcessHeap(), 0, pTcpExTable);
				}

				FreeLibrary(hModule);
				hModule = NULL;

				return dwPortCount;
			}

			for (UINT i = 0;i < pTcpExTable->dwNumEntries; i++)
			{
				// ���˵����ݣ�ֻ��ȡ����Ҫ��ѯ�Ľ��̵� TCP Port ��Ϣ
				if(dwProcessId == pTcpExTable->table[i].dwProcessId)
				{
					if(dwPortCount < dwMaxLen)
					{
						dwAllPort[dwPortCount] = ntohs(0x0000FFFF & pTcpExTable->table[i].dwLocalPort);
						dwPortCount++;
					}
				}
			}

			if (pTcpExTable)
			{
				HeapFree(GetProcessHeap(), 0, pTcpExTable);
			}

			FreeLibrary(hModule);
			hModule = NULL;

			return dwPortCount;
		}
	}
	else if(type == UdpType)
	{
		// ������ѯ���� UDP ��Ϣ
		PMIB_UDPEXTABLE pUdpExTable = NULL;
		PFNAllocateAndGetUdpExTableFromStack pAllocateAndGetUdpExTableFromStack;
		pAllocateAndGetUdpExTableFromStack = (PFNAllocateAndGetUdpExTableFromStack)GetProcAddress(hModule,"AllocateAndGetUdpExTableFromStack");
		if (pAllocateAndGetUdpExTableFromStack != NULL)
		{
			// ����Ϊ XP ���� Server 2003 ����ϵͳ
			if (pAllocateAndGetUdpExTableFromStack(&pUdpExTable, TRUE, GetProcessHeap(), 0, AF_INET) != 0)
			{
				if (pUdpExTable)
				{
					HeapFree(GetProcessHeap(), 0, pUdpExTable);
				}

				FreeLibrary(hModule);
				hModule = NULL;

				return dwPortCount;
			}

			for (UINT i = 0; i < pUdpExTable->dwNumEntries; i++)
			{
				// ���˵����ݣ�ֻ��ȡ����Ҫ��ѯ�Ľ��̵� UDP Port��Ϣ
				if(dwProcessId == pUdpExTable->table[i].dwProcessId)
				{
					if(dwPortCount < dwMaxLen)
					{
						dwAllPort[dwPortCount] = ntohs(0x0000FFFF & pUdpExTable->table[i].dwLocalPort);
						dwPortCount++;
					}
				}
			}

			if (pUdpExTable)
			{
				HeapFree(GetProcessHeap(), 0, pUdpExTable);
			}

			FreeLibrary(hModule);
			hModule = NULL;

			return dwPortCount;
		}
		else
		{
			// ����Ϊ Vista ���� 7 ����ϵͳ
			PFNInternalGetUdpTableWithOwnerPid pInternalGetUdpTableWithOwnerPid;
			pInternalGetUdpTableWithOwnerPid = (PFNInternalGetUdpTableWithOwnerPid)GetProcAddress(hModule, "InternalGetUdpTableWithOwnerPid");
			if (pInternalGetUdpTableWithOwnerPid != NULL)
			{
				if (pInternalGetUdpTableWithOwnerPid(&pUdpExTable, GetProcessHeap(), 1))
				{
					if (pUdpExTable)
					{
						HeapFree(GetProcessHeap(), 0, pUdpExTable);
					}

					FreeLibrary(hModule);
					hModule = NULL;

					return dwPortCount;
				}

				for (UINT i = 0; i < pUdpExTable->dwNumEntries; i++)
				{
					// ���˵����ݣ�ֻ��ȡ����Ҫ��ѯ�Ľ��̵� UDP Port��Ϣ
					if(dwProcessId == pUdpExTable->table[i].dwProcessId)
					{
						if(dwPortCount < dwMaxLen)
						{
							dwAllPort[dwPortCount] = ntohs(0x0000FFFF & pUdpExTable->table[i].dwLocalPort);
							dwPortCount++;
						}
					}
				}
			}

			if (pUdpExTable)
			{
				HeapFree(GetProcessHeap(), 0, pUdpExTable);
			}

			FreeLibrary(hModule);
			hModule = NULL;

			return dwPortCount;
		}
	}
	else
	{
		FreeLibrary(hModule);
		hModule = NULL;

		return dwPortCount;
	}
}


/************************************************************************/
/* �� IP ��ַת��Ϊ ULOGN ����
/************************************************************************/
ULONG IPAddress2ULONG(string strIPAddress)
{
	u_short a;
	u_short b;
	u_short c;
	u_short d;

	sscanf(strIPAddress.c_str(), "%hu.%hu.%hu.%hu", &a, &b, &c, &d );

	return (a << 24) | (b << 16) | (c << 8) | (d);
}


/************************************************************************/
/* �� ULONG ����ת��Ϊ IP ��ַ
/************************************************************************/
string ULONG2IPAddress(ULONG uIPAddress)
{
	u_short a, b, c, d;

	PCHAR cStrIPAddress[MAX_PATH];
	memset(cStrIPAddress, 0, sizeof(PCHAR) * MAX_PATH);

	a = (uIPAddress & (0xff << 24)) >> 24;
	b = (uIPAddress & (0xff << 16)) >> 16;
	c = (uIPAddress & (0xff << 8)) >> 8;
	d = uIPAddress & 0xff;

	sprintf((PCHAR)cStrIPAddress, "%hu.%hu.%hu.%hu", a, b, c, d);

	string strReturn((PCHAR)cStrIPAddress);

	return strReturn;
}


/************************************************************************/
/* ͨ�� PID ��ȡ��������
/************************************************************************/
BOOL GetProcessNameByPID(LPWSTR lpszProcessName, DWORD dwPID, DWORD dwMaxLen)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 
	PROCESSENTRY32W pe; 

	pe.dwSize = sizeof(PROCESSENTRY32W); 
	if (!Process32FirstW(hSnapshot, &pe)) 
	{ 
		CloseHandle(hSnapshot);

		return FALSE; 
	}

	while (Process32NextW(hSnapshot, &pe)) 
	{ 
		if (pe.th32ProcessID == dwPID)
		{ 
			DWORD dwExeNameLen = wcslen(pe.szExeFile);
			if(dwExeNameLen < dwMaxLen)
			{
				memcpy(lpszProcessName, pe.szExeFile, dwExeNameLen * sizeof(WCHAR));
			}
			break;
		} 
	}

	CloseHandle(hSnapshot);

	return FALSE;
}


int main()
{
	DWORD dwAllPort[50];
	DWORD dwMaxLen = 50;

	DWORD dwPort;
	DWORD dwProcessId;

	DWORD dwResult = 0;

	DWORD dwInput = 0;
	while(dwInput != 5)
	{
		cout<<"Input 1: Query TCP Port By Process ID;"<<endl;
		cout<<"Input 2: Query UDP Port By Process ID;"<<endl;
		cout<<"Input 3: Query Process ID By TCP Port;"<<endl;
		cout<<"Input 4: Query Process ID By UDP Port;"<<endl;
		cout<<"Input 5: Exit Application;"<<endl<<endl;
		cout<<"Please Input Your Select Option:   ";
		cin>>dwInput;
		system("cls");

		memset(dwAllPort, 0, sizeof(DWORD) * dwMaxLen);

		switch(dwInput)
		{
		case 1:
			{
				cout<<"Please Input The Process ID:  ";
				cin>>dwProcessId;
				dwResult = GetAllPortByProcessId(TcpType, dwProcessId, dwAllPort, dwMaxLen);
				cout<<endl<<"=========Query TCP Port By Process ID Result : ========="<<endl;
				for(int i=0;i<dwResult;i++)
				{
					cout<<"�� "<<i + 1<<" ��:  "<<dwAllPort[i]<<endl;
				}
				cout<<"========================================================"<<endl<<endl<<endl;
				break;
			}
		case 2:
			{
				cout<<"Please Input The Process ID:  ";
				cin>>dwProcessId;
				dwResult = GetAllPortByProcessId(UdpType, dwProcessId, dwAllPort, dwMaxLen);
				cout<<endl<<"=========Query UDP Port By Process ID Result : ========="<<endl;
				for(int i=0;i<dwResult;i++)
				{
					cout<<"�� "<<i + 1<<" ��:  "<<dwAllPort[i]<<endl;
				}
				cout<<"========================================================"<<endl<<endl<<endl;
				break;
			}
		case 3:
			{
				cout<<"Please Input The Port:  ";
				cin>>dwPort;
				dwResult = GetProcessIdByPort(TcpType, dwPort);
				cout<<endl<<"=========Query Process ID By TCP Port Result : ========="<<endl;
				cout<<"���Ϊ:  "<<dwResult<<endl;
				cout<<"========================================================"<<endl<<endl<<endl;
				break;
			}
		case 4:
			{
				cout<<"Please Input The Port:  ";
				cin>>dwPort;
				dwResult = GetProcessIdByPort(UdpType, dwPort);
				cout<<endl<<"=========Query Process ID By UDP Port Result : ========="<<endl;
				cout<<"���Ϊ:  "<<dwResult<<endl;
				cout<<"========================================================"<<endl<<endl<<endl;
				break;
			}
		case 5:
			{
				return 0;
			}
		default:
			{
				break;
			}
		}
	}

	return 0;
}
