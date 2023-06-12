#include "main.h"
#include <Arduino.h>

// HTML Webfiles
#include "html_index.h"
#include "html_favicon.h"
#include "html_main.h"
#include "html_polyfills.h"
#include "html_runtime.h"
#include "html_styles.h"

DNSServer dnsServer;
AsyncWebServer server(80);

DynamicJsonDocument wifi_settings(1024);
static const char s_content_enc[] PROGMEM = "Content-Encoding";

const char *ssid = "yourNetworkName";
const char *password = "yourNetworkPass";
const char *ap_ssid = "yourNetworkName";
const char *ap_password = "yourNetworkPass";

bool APMODE = true;
int wifiAttempts = 0;

class RainRequestHandler : public AsyncWebHandler
{
public:
  RainRequestHandler()
  {
    /* THIS IS WHERE YOU CAN PLACE THE CALLS */
    server.onNotFound([](AsyncWebServerRequest *request)
                      {
        // Goes back to root, need to create a Notfound page
      AsyncWebServerResponse *response;
      response = request->beginResponse_P(200, "text/html", PAGE_index, PAGE_index_L);
      response->addHeader(FPSTR(s_content_enc),"gzip");
      request->send(response); });

    // Section on Page render resources

    server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        AsyncWebServerResponse *response;
        response = request->beginResponse_P(200, "text/css", PAGE_styles, PAGE_styles_L);
        response->addHeader(FPSTR(s_content_enc),"gzip");
        request->send(response); });

    server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        AsyncWebServerResponse *response;
        response = request->beginResponse_P(200, "text/javascript", PAGE_main, PAGE_main_L);
        response->addHeader(FPSTR(s_content_enc),"gzip");
        request->send(response); });

    server.on("/polyfills.js", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        AsyncWebServerResponse *response;
        response = request->beginResponse_P(200, "text/javascript", PAGE_polyfills, PAGE_polyfills_L);
        response->addHeader(FPSTR(s_content_enc),"gzip");
        request->send(response); });

    server.on("/runtime.js", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        AsyncWebServerResponse *response;
        response = request->beginResponse_P(200, "text/javascript", PAGE_runtime, PAGE_runtime_L);
        response->addHeader(FPSTR(s_content_enc),"gzip");
        request->send(response); });

    server.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        AsyncWebServerResponse *response;
        response = request->beginResponse_P(200, "image/x-icon", PAGE_favicon, PAGE_favicon_L);
        response->addHeader(FPSTR(s_content_enc),"gzip");
        request->send(response); });

    // Section for action APIS

    // Test APIs
    server.on("/settings", HTTP_POST, [](AsyncWebServerRequest *request)
              {
      AsyncWebServerResponse *response;
      response = request->beginResponse(200, "application/json", "{}");
      request->send(response); });
  }
  virtual ~RainRequestHandler() {}

  bool canHandle(AsyncWebServerRequest *request)
  {
    return true;
  }

  void handleRequest(AsyncWebServerRequest *request)
  {
    AsyncWebServerResponse *response;
    response = request->beginResponse_P(200, "text/html", PAGE_index, PAGE_index_L);
    response->addHeader(FPSTR(s_content_enc), "gzip");
    request->send(response);
  }
};

void setup()
{
  Serial.println("Starting");
  /*
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
    wifiAttempts++;
    if (wifiAttempts > 5)
    {
      // Set AP Mode
      APMODE = true;
      break;
    }
  }
  */
  if (APMODE)
  {
    WiFi.softAPConfig(IPAddress(4, 3, 2, 1), IPAddress(4, 3, 2, 1), IPAddress(255, 255, 255, 0));
    WiFi.softAP(apSSID);
    dnsServer.start(53, "*", WiFi.softAPIP());
    server.addHandler(new RainRequestHandler()).setFilter(ON_AP_FILTER); // only when requested from AP
  }
  // your other setup stuff...

  // more handlers...
  server.begin();
}

void loop()
{
  dnsServer.processNextRequest();
}
