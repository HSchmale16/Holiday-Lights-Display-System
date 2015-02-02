#ifndef CLIENTDEVICE_H
#define CLIENTDEVICE_H

#include <string>
#include <SFML/Network.hpp>
#include <SFML/System/Thread.hpp>


/** \brief A client device connected to the server.
 *
 * \author Henry J Schmale
 * \date February 1, 2015
 *
 */
class ClientDevice
{
public:
    /** \brief default ctor
     */
    ClientDevice();

    /** \brief Constructs this device fully and completely with all params
     * inited.
     * \param ipAddress the ip address of this device
     * \param name the name of this device
     * \param listeningPort the network port that this device listens on
     * \param channels the number of channels that this device can output on
     */
    ClientDevice(std::string ipAddress,
                 std::string name,
                 int listeningPort,
                 int channels);

    // dtor
    virtual ~ClientDevice();

    // Getters
    /** \return the ip_address string */
    std::string getIPAddress() {return m_ipAddress;}

    /** \return The name of the device */
    std::string getName() {return m_name;}

    /** \return the port this device is listening on */
    int getListeningPort() {return m_listeningPort;}

    /** \return the number of channnels on this device */
    int getChannels() {return m_channels;}

    // Setters
    /** \brief set the current ip address string */
    void setIPAddress(std::string ip) {m_ipAddress = ip;}

    /** \brief set the name of this device */
    void setName(std::string nm) {m_name = nm;}

    /** \brief set the listening port for this device */
    void setListeningPort(int p) {m_listeningPort = p;}

    /** \brief set the number of output channels on this device */
    void setChannels(int c) { m_channels = c;}

    // Primary Functions
    /** \brief updates the socket connection */
    void updateConnection();

    /** \brief sets the show to play
     *
     * \param show The show to send to the client
     *
     * Then launches a thread to send the show over the socket.
     */
    void setShowToSend(std::string show);
protected:
private:
    // Member Variables
    std::string m_ipAddress;  //!< The ip address of this device
    std::string m_name;
    std::string m_show;
    int m_listeningPort;
    int m_channels;
    sf::TcpSocket m_socket;
    sf::Thread m_thread;

    // Private member functions

    /** \brief this the thread entry point to send the show by using the
     * resend feature of the TCP protocal.
     */
    void sendShow();
};

#endif // CLIENTDEVICE_H
