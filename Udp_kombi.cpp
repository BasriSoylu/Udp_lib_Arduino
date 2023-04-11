#include "Udp_kombi.h"


void Udp_read(WiFiUDP* Udp, char* dizi)
{
  int packetSize = Udp->parsePacket();
    if (packetSize)
    {
      int len = Udp->read(dizi, 255);
      if (len > 0)
      {
        dizi[len] = '\0';
      }
      Serial.println(dizi);
    }
}

void Wifi_connection(const char *ssid, const char *password)
{
  Serial.printf("Connecting to %s ", ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.printf("\nMyIP: %s, MyPort: %d\n",WiFi.localIP().toString().c_str(), 8888);
}

void Udp_broadcast(WiFiUDP* Udp, Udp_kombi_t* Udp_confident)
{
    char broadcastPacket[25];
    IPAddress broadcastIP(255,255,255,255);
    sprintf(broadcastPacket, "%s,%d\n", WiFi.localIP().toString().c_str(), Udp_confident->port);
    Udp->beginPacket(broadcastIP,Udp_confident->port);
    Udp->write(broadcastPacket);
    Udp->endPacket();
    //Serial.println(broadcastPacket);
}

void Udp_SendPacket(WiFiUDP* Udp, Udp_kombi_t* Udp_confident, const char* dizi)
{
  Udp->beginPacket(Udp_confident->broadcastIP, Udp_confident->port);
  Udp->write(dizi);
  Udp->endPacket();
  //Serial.println("Paket Gonderildi");
}


void Udp_GetInfo(WiFiUDP* Udp, Udp_kombi_t* Udp_confident, char *dizi)
{
  while(Udp_confident->portFlag == 0)
  {
    int packetSize = Udp->parsePacket();
    if (packetSize)
    {
      int len = Udp->read(dizi, 255);
      if (len > 0)
      {
        dizi[len] = '\0';
      }
      Serial.println(dizi);
      parseInIP(Udp_confident, dizi);
    }
  }
}



void parseInIP(Udp_kombi_t* Udp_confident, char *dizi)
{
  String strString = String(dizi);
  int commaPosition = strString.indexOf(",");
  String tempStringIP = strString.substring(0, commaPosition);
  IPAddress tempIP;
  bool succes = tempIP.fromString(tempStringIP);
  if(succes)
  {
     Udp_confident->broadcastIP = tempIP;
  }
  else
  {
    Serial.println("Gecersiz IP");
  }

  Udp_confident->port = strString.substring(commaPosition + 1).toInt();

  Serial.print("IP Address: ");
  Serial.println(Udp_confident->broadcastIP);
  Serial.print("Port: ");
  Serial.println(Udp_confident->port);

  if(Udp_confident->port != 0)
  {
    Udp_confident->portFlag = 1;
  }
}
