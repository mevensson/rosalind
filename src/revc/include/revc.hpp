#ifndef ROSALIND_REVC_H
#define ROSALIND_REVC_H

#include <string>

auto revc_ser(const std::string_view& symbols) -> std::string;

auto revc_par(const std::string_view& symbols, int nthreads) -> std::string;

#endif // ROSALIND_REVC_H
