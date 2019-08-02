/* 
   _____ _                           _            
  / ____| |                         | |           
 | (___ | |_   _ _ __ ___   __ _ ___| |_ ___ _ __ 
  \___ \| | | | | '_ ` _ \ / _` / __| __/ _ \ '__|
  ____) | | |_| | | | | | | (_| \__ \ ||  __/ |   
 |_____/|_|\__, |_| |_| |_|\__,_|___/\__\___|_|   
            __/ |                                 
           |___/                                  

client.c
DATE:02/08/2019
DESC:Available only for GNU/Linux only
*/

#if defined (linux)
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define INVALID_SCOKET -1
    #define SOCKET_ERROR -1
    #define closesocket(s) close(s)
    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
#endif

#include <stdio.h>
#include <stdlib.h>
#define IP "127.0.0.1"
#define PORT 1337




int main(void)
{
    int err = 0;

    SOCKET sock;
    SOCKADDR_IN sin;

    if(!err)
    {
        /* Création de la socket */
        sock = socket(AF_INET, SOCK_STREAM, 0);

        /* Configuration de la connexion */
        sin.sin_addr.s_addr = inet_addr(IP);
        sin.sin_family = AF_INET;
        sin.sin_port = htons(PORT);

        /* Si le client arrive à se connecter */
        if(connect(sock, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR)
            printf("Connexion à %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));
        else
            printf("Impossible de se connecter\n");

        /* On ferme la socket précédemment ouverte */
        closesocket(sock);
    }
    
    return EXIT_SUCCESS;
}