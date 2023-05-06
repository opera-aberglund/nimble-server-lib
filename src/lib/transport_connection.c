/*---------------------------------------------------------------------------------------------
 *  Copyright (c) Peter Bjorklund. All rights reserved.
 *  Licensed under the MIT License. See LICENSE in the project root for license information.
 *--------------------------------------------------------------------------------------------*/
#include <nimble-server/transport_connection.h>

/// Initializes a transport connection
/// Holds information for a specified connection in the transport
/// @param self
/// @param blobStreamAllocator
/// @param log
void transportConnectionInit(NbdTransportConnection* self, ImprintAllocatorWithFree* blobStreamAllocator, Clog log)
{
    orderedDatagramOutLogicInit(&self->orderedDatagramOutLogic);
    orderedDatagramInLogicInit(&self->orderedDatagramInLogic);

    self->nextBlobStreamOutChannel = 127;
    self->blobStreamOutAllocator = blobStreamAllocator;
    self->log = self->log;
    self->debugCounter = 0;
    self->isUsed = true;
    self->log = log;
    self->noRangesToSendCounter = 0;
    self->nextAuthoritativeStepIdToSend = 0xFFFFFFFF;
    self->phase = NbTransportConnectionPhaseIdle;
    self->blobStreamOutClientRequestId = 0;

    statsIntInit(&self->stepsBehindStats, 60);
}

/// sets the latest authoritative state tick id
/// @param self
/// @param lastAuthoritativeStateTickId
void transportConnectionSetGameStateTickId(NbdTransportConnection* self, StepId lastAuthoritativeStateTickId)
{
    self->phase = NbTransportConnectionPhaseInitialStateDetermined;
    self->nextAuthoritativeStepIdToSend = lastAuthoritativeStateTickId;
}
