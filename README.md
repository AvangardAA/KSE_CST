# HW 4

I`ll use TCPDump instead of Wireshark

In order to launch it with appropriate info, start command is:
```
sudo tcpdump -i lo -X -vv 'tcp port <port>'
```

Starting of with HW2 and HW3 analysis, lets break-up them to 3 parts:
```
1. Connection when client starts
2. Message swap between client and server
3. Disconnect
```

# HW3

# 1.
Our connection part of communication is quite simple, over here on screenshot we can see the SYN-SYNACK sequence, when client initiates an
connection and server accepts it. Interesting parts of this is MSS, which is maximum TCP segment size which our server can receive in single packet,
the TCP protocol itself, and 0 payload since we dont send anything to server at this moment
![Screenshot from 2024-03-02 14-59-31](https://github.com/AvangardAA/KSE_CST/assets/70914823/4afac19c-bd17-4d51-beb5-14ec51ea1062)

# 2.
Then basically any transfered message as functionality of server and client on this level will be PUSH-ACK sequence, where initiator pushes data and remote host accepts it with acknowledge.

Screenshots for connection to room and message to room from client
![Screenshot from 2024-03-02 15-03-07](https://github.com/AvangardAA/KSE_CST/assets/70914823/6cdd70b3-7271-46b3-a92d-d3c2369027df)
![Screenshot from 2024-03-02 15-02-39](https://github.com/AvangardAA/KSE_CST/assets/70914823/4b7ffdfb-9a49-4abb-af32-f667b910c83b)

# 3.
And connection close happens at the end, where with normal conditions when client closes and server confirms closure it can be observed like that (grateful close in tcp is client FIN,ACK -> server FIN,ACK):
![Screenshot from 2024-03-02 15-03-55](https://github.com/AvangardAA/KSE_CST/assets/70914823/77d5eebc-9136-447f-8669-c9f1e086db1a)

# Remarks about HW3:

On TCP (L4) level, our client-server functionality such as connect,rejoin,send message is nothing else as PSH,ACK, because only software on server and client knows for what this instructions are needed and their flow.
Only different things we can observe is connection open, connection close, message transfer and message transfer truncation, when either client or server is sending big chunk of data which they cant process as single payload


