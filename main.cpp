#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class Trie {
    // Index 0 is the root; 0 also denotes a missing child/sibling.
    struct Node {
        std::uint32_t first_child = 0;
        std::uint32_t next_sibling = 0;
        std::uint32_t count = 0;
        char letter = '\0';
    };

    std::vector<Node> nodes;

    std::uint32_t child(std::uint32_t parent, char letter) const {
        for (auto v = nodes[parent].first_child; v != 0;
             v = nodes[v].next_sibling) {
            if (nodes[v].letter == letter) return v;
        }
        return 0;
    }

public:
    explicit Trie(int operations) {
        // At most 30 new nodes per operation; avoid vector reallocations.
        nodes.reserve(static_cast<std::size_t>(operations) * 30 + 1);
        nodes.emplace_back();
    }

    void add(const std::string& word) {
        std::uint32_t u = 0;
        for (char letter : word) {
            auto v = child(u, letter);
            if (v == 0) {
                v = static_cast<std::uint32_t>(nodes.size());
                Node node;
                node.letter = letter;
                node.next_sibling = nodes[u].first_child;
                nodes.push_back(node);
                nodes[u].first_child = v;
            }
            u = v;
            ++nodes[u].count;
        }
    }

    std::uint32_t find(const std::string& prefix) const {
        std::uint32_t u = 0;
        for (char letter : prefix) {
            u = child(u, letter);
            if (u == 0) return 0;
        }
        return nodes[u].count;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    if (!(std::cin >> n)) return 0;
    Trie contacts(n);
    for (int i = 0; i < n; ++i) {
        std::string operation, word;
        std::cin >> operation >> word;
        if (operation == "add") contacts.add(word);
        else if (operation == "find") std::cout << contacts.find(word) << '\n';
    }
}
