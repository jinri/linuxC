/*
gcc -Wall ssl_client.c -o client -lssl -lcrypto 

*/
#include"createcert.h"
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
