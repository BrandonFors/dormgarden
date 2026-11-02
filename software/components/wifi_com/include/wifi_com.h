#ifndef WIFI_COM_H
#define WIFI_COM_H

void wifi_com_init();
int wifi_http_request(const char *host, const char *port, const char *request, char *res_buf, int res_buf_len);
#endif
