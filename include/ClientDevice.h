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
class ClientDevice {
public:
    /** \brief the default ctor, with params inited to default values
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

    /** \brief The Copy Ctor
     * \param cdSrc A ClientDevice instance to copy from.
     */
    ClientDevice(const ClientDevice &cdSrc);
    // dtor
    virtual ~ClientDevice();

    // Getters
    /** \return the ip_address string
     */
    std::string getIPAddress() {
        return m_ipAddress;
    }

    /** \return The name of the device
     */
    std::string getName() {
        return m_name;
    }

    /** \return the port this device is listening on
     */
    int getListeningPort() {
        return m_listeningPort;
    }

    /** \return the number of channnels on this device
     */
    int getChannels() {
        return m_channels;
    }

    // Setters
    /** \brief set the current ip address string
     */
    void setIPAddress(std::string ip) {
        m_ipAddress = ip;
    }

    /** \brief set the name of this device
     */
    void setName(std::string nm) {
        m_name = nm;
    }

    /** \brief set the listening port for this device
     */
    void setListeningPort(int p) {
        m_listeningPort = p;
    }

    /** \brief set the number of output channels on this device
     */
    void setChannels(int c) {
        m_channels = c;
    }

    // ==================================================================
    // Regular Member Functions

    /** \brief updates the socket connection
     * \todo Implement ME!
     *
     * This function should be called after using any of the setter methods.
     */
    void updateConnection();

    /** \brief sets the show to play
     *
     * \param show The show to send to the client
     *
     * Then launches a thread to send the show over the socket.
     */
    void setShowToSend(std::string show);

    /** \brief begins the show
     */
    void beginShow();

    /** \brief pings the client to see if it's still there
     * \return true if the ping was successful otherwise false.
     *
     * It makes a connection then disconnects. If this was successful it returns
     * true.
     */
    bool ping();


protected:
private:
    // Member Variables
    std::string m_ipAddress;  //!< The ip address of this device
    std::string m_name;       //!< The name of this device
    std::string m_show;       //!< The current show to be playing
    int m_listeningPort;      //!< The port that this device listens on
    int m_channels;           //!< Number of Channels this device can output on
    sf::TcpSocket m_socket;   //!< Socket to send data over
    sf::Thread m_thread;      //!< Thread for sending data

    // Constants
    const int SHOW_CHUNK_SZ = 128; //!< Size of show chuncks to send to client
    const int INSTR_PER_SEC = 10;  //!< How many INSTR the client runs per sec
    const int BYTE_INSTRUCT = 8;   //!< How many bytes comprise 1 insturction

    // Private member functions

    /** \brief this the thread entry point to send the show by using the
     * resend feature of the TCP protocal.
     */
    void sendShow();
};

#endif // CLIENTDEVICE_H
