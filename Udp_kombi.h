#ifndef UDP_KOMBI_H
#define UDP_KOMBI_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <stdio.h>
#include <string.h>
#include "SimpleTimer.h"

typedef struct 
{
int port = 8888;
const char *ssid = "Basri_2.4GHz";
const char *password = "Soylu.1905";
IPAddress broadcastIP;
bool portFlag = 0;
}Udp_kombi_t;


void Wifi_connection(const char *ssid, const char *password);
void Udp_broadcast(WiFiUDP* Udp, Udp_kombi_t* Udp_confident);
void Udp_read(WiFiUDP* Udp, char* dizi);
void Udp_SendPacket(WiFiUDP* Udp, Udp_kombi_t* Udp_confident, const char* dizi);
void parseInIP(Udp_kombi_t* Udp_confident, char *dizi);
void Udp_GetInfo(WiFiUDP* Udp, Udp_kombi_t* Udp_confident, char *dizi);

#endif