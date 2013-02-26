#ifndef __PORT_VIEWER_H__
#define __PORT_VIEWER_H__


// �� Netstat -anb �������õ�ͬ

#include <Windows.h>
#include <Psapi.h>
#include <TlHelp32.h>
#include <Iprtrmib.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;


#pragma  comment(lib,"Psapi.lib")
#pragma  comment(lib,"Iphlpapi.Lib")
#pragma  comment(lib,"WS2_32.lib")



enum TcpOrUdp
{
	TcpType, 
	UdpType
};


typedef struct
{
	DWORD dwState;      //����״̬
	DWORD dwLocalAddr;  //���ص�ַ
	DWORD dwLocalPort;  //���ض˿�
	DWORD dwRemoteAddr; //Զ�̵�ַ
	DWORD dwRemotePort; //Զ�̶˿�
	DWORD dwProcessId;  //���̱�ʶ

}MIB_TCPEXROW,*PMIB_TCPEXROW;


typedef struct
{
	DWORD dwLocalAddr;  //���ص�ַ
	DWORD dwLocalPort;  //���ض˿�
	DWORD dwProcessId;  //���̱�ʶ

}MIB_UDPEXROW,*PMIB_UDPEXROW;


typedef struct
{
	DWORD dwState;      //����״̬
	DWORD dwLocalAddr;  //���ص�ַ
	DWORD dwLocalPort;  //���ض˿�
	DWORD dwRemoteAddr; //Զ�̵�ַ
	DWORD dwRemotePort; //Զ�̶˿�
	DWORD dwProcessId;  //���̱�ʶ
	DWORD Unknown;      //������ʶ

}MIB_TCPEXROW_VISTA,*PMIB_TCPEXROW_VISTA;


typedef struct
{
	DWORD dwNumEntries;
	MIB_TCPEXROW table[ANY_SIZE];

}MIB_TCPEXTABLE,*PMIB_TCPEXTABLE;


typedef struct
{
	DWORD dwNumEntries;
	MIB_TCPEXROW_VISTA table[ANY_SIZE];

}MIB_TCPEXTABLE_VISTA,*PMIB_TCPEXTABLE_VISTA;


typedef struct
{
	DWORD dwNumEntries;
	MIB_UDPEXROW table[ANY_SIZE];

}MIB_UDPEXTABLE,*PMIB_UDPEXTABLE;


/* �ú�������ֻ�� Windows XP��Windows Server 2003 ����Ч */
typedef DWORD (WINAPI *PFNAllocateAndGetTcpExTableFromStack)(
	PMIB_TCPEXTABLE *pTcpTabel,
	bool bOrder,
	HANDLE heap,
	DWORD zero,
	DWORD flags
	);

/* �ú�������ֻ�� XP��Windows Server 2003 ����Ч */
typedef DWORD (WINAPI *PFNAllocateAndGetUdpExTableFromStack)(
	PMIB_UDPEXTABLE *pUdpTable,
	bool bOrder,
	HANDLE heap,
	DWORD zero,
	DWORD flags
	);

/* �ú����� Windows Vista �Լ� Windows 7 ����Ч */
typedef DWORD (WINAPI *PFNInternalGetTcpTable2)(
	PMIB_TCPEXTABLE_VISTA *pTcpTable_Vista,
	HANDLE heap,
	DWORD flags
	);

/* �ú����� Windows Vista �Լ� Windows 7 ����Ч */
typedef DWORD (WINAPI *PFNInternalGetUdpTableWithOwnerPid)(
	PMIB_UDPEXTABLE *pUdpTable,
	HANDLE heap,
	DWORD flags
	);


#endif	// end of __PORT_VIEWER_H__