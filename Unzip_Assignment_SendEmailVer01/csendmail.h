 
struct SMailInfo //mail info  
{  
    char*   m_pcUserName;//user name 
    char*   m_pcUserPassWord;//password  
    char*   m_pcSenderName;//the name of the sender  
    char*   m_pcSender;//the email address used to send email 
    char*   m_pcReceiver;//emaill address  
    char*   m_pcTitle;//title  
    char*   m_pcBody;//text body  
    char*   m_pcIPAddr;//server ip  
    char*   m_pcIPName;//server name  
    SMailInfo(){memset(this,0,sizeof(SMailInfo));}  
};  
class CSendMail  
{  
public:  
    CSendMail(void);  
    ~CSendMail(void);  
  
public:  
    bool SendMail(SMailInfo &smailInfo);//initiate the email  
   
protected:  
   
    void Char2Base64(unsigned char* pBuff64, unsigned char* pSrcBuff,int iLen);//char to Base64  
    bool  CReateSocket(SOCKET &sock);//establish the socket  
    bool Login(SOCKET &sock);//login the email account  
    
  
    bool SendHead(SOCKET &sock);  
    bool SendTextBody(SOCKET &sock);
    bool SendFileBody(SOCKET &sock);  
    bool SendEnd(SOCKET &sock);  
protected:  
    
  
    char  m_cSendBuff[4096];  
    char  m_cReceiveBuff[1024];  
      
    SMailInfo m_sMailInfo;  
};  
