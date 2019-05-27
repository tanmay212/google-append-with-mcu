#include <ESP8266WiFi.h>
#include "HTTPSRedirect.h"

//https://script.google.com/macros/s/AKfycbwso1fSSVSvuwbTj83XQwT2hWgGCVASUOySY3m-VlI8tdnduDI/exec?toll no=123&rate=100
// Fill ssid and password with your network credentials
const char* ssid = "Nightwing";
const char* password = "nopassword";

const char* host = "script.google.com";
const int httpsPort = 443;
const char *GScriptId = "AKfycbwso1fSSVSvuwbTj83XQwT2hWgGCVASUOySY3m-VlI8tdnduDI";

// Write to Google Spreadsheet
String url = String("/macros/s/") + GScriptId + "/exec?toll no=2000&rate=69";

String payload = "";

HTTPSRedirect* client = nullptr;
// used to store the values of free stack and heap×
// before the HTTPSRedirect object is instantiated
// so that they can be written to Google sheets
// upon instantiation



void setup() 
{
  Serial.begin(115200);
  Serial.flush();
    
  Serial.println();
  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);
  
  // flush() is needed to print the above (connecting...) message reliably, 
  // in case the wireless connection doesn't go through
  Serial.flush();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Use HTTPSRedirect class to create a new TLS connection
  client = new HTTPSRedirect(httpsPort);
  client->setPrintResponseBody(true);
  client->setContentTypeHeader("application/json");
  
  Serial.print("Connecting to ");
  Serial.println(host);

  // Try to connect for a maximum of 5 times
  bool flag = false;
  for (int i=0; i<5; i++)
  {
    int retval = client->connect(host, httpsPort);
    if (retval == 1) 
    {
       flag = true;
       break;
    }
    else
      Serial.println("Connection failed. Retrying...");
  }

  if (!flag)
  {
    Serial.print("Could not connect to server: ");
    Serial.println(host);
    Serial.println("Exiting...");
    return;
  }
  
  payload = "toll no=7&rate=122";
  client->POST(url, host, payload, false);
  client->GET(url, host); 
}

void loop() 
{
  static int connect_count = 0;
  static bool flag = false;
  

 // Serial.print("Ambient = "); 
//  inputVal = mlx.readObjectTempC();
//  Serial.print(inputVal);
 // Serial.println("*C");
  
  
  //String myString = String(inputVal);  
  String FinalStringToSend;
  
  FinalStringToSend = url;

  
  if (client != nullptr)
  {
    if (!client->connected())
    {
      client->connect(host, httpsPort);
      payload= "";
       Serial.println("POST Data to Sheet");
    //  FinalStringToSend = url + myString;
  // Serial.println("POST url :" + FinalStringToSend);
 // client->POST(FinalStringToSend, host, payload);
    }
  }
 // else if (client == nullptr)
  //{
   // Serial.println(" >> Failed to POST data");
  //}

  FinalStringToSend = url + host;
   Serial.println("GET url :" + FinalStringToSend);
 client->GET(FinalStringToSend, host, payload);
  //Serial.println("GET url :"+FinalStringToSend + host);
  //client->GET(FinalStringToSend, host);

  delay(500);
                          
}
