#!/usr/bin/env python3
#coding:utf-8

from socket import *
serverPort = 12000
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('', serverPort))
serverSocket.listen(1)
print("The server is ready to receive:")
while 1:
    connectSocket, addr = serverSocket.accept()
    sentence = connectSocket.recv(1024)
    capitalizeSentense = sentence.upper()
    connectSocket.send(capitalizeSentense)
