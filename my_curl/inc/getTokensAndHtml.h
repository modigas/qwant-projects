#include <libs.h>

char* getTokensAndHtml(char** url, char*** tokens);
struct hostent* getHost(char** url);
int connectToHost(char** ip, struct hostent* host);
void cutUrlTail(char** url);
char* getStartOfUrl(char** url);
int createSocket(char** ip, struct sockaddr_in* server);
bool sendMessage(int socketDesc, char** url);
char* formGetRequest(char** url);
char* getResponse(int socketDesc, char*** tokens);
void getLink(char** url, char** link);
void getHostname(char** url, char** hostname);
void composeMessage(char** message, char** link, char** hostname);
void parseHtmlHeader(int socketDesc, char*** tokens);
bool endOfLine(char*** tokens, int* memory, int* tokenSize, int* i, int* j);
char* readResponse(int socketDesc, char*** tokens);
int findContentLength(char*** tokens);
void freeTokens(char*** tokens);