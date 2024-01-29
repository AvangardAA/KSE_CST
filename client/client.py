import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

sock.connect(("127.0.0.1", 13000))

while True:
    choice = input()

    if (choice == "GET"):
        fname = input()
        sock.send(bytes(fname, 'utf-8'))

    elif (choice == "LIST"):
        sock.send(b"list")

    elif (choice == "PUT"):
        fname = input()
        resstr = "put " + fname
        sock.send(bytes(resstr, 'utf-8'))

    elif (choice == "DELETE"):
        fname = input()
        resstr = "delete " + fname
        sock.send(bytes(resstr, 'utf-8'))

    elif (choice == "LIST"):
        fname = input()
        resstr = "info " + fname
        sock.send(bytes(resstr, 'utf-8'))
    
    elif (choice == "EXIT"):
        sock.close()
        exit(0)

    print(sock.recv(1024).decode())
