#include <PubSubClient.h>
#include <WiFi.h>
#include <Preferences.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

// MQTT client
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

//System Level
bool debug = true;
String Name = "MakeItRain";
String ID;
int NumberOfWifiReconntionFailures = 0;
int MaxAttempts = 4;
Preferences preferences;
long ThirtyMinTimer, ThirtySecondTimer, TenSecondTimer, FifthteenSecondTimer;
bool LocalControlLockOut = false;
#define RTCBatteryVoltagePin 39
#define VSVoltagePin 36
#define ResetButton 22
#define LEDOut 21
float LastBatteryVoltage, LastRTCBatteryVoltage;

//Zone definitions
#define Zone1Input 26
#define Zone1Output 17
String ZO1Topic = "";
String ZO1State = "off";
String LastMQTTZO1State = "off";
float ZO1MaxOn;
long Zone1TurnedOnTime;

#define Zone2Input 27
#define Zone2Output 16
String ZO2Topic = "";
String ZO2State = "off";
String LastMQTTZO2State = "off";
float ZO2MaxOn;
long Zone2TurnedOnTime;

#define Zone3Input 14
#define Zone3Output 15
String ZO3Topic = "";
String ZO3State = "off";
String LastMQTTZO3State = "off";
float ZO3MaxOn;
long Zone3TurnedOnTime;

#define Zone4Input 12
#define Zone4Output 2
String ZO4Topic = "";
String ZO4State = "off";
String LastMQTTZO4State = "off";
float ZO4MaxOn;
long Zone4TurnedOnTime;


void setup() {
  Serial.begin(115200);
  SerialOutput("Starting to... MAKEITRAIN",true);
  //SetupAllStoredInformation();

  pinMode(Zone1Input, INPUT);
  attachInterrupt(digitalPinToInterrupt(Zone1Input), LocalInput1, FALLING);
  pinMode(Zone1Output, OUTPUT);

  pinMode(Zone2Input, INPUT);
  attachInterrupt(digitalPinToInterrupt(Zone2Input), LocalInput2, FALLING);
  pinMode(Zone2Output, OUTPUT);

  pinMode(Zone3Input, INPUT);
  attachInterrupt(digitalPinToInterrupt(Zone3Input), LocalInput3, FALLING);
  pinMode(Zone3Output, OUTPUT);

  pinMode(Zone4Input, INPUT);
  attachInterrupt(digitalPinToInterrupt(Zone4Input), LocalInput4, FALLING);
  pinMode(Zone4Output, OUTPUT);

  preferences.begin("SystemSettings", true);
  //setup other System Level settings
  LocalControlLockOut = preferences.getBool("LocalLockOut");

  ZO1MaxOn = preferences.getFloat("Z1_Max");
  ZO2MaxOn = preferences.getFloat("Z2_Max");
  ZO3MaxOn = preferences.getFloat("Z3_Max");
  ZO4MaxOn = preferences.getFloat("Z4_Max");

  preferences.end();

  String MAC = WiFi.macAddress();
  for (int x = 9; x < 17; x++) {
    if (MAC.charAt(x) != ':') {
      ID.concat(MAC.charAt(x));
    }
  }

  ConnectToDaWEEEEFEEEEEEEE(1, 60000);
  SetupMQTT();

  if (WiFi.status() == WL_CONNECTED) {
    delay(100);
    MqttConnectionCheck();
  }
  else {
    //Turn on Bluetooth and put Wifi into AP mode
  }

  SetOutput(1, LOW);
  SetOutput(2, LOW);
  SetOutput(3, LOW);
  SetOutput(4, LOW);
  ReadVoltage();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    ConnectToDaWEEEEFEEEEEEEE(MaxAttempts, 60000);
  }

  if (NumberOfWifiReconntionFailures > MaxAttempts) {
    Serial.println("Connection attempts exhausted");
    LocalControlLockOut = false; //turn off lockout so control via buttons is restored.
  }

  MqttConnectionCheck();

  /* Enable/Disable the local input Interrupts
      If they are disabled they will be polled and pushed to MQTT for state
  */
  if (LocalControlLockOut == false) {
    interrupts();
  } else {
    noInterrupts();
    long CurrentTime = millis();
    //Read all the inputs and post to MQTT every 15 seconds
    if (abs(FifthteenSecondTimer - CurrentTime) > 15000) {
      for (int x = 1; x < 5; x++) {
        String PathName = "/" + Name + "/" + ID + "/ZoneInput/" + String(x);
        mqttClient.publish(PathName.c_str(), String(ReadInput(x)).c_str());
        SerialOutput("Input:" + String(x) + ":" + ReadInput(x),true);
      }
      FifthteenSecondTimer = millis();
    }
  }

  long CurrentTime = millis();
  if (abs(TenSecondTimer - CurrentTime) > 180000) {
    ReadVoltage();
    TenSecondTimer = millis();
  }


  if (LastMQTTZO1State != ReadOutput(1)) {
    mqttClient.publish(ZO1Topic.c_str(), String(ReadOutput(1)).c_str());
  }

  if (LastMQTTZO2State != ReadOutput(2)) {
    mqttClient.publish(ZO2Topic.c_str(), String(ReadOutput(2)).c_str());
  }

  if (LastMQTTZO3State != ReadOutput(3)) {
    mqttClient.publish(ZO3Topic.c_str(), String(ReadOutput(3)).c_str());
  }

  if (LastMQTTZO4State != ReadOutput(4)) {
    mqttClient.publish(ZO4Topic.c_str(), String(ReadOutput(4)).c_str());
  }

  MaxZoneTimeOnCheck();

}

