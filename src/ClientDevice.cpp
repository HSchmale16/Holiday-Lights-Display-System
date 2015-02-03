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
        LOG(WARNING) << "Couldn't connect to client listed in database with ip "
                     << "of " << m_ipAddress << " listening on port "
                     << m_listeningPort;
    }
}

ClientDevice::~ClientDevice()
{
    //dtor
    m_socket.disconnect(); // disconnect from the clients
    LOG(INFO) << "ClientDevice DTOR: name = " << m_name;
}


void ClientDevice::updateConnection()
{

}

/// Sets the data to send
void ClientDevice::setShowToSend(std::string show)
{
    m_show = show;
}

void ClientDevice::sendShow()
{
    if(m_socket.connect(sf::IpAddress(m_ipAddress),
                        m_listeningPort) != sf::Socket::Done)
    {
        LOG(WARNING) << "Couldn't connect to client listed in database with ip "
                     << "of " << m_ipAddress << " listening on port "
                     << m_listeningPort;
    }
    else
    {
        for(unsigned int i = 0; i < m_show.length(); i += this->SHOW_CHUNK_SZ)
        {
            // Prepare a chunk to send over the network
            std::string chunk = m_show.substr(i, i + this->SHOW_CHUNK_SZ);
            if(m_socket.send(chunk.c_str(), chunk.length()) != sf::Socket::Done)
            {
                LOG(WARNING) << "Data Transmission Interupted: Name = "
                             << m_name;
            }
        }
        LOG(INFO) << "Finished sending a show to " << this->m_name;
    }
    m_socket.disconnect();
}

void ClientDevice::beginShow()
{
    m_thread.launch();
}

bool ClientDevice::ping()
{
    if(m_socket.connect(sf::IpAddress(m_ipAddress),
                        m_listeningPort != sf::Socket::Done))
    {
        return false;
    }
    m_socket.disconnect();
    return true;
}


