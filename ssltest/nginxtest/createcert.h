/*
gcc -Wall ssl_client.c -o client -lssl -lcrypto 

*/
#ifndef _CREATECERT_H_
#define _CREATECERT_H_

#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/err.h>


 EVP_PKEY* create_key();
 X509* create_fake_certificate(SSL* ssl_to_server, EVP_PKEY *key);
 int ngx_create_fake_certificate(SSL *ssl, char *server);
// 从文件读取伪造SSL证书时需要的RAS私钥和公钥
 EVP_PKEY* create_key()
 {
     EVP_PKEY *key = EVP_PKEY_new();
     RSA *rsa = RSA_new();
     FILE *fp;
     char szcmd[1024]="";
     int ret;
   // 生成明文无保护的私钥 , 默认名字为private.key,长度为2048 bit 
    memset(szcmd,'0',1024);
    sprintf(szcmd, "openssl genrsa -out %s.key %d", "private", 2048);
    printf("Commond: %s\n", szcmd);
    ret = system(szcmd);
    if (ret==-1 || ret == 127)
    {
         perror("create private.key error\n");
         exit(1);
    }
    memset(szcmd,'0',1024);
   // 根据私钥生成公钥 , 默认名字为public.key 
    sprintf(szcmd, "openssl rsa -in %s.key -out %s.key", "private", "public");
    printf("Commond: %s\n", szcmd);
    ret = system(szcmd);
	
      if (ret==-1 || ret == 127)
     {
         perror("create public.key error\n");
         exit(1);
     }
	  if ((fp = fopen("private.key", "r")) == NULL)
     {
         perror("no private.key");
         exit(1);
     }
     PEM_read_RSAPrivateKey(fp, &rsa, NULL, NULL);

     if ((fp = fopen("public.key", "r")) == NULL)
     {
         perror("no public.key");
         exit(1);
     }
     PEM_read_RSAPublicKey(fp, &rsa, NULL, NULL);

     EVP_PKEY_assign_RSA(key,rsa);

     return key;
 }
 
 X509* create_fake_certificate(SSL* ssl_to_server, EVP_PKEY *key)
{        
     //unsigned char buffer[128] = { 0 };
     //int length = 0, loc;
     X509 *server_x509 = SSL_get_peer_certificate(ssl_to_server);
     X509 *fake_x509 = X509_dup(server_x509);
	 
     if (server_x509 == NULL)
     {
         perror("Fail to get the certificate from server!");
     }
	 
     X509_set_version(fake_x509, X509_get_version(server_x509));
     ASN1_INTEGER *a = X509_get_serialNumber(fake_x509);
     a->data[0] = a->data[0] + 1;
     X509_NAME *issuer =  X509_get_issuer_name(server_x509);
     X509_set_issuer_name(fake_x509, issuer);
     X509_set_pubkey(fake_x509, key);
     X509_sign(fake_x509, key, EVP_sha1());

     return fake_x509;
 }
 
 int ngx_create_fake_certificate(SSL *ssl, char *server)
 {
	X509 *fake_x509;     // 伪造证书的句柄   
	FILE * fpem;         //存放伪造的证书文件
    EVP_PKEY* key = create_key();// 从文件读取伪造SSL证书时需要的RAS私钥和公钥 
	fake_x509 = create_fake_certificate(ssl, key);
	fpem = fopen("./cert.pem","w+");
	if (fake_x509 == NULL)
    {
         perror("Fail to  fake certificate!");
         exit(errno);
    }
        PEM_write_X509(fpem, fake_x509);
		fclose(fpem);
		X509_free(fake_x509);
		EVP_PKEY_free(key);
	return 0;
}

#endif
/*
 int main(int argc ,char * argv[])
 {
	int sockfd ,ret;
	struct sockaddr_in dest;
	SSL_CTX * ctx;                                                                                                        
    SSL * ssl; 

    if (argc != 3)  
    {   
        printf("参数格式错误！正确用法如下：\n\t\t%s IP 地址端口\n\t 比如:\t%s 127.0.0.1 80\n ", argv[0], argv[0]);
        exit(0);
    }   
    // SSL 库初始化
    SSL_library_init();
    // 载入所有SSL 算法
    OpenSSL_add_all_algorithms();
    // 载入所有SSL 错误消息
    SSL_load_error_strings();
    // 以SSL V2 和V3 标准兼容方式产生一个SSL_CTX ，即SSL Content Text 
    ctx = SSL_CTX_new(SSLv23_client_method());
    if (ctx == NULL) 
    {   
        ERR_print_errors_fp(stdout);
        exit(1);
    }   
    // 创建一个socket 用于tcp 通信
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)  
    {   
        perror("Socket");
        exit(errno);
    }   
    printf("socket created\n");
    // 初始化服务器端（对方）的地址和端口信息
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
    // 连接服务器
    if (connect(sockfd, (struct sockaddr * ) &dest, sizeof(dest)) != 0)
    {
        perror("Connect ");
        exit(errno);
    }
    printf("server connected\n");
    // 基于ctx 产生一个新的SSL 
    ssl = SSL_new(ctx);
    // 将新连接的socket 加入到SSL 
    SSL_set_fd(ssl, sockfd);
    // 建立SSL 连接
    if (SSL_connect(ssl) == -1)
    {   
        ERR_print_errors_fp(stderr);
    }
    else
    {   
        printf("Connected with %s encryption\n", SSL_get_cipher(ssl));
    }
	
	 ret =  ngx_create_fake_certificate(ssl, NULL);
	if(ret==0) { printf("create fake certificate success\n");}
	else {printf("create fake certificate failed\n");}
    // 关闭连接
    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(sockfd);
    SSL_CTX_free(ctx);
	return 0;
 }
*/
