/*
usage:
1. 程序中用到的包含公钥的服务端证书cacert.pem和服务端私钥文件privkey.pem需要使用如下方式生成：
openssl genrsa -out privkey.pem 2048
openssl req -new -x509 -key privkey.pem -out cacert.pem -days 1095
2. 编译程序用下列命令：
gcc -Wall ssl_client.c -o client -lssl -lcrypto
gcc -Wall ssl-server.c -o server -lssl -lcrypto
3. 运行程序用如下命令：
./server 8888 3 127.0.0.1 cacert.pem privkey.pem
./client 127.0.0.1 8888
复制代码

*/

#include <stdio.h> 
#include <string.h> 
#include <errno.h> 
#include <sys/socket.h> 
#include <resolv.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <openssl/ssl.h> 
#include <openssl/err.h> 
#include <openssl/pem.h> 

#define MAXBUF 1024 

void ShowCerts(SSL * ssl) 
{
    X509 * cert;
    char * line;
    EVP_PKEY *pstPubKey;
	int len;
    cert = SSL_get_peer_certificate(ssl);
    if (cert != NULL) 
    {
	
        printf("----------数字证书信息-----------begin\n");
		// 获取真实证书的公钥
        printf("真实证书公钥:");
		pstPubKey = X509_get_pubkey(cert);
        //printf("%s\n",pstPubKey);
        printf("真实证书长度:");
		len = EVP_PKEY_bits(pstPubKey);
        printf("bytes size = %d,bits size =%d\n",EVP_PKEY_size(pstPubKey) ,len);
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("证书: %s\n", line);
        free(line);
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("颁发者: %s\n", line);
        free(line);
        printf("----------数字证书信息-----------end\n");
        X509_free(cert);
    } 
    else 
    {
        printf("无证书信息！\n");
    }
} 
// 从文件读取伪造SSL证书时需要的RAS私钥和公钥
 EVP_PKEY* create_key() 
 {   
     EVP_PKEY *key = EVP_PKEY_new();
     RSA *rsa = RSA_new();
     
     FILE *fp;
     if ((fp = fopen("private.key", "r")) == NULL)
     {
         perror("private.key");
     }   
     PEM_read_RSAPrivateKey(fp, &rsa, NULL, NULL);
         
     if ((fp = fopen("public.key", "r")) == NULL)
     {   
         perror("public.key");
     }   
     PEM_read_RSAPublicKey(fp, &rsa, NULL, NULL);
         
     EVP_PKEY_assign_RSA(key,rsa);
     return key;
 }

void SSL_Warning(char *custom_string) {
     char error_buffer[256] = { 0 };
 
     fprintf(stderr, " %s ", custom_string);
     ERR_error_string(ERR_get_error(), error_buffer);
     fprintf(stderr, "%s\n", error_buffer);
 }

void SSL_Error(char *custom_string) {
     SSL_Warning(custom_string);
     exit(EXIT_FAILURE);
 }

X509* create_fake_certificate(SSL* ssl_to_server, EVP_PKEY *key)
{
     unsigned char buffer[128] = { 0 };
     int length = 0, loc;
     X509 *server_x509 = SSL_get_peer_certificate(ssl_to_server);
     X509 *fake_x509 = X509_dup(server_x509);
     if (server_x509 == NULL)
     {
         SSL_Error("Fail to get the certificate from server!");
     }
 
     X509_set_version(fake_x509, X509_get_version(server_x509));
     ASN1_INTEGER *a = X509_get_serialNumber(fake_x509);
     a->data[0] = a->data[0] + 1;
     X509_NAME *issuer =  X509_get_issuer_name(server_x509);
  //   X509_NAME *issuer = X509_NAME_new();
  //   X509_NAME_add_entry_by_txt(issuer, "CN", MBSTRING_ASC, "Thawte SGC CA", -1, -1, 0);
  //   X509_NAME_add_entry_by_txt(issuer, "O", MBSTRING_ASC, "Thawte Consulting (Pty) Ltd.", -1, -1, 0);
  //   X509_NAME_add_entry_by_txt(issuer, "OU", MBSTRING_ASC, "Thawte SGC CA", -1,-1, 0);
     X509_set_issuer_name(fake_x509, issuer);
	 X509_set_pubkey(fake_x509, key);
     X509_sign(fake_x509, key, EVP_sha1());
 
     return fake_x509;
 }

