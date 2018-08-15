#include "dna.hpp"

#include <boost/program_options.hpp>
#include <cstdlib>
#include <iostream>

using namespace boost::program_options;

static auto parse_options(const int argc, const char* const argv[])
{
    auto options = options_description{"Options"};
    options.add_options()("help,h", "Display this help message.");

    auto parse_error = false;
    auto vm = variables_map{};
    try
    {
        store(parse_command_line(argc, argv, options), vm);
        notify(vm);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << "\n\n";
        parse_error = true;
    }

    if (argc <= 1 || parse_error || vm.count("help"))
    {
        auto program_name = argc >= 1 ? argv[0] : "dna";
        std::cout << "Usage: " << program_name << " [options]\n\n";
        std::cout << options;
        std::exit(EXIT_SUCCESS);
    }
}

static auto readAllInput()
{
    const std::istreambuf_iterator<char> begin(std::cin);
    const std::istreambuf_iterator<char> end;
    const std::string input(begin, end);
    return input;
}

int main(const int argc, const char* const argv[])
{
    parse_options(argc, argv);

    auto input = readAllInput();
    auto [a, c, g, t] = dna(input);
    std::cout << a << " " << c << " " << g << " " << t << "\n";

    return 0;
}
