#ifndef ROSALIND_OPTIONS_H
#define ROSALIND_OPTIONS_H

#include <string>

class ExecutionType
{
public:
    enum class Type
    {
        Serial,
        Parallel
    };

    static auto serial() -> ExecutionType;

    static auto parallel(const int numThreads) -> ExecutionType;

    auto type() const -> Type;
    auto numThreads() const -> int;

private:
    Type mType;
    int mNumThreads;

    ExecutionType(const Type type, const int numThreads);
};

enum class Problem
{
    Dna,
    Rna,
    Revc
};

class Options
{
public:
    Options(
        const ExecutionType executionType,
        const Problem problem,
        std::string filename);

    auto executionType() const -> ExecutionType;
    auto problem() const -> Problem;
    auto filename() const -> std::string;

private:
    ExecutionType mExcutionType;
    Problem mProblem;
    std::string mFilename;
};

auto parseOptions(const int argc, const char* const argv[]) -> Options;

#endif // ROSALIND_OPTIONS_H
