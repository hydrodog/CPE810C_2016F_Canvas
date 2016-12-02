//
// pch.cpp
// Include the standard header and generate the precompiled header.
//

#include "pch.h"
#include <string.h>
#include <iostream>
#include <WinSock2.h>
#include <windows.h>
#include <string.h>
#pragma  comment(lib, "ws2_32.lib")	
using namespace std;

const int MAXSIZE = 1024;

int srvPort = 25;
char srvDomain[256] = "smtp.gmail.com";
char userName[256] = "users@gmail.com"; //your email address
char password[256] = "password"; 
char targetEmail[256] = "it_is_just_a_test@gmail.com"; //recipient
char emailTitle[256] = "have fun"; //title of the mail
char content[256] = "oh,i made it";//content

SOCKET CreateConn(char* pWebsite, int port)
{
	//perpare for the socket
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);     //set up socket
	SOCKADDR_IN addrSrv;
	HOSTENT* pHostent;
	pHostent = gethostbyname(pWebsite);  //get the info of host

	addrSrv.sin_addr.S_un.S_addr = *((DWORD *)pHostent->h_addr_list[0]);	//get the ip address of smtp server   
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(port);
	int tf = connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));     
	if (tf != 0)
	{
		return 0;
		//printf("connection error\n");
	}
	return sockClient;
}


void SendAndRecvMsg(
	SOCKET sockClient,		
	char* pMessage,			//message needs to be sent
	int Messagelen,			//length of message
	int DoWhat,				//to determine what to do
	char* recvBuf,			//buffer of recv
	int recvBufLen			//length of recv
	)
{
	char lpMessage[256] = { 0 };
	memcpy(lpMessage, pMessage, Messagelen);
	printf("\n\n%s \n", lpMessage);
	if (DoWhat == 0)
	{
		send(sockClient, lpMessage, Messagelen, 0);
		memset(recvBuf, 0, recvBufLen);
		DWORD num = recv(sockClient, recvBuf, recvBufLen, 0);     //receive data
		printf("%s \n", recvBuf);
		int i = 0;
		while (i != num)
		{
			printf("%02X ", recvBuf[i++]);
			if ((i) % 16 == 0)
			{
				printf("\n");
			}
		}
		printf("\n");

	}
	else if (DoWhat == 1)
	{
		send(sockClient, lpMessage, Messagelen, 0);

	}
	else if (DoWhat == 2) //only receive data
	{
		memset(recvBuf, 0, recvBufLen);
		DWORD num = recv(sockClient, recvBuf, recvBufLen, 0);     //receive data
		cout << recvBuf << endl;
		int i = 0;
		while (i < num)
		{
			printf("%02X ", (byte)recvBuf[i++]);
			if ((i) % 16 == 0)
			{
				printf("\n");
			}
		}
		printf("\n");
	}

}

int GetStrLen(char* pString) //get the length 
{
	int i = 0;
	while (pString[i++] != 0);
	return i - 1;
}


