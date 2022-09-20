String getStringFullDB(){
  
  EEPROM.begin(1024);
  String str;
  for( int i = 0; i < 1024 ; i++){
    const byte letter = EEPROM.read(i);
    if( letter != 0 ){
      str = str + char( letter );
    }else{
      i = 1024;
    }
    delay(1);
  }
  EEPROM.end();
  return str;
}

void saveStringDB(String str){
  
  EEPROM.begin(1024);
  for( int i = 0, n = 0; n < 1024; i++ ){
    
    const byte byteRead    = EEPROM.read(n);
    if( str[i] ){
      if( str[i] != char(byteRead)  ){
        EEPROM.write(n, str[i] );
      }
      n++;
    }else if( i > str.length() ){
      if( byteRead != 0){
        EEPROM.write(n, 0 );
      }
      n++;
    }
    delay(1);
  }
  EEPROM.commit();
  EEPROM.end();  
  
}

void saveKeyDB( const String key, const String data ){
  
  FirebaseJson json( getStringFullDB() );
  json.set( key, data );
  String str;
  json.toString( str, true );
  saveStringDB(str);
}

String getKeyDB( const String key ){

  FirebaseJson json( getStringFullDB() );
  FirebaseJsonData result;
  json.get( result, key );
  
  return result.to<String>();
}