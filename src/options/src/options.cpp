
#include "options.hpp"

#include <boost/program_options.hpp>
#include <cstdlib>
#include <iostream>

using namespace boost::program_options;

auto ExecutionType::serial() -> ExecutionType
{
    return ExecutionType(Type::Serial, 0);
}

auto ExecutionType::parallel(const int numThreads) -> ExecutionType
{
    return ExecutionType(Type::Parallel, numThreads);
}

auto ExecutionType::type() const -> Type
{
    return mType;
}

auto ExecutionType::numThreads() const -> int
{
    return mNumThreads;
}

ExecutionType::ExecutionType(const Type type, const int numThreads) :
    mType(type), mNumThreads(numThreads)
{
}

Options::Options(const ExecutionType executionType) :
    mExcutionType(executionType)
{
}

auto Options::executionType() const -> ExecutionType
{
    return mExcutionType;
}

static auto do_parse(const int argc, const char* const argv[])
{
    auto options = options_description{"Options"};

    // clang-format off
    options.add_options()
        ("help,h", "Display this help message.")
        ("parallel,p", value<int>(), "Use parallel algorithm with the specified number of threads.");
    // clang-format on

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

    if (parse_error || vm.count("help") > 0)
    {
        const auto program_name = argc >= 1 ? argv[0] : "dna";
        std::cout << "Usage: " << program_name << " [options]\n\n";
        std::cout << options;
        std::exit(EXIT_SUCCESS);
    }

    return vm;
}

auto get_execution_type(const variables_map& vm)
{
    return vm.count("parallel")
        ? ExecutionType::parallel(vm["parallel"].as<int>())
        : ExecutionType::serial();
}

auto parse_options(const int argc, const char* const argv[]) -> Options
{
    const auto vm = do_parse(argc, argv);
    return Options{get_execution_type(vm)};
}
