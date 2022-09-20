void setFirebaseConfig(){

  Serial.println("GET FIREBASE DATA");
  const String path = "/devices/"+getKeyDB("name");

  for (int i = 0; i < 20; i++){
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN) );
    if( Firebase.ready() ){
      i = Firebase.RTDB.getJSON( &fbdo, path ) ? 20 : i ;
    }
    delay( 200 );
  }
  digitalWrite(LED_BUILTIN, LOW);
  
  FirebaseJsonData result;
  fbdo.to<FirebaseJson>().get( result, "tipo" );
  saveKeyDB("config", result.to<String>() );
  fbdo.to<FirebaseJson>().get( result, "devices" );  
  saveKeyDB("devices", result.to<String>() );
  
  FirebaseJsonArray devices( result.to<String>() );
  for( int i = 0 ;  i < devices.size(); i ++){
    pinMode( myPins[i], OUTPUT );
    delay(1);
  }
  
  Serial.println("CONFIGURACION GUARDADA || PINES SETEADOS");
  releActions();
  delay(10);
 
}

void streamCallback(StreamData data){
  if( myTimer > 10000 ){ setFirebaseConfig(); }
}

void streamTimeoutCallback(bool timeout){}