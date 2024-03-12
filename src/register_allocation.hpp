#ifndef __PROJ6_REGISTER_ALLOCATION__HPP
#define __PROJ6_REGISTER_ALLOCATION__HPP

#include <string>
#include <unordered_map>
#include <vector>
#include "InterferenceGraph.hpp"

namespace shindler::ics46::project6 {

using Variable = std::string;
using Register = int;
using RegisterAssignment = std::unordered_map<Variable, Register>;

RegisterAssignment assignRegisters(const std::string &pathToGraph,
                                   int numRegisters) noexcept;

void MergeSort(std::vector<Variable> & numbers, unsigned i, unsigned k, InterferenceGraph<Variable> & igraph);
void Merge(std::vector<Variable> & numbers, unsigned i, unsigned j, unsigned k, InterferenceGraph<Variable> & igraph);
};  // namespace shindler::ics46::project6

#endif
