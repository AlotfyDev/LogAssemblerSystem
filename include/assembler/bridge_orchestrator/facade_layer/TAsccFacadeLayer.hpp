#pragma once

#include "assembler/communication_context/facade_layer/common/TAsccComponentId.hpp"
#include "assembler/communication_context/facade_layer/common/TAsccComponentVersion.hpp"
#include "assembler/communication_context/facade_layer/common/TAsccFacadeSurfaceKind.hpp"

#include "assembler/communication_context/facade_layer/administrative/TAsccAdministrativeFacade.hpp"
#include "assembler/communication_context/facade_layer/administrative/TAsccComponentCapabilityCatalog.hpp"
#include "assembler/communication_context/facade_layer/administrative/TAsccComponentDescriptor.hpp"
#include "assembler/communication_context/facade_layer/administrative/TAsccComponentProfileId.hpp"
#include "assembler/communication_context/facade_layer/administrative/TAsccProtocolCatalogView.hpp"

#include "assembler/communication_context/facade_layer/managerial/TAsccComponentAdmission.hpp"
#include "assembler/communication_context/facade_layer/managerial/TAsccComponentReadinessStatus.hpp"
#include "assembler/communication_context/facade_layer/managerial/TAsccManagerialFacade.hpp"
#include "assembler/communication_context/facade_layer/managerial/TAsccManagerialReadinessView.hpp"
#include "assembler/communication_context/facade_layer/managerial/TAsccProtocolAdmissionPolicy.hpp"
#include "assembler/communication_context/facade_layer/managerial/TAsccProtocolReadinessView.hpp"

#include "assembler/communication_context/facade_layer/consuming/TAsccConsumingFacade.hpp"
#include "assembler/communication_context/facade_layer/consuming/TAsccConsumingOperationView.hpp"
#include "assembler/communication_context/facade_layer/consuming/TAsccConsumingResult.hpp"
#include "assembler/communication_context/facade_layer/consuming/TAsccOperationMode.hpp"

namespace assembler::communication_context
{
    inline constexpr bool ASCC_FACADE_LAYER_AVAILABLE = true;
    inline constexpr bool ASCC_PROTOCOL_FACADE_SURFACES_AVAILABLE = true;
}
