#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <mariadb/mysql.h>

void update(int id, char *status);

int main(int ac, char **ap) {
  // Variable Declaration //
  int sockfd, newsockfd;
  socklen_t clilen;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  int n;

  // Make A New Socket (AF_INET Is A Internet Socket) (SOCK_STREAM Is A TCP Protocol) //
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) { // Only If It Fails //
    syslog(LOG_NOTICE, "domo-daemon: kan geen socket aanmaken");
    exit(-1);
  }

  // Empty serv_addr //
  bzero((char*)&serv_addr, sizeof(serv_addr));

  // Set The Address //
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(1234);
  if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) { // Only If It Fails To Bind The Socket To The Port //
    syslog(LOG_NOTICE, "domo-daemon: binden is mislukt");
    exit(-1);
  }

  while (1) {
    // Wait For A Connection //
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    // Wait For A Accept From The Client //
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0) {
      syslog(LOG_NOTICE, "domo-daemon: kan client niet accepten");
      exit(-1);
    }

    // ! -- Set Value For Id -- ! //
    // Set The Sended Value To Buffer //
    bzero(buffer, 256);
    n = write(newsockfd, "ID: ", 4);
    n = read(newsockfd, buffer, 256);
    if (n < 0) { // Only If It Fails To Read //
      syslog(LOG_NOTICE, "domo-daemon: kan geen id van client ontvangen");
      exit(-1);
    }
    buffer[n - 2] = '\0';
    int id = atoi(buffer);

    syslog(LOG_NOTICE, "PRINT SOME TEXT FOR DEBUGGING: %d", id);

    // Only 1 Script Will Send A 0 This Is The Quit Server Script //
    if (id == 8) {
      break;
    }

    // ! -- Set Value For led_status -- ! //
    // Set The Sended Value To Buffer //
    n = write(newsockfd, "Status: ", 8);
    n = read(newsockfd, buffer, 256);
    if (n < 0) { // Only If It Fails To Read //
      syslog(LOG_NOTICE, "domo-daemon: kan geen status van client ontvangen");
      exit(-1);
    }
    buffer[n - 2] = '\0';

    update(id, buffer);

    // Write A Response Back //
    n = write(newsockfd, "ok\n", 2);
  }

  // Close The Connection //
  close(newsockfd);
  close(sockfd);

  return EXIT_SUCCESS;
}

void update(int id, char *status) {
  MYSQL *connection = mysql_init(NULL);
  char query[256];

  mysql_real_connect(connection, "localhost", "pipo", "pipo", "mijndb", 0, NULL, 0);
  if (connection == NULL) {
    syslog(LOG_NOTICE, "domo-daemon: kan geen verbinding maken\n");
    exit(-1);
  } else {
    syslog(LOG_NOTICE, "domo-daemon: verbinding is gemaakt\n");
  }

  // Line For Updating Database //
  sprintf(query, "UPDATE leds SET led_status=\"%s\" WHERE led_id=%d", status, id);
  mysql_query(connection, query);


  mysql_close(connection);

  syslog(LOG_NOTICE, "domo-daemon: connectie gestopt");
}
