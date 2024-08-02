#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <chrono>
#include "message.pb.h"

using boost::asio::ip::tcp;

void send_message(boost::asio::io_context& io_context, const std::string& server, const std::string& port) {
    // Create a Person object and populate it
    Person person;
    person.set_name("Omer Faruk Okuyan");
    person.set_id(34);
    person.set_email("omerokuyan@taurob.com");

    // Serialize the object to a byte string
    std::string serialized_data;
    person.SerializeToString(&serialized_data);

    // Resolve the server address and port
    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(server, port);

    // Create and connect the socket
    tcp::socket socket(io_context);
    boost::asio::connect(socket, endpoints);

    // Send the serialized data
    boost::asio::write(socket, boost::asio::buffer(serialized_data));

    std::cout << "Data sent" << std::endl;
}

void handle_client(tcp::socket socket) {
    try {
        std::array<char, 1024> buf;
        boost::system::error_code error;

        size_t len = socket.read_some(boost::asio::buffer(buf), error);
        if (error == boost::asio::error::eof) {
            return; // Connection closed cleanly by peer.
        } else if (error) {
            throw boost::system::system_error(error); // Some other error.
        }

        // Deserialize the data
        Person person;
        person.ParseFromArray(buf.data(), len);

        // Print the structured data
        std::cout << "Received data:" << std::endl;
        std::cout << "Name: " << person.name() << std::endl;
        std::cout << "ID: " << person.id() << std::endl;
        std::cout << "Email: " << person.email() << std::endl;
    } catch (std::exception& e) {
        std::cerr << "Exception in thread: " << e.what() << std::endl;
    }
}

void start_receiver(boost::asio::io_context& io_context, const std::string& port) {
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), std::stoi(port)));

    std::cout << "Receiver is running on port " << port << std::endl;

    while (true) {
        tcp::socket socket(io_context);
        acceptor.accept(socket);
        std::thread(handle_client, std::move(socket)).detach();
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <sender|receiver>" << std::endl;
        return 1;
    }

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    try {
        boost::asio::io_context io_context;

        const std::string server = "127.0.0.1";
        const std::string port = "5005";

        if (std::string(argv[1]) == "sender") {
            while (true) {
                send_message(io_context, server, port);
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        } else if (std::string(argv[1]) == "receiver") {
            start_receiver(io_context, port);
        } else {
            std::cerr << "Invalid argument: " << argv[1] << std::endl;
            return 1;
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