void StringToBase64(const char *src, char *dst)
{/*it has to be base64 to login smtp.google.com*/
	int i = 0;
	char *p = dst;
	int d = strlen(src) - 3;
	static const char Base64[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	//for(i=0;i<strlen(src)-3;i+=3) ;if (strlen(src)-3)<0 there is a buf

	for (i = 0; i <= d; i += 3)
	{
		*p++ = Base64[((*(src + i)) >> 2) & 0x3f];
		*p++ = Base64[(((*(src + i)) & 0x3) << 4) + ((*(src + i + 1)) >> 4)];
		*p++ = Base64[((*(src + i + 1) & 0xf) << 2) + ((*(src + i + 2)) >> 6)];
		*p++ = Base64[(*(src + i + 2)) & 0x3f];
	}
	if ((strlen(src) - i) == 1)
	{
		*p++ = Base64[((*(src + i)) >> 2) & 0x3f];
		*p++ = Base64[((*(src + i)) & 0x3) << 4];
		*p++ = '=';
		*p++ = '=';
	}
	if ((strlen(src) - i) == 2)
	{
		*p++ = Base64[((*(src + i)) >> 2) & 0x3f];
		*p++ = Base64[(((*(src + i)) & 0x3) << 4) + ((*(src + i + 1)) >> 4)];
		*p++ = Base64[((*(src + i + 1) & 0xf) << 2)];
		*p++ = '=';
	}
	*p = '\0';
}


bool FormatEmail(char* pFrom, char* pTo, char* pSubject, char* pMessage, char* Email)
{/*formatting the content*/
	strcat(Email, "From: ");
	strcat(Email, pFrom);
	strcat(Email, "\r\n");

	strcat(Email, "To: ");
	strcat(Email, pTo);
	strcat(Email, "\r\n");

	strcat(Email, "Subject: ");
	strcat(Email, pSubject);
	strcat(Email, "\r\n");

	strcat(Email, "MIME-Version: 1.0");
	strcat(Email, "\r\n");
	strcat(Email, "\r\n");

	strcat(Email, pMessage);

	strcat(Email, "\r\n.\r\n");
	return TRUE;
}

void main()
{

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	SOCKET sockClient = CreateConn(srvDomain, srvPort); //google smtp,port 25

	char buff[MAXSIZE];
	memset(buff, 0, sizeof(char) * MAXSIZE);  //set all zero

	SendAndRecvMsg(sockClient, 0, 0, 2, buff, MAXSIZE); 

	char UserNameToSendEmail[256] = { 0 };
	sprintf(UserNameToSendEmail, "EHLO %s", "it_is_just_a_test@163.com");
	strcat(UserNameToSendEmail, "\r\n\0");
	SendAndRecvMsg(sockClient, UserNameToSendEmail, GetStrLen(UserNameToSendEmail), 0, buff, MAXSIZE); //receive and send

	SendAndRecvMsg(sockClient, "AUTH LOGIN\r\n", strlen("AUTH LOGIN\r\n"), 0, buff, MAXSIZE); //request to login
	char pUerName[256] = { 0 };
	

	DWORD p = strstr(userName, "@") - userName;
	memcpy(pUerName, userName, p); //get the user's name,like "users"from"users@gmail.com"
	char base[256];
	StringToBase64(pUerName, base); //turn it to base64

	char str[MAXSIZE];
	memset(str, 0, MAXSIZE);
	sprintf(str, "%s\r\n", base);
	SendAndRecvMsg(sockClient, str, strlen(str), 0, buff, MAXSIZE); //send the userName and receive the data from server

	StringToBase64(password, base);
	memset(str, 0, 1024);
	sprintf(str, "%s\r\n", base);
	SendAndRecvMsg(sockClient, str, strlen(str), 0, buff, MAXSIZE); //send the password and receive the data from server

	char MailFrom[256] = { 0 };
	sprintf(MailFrom, "MAIL FROM: <%s>\r\n", userName);

	SendAndRecvMsg(sockClient, MailFrom, strlen(MailFrom), 0, buff, MAXSIZE);

	char RcptTo[256] = { 0 };
	sprintf(RcptTo, "RCPT TO: <%s>\r\n", targetEmail);
	SendAndRecvMsg(sockClient, RcptTo, strlen(RcptTo), 0, buff, MAXSIZE);

	SendAndRecvMsg(sockClient, "DATA\r\n", strlen("DATA\r\n"), 0, buff, MAXSIZE);

	char Email[1024] = { 0 };
	FormatEmail(userName, targetEmail, emailTitle, content, Email);

	SendAndRecvMsg(sockClient, Email, strlen(Email), 0, buff, MAXSIZE);

	SendAndRecvMsg(sockClient, "QUIT\r\n", strlen("QUIT\r\n"), 0, buff, MAXSIZE);

	closesocket(sockClient);
	WSACleanup();
}