void SetupAllStoredInformation() {
  /*
     Comment out the stuff you don't need to update in perferences.
  */
  preferences.begin("credentials", false);
  //preferences.clear();
  //preferences.putString("ssid", "Your WiFi SSID");
  //preferences.putString("password", "Your Wifi Password");
  preferences.end();

  preferences.begin("SystemSettings", false);
  //preferences.clear();
  //preferences.putBool("LocalLockOut", true);
  //preferences.putString("MQTTIP", "IP"); //Tested with IP not hostnames
  //preferences.putInt("MQTTPORT", 1883);

  preferences.putFloat("Z1_Max", 7.5);
  preferences.putFloat("Z2_Max", 7.5);
  preferences.putFloat("Z3_Max", 7.5);
  preferences.putFloat("Z4_Max", 7.5);
  preferences.end();
}

//-----------------------------------------------------------------------------------
//Wifi, AP and BLE
//-----------------------------------------------------------------------------------
void ConnectToDaWEEEEFEEEEEEEE(int Attempts, int Timeout) {
  if (NumberOfWifiReconntionFailures < Attempts) {
    preferences.begin("credentials", false);
    preferences.begin("credentials", false);
    SerialOutput("Connecting to ",false);
    SerialOutput(preferences.getString("ssid"),false);
    SerialOutput("  Attempt: ",false);
    SerialOutput(String(NumberOfWifiReconntionFailures),true);
    WiFi.begin(preferences.getString("ssid").c_str(), preferences.getString("password").c_str());
    preferences.end();

    int StartTime = millis();
    int CurrentTime = millis();
    while (WiFi.status() != WL_CONNECTED && abs(StartTime - CurrentTime) < Timeout) {
      delay(500);
      SerialOutput(".",false);
      CurrentTime = millis();
    }
    SerialOutput("",true);
    if (WiFi.status() == WL_CONNECTED) {
      NumberOfWifiReconntionFailures = 0;
    }
    else {
      NumberOfWifiReconntionFailures += 1;
    }
  }
}

void SetupAP() {
  //WiFi.softAP(Name);
}

//-----------------------------------------------------------------------------------
//Reading states
//-----------------------------------------------------------------------------------
void ReadVoltage() {
  LastBatteryVoltage = (30.954 / 4095) * analogRead(VSVoltagePin);
  SerialOutput("Voltage:" + String(LastBatteryVoltage),true);
  String VTopic = "/" + Name + "/" + ID + "/VS Votlage";
  mqttClient.publish(VTopic.c_str(), String(LastBatteryVoltage).c_str());

  LastRTCBatteryVoltage = (30.954 / 4095) * analogRead(RTCBatteryVoltagePin);
  SerialOutput("RTC Voltage:" + String(LastRTCBatteryVoltage),true);
  VTopic = "/" + Name + "/" + ID + "/RTC Battery Votlage";
  mqttClient.publish(VTopic.c_str(), String(LastRTCBatteryVoltage).c_str());
}

