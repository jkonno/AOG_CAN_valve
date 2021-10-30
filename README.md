# AOG_CAN_valve
AOG ino with support for ISOBUS CAN valve commands

This file is to be used with a standard arduino nano and an MCP board for CAN

Everything else works as in standard V5 AOG, except you can define two options:

1. Valve control via CAN using ISOBUS flow commands. This works with every type of CAN valve using the standard flow commands, e.g. Danfoss PVEA-CI, or you can directly drive a spool valve in the tractor hydraulics, for example.

2. WAS via J1939, this is configured for Danfoss DST X510 sensor, but the code is easy to adapt to any sensor utilizing the J1939 protocol. Note, that the steering angle calculation needs to happen inside the WAS function, as the WAS is not queried, but there's a new WAS message every 100 ms or so in the bus, so the WAS reading is event driven.
