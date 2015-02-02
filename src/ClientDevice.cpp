/** Implementation of the ClientDevice Class
 * \author Henry J Schmale
 * \date February 1, 2015
 */

#include "../include/ClientDevice.h"
#include <glog/logging.h>
#include <cstdlib> // for exit

ClientDevice::ClientDevice(std::string ipAddress,
                           std::string name,
                           int listeningPort,
                           int channels)
    : m_ipAddress(ipAddress),
      m_name(name),
      m_listeningPort(listeningPort),
      m_channels(channels),
      m_thread(&ClientDevice::sendShow, this)
{
    if(m_socket.connect(sf::IpAddress(m_ipAddress),
                        m_listeningPort) != sf::Socket::Done)
    {
        // Throw an exception that something bad happened, also log it
        LOG(WARNING) << "An instance of client device was not constructed "
                     << "properly. This is really bad, but it is recoverable.";
        exit(0);
    }
}

ClientDevice::~ClientDevice()
{
    //dtor
    m_socket.disconnect(); // disconnect from the clients
}


void ClientDevice::updateConnection()
{

}

void ClientDevice::setShowToSend(std::string show)
{

}

void ClientDevice::sendShow()
{

}

