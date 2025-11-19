//**********************************************************************
// file name: TcpClient.cc
//**********************************************************************

#include "TcpClient.h"
#include <stdio.h>

/**************************************************************************

  Name: TcpClient

  Purpose: The purpose of this function is to serve as the constructor
  of a TcpClient object.  This function opens a socket, and if
  successful, populates the peer address structure with the appropriate
  information.

  Calling Sequence: TcpClient(ipAddressPtr,port,*successPtrPtr)

  Inputs:

    ipAddressPtr - A pointer to a character string that represents the
    IP address of the link partner.  The format is in dotted decimal
    notation.

    port - The port number for the link partner listener.

    *successPtrPtr - A flag that indicates whether or not the system
    was initialized. A value of true indicates that the systeem was
    initialized, and a value of false indicates that a failure occurred
    during initialization.

  Outputs:

    None.

**************************************************************************/
TcpClient::TcpClient(char *ipAddressPtr,int port,bool *successPtr)
{
  int result;

  //  Defaault to failure result.
  *successPtr = false;
 
  // 1. Create socket.
  socketDescriptor = socket(AF_INET,SOCK_STREAM,0);

  if (socketDescriptor  > 0)
  {
    *successPtr = true;
  } // if
  else
  {
    fprintf(stderr,"ERROR, socket()\n");
  } // else

  if (*successPtr == true)
  {
    // Configure server address.
    peerAddress.sin_family = AF_INET;
    peerAddress.sin_port = htons(port);
    inet_pton(AF_INET,ipAddressPtr,&peerAddress.sin_addr);
  } // if

  if (*successPtr == true)
  {
    // Connect to server.
    result = connect(socketDescriptor,
                     (struct sockaddr *)&peerAddress,
                      sizeof(peerAddress));

    if (result == 0)
    {
      fprintf(stderr,"ERROR: connect()\n");
      *successPtr = false;
    } // if
  } // if
 
} // TcpClient

/**************************************************************************

  Name: ~TcpClient

  Purpose: The purpose of this function is to serve as the destructor
  of a TcpClient object.

  Calling Sequence: ~TcpClient()

  Inputs:

    None.

  Outputs:

    None.

**************************************************************************/
TcpClient::~TcpClient(void)
{

  if (socketDescriptor > 0)
  {
    // Close the connection.
    close(socketDescriptor);
  } // if

} // ~TcpClient

/**************************************************************************

  Name: connectionIsEstablished

  Purpose: The purpose of this function is to serve as the destructor
  of a TcpClient object.

  Calling Sequence: status = connectionIsEstablished()

  Inputs:

    None.

  Outputs:

    status - A boolean that indicates whether or not a connection is
    established.  A value of true indicates that a connect has been
    established, and a value of false indicates that a connection has
    not been established.

**************************************************************************/
bool TcpClient::connectionIsEstablished(void)
{
  bool status;

  if (socketDescriptor > 0)
  {
    status = true;
  } // if
  else
  {
    status = false;
  } // else

  return (status);
 
} // connectionIsEstablished

/**************************************************************************

  Name: sendData

  Purpose: The purpose of this function is to send a buffer of data over
  a TCP connection.

  Calling Sequence: octetsSent = sendData(bufferPtr,bufferLength)

  Inputs:

    bufferPtr - A pointer to the octets to send.

    bufferLength - The number of octets to send.

  Outputs:

    octetsSent - The number of octets sent over the TCP connection.

**************************************************************************/
ssize_t TcpClient::sendData(void *bufferPtr,int bufferLength)
{
  ssize_t octetsSent;
  unsigned char *octetPtr;

  // Default to nothing sent.
  octetsSent = 0;

  if (connectionIsEstablished())
  {
    // Reference the buffer in the octet context.
    octetPtr = (unsigned char *)bufferPtr;

    // Send the octets over the TCP connection.
    octetsSent = send(socketDescriptor,octetPtr,bufferLength,0);
  } // if

  return (octetsSent);

} // sendData

/**************************************************************************

  Name: receiveData

  Purpose: The purpose of this function is to receive incoming data
  over a TCP connection.

  Calling Sequence: octetsReceived = receiveData(bufferPtr,bufferLength)

  Inputs:

    bufferPtr - A pointer to the octets to send.

    bufferLength - The number of size of the receive buffer, referenced.

  Outputs:

    octetsReceived - The number ogf octects recieved over the connection.


**************************************************************************/
ssize_t  TcpClient::receiveData(void *bufferPtr,int bufferLength)
{
  ssize_t octetsReceived;
  unsigned char *octetPtr;

  // Default to nothing received.
  octetsReceived = 0;

  if (connectionIsEstablished())
  {
    // Reference the buffer in the octet context.
    octetPtr = (unsigned char *)bufferPtr;

    // Read what's available.
    octetsReceived = recv(socketDescriptor,octetPtr,bufferLength,0);
  } // if

  return (octetsReceived);

} // receiveData

