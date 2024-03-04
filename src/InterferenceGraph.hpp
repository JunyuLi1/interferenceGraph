#ifndef __PROJ6_INTERFERENCE_GRAPH__HPP
#define __PROJ6_INTERFERENCE_GRAPH__HPP

#include <stdexcept>
#include <string>
#include <unordered_set>

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
    // Private member variables here.
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
    // TODO: Implement this
    return {};
}

template <typename T>
std::unordered_set<T> InterferenceGraph<T>::vertices() const noexcept {
    // TODO: Implement this
    return {};
}

template <typename T>
unsigned InterferenceGraph<T>::numVertices() const noexcept {
    // TODO: Implement this
    return {};
}

template <typename T>
unsigned InterferenceGraph<T>::numEdges() const noexcept {
    // TODO: Implement this
    return {};
}

template <typename T>
void InterferenceGraph<T>::addEdge(const T &source, const T &destination) {
    // TODO: Implement this
}

template <typename T>
void InterferenceGraph<T>::removeEdge(const T &source, const T &destination) {
    // TODO: Implement this
}

template <typename T>
void InterferenceGraph<T>::addVertex(const T &vertex) {
    // TODO: Implement this
}

template <typename T>
void InterferenceGraph<T>::removeVertex(const T &vertex) {
    // TODO: Implement this
}

template <typename T>
bool InterferenceGraph<T>::interferes(const T &source,
                                      const T &destination) const {
    // TODO: Implement this
    return {};
}

template <typename T>
unsigned InterferenceGraph<T>::degree(const T &vertex) const {
    // TODO: Implement this
    return {};
}

}  // namespace shindler::ics46::project6

#endif
