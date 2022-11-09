#include "Credenciais.h"

#define MYSQL_DEBUG_PORT Serial
#define _MYSQL_LOGLEVEL_ 1
int botao = 4;
#define motor 3
#define pinTrigger 8
#define pinEcho 7

long distancia

//#include <Ultrasonic.h> 
#include <MySQL_Generic.h>

IPAddress server(185, 42, 117, 115);

uint16_t server_port = 3306;

char default_database[] = "b12nbguyeuypjmt36i5j";
char default_table[]    = "localizacao";

String default_value = "-22.8875468,-47.0463506"; 

String INSERT_SQL = String("INSERT INTO ") + default_database + "." + default_table 
                  + " (coordenada) VALUES ('" + default_value + "')";

MySQL_Connection conn((Client *)&client);
MySQL_Query *query_mem;

void setup()
{
  pinMode(botao, INPUT_PULLUP);
  pinMode(motor, OUTPUT);
  
  Serial.begin(115200);
  while (!Serial && millis() < 5000);

  MYSQL_DISPLAY1("\nInicializando a Bengala Smart utilizando", ARDUINO_BOARD);
  MYSQL_DISPLAY(MYSQL_MARIADB_GENERIC_VERSION);

  MYSQL_DISPLAY1("Conectando na rede:", ssid);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    MYSQL_DISPLAY0(".");
  }

  MYSQL_DISPLAY1("Conectado à rede. Endereço IP:", WiFi.localIP());
}


void runInsert()
{
  MySQL_Query query_mem = MySQL_Query(&conn);

  if (conn.connected())
  {
    MYSQL_DISPLAY(INSERT_SQL);
    
    if ( !query_mem.execute(INSERT_SQL.c_str()) )
    {
      MYSQL_DISPLAY("Erro ao inserir dados.");
    }
    else
    {
      MYSQL_DISPLAY("Dado inserido.");
    }
  }
  else
  {
    MYSQL_DISPLAY("Disconectado do servidor. Não foi possível iserir dados.");
  }
}


void conectar()
{
  MYSQL_DISPLAY("Conectando...");
  if (conn.connectNonBlocking(server, server_port, user, password) != RESULT_FAIL)
  {
    delay(500);
    runInsert();
    conn.close();
  }
  else 
  {
    MYSQL_DISPLAY("\nConexão falhou.");
  }
}


void loop()
{
  if (digitalRead(botao) == LOW)
  {
    conectar();
  }
/*
  distancia = sensorUltrassonico.Ranging(CM);
  
  Serial.print(distancia);
  Serial.println("cm");

  
  if (distancia <= 20)
  {
    digitalWrite(motor, HIGH);
  }
  else
  {
    digitalWrite(motor, LOW);
  }
*/

  delay(100);
}
