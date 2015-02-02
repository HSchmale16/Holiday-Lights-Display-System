#include "../include/ClientDevice.h"

ClientDevice::ClientDevice()
    : m_thread(&ClientDevice::sendShow, this)
{
    //ctor
}

ClientDevice::ClientDevice(std::string ipAddress,
                           std::string name,
                           int listeningPort,
                           int channels)
    : m_thread(&ClientDevice::sendShow, this)
{

}

ClientDevice::~ClientDevice()
{
    //dtor
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

