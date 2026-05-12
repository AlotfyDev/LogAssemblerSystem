#include "cme_benchmark_common.hpp"
#include "assembler/circulation_mechanism/circulation_mechanism_container_registry.hpp"

using namespace assembler::circulation_mechanism;

struct BenchContainer { std::uint64_t value{0}; };

int main() {
    TContainerRegistry<BenchContainer, 1024> registry{};
    registry.initialize();
    for (std::uint64_t i = 1; i <= 1024; ++i) {
        registry.assign(TContainerRegistryIndex::from_raw(i), BenchContainer{i});
    }
    volatile std::uint64_t sink = 0;
    auto result = cme_bench::run("registry_resolution", 200000, [&](std::uint64_t i) {
        const auto index = TContainerRegistryIndex::from_raw((i % 1024) + 1);
        auto* item = registry.try_get(index);
        if (item) sink += item->value;
    });
    result.print();
    return sink == 0 ? 1 : 0;
}
