
#include "options.hpp"

#include <algorithm>
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

Options::Options(
    const ExecutionType executionType,
    const Problem problem,
    std::string filename) :
    mExcutionType(executionType),
    mProblem(problem), mFilename(std::move(filename))
{
}

auto Options::executionType() const -> ExecutionType
{
    return mExcutionType;
}

auto Options::problem() const -> Problem
{
    return mProblem;
}

auto Options::filename() const -> std::string
{
    return mFilename;
}

static auto validate(
    boost::any& result,
    const std::vector<std::string>& values,
    Problem* /*unused*/,
    int /*unused*/)
{
    validators::check_first_occurrence(result);

    const auto& string = validators::get_single_string(values);
    if (string == "dna")
    {
        result = Problem::Dna;
    }
    else if (string == "rna")
    {
        result = Problem::Rna;
    }
    else if (string == "revc")
    {
        result = Problem::Revc;
    }
    else
    {
        throw validation_error(validation_error::invalid_option_value);
    }
}

static auto doParse(const int argc, const char* const argv[])
{
    auto options = options_description{"Options"};

    // clang-format off
    options.add_options()
        ("help,h", "Display this help message.")
        ("parallel", value<int>(), "Use parallel algorithm with the specified number of threads.")
        ("problem,p", value<Problem>()->required(), "Select which problem to solve.\n"
                                                    "Valid values are:\n"
                                                    "    dna\n"
                                                    "    rna\n")
        ("filename,f", value<std::string>()->required(), "The input file.");
    // clang-format on

    auto parseError = false;
    auto vm = variables_map{};
    try
    {
        store(parse_command_line(argc, argv, options), vm);
        notify(vm);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << "\n\n";
        parseError = true;
    }

    if (parseError || vm.count("help") > 0)
    {
        const auto programName = argc >= 1 ? argv[0] : "rosalind"; // NOLINT
        std::cout << "Usage: " << programName << " [options]\n\n";
        std::cout << options;
        std::exit(EXIT_SUCCESS);
    }

    return vm;
}

auto getExecutionType(const variables_map& vm)
{
    return vm.count("parallel") > 0
        ? ExecutionType::parallel(vm["parallel"].as<int>())
        : ExecutionType::serial();
}

auto getProblem(const variables_map& vm)
{
    return vm["problem"].as<Problem>();
}

auto getFilename(const variables_map& vm)
{
    return vm["filename"].as<std::string>();
}

auto parseOptions(const int argc, const char* const argv[]) -> Options
{
    const auto vm = doParse(argc, argv);
    return Options{getExecutionType(vm), getProblem(vm), getFilename(vm)};
}
