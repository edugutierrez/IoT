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

Para empezar a operar se debe mantener presionado el boton auxiliar del NodeMCU en los primeros segundos lo que pondrá al dispositivo en modo Access Point con una red llamada "myDevice" y password "atentoMyConfig"

Una vez dentro desde un navegador en la dirección http://192.168.4.1 podra configurar los accesos de FireBase.
Para administrar los dispositivos podrá hacerlo desde el proyecto InfrApp.

A futuro se proyecta agregar un modulo RTC para manejo de horario
