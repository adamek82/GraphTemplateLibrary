# GraphTemplateLibrary

**Created:** ~15 years ago (circa 2009)

This is a C++ template-based graph data structures and algorithms library, originally implemented with C++98 idioms and the Visual Studio 2008 toolchain.

## Data Structures

- **Node<T>**
  - Stores a value `T name`, visitation flags, previous-pointer for path reconstruction.
  - Adjacency list as `std::list<Arc<T>> neighbors`.

- **Arc<T>**
  - Directed, weighted edge: reference to `Node<T>& destNode` and `int weight`.

- **Graph<T>**
  - Holds `std::vector<Node<T>*> nodes` and a lookup map `std::map<T, Node<T>*> nodeNamesToNodesMap` (O(log N) access).
  - Defines aliases:
    - `Edge = std::pair<Node<T>*, Node<T>*>`
    - `VecListEdges = std::vector<std::list<Edge>>`

- **PriorityQueue<KeyType, DataType>**
  - Binary heap with manual `upheap`/`downheap`, backed by `std::vector<HeapItem>`.
  - Position map `std::map<KeyType,int>` for decrease-key semantics.

## Algorithms

- **Depth-First Search (DFS)** & **Breadth-First Search (BFS)**, with path reconstruction and cycle detection.
- **Dijkstra-like Shortest Path** using the custom priority queue.
- **Prim’s Minimum Spanning Tree** via modified Dijkstra dequeue iterations.
- **Articulation Points** detection (Tarjan’s algorithm variant).
- **Biconnected Components** extraction using an edge stack and low-link logic.
- **Cycle Finding** through timestamped DFS.
- **Topological Sort** (DFS post-order).
- **Strongly Connected Components** using Kosaraju’s algorithm (DFS + transpose).
- **Graph Transpose** generation.
- **Graph I/O**: `ReadGraphFromFile(std::string fileName)`.

## Legacy & Modernization

This code was written back when **C++11 was in its infancy**, so it relies on:

- Raw pointers and manual `new`/`delete`.
- `std::list` instead of `std::vector` for adjacency.
- Explicit iterator types and `typename` prefixes.
- `std::map` rather than hash-based lookups.
- A hand-rolled priority queue.

There’s ample room for improvement by adopting modern C++ (C++17/20):

- Use `std::unordered_map` for O(1) node lookups.
- Replace raw pointers with `std::unique_ptr` or `shared_ptr`.
- Switch adjacency containers to `std::vector` and use range-based `for` loops with `auto`.
- Leverage `std::priority_queue` and heap algorithms from `<algorithm>`.
- Utilize `nullptr`, `auto`, structured bindings, and smart pointers throughout.

Happy refactoring!
