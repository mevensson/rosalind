#ifndef ROSALIND_OPTIONS_H
#define ROSALIND_OPTIONS_H

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

class Options
{
public:
    Options(const ExecutionType executionType);

    auto executionType() const -> ExecutionType;

private:
    ExecutionType mExcutionType;
};

auto parse_options(const int argc, const char* const argv[]) -> Options;

#endif // ROSALIND_OPTIONS_H
