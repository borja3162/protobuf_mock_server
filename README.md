# protobuf_mock_server

## Project description:

The project is a simple non-interactive example of serialization and deserialization of messages using the protobuf library in the context of a mock client-server interaction. The app shows the way the data is moved and transformed by displaying the relevant information in the terminal.

## Motivation:

There were two main learning objectives that inspired this project:
- Learn about some serialization library  in C++
- Larn about CI workflows in Github

## Architecture:


### Network modeling
In the app, There are three main classes to model the network and exchange of data :

- A client, that sends messages to the server, and doesn’t know about serialization or networking
- A “connection” that acts as a messenger that serializes and sends data to the server, receives serialized responses (alerts), and manages queues of messages if sending is not possible.
- A (mock) server, that receives the serialized messages, deserializes them, and produces simple responses (status code + time) that are serialized and send back 

In the app, there is a single connection object and it is owned by the client. This makes the relationship between client and server  asymmetrical.





#### Simplified client - server network model used in app

<p align="center">
  <img src="img/abc.png" alt="Architecture", width="880" >
</p>






## Project description:



## Project description:



## Project description:



## Project description:



