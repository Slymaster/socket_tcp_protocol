/* 
   _____ _                           _            
  / ____| |                         | |           
 | (___ | |_   _ _ __ ___   __ _ ___| |_ ___ _ __ 
  \___ \| | | | | '_ ` _ \ / _` / __| __/ _ \ '__|
  ____) | | |_| | | | | | | (_| \__ \ ||  __/ |   
 |_____/|_|\__, |_| |_| |_|\__,_|___/\__\___|_|   
            __/ |                                 
           |___/                                  

server.c
DATE:02/08/2019
DESC:Available only for GNU/Linux only
*/

#if defined (linux)
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket(s) close(s)
    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
#endif

#include <stdio.h>
#include <stdlib.h>
#define PORT 1337




int init_server(void)
{
    int err = 0;

    /* Socket et contexte d'adresse du serveur */
    SOCKADDR_IN sin;
    SOCKET sock;
    socklen_t recsize = sizeof(sin);

    /* Socket et contexte d'adresse du client */
    SOCKADDR_IN csin;
    SOCKET csock;
    socklen_t crecsize = sizeof(csin);

    int sock_err;

    if(!err)
    {
        /* Création d'une socket */
        sock = socket(AF_INET, SOCK_STREAM, 0);

        /* Si la socket est valide */
        if(sock != INVALID_SOCKET)
        {
            printf("La socket %d est maintenant ouverte en mode TCP/IP\n", sock);

            /* Configuration */
            sin.sin_addr.s_addr = htonl(INADDR_ANY); /* Adresse IP automatique */
            sin.sin_family = AF_INET; /* Protocole familial (IP) */
            sin.sin_port = htons(PORT); /* Listage du port */
            sock_err = bind(sock, (SOCKADDR*)&sin, recsize);

            /* Si la socket fonctionne */
            if(sock_err != SOCKET_ERROR)
            {
                /* Démarrage du listage (mode server) */
                sock_err = listen(sock, 5);
                printf("Listage du port %d...\n", PORT);


                /* Si la socket fonctionne */
                if(sock_err != SOCKET_ERROR)
                {
                    /* Attente pendant laquelle le client se connecte */
                    printf("Patientez pendant que le client se connete sur le port %d...\n", PORT);
                    csock = accept(sock, (SOCKADDR*)&csin, &crecsize);
                    printf("Un client se connecte avec la socket %d de %s:%d\n", csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
                }
                else
                    perror("listen");
            }
            else
                perror("bind");

            /* Fermeture de la socket client et de la socket serveur */
            printf("Fermeture de la socket client\n");
            closesocket(csock);
            printf("Fermeture de la socket serveur\n");
            closesocket(sock);
            printf("Fermeture du serveur terminée\n");
        }
        else
            perror("socket");
    }   
    return EXIT_SUCCESS;
}
