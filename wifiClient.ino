void wifiClient(){
  Serial.print("red: ");
  Serial.print( getKeyDB("red") );
  Serial.print("pass: ");
  Serial.println( getKeyDB("pass") );
  WiFi.begin( getKeyDB("red") , getKeyDB("pass") );
  Serial.println("INICIANDO CONEXION WIFI");
  
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN) );
    delay(250);
    Serial.print(".");
  }

  while (!NTPch.setSNTPtime()) Serial.print(".");

  const String secret = getKeyDB("secr");
  char charSecret[ secret.length() +1 ];
  secret.toCharArray( charSecret, secret.length() +1 );
  
  config.api_key = getKeyDB("key");
  config.database_url = getKeyDB("url");
  config.signer.tokens.legacy_token = charSecret;
  config.token_status_callback = tokenStatusCallback;
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  
  Serial.printf("\nFirebase Stream Client Connecting... v%s\n", FIREBASE_CLIENT_VERSION);
  stream.setBSSLBufferSize( 2048 , 512 );
  Firebase.setStreamCallback(stream, streamCallback, streamTimeoutCallback);
  const String path = "/devices/"+getKeyDB("name");
  if( !Firebase.beginStream( stream, path ) ) Serial.printf("sream begin error, %s\n\n", stream.errorReason().c_str());

}