#include "include/WildRPCClient.h"

#include <iostream>
#include <array>

namespace WRPC
{
    RPCClient::RPCClient()
    {
    }
    RPCClient::~RPCClient()
    {
    }

    bool RPCClient::test()
    {
        asio::ip::tcp::iostream s;

        // The entire sequence of I/O operations must complete within 60 seconds.
        // If an expiry occurs, the socket is automatically closed and the stream
        // becomes bad.
        s.expires_after(std::chrono::seconds(60));

        // Establish a connection to the server.
        char const* server = "wildsheepstudio.com";
        s.connect(server, "http");
        if (!s)
        {
            std::cout << "Unable to connect: " << s.error().message() << "\n";
            return false;
        }

        char const* arg2 = "/";
        // Send the request. We specify the "Connection: close" header so that the
        // server will close the socket after transmitting the response. This will
        // allow us to treat all data up until the EOF as the content.
        s << "GET " << arg2 << " HTTP/1.0\r\n";
        s << "Host: " << server << "\r\n";
        s << "Accept: */*\r\n";
        s << "Connection: close\r\n\r\n";

        // By default, the stream is tied with itself. This means that the stream
        // automatically flush the buffered output before attempting a read. It is
        // not necessary not explicitly flush the stream at this point.

        // Check that response is OK.
        std::string http_version;
        s >> http_version;
        unsigned int status_code;
        s >> status_code;
        std::string status_message;
        std::getline(s, status_message);
        if (!s || http_version.substr(0, 5) != "HTTP/")
        {
            std::cout << "Invalid response\n";
            return false;
        }
        if (status_code != 200)
        {
            std::cout << "Response returned with status code " << status_code << "\n";
            return false;
        }

        // Process the response headers, which are terminated by a blank line.
        std::string header;
        while (std::getline(s, header) && header != "\r")
            std::cout << header << "\n";
        std::cout << "\n";

        // Write the remaining data to output.
        std::cout << s.rdbuf();
        return true;
    }
} // namespace WRPC
