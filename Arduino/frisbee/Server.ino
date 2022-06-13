#include <ESP8266WebServer.h>

ESP8266WebServer  webServer(80);          // HTTP server

const char* AnimationNames[] = {
  "ThreeDotsRGB",
  "Glow",
  "RedToGreen",
  "HueFuu",
  "TwoWayRotation",
  "SineRotation",
  "Radioactive",
  "Randots",
  "FadingDot",
  "Sparkling",
  "ColorByDirection",
  "ReversedDots",

  "NumOfAnimations"
};

String responseHead = String("") +
                   "<!DOCTYPE html><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">" +
                   "<html><head><title>CaptivePortal</title></head><body>" +
                   "<h1>Frisbee Settings!</h1><p>Choose Animation:</p><p>" +
                   "<a href=\"/anim/" + ThreeDotsRGB + "\">ThreeDotsRGB</a><br/>" +
                   "<a href=\"/anim/" + Glow + "\">Glow</a><br/>" +
                   "<a href=\"/anim/" + RedToGreen + "\">RedToGreen</a><br/>" +
                   "<a href=\"/anim/" + HueFuu + "\">HueFuu</a><br/>" +
                   "<a href=\"/anim/" + TwoWayRotation + "\">TwoWayRotation</a><br/>" +
                   "<a href=\"/anim/" + SineRotation + "\">SineRotation</a><br/>" +
                   "<a href=\"/anim/" + Radioactive + "\">Radioactive</a><br/>" +
                   "<a href=\"/anim/" + Randots + "\">Randots</a><br/>" +
                   "<a href=\"/anim/" + FadingDot + "\">FadingDot</a><br/>" +
                   "<a href=\"/anim/" + Sparkling + "\">Sparkling</a><br/>" +
                   "<a href=\"/anim/" + ColorByDirection + "\">ColorByDirection</a><br/>" +
                   "<a href=\"/anim/" + ReversedDots + "\">ReversedDots</a><br/>" ;

String responseDyn = String("") +
                   "<br/>Currently active Animation: " + AnimationNames[currentAnim] + "<br/>" ;

String responseFoot = String("") +
                   "</p></body></html>";

String responseHTML ;

bool _Srv_running = false;

void Srv_setup() {
  // reply to all requests with same HTML
  webServer.onNotFound([]() {
    responseDyn = String("") + "<br/>Currently Active Animation: " + AnimationNames[currentAnim] + "<br/>" ;
    responseHTML = responseHead + responseDyn + responseFoot ;
    webServer.send(200, "text/html", responseHTML);
    String uri = webServer.uri();
    Serial.println(uri);
    if (uri.startsWith("/anim/")) {
      Serial.println(uri.substring(6));
      currentAnim = (Animation) uri.substring(6).toInt();
      lastChangeTime = micros();
      Serial.print("currentAnim = ");
      Serial.println(currentAnim);
    }
  });

  webServer.begin();
  _Srv_running = true;
}

void Srv_loop() {
  if (_Srv_running) {
    webServer.handleClient();
  }
}

