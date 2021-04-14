#include <getTokensAndHtml.h>

char* getTokensAndHtml(char** url, char*** tokens)
{
    char* response = NULL;
    while (true)
    {
        int socketDesc = 0;
        struct hostent* host = NULL;
        if ((host = getHost(url)) == NULL) return NULL;
        char* ip = getString(INIT_SIZE);
        if ((socketDesc = connectToHost(&ip, host)) < 0) return NULL;
        if (!sendMessage(socketDesc, url)) return NULL;
        if ((response = getResponse(socketDesc, tokens)) != NULL)
            break;
    }
    return response;
}

struct hostent* getHost(char** url)
{
    struct hostent* host = NULL;
    char* startOfUrl = getString(strlen(*url));
    strcpy(startOfUrl, getStartOfUrl(url));
    cutUrlTail(&startOfUrl);
    if ((host = gethostbyname(startOfUrl)) == NULL) herror("Error");
    free(startOfUrl);
    return host;
}

void cutUrlTail(char** url)
{
    char delim = '/';
    char* tail = my_strchr(*url, delim);
    if (tail != NULL) (*url)[strlen(*url) - strlen(tail)] = '\0';
}

char* getStartOfUrl(char** url)
{
    char* startOfUrl = NULL;
    char* http = "http://";
    if ((startOfUrl = my_strstr(*url, http)) != NULL)
        startOfUrl = &(startOfUrl[strlen(http)]);
    else
        startOfUrl = &((*url)[0]);
    return startOfUrl;
}

int connectToHost(char** ip, struct hostent* host)
{
    int socketDesc = 0;
    struct sockaddr_in server;
    struct in_addr** addressList = (struct in_addr**)host->h_addr_list;
    for (int i = 0; addressList[i] != NULL; i++)
    {
		strcpy(*ip, inet_ntoa(*addressList[i]));
        if ((socketDesc = createSocket(ip, &server)) < 0) return CONNECT_ERROR;
        if (connect(socketDesc, (struct sockaddr*)&server, sizeof(server)) != -1)
        {
            free(*ip);
            return socketDesc;
        }
	}
    free(*ip);
    fprintf(stderr, "Error: could not connect to the server\n");
    return CONNECT_ERROR;
}

int createSocket(char** ip, struct sockaddr_in* server)
{
    int socketDesc = 0;
	if ((socketDesc = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		fprintf(stderr, "Error: could not create a socket\n");
        return CONNECT_ERROR;
	}
	server->sin_addr.s_addr = inet_addr(*ip);
	server->sin_family = AF_INET;
	server->sin_port = htons(HTTP_PORT);
    return socketDesc;
}

bool sendMessage(int socketDesc, char** url)
{
    char* message = formGetRequest(url);
    if (write(socketDesc, message, strlen(message)) < 0)
    {
        fprintf(stderr, "Error: could not send a request\n");
        free(message);
        close(socketDesc);
        return false;
    }
    free(message);
    return true;
}

char* formGetRequest(char** url)
{
    unsigned int formatLength = strlen(*url) + 32;
    char* message = getString(formatLength);
    char* link = getString(formatLength);
    char* hostname = getString(formatLength);
    getLink(url, &link);
    getHostname(url, &hostname);
    composeMessage(&message, &link, &hostname);
    free(link);
    free(hostname);
    return message;
}

void getLink(char** url, char** link)
{
    char* temp1 = my_strstr(*url, "//");
    char* temp2 = NULL;
    if (temp1 != NULL)
    {
        temp1 = &(temp1[2]);
        temp2 = my_strchr(temp1, '/');
    }
    else
        temp2 = my_strchr(*url, '/');
    if (temp2 == NULL)
        (*link)[0] = '/';
    else
        strcat(*link, temp2);
}

void getHostname(char** url, char** hostname)
{
    strcpy(*hostname, getStartOfUrl(url));
    cutUrlTail(hostname);
}

void composeMessage(char** message, char** link, char** hostname)
{
    strcat(*message, "GET ");
    strcat(*message, *link);
    strcat(*message, " HTTP/1.1\r\nHost: ");
    strcat(*message, *hostname);
    strcat(*message, "\r\n\r\n");
}

char* getResponse(int socketDesc, char*** tokens)
{
    char* response = NULL;
    parseHtmlHeader(socketDesc, tokens);
    response = readResponse(socketDesc, tokens);
    close(socketDesc);
    return response;
}

void parseHtmlHeader(int socketDesc, char*** tokens)
{
    int tokenSize = TOKEN_SIZE;
    (*tokens) = (char**)malloc(sizeof(char*) * tokenSize);
    int memory = INIT_SIZE;
    (*tokens)[0] = getString(memory);
    int i = 0;
    int j = 0;
    while (read(socketDesc, &((*tokens)[i][j]), 1))
    {
        if ((*tokens)[i][0] == '\r' && (*tokens)[i][1] == '\n')
        {
            free((*tokens)[i]);
            (*tokens)[i] = NULL;
            break;
        }
        if (endOfLine(tokens, &memory, &tokenSize, &i, &j))
            continue;
        j += 1;
        incStringMemory(&((*tokens)[i]), &memory, &j);
    }
}

bool endOfLine(char*** tokens, int* memory, int* tokenSize, int* i, int* j)
{
    if ((*tokens)[*i][*j] == '\n')
    {
        (*tokens)[*i][*j - 1] = '\0';
        *memory = INIT_SIZE;
        (*i) += 1;
        if (*tokenSize <= *i)
        {
            (*tokenSize) *= 2;
            (*tokens) = (char**)realloc((*tokens), sizeof(char*) * (*tokenSize));
        }
        (*tokens)[*i] = getString(*memory);
        (*j) = 0;
        return true;
    }
    return false;
}

char* readResponse(int socketDesc, char*** tokens)
{
    int contentLength = 0;
    int actualContentLength = 0;
    contentLength = findContentLength(tokens);
    actualContentLength = contentLength;
    char* response = getString(contentLength + 1);
    contentLength = read(socketDesc, response, contentLength);
    if (contentLength != actualContentLength)
    {
        free(response);
        freeTokens(tokens);
        return NULL;
    }
    else if (actualContentLength == 0)
    {
        free(response);
        response = getString(strlen((*tokens)[0]));
        strcat(response, &((*tokens)[0][9]));
    }
    return response;
}

int findContentLength(char*** tokens)
{
    char* temp = NULL;
    char contentString[12];
    int contentInt = 0;
    for (int i = 0; (*tokens)[i] != NULL; i++)
    {
        if ((temp = my_strstr((*tokens)[i], "Content-Length:")) != NULL)
        {
            for (int j = 16, k = 0; (*tokens)[i][j] != '\0'; j++, k++)
            {
                contentString[k] = (*tokens)[i][j];
            }
            contentInt = atoi(contentString);
            break;
        }
    }
    return contentInt;
}