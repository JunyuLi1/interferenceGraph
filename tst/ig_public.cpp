#include <CSVReader.hpp>
#include <IGWriter.hpp>
#include <InterferenceGraph.hpp>
#include <catch2/catch_amalgamated.hpp>

namespace {

namespace proj6 = shindler::ics46::project6;

const std::string &GRAPH_DIR = std::string("tst/graphs/");

TEST_CASE("SimpleAddEdgesAndVertices", "[Required][IG]") {
    const auto &GRAPH = GRAPH_DIR + "simple.csv";
    /// autograder/git-repo/student-execution-files/tests/
    const proj6::InterferenceGraph<proj6::Variable> &igraph =
        proj6::CSVReader::load(GRAPH);

    REQUIRE(igraph.numEdges() == 3);
    REQUIRE(igraph.numVertices() == 3);
}

TEST_CASE("Neighbors", "[Required][IG]") {
    const auto &GRAPH = GRAPH_DIR + "simple.csv";

    const proj6::InterferenceGraph<proj6::Variable> &igraph =
        proj6::CSVReader::load(GRAPH);
    const std::unordered_set<proj6::Variable> &expected_neighbors = {"y", "z"};

    REQUIRE(igraph.neighbors("x") == expected_neighbors);
}

TEST_CASE("NeighborsThrowsWhenEmptyOrNonexistent", "[IG]") {
    const auto &GRAPH = GRAPH_DIR + "simple.csv";

    const proj6::InterferenceGraph<proj6::Variable> &igraph =
        proj6::CSVReader::load(GRAPH);

    REQUIRE_THROWS_AS(igraph.neighbors("m"), shindler::ics46::project6::UnknownVertexException);

    const proj6::InterferenceGraph<proj6::Variable> igraph2;
    REQUIRE_THROWS_AS(igraph2.neighbors("a"), shindler::ics46::project6::UnknownVertexException);

}

TEST_CASE("BigBipartiteNumVE", "[IG]") {
    const auto &GRAPH = GRAPH_DIR + "big_bipartite.csv";
    /// autograder/git-repo/student-execution-files/tests/
    const proj6::InterferenceGraph<proj6::Variable> &igraph =
        proj6::CSVReader::load(GRAPH);

    REQUIRE(igraph.numEdges() == 8);
    REQUIRE(igraph.numVertices() == 6);
}

TEST_CASE("BigBipartiteRemoveEdge", "[IG]") {
    const auto &GRAPH = GRAPH_DIR + "big_bipartite.csv";
    /// autograder/git-repo/student-execution-files/tests/
    proj6::InterferenceGraph<proj6::Variable> igraph =
        proj6::CSVReader::load(GRAPH);

    REQUIRE(igraph.numEdges() == 8);
    REQUIRE(igraph.numVertices() == 6);

    igraph.removeEdge("a", "x");
    REQUIRE(igraph.numEdges() == 7);
    REQUIRE(igraph.numVertices() == 6);
}

TEST_CASE("BigBipartiteRemoveVertex", "[IG]") {
    const auto &GRAPH = GRAPH_DIR + "big_bipartite.csv";
    /// autograder/git-repo/student-execution-files/tests/
    proj6::InterferenceGraph<proj6::Variable> igraph =
        proj6::CSVReader::load(GRAPH);

    REQUIRE(igraph.numEdges() == 8);
    REQUIRE(igraph.numVertices() == 6);

    igraph.removeVertex("a");
   // igraph.printGraph();
    REQUIRE(igraph.numEdges() == 6);
    REQUIRE(igraph.numVertices() == 5);
}

TEST_CASE("InterferenceCheck", "[Optional][IG]") {
    const auto &GRAPH = GRAPH_DIR + "simple.csv";

    const proj6::InterferenceGraph<proj6::Variable> &igraph =
        proj6::CSVReader::load(GRAPH);

    REQUIRE(igraph.interferes("y", "z"));
}

TEST_CASE("Complete1KRuntimeTest", "[ig-complete_1000]") {
const auto &GRAPH = GRAPH_DIR + "complete_1000.csv";
proj6::InterferenceGraph<proj6::Variable> igraph =
    proj6::CSVReader::load(GRAPH);

    REQUIRE(igraph.numVertices() == 1000);
    REQUIRE(igraph.numEdges() == (1000*999)/2);
}

}  // namespace
