#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include <chrono>
#include "message.pb.h"

using boost::asio::ip::tcp;

int sender_counter = 0;
int receiver_counter = 0;


void send_messages(boost::asio::io_context& io_context, const std::string& server, const std::string& port) {
    for (int i = 0; i < 100000; ++i) {

        Person person;
        person.set_name("Omer Faruk Okuyan");
        person.set_id(i + 1);  // Unique ID for each message
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
        sender_counter++;
        //wait 10 microseconds
        std::this_thread::sleep_for(std::chrono::microseconds(1)); // hz: 1mhz
    }
}

void handle_client(tcp::socket socket) {
    try {
        std::array<char, 1024> buf;
        boost::system::error_code error;

        size_t len = socket.read_some(boost::asio::buffer(buf), error);
        if (error == boost::asio::error::eof) {
            return;
        } else if (error) {
            throw boost::system::system_error(error); // Some other error.
        }

        // Deserialize the data
        Person person;
        person.ParseFromArray(buf.data(), len);
        receiver_counter++;

        std::cout << "Received message ID: " << person.id() << std::endl;
    } catch (std::exception& e) {
        std::cerr << "Exception in thread: " << e.what() << std::endl;
    }
}

void start_receiver(boost::asio::io_context& io_context, const std::string& port) {
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), std::stoi(port)));

    std::cout << "Receiver is running on port " << port << std::endl;

    for (int i = 0; i < 100000; ++i) {
        tcp::socket socket(io_context);
        acceptor.accept(socket);
        handle_client(std::move(socket));
    }
}

int main(int argc, char* argv[]) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    try {
        boost::asio::io_context io_context;

        const std::string server = "127.0.0.1";
        const std::string port = "5005";

        std::thread receiver_thread(start_receiver, std::ref(io_context), port);
        std::this_thread::sleep_for(std::chrono::seconds(1));  // Give the receiver a moment to start
        std::thread sender_thread(send_messages, std::ref(io_context), server, port);

        sender_thread.join();
        receiver_thread.join();

        if (sender_counter == receiver_counter) {
            std::cout << "Test passed. All messages were sent and received correctly." << std::endl;
        } else {
            std::cout << "Test failed. Sender count: " << sender_counter << ", Receiver count: " << receiver_counter << std::endl;
        }
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
