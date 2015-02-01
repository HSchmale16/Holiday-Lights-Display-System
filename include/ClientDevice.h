#ifndef CLIENTDEVICE_H
#define CLIENTDEVICE_H

#include <string>
#include <SFML/Network.hpp>


class ClientDevice
{
public:
    /** \brief default ctor
     */
    ClientDevice();

    /** \brief Something
     */
    ClientDevice(std::string ipAddress,
                 std::string name,
                 int listeningPort,
                 int channels);

    // dtor
    virtual ~ClientDevice();

    // Getters
    std::string getIPAddress() {return m_ipAddress;}
    std::string getName() {return m_name;}
    int getListeningPort() {return m_listeningPort;}
    int getChannels() {return m_channels;}

    // Setters
    void setIPAddress(std::string ip) {m_ipAddress = ip;}
    void setName(std::string nm) {m_name = nm;}
    void setListeningPort(int p) {m_listeningPort = p;}
    void setChannels(int c) {return m_channels = c;}
protected:
private:
    // Member Variables
    std::string m_ipAddress;
    std::string m_name;
    int m_listeningPort;
    int m_channels;
    sf::TcpSocket m_socket;
};

#endif // CLIENTDEVICE_H
