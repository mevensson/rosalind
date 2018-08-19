#ifndef ROSALIND_RNA_H
#define ROSALIND_RNA_H

#include <string>

auto rna_ser(const std::string_view& symbols) -> std::string;

auto rna_par(const std::string_view& symbols, const int nthreads)
    -> std::string;

#endif // ROSALIND_RNA_H
