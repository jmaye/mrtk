/******************************************************************************
 * Copyright (C) 2011 by Jerome Maye                                          *
 * jerome.maye@gmail.com                                                      *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the Lesser GNU General Public License as published by*
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file TCPConnectionClient.h
    \brief This file defines the TCPConnectionClient class, which is an
           interface for a client TCP connection
  */

#ifndef TCPCONNECTIONCLIENT_H
#define TCPCONNECTIONCLIENT_H

#include <string>

#include "exceptions/IOException.h"
#include "base/Serializable.h"

/** The class TCPConnectionClient is an interface for a client TCP
    communication.
    \brief Client TCP communication interface
  */
class TCPConnectionClient :
  public virtual Serializable {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  TCPConnectionClient(const TCPConnectionClient& other);
  /// Assignment operator
  TCPConnectionClient& operator = (const TCPConnectionClient& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs UDP connection from parameters
  TCPConnectionClient(const std::string& serverIP, short port,
    double timeout = 2.5);
  /// Destructor
  virtual ~TCPConnectionClient();
 /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the timeout of the connection
  void setTimeout(double timeout);
  /// Returns the timeout of the connection
  double getTimeout() const;
  /// Returns the port
  short getPort() const;
  /// Returns the server IP
  const std::string& getServerIP() const;
 /** @}
    */

  /** \name Methods
    @{
    */
  /// Open the connection
  void open() throw (IOException);
  /// Close the connection
  void close() throw (IOException);
  /// Test if the connection is open
  bool isOpen() const;
  /// Read buffer from UDP
  void readBuffer(char* buffer, ssize_t numBytes) throw (IOException);
  /// Write buffer to UDP
  void writeBuffer(const char* buffer, ssize_t numBytes) throw (IOException);
 /** @}
    */

protected:
  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  virtual void read(std::istream& stream);
  /// Writes to standard output
  virtual void write(std::ostream& stream) const;
  /// Reads from a file
  virtual void read(std::ifstream& stream);
  /// Writes to a file
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Server IP
  std::string mServerIP;
  /// UDP port
  short mPort;
  /// Timeout of the port
  double mTimeout;
  /// Socket for the port
  ssize_t mSocket;
  /** @}
    */

};

#endif // TCPCONNECTIONCLIENT_H
