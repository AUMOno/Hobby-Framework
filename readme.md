Guides:
https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa

Resources:
https://en.wikipedia.org/wiki/OSI_model
https://www.rfc-editor.org/retrieve
https://en.wikipedia.org/wiki/List_of_RFCs

# Address families:

    AF_INET (IP)
    AF_INET6 (IPv6)
    AF_UNIX (local channel, similar to pipes)
    AF_ISO (ISO protocols)
    AF_NS (Xerox Network Systems protocols)

# OSI:

    The Open Systems Interconnection model (OSI model) is a conceptual model that characterises and standardises the communication functions of a telecommunication or computing system without regard to its underlying internal structure and technology. Its goal is the interoperability of diverse communication systems with standard communication protocols.

# Standardized ports:

    80=http
    443=https

# Transport Layer:

    The transport layer provides the functional and procedural means of transferring variable-length data sequences from a source to a destination host, while maintaining the quality of service functions.

    The transport layer may control the reliability of a given link through flow control, segmentation/desegmentation, and error control. Some protocols are state- and connection-oriented. This means that the transport layer can keep track of the segments and retransmit those that fail delivery. The transport layer may also provide the acknowledgement of the successful data transmission and sends the next data if no errors occurred. The transport layer creates segments out of the message received from the application layer. Segmentation is the process of dividing a long message into smaller messages.

    Reliability, however, is not a strict requirement within the transport layer. Protocols like UDP, for example, are used in applications that are willing to accept some packet loss, reordering, errors or duplication. Streaming media, real-time multiplayer games and voice over IP (VoIP) are examples of applications in which loss of packets is not usually a fatal problem.

# Types:

    SOCK_STREAM (virtual circuit service)
    SOCK_DGRAM (datagram service)
    SOCK_RAW (direct IP service)