String ReadOutput(int Number) {
  /*

  */
  String ValueToReturn = "off";
  switch (Number) {
    case 1:
      if (digitalRead(Zone1Output) == 1) {
        ValueToReturn = "on";
      }
      break;
    case 2:
      if (digitalRead(Zone2Output) == 1) {
        ValueToReturn = "on";
      }
      break;
    case 3:
      if (digitalRead(Zone3Output) == 1) {
        ValueToReturn = "on";
      }
      break;
    case 4:
      if (digitalRead(Zone4Output) == 1) {
        ValueToReturn = "on";
      }
      break;
  }

  return ValueToReturn;
}

String ReadInput(int Number) {
  /*

  */
  String ValueToReturn = "off";
  switch (Number) {
    case 1:
      if (digitalRead(Zone1Input) == 1) {
        ValueToReturn = "on";
      }
      break;
    case 2:
      if (digitalRead(Zone2Input) == 1) {
        ValueToReturn = "on";
      }
      break;
    case 3:
      if (digitalRead(Zone3Input) == 1) {
        ValueToReturn = "on";
      }
      break;
    case 4:
      if (digitalRead(Zone4Input) == 1) {
        ValueToReturn = "on";
      }
      break;
  }
  return ValueToReturn;
}

//-----------------------------------------------------------------------------------
//Local control interrupts
//-----------------------------------------------------------------------------------
void LocalInput1() {
  if (digitalRead(Zone1Output) == LOW) {
    SetOutput(1, HIGH);
  }
  else {
    SetOutput(1, LOW);
  }
}

void LocalInput2() {
  if (digitalRead(Zone2Output) == false) {
    SetOutput(2, HIGH);
  }
  else {
    SetOutput(2, LOW);
  }
}

void LocalInput3() {
  if (digitalRead(Zone3Output) == false) {
    SetOutput(3, HIGH);
  }
  else {
    SetOutput(3, LOW);
  }
}

void LocalInput4() {
  if (digitalRead(Zone4Output) == false) {
    SetOutput(4, HIGH);
  }
  else {
    SetOutput(4, LOW);
  }
}

//-----------------------------------------------------------------------------------
//Set Functions
//-----------------------------------------------------------------------------------
void SetOutput(int Number, bool State) {
  /*

  */
  String Translation = "off";
  if (State == HIGH) {
    Translation = "on";
  }

  switch (Number) {
    case 1:
      digitalWrite(Zone1Output, State);
      if (State == HIGH) {
        Zone1TurnedOnTime = millis();
      }
      ZO1State = Translation;
      break;
    case 2:
      digitalWrite(Zone2Output, State);
      if (State == HIGH) {
        Zone2TurnedOnTime = millis();
      }
      ZO2State = Translation;
      break;
    case 3:
      digitalWrite(Zone3Output, State);
      if (State == HIGH) {
        Zone3TurnedOnTime = millis();
      }
      ZO3State = Translation;
      break;
    case 4:
      digitalWrite(Zone4Output, State);
      if (State == HIGH) {
        Zone4TurnedOnTime = millis();
      }
      ZO4State = Translation;
      break;
  }
}

//-----------------------------------------------------------------------------------
//Timer Related
//-----------------------------------------------------------------------------------

void MaxZoneTimeOnCheck() {
  long CurrentTime = millis();
  if (digitalRead(Zone1Output) == HIGH && abs(CurrentTime - Zone1TurnedOnTime) >= ZO1MaxOn * 60000) {
    SetOutput(1, LOW);
  }

  if (digitalRead(Zone2Output) == HIGH && abs(CurrentTime - Zone2TurnedOnTime) >= ZO2MaxOn * 60000) {
    SetOutput(2, LOW);
  }

  if (digitalRead(Zone3Output) == HIGH && abs(CurrentTime - Zone3TurnedOnTime) >= ZO3MaxOn * 60000) {
    SetOutput(3, LOW);
  }

  if (digitalRead(Zone4Output) == HIGH && abs(CurrentTime - Zone4TurnedOnTime) >= ZO4MaxOn * 60000) {
    SetOutput(4, LOW);
  }
}

//-----------------------------------------------------------------------------------
//Communication (MQTT/Serial/WEB)
//-----------------------------------------------------------------------------------
void SerialOutput(String Data, bool CR) {
  if (CR == true) {
    Serial.println(Data);
  }
  else {
    Serial.print(Data);
  }
}

