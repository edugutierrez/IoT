# IoT
Proyecto en C++ para integrar en Arduino NOdeMCU

El proyecto basa su funcionamiento en un equipo NodeMCU, conexión internet por wifi y una base de datos en firebase.

Se hace uso de las siguientes librerias.

#include <EEPROM.h>             Para almacenar los datos de configuracion.
#include "FirebaseESP8266.h"    Para administrar las base de datos de FireBase
#include <ESP8266WiFi.h>        Parametros de conexion WiFi
#include <WiFiClient.h>         Idem anterior
#include <ESP8266WebServer.h>   Acceso Html al dispositivo.

#include <SNTPtime.h>           Obtener fecha y hora

A futuro se proyecta agregar un modulo RTC para manejo de horario
