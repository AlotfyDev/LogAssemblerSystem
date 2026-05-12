#include "assembler/communication_context/obligations/ports/contracts/TPort.hpp"
#include "assembler/communication_context/bridge_core/orchestration/TBridge.hpp"

#include <cstddef>
#include <type_traits>

int main()
{
    using namespace assembler::communication_context;

    static_assert(std::is_class<TBridge<12>>::value,
                  "TBridge forwarding header must expose the canonical TBridge template");

    static_assert(sizeof(TBridge<12>) > 0u,
                  "TBridge<12> must be a complete type through the orchestration forwarding header");

    return 0;
}