void SetupMQTT() {
  preferences.begin("SystemSettings", true);
  //set up the MQTT
  String TargetFromMem = preferences.getString("MQTTIP");
  char Target[TargetFromMem.length()];
  TargetFromMem.toCharArray(Target, TargetFromMem.length() + 1);
  char *mqttServer;
  mqttServer = &Target[0];
  mqttClient.setServer(mqttServer, preferences.getInt("MQTTPORT"));
  mqttClient.setCallback(callback);
  preferences.end();
}

void MqttConnectionCheck() {
  if (WiFi.status() == WL_CONNECTED) {
    if (!mqttClient.connected()) {
      reconnect();
    }
    mqttClient.loop();
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    SerialOutput("Attempting MQTT connection...",false);
    // Attempt to connect
    if (mqttClient.connect(ID.c_str())) {
      SerialOutput("connected",true);
      // sub to the Zone Output topics and pub the currect state
      ZO1Topic =  "/" + Name + "/" + ID + "/ZoneOutput/1";
      mqttClient.subscribe(ZO1Topic.c_str());
      mqttClient.publish(ZO1Topic.c_str(), String(ReadOutput(1)).c_str());
      ZO2Topic =  "/" + Name + "/" + ID + "/ZoneOutput/2";
      mqttClient.subscribe(ZO2Topic.c_str());
      mqttClient.publish(ZO2Topic.c_str(), String(ReadOutput(2)).c_str());
      ZO3Topic =  "/" + Name + "/" + ID + "/ZoneOutput/3";
      mqttClient.subscribe(ZO3Topic.c_str());
      mqttClient.publish(ZO3Topic.c_str(), String(ReadOutput(3)).c_str());
      ZO4Topic =  "/" + Name + "/" + ID + "/ZoneOutput/4";
      mqttClient.subscribe(ZO4Topic.c_str());
      mqttClient.publish(ZO4Topic.c_str(), String(ReadOutput(4)).c_str());
    }
    else {
      SerialOutput("failed, rc=",false);
      SerialOutput(String(mqttClient.state()),false);
      SerialOutput(" try again in 5 seconds",true);
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  SerialOutput("Message arrived [",false);
  SerialOutput(topic,false);
  SerialOutput("] ",false);
  String message;
  String CurrentOutputState;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  SerialOutput(String(message),true);

  //Zone 1
  if (String((char*)topic) == ZO1Topic) {
    CurrentOutputState = String(ReadOutput(1)).c_str();
    LastMQTTZO1State = message;
    if (message != CurrentOutputState) {
      if (message == "on") {
        SetOutput(1, true);
        SerialOutput("Turning Zone 1: on",true);
      }
      if (message == "off") {
        SetOutput(1, false);
        SerialOutput("Turning Zone 1: off",true);
      }
    }
  }

  //Zone 2
  if (String((char*)topic) == ZO2Topic) {
    CurrentOutputState = String(ReadOutput(2)).c_str();
    LastMQTTZO2State = message;
    if (message != CurrentOutputState) {
      if (message == "on") {
        SetOutput(2, true);
        SerialOutput("Turning Zone 2: on",true);
      }
      if (message == "off") {
        SetOutput(2, false);
        SerialOutput("Turning Zone 2: off",true);
      }
    }
  }

  //Zone 3
  if (String((char*)topic) == ZO3Topic) {
    CurrentOutputState = String(ReadOutput(3)).c_str();
    LastMQTTZO3State = message;
    if (message != CurrentOutputState) {
      if (message == "on") {
        SetOutput(3, true);
        SerialOutput("Turning Zone 3: on",true);
      }
      if (message == "off") {
        SetOutput(3, false);
        SerialOutput("Turning Zone 3: off",true);
      }
    }
  }

  //Zone 4
  if (String((char*)topic) == ZO4Topic) {
    CurrentOutputState = String(ReadOutput(4)).c_str();
    LastMQTTZO4State = message;
    if (message != CurrentOutputState) {
      if (message == "on") {
        SetOutput(4, true);
        SerialOutput("Turning Zone 4: on",true);
      }
      if (message == "off") {
        SetOutput(4, false);
        SerialOutput("Turning Zone 4: off",true);
      }
    }
  }

}
