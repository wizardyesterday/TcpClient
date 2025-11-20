0.0  Introduction
This TCP client allows you to connect to a TCP server. It is generic in
the sense that allows connection to a specified IP address and specified
port number. It is implemented in the C++ language so all that needs to
be done is to have an application instantiate a TCPClient object and use
the appropriate methods to send data to a server. A method has been provided
so that an application could read the response. 

1.0 Building Example Program
To build the example program, Perform the following steps:

1. git clone https::github.com/wizardyesterday/TcpClient
2. cd TcpClient
3. sh buildClient.sh

You will now have a file called tcpClient in the current directory.

2.0 Running The Example Program
To run the example program, follow the follow the folling steps:

1. ./tcpClient -a ipaddress -p port,

where ipaddress is the 4-octet IP address (for example 192.168.1.30) of the
server and port is the port number for which the server is listening.

3.0 Building Your Own Application
To build your own application, follow the example of the buildClient.sh
script. If you're using a makefile, all you need to do is to inculde the
header file path, and reference the source directory. The only files that
you need are include/TcpClient.h and rc/TcpClient.cc.

4.0 Summary
I created this software because I wanted to creat software that usies
System V messages for input to a program, decode the message, and send the
appropriate command and  control data to a remote server. Hopefully,
others will find this software suitable for their needs.

Happy networking!

Chris G.
IRC Server: irc.libera.chat
IRC Nick: wizardyesterday
IRC Channels: ##rtlsdr

