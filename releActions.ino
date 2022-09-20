void releActions(){
  
  dateTime = NTPch.getTime( -4.0, 1 );

  const String str = getKeyDB("devices");
  Serial.println("RELE ACTIONS");
  String myDevices;
  for( int i = 0; i < str.length(); i ++){
    const uint8_t byteChar = (uint8_t) str[i];
    if( byteChar != 92 && byteChar != 9 && byteChar != 10 ){
      myDevices += str[i];
    }
  }
  
  FirebaseJsonArray myArray( myDevices );
  Serial.println("start iterator: ");
  
  for( int i = 0; i < myArray.size(); i ++){

    Serial.print( "Device: " );
    Serial.print( i );

    FirebaseJsonData result;
    myArray.get( result, i );
    FirebaseJson json( result.to<String>() );
    
    json.get( result, "config");
    if( result.to<String>() == "off" ){
      digitalWrite( myPins[i], !releDefault );
      Serial.println( " || config: off  - status: apagado " );
    }
    else if( result.to<String>() == "on" ){
      digitalWrite( myPins[i], releDefault );
      Serial.println( " || config: on - status: encendido " );
    }
    else{
      json.get( result, "days");
      Serial.print( " || config: auto " );
      
      if( result.to<String>()[ dateTime.dayofWeek - 1 ] == 's'){
        const int now = ( dateTime.hour * 60 ) + dateTime.minute;
        json.get( result, "on");
        const int on  = result.to<int>();
        json.get( result, "off");
        const int off = result.to<int>();
        
        Serial.print( " || day: ok - time now: " );
        Serial.print( now );
        Serial.print( " - time on: " );
        Serial.print( on );
        Serial.print( " - time off: " );
        Serial.print( off );
        Serial.print( " - status: " );
        Serial.println( off > now && now > on ? "encendido" : "apagado");
        digitalWrite( myPins[i], releDefault );
      }
      else{
        digitalWrite( myPins[i], !releDefault );
        Serial.println( " || day: no - status: apagado " );        
      }
    }
    delay(100);
  }

}