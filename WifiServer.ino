void checkWifiServer() {
  
  const String name = getKeyDB("name");
  Serial.print("INIT SERVER DEVICE: ");
  Serial.println( name );
  
  bool myServer = false;

  while ( millis() < 2500 && !myServer ) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN) );
    if (digitalRead(0) != HIGH) { myServer = true; }
    delay(200);
  }
  digitalWrite(LED_BUILTIN, HIGH);
  
  if (myServer) {

    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Configuring access point myDevice");
    WiFi.softAP("myDevice", "atentoMyConfig");

    IPAddress myIP = WiFi.softAPIP();
    server.on("/", []() { server.send(200, "text/html", 
    "<html>\
        <head><title>InfrApp</title>\
        <style>\
          body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #2874A6; text-align: center }\
          ::placeholder{ text-align: center; Color: #2874A6 }\
          input{ margin:1%; width:30%; line-height: 3em; border-radius: 5px; text-align: center}\
          button{ margin:2%; line-height: 3em; width:15%; border-radius: 5px}\
        </style></head>\
        <body>\
          <h1>InfrApp IoT</h1>\
          <h1>MAC DEVICE: </h1>\
          <form action=\"/upData\" method=\"POST\">\
            <input type=\"text\" name=\"red\" placeholder=\"red wifi\"></br>\
            <input type=\"password\" name=\"pass\" placeholder=\"password max 10 char\"></br>\
            <input type=\"text\" name=\"url\" placeholder=\"url\"></br>\
            <input type=\"text\" name=\"secr\" placeholder=\"secret\"></br>\
            <input type=\"text\" name=\"key\" placeholder=\"key\"></br>\
            <input type=\"text\" name=\"name\" placeholder=\"device name\"></br>\
            <button type=\"submit\" >save!</button>\
          </form>\
        </body>\
      </html>");
    });
    server.on("/upData", HTTP_POST, [](){
      const String json = "{\"red\":\""+server.arg("red")+"\",\"pass\":\""+server.arg("pass")+"\","
                          +"\"url\":\""+server.arg("url")+"\",\"secr\":\""+server.arg("secr")+"\","
                          +"\"key\":\""+server.arg("key")+"\",\"name\":\""+server.arg("name")+"\"}";
      saveStringDB(json);
      server.send(200, "text/html", "<h1>Listo!</h1><p>se guardaron los cambios</p>");
      delay(100);        
    });

    server.begin();
    Serial.print("HTTP server started - AP IP address: ");
    Serial.println(myIP);
    while (true) server.handleClient();
  }
 
}