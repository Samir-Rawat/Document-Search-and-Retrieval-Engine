# Document-Search-and-Retrieval-Engine


A desktop-based document search engine built using C++ and Qt. It allows users to load directories containing text documents, search their contents using Boolean queries, and view ranked results based on term frequency or TF-IDF.

The project demonstrates the practical application of data structures and algorithms in building a functional search system, including a custom hash table, inverted index, expression tree, heap-based ranking, and Trie-based autocomplete.

## Features

- Load documents from a selected directory.
- Search document contents using Boolean queries (`AND`, `OR`, `NOT`).
- Support parentheses and implicit `AND` between terms.
- Rank search results by term frequency or TF-IDF.
- Provide Trie-based autocomplete suggestions.
- Display matching documents and their ranking scores.
- Support loading different directories without restarting the application.

## Data Structures and Algorithms

- **Hash Table:** Stores indexed terms and their associated document postings using separate chaining.
- **Inverted Index:** Maps terms to the documents in which they appear, along with their frequencies.
- **Expression Tree:** Represents parsed Boolean queries and their operators.
- **Heap Sort:** Used to rank search results in descending order.
- **Trie:** Stores indexed terms and generates autocomplete suggestions.
- **TF-IDF:** Calculates relevance scores based on term frequency and inverse document frequency.

## Supported Query Syntax

The search engine supports the following query operations:

| Operation | Example |
|---|---|
| AND | `harry AND potter` |
| OR | `harry OR voldemort` |
| NOT | `NOT harry` |
| Parentheses | `(harry OR ron) AND hermione` |
| Implicit AND | `harry potter` |

**Operator precedence:** `NOT` > `AND` > `OR`.

Terms separated by spaces are treated as an implicit `AND` operation.

## Technologies Used

- **Language:** C++17
- **GUI Framework:** Qt 6 Widgets
- **Build System:** CMake
- **IDE:** CLion

## Build and Run

### Prerequisites

- C++17 compatible compiler
- CMake
- Qt 6 with Widgets module

### Building from Source

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd <repository-folder>
   ```

2. Create a build directory:
   ```bash
   cmake -B build
   ```

3. Build the project:
   ```bash
   cmake --build build --config Release
   ```

4. Run the generated executable.

### Pre-built Release

A pre-built Windows executable is available in the [Releases](../../releases) section.