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

#include "com/NetUtils.h"

#include <netdb.h>
#include <cstring>
#include <arpa/inet.h>

#include <sstream>

#include "exceptions/IOException.h"

namespace NetUtils {

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

std::string getHostIP(const std::string &serverHost) {
  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;
  hints.ai_protocol = 0;
  struct addrinfo* result;
  int ret = getaddrinfo(serverHost.c_str(), NULL, &hints, &result);
  if (ret) {
    std::stringstream exceptStream;
    exceptStream << "NetUtils::getServerIP()::getaddrinfo(): ";
    exceptStream << gai_strerror(ret);
    throw IOException(exceptStream.str());
  }
  std::string ipString(inet_ntoa(
    ((const struct sockaddr_in*)result->ai_addr)->sin_addr));
  freeaddrinfo(result);
  return ipString;
}

}
