#pragma once
/*
    circulation_mechanism_read_side_adapter_contracts.hpp

    Delivery:
        CME-READSIDE-PROD-W04 — Addon And Receiver Adapter Contracts
*/
#include "read_side/adapter_contracts/common/TReadSideAdapterContractId.hpp"
#include "read_side/adapter_contracts/common/TReadSideAdapterKind.hpp"
#include "read_side/adapter_contracts/common/TReadSideAdapterStatus.hpp"
#include "read_side/adapter_contracts/common/TReadSideAdapterCapabilityKind.hpp"
#include "read_side/adapter_contracts/common/TReadSideAdapterCapabilitySet.hpp"
#include "read_side/adapter_contracts/common/TReadSidePayloadRef.hpp"
#include "read_side/adapter_contracts/common/TReadSideAdapterInvocationStatus.hpp"
#include "read_side/adapter_contracts/common/TReadSideAdapterContract.hpp"
#include "read_side/adapter_contracts/in_process_receiver/TInProcessReceiverAdapterContract.hpp"
#include "read_side/adapter_contracts/database_adapter/TDatabaseAdapterContract.hpp"
#include "read_side/adapter_contracts/file_sink_adapter/TFileSinkAdapterContract.hpp"
#include "read_side/adapter_contracts/open_telemetry_adapter/TOpenTelemetryAdapterContract.hpp"
#include "read_side/adapter_contracts/diagnostic_sink_adapter/TDiagnosticSinkAdapterContract.hpp"
#include "read_side/adapter_contracts/thin_c_abi_adapter/TThinCAbiAdapterContract.hpp"
#include "read_side/adapter_contracts/views/TReadSideAdapterContractView.hpp"
#include "read_side/adapter_contracts/reports/TReadSideAdapterIssueKind.hpp"
#include "read_side/adapter_contracts/reports/TReadSideAdapterReport.hpp"