int main(int argc, char * *argv) 
{
    int sockfd, len;
    struct sockaddr_in dest;
    char buffer[MAXBUF + 1];
    SSL_CTX * ctx;
    SSL * ssl;
   
    X509 *pstRealCert;   // 服务器证书的句柄
	X509 *fake_x509;     // 伪造证书的句柄
	BIO  *b,*c;
	int ret;
	FILE * fpem;
    
if (argc != 3) 
    {
        printf("参数格式错误！正确用法如下：\n\t\t%s IP 地址端口\n\t 比如:\t%s 127.0.0.1 80\n 此程序用来从某个IP 地址的服务器某个端口接收最多MAXBUF 个字节的消息", argv[0], argv[0]);
        exit(0);
    }
    // 从文件读取伪造SSL证书时需要的RAS私钥和公钥
    EVP_PKEY* key = create_key();
    /* SSL 库初始化*/
    SSL_library_init();
    /* 载入所有SSL 算法*/
    OpenSSL_add_all_algorithms();
    /* 载入所有SSL 错误消息*/
    SSL_load_error_strings();
    /* 以SSL V2 和V3 标准兼容方式产生一个SSL_CTX ，即SSL Content Text */
    ctx = SSL_CTX_new(SSLv23_client_method());
    if (ctx == NULL) 
    {
        ERR_print_errors_fp(stdout);
        exit(1);
    }
    /* 创建一个socket 用于tcp 通信*/
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
        perror("Socket");
        exit(errno);
    }
    printf("socket created\n");
    /* 初始化服务器端（对方）的地址和端口信息*/
    bzero( &dest, sizeof(dest));
    dest.sin_family = AF_INET;
    //设置连接的端口
    dest.sin_port = htons(atoi(argv[2]));
    //设置连接的IP地址
    if (inet_aton(argv[1], (struct in_addr * ) &dest.sin_addr.s_addr) == 0) 
    {
        perror(argv[1]);
        exit(errno);
    }
    printf("address created\n");
    /* 连接服务器*/
    if (connect(sockfd, (struct sockaddr * ) &dest, sizeof(dest)) != 0) 
    {
        perror("Connect ");
        exit(errno);
    }
    printf("server connected\n");
    /* 基于ctx 产生一个新的SSL */
    ssl = SSL_new(ctx);
    /* 将新连接的socket 加入到SSL */
    SSL_set_fd(ssl, sockfd);
    /* 建立SSL 连接*/
    if (SSL_connect(ssl) == -1) 
    {
        ERR_print_errors_fp(stderr);
    }
    else 
    {
        printf("Connected with %s encryption\n", SSL_get_cipher(ssl));
//        ShowCerts(ssl);
    }
	
    // 从服务器获得证书，并通过这个证书伪造一个假的证书
    //fake_x509 = create_fake_certificate(ssl, key);
	
    pstRealCert = SSL_get_peer_certificate(ssl);  
     if ( pstRealCert== NULL)
     {
         SSL_Error("Fail to get the certificate from server!");
         exit(errno);
     }
	fpem = fopen("cert.pem","w+"); 
	//	PEM_write_X509(fpem,pstRealCert);
    	b = BIO_new(BIO_s_file());
		BIO_set_fp(b,stdout,BIO_NOCLOSE);
    	X509_print(b,pstRealCert );
    	BIO_free(b);
	fake_x509 = create_fake_certificate(ssl, key);
	 if (fake_x509 == NULL)
	{
         SSL_Error("Fail to  fake certificate!");
         exit(errno);
     }
	//  PEM_write_X509(fpem, fake_x509);
    	c = BIO_new(BIO_s_file());
		BIO_set_fp(c,stdout,BIO_NOCLOSE);
    	X509_print(c,fake_x509);
    	BIO_free(c);
    /* 接收对方发过来的消息，最多接收MAXBUF 个字节*/
    bzero(buffer, MAXBUF + 1);
    /* 接收服务器来的消息*/
    len = SSL_read(ssl, buffer, MAXBUF);
    if (len > 0) 
    {
        printf("接收消息成功:'%s'，共%d 个字节的数据\n", buffer, len);
    }
    else 
    {
        printf("消息接收失败！错误代码是%d，错误信息是'%s'\n", errno, strerror(errno));
        goto finish;
    }
    bzero(buffer, MAXBUF + 1);
    strcpy(buffer, "from client->server");
    /* 发消息给服务器*/
    len = SSL_write(ssl, buffer, strlen(buffer));
    if (len < 0) 
    {
        printf("消息'%s'发送失败！错误代码是%d，错误信息是'%s'\n", buffer, errno, strerror(errno));
    }
    else 
    {
        printf("消息'%s'发送成功，共发送了%d 个字节！\n", buffer, len);
    }
    finish:
    /* 关闭连接*/
	fclose(fpem);
    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(sockfd);
    SSL_CTX_free(ctx);
//    X509_free(fake_x509);                                                                                         
    X509_free(pstRealCert);                                                                                         
    EVP_PKEY_free(key);
    return 0;
}

