#include <iostream>
#include <boost/version.hpp>
#include <boost/asio.hpp>

int main() {
    std::cout << "Boost version: " 
              << BOOST_VERSION / 100000 << "."
              << BOOST_VERSION / 100 % 1000 << "."
              << BOOST_VERSION % 100 << std::endl;

    boost::asio::io_context io;

    std::cout << "Boost.Asio is working" << std::endl;

    return 0;
}