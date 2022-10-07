#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Initialize Wifi connection to the router
char ssid[] = "WiFi";     // your network SSID (name)
char password[] = "password123"; // your network key

// Initialize Telegram BOT
#define BOTtoken "0000:XXXXX"  // your Bot Token (Get from Botfather)

WiFiClientSecure client;

UniversalTelegramBot bot(BOTtoken, client);

int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done

String defaultChatID = "0000";

void setup() {
  Serial.begin(9600);
  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  client.setInsecure();
}

void loop() {
  Serial.print("millis()\t: ");
  Serial.println(millis());
  Serial.println("<--Checking-->");
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    Serial.print("Bot_lasttime\t: ");
    Serial.println(Bot_lasttime);
    Serial.print("Bot_mtbs\t: ");
    Serial.println(Bot_mtbs);
    Serial.print("bot.last_message_received\t: ");
    Serial.println(bot.last_message_received);
    Serial.print("numNewMessages\t: ");
    Serial.println(numNewMessages);
    while(numNewMessages) {
      Serial.println("got response");
      for (int i=0; i<numNewMessages; i++) {
        Serial.println(bot.messages[i].chat_id);
        Serial.println(bot.messages[i].text);
        String chat_id = String(bot.messages[i].chat_id);
        if(chat_id == "0000"){
          String text = bot.messages[i].text;
          String from_name = bot.messages[i].from_name;
          if (text == "/start") {
            bot.sendMessage(chat_id, "Welcome to Locker Controler.\n", "Markdown");
          }else if (text == "/open"){
            Serial.write("1560QW");
            bot.sendMessage(chat_id,"OPENING . . . . ." , "Markdown");
            delay(1000);
          }else if (text == "/close"){
            Serial.write("1525QW");
            bot.sendMessage(chat_id,"CLOSING . . . . ." , "Markdown");
            delay(1000);
          }else {
            delay(2000);
          }
        }
      }
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    Bot_lasttime = millis();
    Serial.print("Last Bot_lasttime\t: ");
    Serial.println(Bot_lasttime);
  }
  Serial.println("Done");
}
