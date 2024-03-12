#ifndef __PROJ6_INTERFERENCE_GRAPH__HPP
#define __PROJ6_INTERFERENCE_GRAPH__HPP

#include <stdexcept>
#include <string>
#include <unordered_set>
#include <unordered_map>


namespace shindler::ics46::project6 {

class UnknownVertexException : public std::runtime_error {
   public:
    explicit UnknownVertexException(const std::string &vertex)
        : std::runtime_error("Unkown vertex " + vertex) {}
};

class UnknownEdgeException : public std::runtime_error {
   public:
    UnknownEdgeException(const std::string &source,
                         const std::string &destination)
        : std::runtime_error("Unknown edge " + source + " - " + destination) {}
};

// InterferenceGraph
//
// This is a class representing an interference graph
// as described in "Part 1: Interference Graph" of the README.md
// file. Though this class is templated, because of the usage of exceptions
// UnknownVertexException and UnknownEdgeException it will
// ONLY be tested with strings.
template <typename T>
class InterferenceGraph {
   public:
    // Custom type used to represent edges. This is mainly
    // used in the utility function for reading and writing
    // the graph structure to/from files. You don't need to use it.
    using EdgeTy = std::pair<T, T>;

    InterferenceGraph();

    // You DO NOT need to implement these
    InterferenceGraph(const InterferenceGraph &) = delete;
    InterferenceGraph(InterferenceGraph &&) = default;
    InterferenceGraph &operator=(const InterferenceGraph &) = delete;
    InterferenceGraph &operator=(InterferenceGraph &&) = default;

    ~InterferenceGraph();

    void addEdge(const T &source, const T &destination);

    void addVertex(const T &vertex);

    void removeEdge(const T &source, const T &destination);

    void removeVertex(const T &vertex);

    [[nodiscard]] std::unordered_set<T> vertices() const noexcept;

    [[nodiscard]] std::unordered_set<T> neighbors(const T &vertex) const;

    [[nodiscard]] unsigned numVertices() const noexcept;

    [[nodiscard]] unsigned numEdges() const noexcept;

    [[nodiscard]] bool interferes(const T &source, const T &destination) const;

    [[nodiscard]] unsigned degree(const T &vertex) const;

   private:
    std::unordered_map<T, std::unordered_set<T>> graphNodes;
    unsigned numberedge = 0;
};

template <typename T>
InterferenceGraph<T>::InterferenceGraph() {
    // TODO: Implement this
}

template <typename T>
InterferenceGraph<T>::~InterferenceGraph() {
    // TODO: Implement this
}

template <typename T>
std::unordered_set<T> InterferenceGraph<T>::neighbors(const T &vertex) const {
    if (graphNodes.count(vertex) == 0){
        throw UnknownVertexException(vertex);
    }
    return graphNodes.at(vertex);
}

template <typename T>
std::unordered_set<T> InterferenceGraph<T>::vertices() const noexcept {
    std::unordered_set<T> result;
    for(const auto & pair:graphNodes)
    {
        result.insert(pair.first);
    }
    return result;
}

template <typename T>
unsigned InterferenceGraph<T>::numVertices() const noexcept {
    return graphNodes.size();
}

template <typename T>
unsigned InterferenceGraph<T>::numEdges() const noexcept {
    return numberedge;
}

template <typename T>
void InterferenceGraph<T>::addEdge(const T &source, const T &destination) {
    if (graphNodes.count(source) == 0){
        throw UnknownVertexException(source);
    }
    if(graphNodes.count(destination) == 0){
        throw UnknownVertexException(destination);
    }
    graphNodes[source].insert(destination);
    graphNodes[destination].insert(source);
    numberedge++;
}

template <typename T>
void InterferenceGraph<T>::removeEdge(const T &source, const T &destination) {
    if (graphNodes.count(source) == 0){
        throw UnknownVertexException(source);
    }
    if(graphNodes.count(destination) == 0){
        throw UnknownVertexException(destination);
    }
    if (graphNodes[source].count(destination) == 0){
        throw UnknownEdgeException(source, destination);
    }
    graphNodes[source].erase(destination);
    graphNodes[destination].erase(source);
    numberedge--;
}

template <typename T>
void InterferenceGraph<T>::addVertex(const T &vertex) {
    graphNodes[vertex];
}

template <typename T>
void InterferenceGraph<T>::removeVertex(const T &vertex) {
    if (graphNodes.count(vertex) == 0){
        throw UnknownVertexException(vertex);
    }
    graphNodes.erase(vertex);
    for(auto& pairs: graphNodes)
    {
        if(pairs.second.find(vertex)!=pairs.second.end())
        {
            pairs.second.erase(vertex);
            numberedge--; //here
        }
    }
}

template <typename T>
bool InterferenceGraph<T>::interferes(const T &source,
                                      const T &destination) const {
    if (graphNodes.count(source) == 0){
        throw UnknownVertexException(source);
    }
    if(graphNodes.count(destination) == 0){
        throw UnknownVertexException(destination);
    }
    return graphNodes.at(source).count(destination) == 1;
}

template <typename T>
unsigned InterferenceGraph<T>::degree(const T &vertex) const {
     if (graphNodes.count(vertex) == 0){
        throw UnknownVertexException(vertex);
    }
    return graphNodes.at(vertex).size();
}

}  // namespace shindler::ics46::project6

#endif
