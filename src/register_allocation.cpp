#include "register_allocation.hpp"

#include "CSVReader.hpp"
#include "InterferenceGraph.hpp"
#include <vector>
#include <unordered_set>

namespace shindler::ics46::project6 {

// assignRegisters
//
// This is where you implement the register allocation algorithm
// as mentioned in the README. Remember, you must allocate at MOST
// d(G) + 1 registers where d(G) is the maximum degree of the graph G.
// If num_registers is not enough registers to accomodate the passed in
// graph you should return an empty map. You MUST use registers in the
// range [1, num_registers] inclusive.
RegisterAssignment assignRegisters(const std::string &pathToGraph,
                                   int numRegisters) noexcept {
    InterferenceGraph<Variable> igraph = CSVReader::load(pathToGraph);
    std::vector<Variable> sortednodes;
    for(const auto& items: igraph.vertices()){
        sortednodes.push_back(items);
    }
    MergeSort(sortednodes, 0, sortednodes.size()-1, igraph);
    int maxregisters = igraph.degree(sortednodes[0]) + 1;
    if(numRegisters<maxregisters)
    {
        return {};
    }
    RegisterAssignment result;
    for(const auto&vertex: sortednodes)
    {
        std::unordered_set<int>usedregisters;
        for(const auto&nextvertexs: igraph.neighbors(vertex))
        {
            if (result.find(nextvertexs) != result.end()) {
                usedregisters.insert(result[nextvertexs]);
            }
        }
        for (int reg = 1; reg <= numRegisters; ++reg) {
            if (usedregisters.find(reg) == usedregisters.end()) {
                result[vertex] = reg;
                break;
            }
        }
    }
    return result;
}

void MergeSort(std::vector<Variable> & numbers, unsigned i, unsigned k, InterferenceGraph<Variable> & igraph)
{
    unsigned j = 0;
    if (i < k){
        j = (i + k) / 2;
        MergeSort(numbers, i, j,igraph);
        MergeSort(numbers, j + 1, k,igraph);
        Merge(numbers, i, j, k,igraph);
    }
}

void Merge(std::vector<Variable> & numbers, unsigned i, unsigned j, unsigned k, InterferenceGraph<Variable> & igraph)
{
    unsigned merged_size = k - i + 1;
    unsigned merge_pos = 0;
    unsigned leftpos = 0;
    unsigned rightpos = 0;
    std::vector<Variable> merged_vertex(merged_size);
    leftpos = i;
    rightpos = j + 1;
    while(leftpos <= j && rightpos <= k){
        if (igraph.degree(numbers[leftpos]) >= igraph.degree(numbers[rightpos])){
            merged_vertex[merge_pos] = numbers[leftpos];
            leftpos++;
        }
        else{
            merged_vertex[merge_pos] = numbers[rightpos];
            rightpos++;
        }
        merge_pos++;
    }
    while (leftpos <= j){
        merged_vertex[merge_pos] = numbers[leftpos];
        leftpos++;
        merge_pos++;
    }
    while (rightpos <= k){
        merged_vertex[merge_pos] = numbers[rightpos];
        rightpos++;
        merge_pos++;
    }
    for (merge_pos = 0; merge_pos < merged_size; merge_pos++){
        numbers[i + merge_pos] = merged_vertex[merge_pos];
    }
}

}  // namespace shindler::ics46::project6
