# MQTT example

This examples demonstrates communication via MQTT protocol (version 5) and storing data into PostgreSQL database.

## Applications

### mqtt-example

This is Spring Boot application that serves as MQTT subscriber and saves data into database. It uses Maven to manage dependencies. It can be started as regular Spring Boot application by using run configuration in IDE or by running command in terminal.

It has API with two actions:

- `GET /topics?topic={value}` - gets last 10 messages that belong to topic with name *value*
- `POST /topics` - Adds subscription to topic that is defined in request body

Directory **postman** provides collection of Postman requests to test the API.

### mqtt-client
This is a simple Java console application that serves as MQTT publisher and periodically sends randomly generated data. It uses Maven to manage dependencies. It can be started by using run configuration in IDE or by running command in terminal. When running this application, it is mandatory to specify `topic name` as **CLI argument**. Topic name is name of some topic in Mosquitto MQTT broker where message will be published to.

## Requirements

* Java 17
* Maven
* [PostgreSQL database](https://www.postgresql.org/) listening on port 5432
* [Mosquitto MQTT broker](https://mosquitto.org/) listening on port 1883

## Setup

1. Install Java and Maven
2. Install and start PostgreSQL
   - Set credentials for authentication in application.properties (`spring.datasource.username` and `spring.datasource.password`) and create database with name `mqttexample`
3. Install Mosquitto, add credentials and start it
   - Open cmd (it could require running it as Administrator) and position inside directory where Mosquitto is installed (on Windows machine default installation directory is `C:\Program Files\mosquitto`) 
   - Run command `mosquitto_passwd -c <password file> <username>` (example: `mosquitto_passwd -c pwfile client`) and insert password when asked (in this example password is `password`)
   - After that check if file with credentials is generated (in this example it is `pwfile`)
   - Run Mosquitto broker ((re)start service or start stand-alone application)
   - Set required information in **application.properties** (`mqtt.host`, `mqtt.port`, `mqtt.username` and `mqtt.password`)
4. Load dependencies of both applications (`pom.xml`) with Maven and start applications
5. Run applications in following order:
   1) Mosquitto broker
   2) PostgreSQL database
   3) mqtt-example application
   4) mqtt-client (one or more of them)
   5) Send POST request `localhost:8081/topics` to subscribe to the same topic that mqtt-client application is publishing messages to
      - you can load collection from `postman` folder into **Postman** application 