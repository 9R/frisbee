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
                   "<html><head><title>CaptivePortal</title>" +
                   "<meta http-equiv=\"refresh\" content=\"5\;url=/\" /></head><body>" +
                   "<h1>Frisbee Settings!</h1><h3>Choose Animation:</h3><p>" +
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
                   "<a href=\"/anim/" + ReversedDots + "\">ReversedDots</a><p/>" +
                   "<h3>Settings:</h3><p>" +
                   "<a href=\"/brightnesshi\">Brightness High</a><br/>" +
                   "<a href=\"/brightnessmed\">Brightness Medium</a><br/>" +
                   "<a href=\"/brightnesslow\">Brightness Low</a><br/>" +
                   "<br/><a href=\"/collisionshow\">Toggle Show Collisions</a><br/>" +
                   "<a href=\"/collisionswitch\">Toggle Switch On Collisions</a></p>" + 
                   "<h3>State:</h3><p>";

String responseCurrAnim ;
String responseCollisionSettings ;
String responseBrightness ;
String responseDyn ;
String responseHTML ;

String responseFoot = "</p></body></html>";

bool _Srv_running = false;

void Srv_setup() {
  // reply to all requests with same HTML
  webServer.onNotFound([]() {
    responseCurrAnim = String("") + "Active Animation: " + AnimationNames[currentAnim] + "<br/>" ;
    responseBrightness = String("") + "Brightness: " + RGB_BRIGHTNESS + "<br/>" ;
    responseCollisionSettings = String("") + "<br/>Show Collisions: " + showCollision + "<br/>" +
                                "Change Animation On Collision: " + switchOnCollision + "<br/>" ;
    responseDyn =  responseBrightness + responseCurrAnim + responseCollisionSettings ;
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
    if (uri.startsWith("/brightnesshi")) {
      RGB_BRIGHTNESS = 127;
    }
    if (uri.startsWith("/brightnessmed")) {
      RGB_BRIGHTNESS = 30;
    }
    if (uri.startsWith("/brightnesslow")) {
      RGB_BRIGHTNESS = 5;
    }
    if (uri.startsWith("/collisionshow")) {
      showCollision = !showCollision ;      
    }
    if (uri.startsWith("/collisionswitch")) {
      switchOnCollision = !switchOnCollision ;      
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

