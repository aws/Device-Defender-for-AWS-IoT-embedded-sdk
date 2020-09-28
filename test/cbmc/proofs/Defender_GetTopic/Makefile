# Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
# SPDX-License-Identifier: Apache-2.0

HARNESS_ENTRY=harness
HARNESS_FILE=Defender_GetTopic_harness

# This should be a unique identifier for this proof, and will appear on the
# Litani dashboard. It can be human-readable and contain spaces if you wish.
PROOF_UID = Defender_GetTopic

DEFINES +=
INCLUDES +=

REMOVE_FUNCTION_BODY +=
UNWINDSET +=

PROOF_SOURCES += $(PROOFDIR)/$(HARNESS_FILE).c
PROOF_SOURCES += $(SRCDIR)/test/cbmc/sources/defender_cbmc_state.c
PROJECT_SOURCES += $(SRCDIR)/source/defender.c

include ../Makefile.common