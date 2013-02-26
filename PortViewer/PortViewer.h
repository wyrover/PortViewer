#ifndef __PORT_VIEWER_H__
#define __PORT_VIEWER_H__


// 与 Netstat -anb 命令作用等同

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
	DWORD dwState;      //连接状态
	DWORD dwLocalAddr;  //本地地址
	DWORD dwLocalPort;  //本地端口
	DWORD dwRemoteAddr; //远程地址
	DWORD dwRemotePort; //远程端口
	DWORD dwProcessId;  //进程标识

}MIB_TCPEXROW,*PMIB_TCPEXROW;


typedef struct
{
	DWORD dwLocalAddr;  //本地地址
	DWORD dwLocalPort;  //本地端口
	DWORD dwProcessId;  //进程标识

}MIB_UDPEXROW,*PMIB_UDPEXROW;


typedef struct
{
	DWORD dwState;      //连接状态
	DWORD dwLocalAddr;  //本地地址
	DWORD dwLocalPort;  //本地端口
	DWORD dwRemoteAddr; //远程地址
	DWORD dwRemotePort; //远程端口
	DWORD dwProcessId;  //进程标识
	DWORD Unknown;      //待定标识

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


/* 该函数仅仅只在 Windows XP，Windows Server 2003 下有效 */
typedef DWORD (WINAPI *PFNAllocateAndGetTcpExTableFromStack)(
	PMIB_TCPEXTABLE *pTcpTabel,
	bool bOrder,
	HANDLE heap,
	DWORD zero,
	DWORD flags
	);

/* 该函数仅仅只在 XP，Windows Server 2003 下有效 */
typedef DWORD (WINAPI *PFNAllocateAndGetUdpExTableFromStack)(
	PMIB_UDPEXTABLE *pUdpTable,
	bool bOrder,
	HANDLE heap,
	DWORD zero,
	DWORD flags
	);

/* 该函数在 Windows Vista 以及 Windows 7 下面效 */
typedef DWORD (WINAPI *PFNInternalGetTcpTable2)(
	PMIB_TCPEXTABLE_VISTA *pTcpTable_Vista,
	HANDLE heap,
	DWORD flags
	);

/* 该函数在 Windows Vista 以及 Windows 7 下面效 */
typedef DWORD (WINAPI *PFNInternalGetUdpTableWithOwnerPid)(
	PMIB_UDPEXTABLE *pUdpTable,
	HANDLE heap,
	DWORD flags
	);


#endif	// end of __PORT_VIEWER_H__