# Park Crescent Network

PAN: 0x104f
Channel: 14, 0x0E.

|UUID|Device|
|-|-|
|00 0b 6b aa 20 08 bc f8<br/>0x0000|WistroN ZigBee Coordinator/<br/>Celluar Gateway|
|98 b1 77 ff ff 02 17 14<br/>0x0ad9|Landis+Ghyr electrcity meter|
|98 b1 77 ff ff 01 2f ff|Landis+Ghyr gas meter|
|0c a2 f4 00 00 7f c6 36<br/>0x2742?|Chameleon IHD|

# ZigBee Association - Base Device Behavior Specification
## Page 46
- This seems to be "first time" network association
- NLME-NETWORK-DISCOVERY request
- A suitable network has...
  - NetworkCount
  - NetworkDescriptor
  - But what is suitable?
- We might expect an NLME-JOIN next.

## Debugging
- Built `sampleGW` app
- IHD sends beacon requests
- TLSR8258 responds with a beacon
- IHD ignores the beacon

> - Could this be because the PAN is wrong?  Try setting this to match the power network?

### Investigation - IHD Beaconing
- Turn off the IHD
- Take it away from the network
- Turn on the IHD and wait for it to indicate "lost connection"
- Bring it back towards the network
- Watch packets are this takes place
- `27pc002.pcapng` captured around 10:20, 2023/01/15.

#### Outcomes
- [125] IHD sends a _discover route_ to the coordinator
- [147] Coordinator sends a discover route back
- The IHD asks for data from the **_electricity meter!_**
  - [2480] Before this, the electricity meter had broadcast a _Discover Route_ message
  - [2482] The IHD sends the electricity meter an _Acknowledge Request_ message
- [2514] IHD starts beaconing around 10:18:15
- [2519] Coordinator (WistronN...) responds with a beacon frame with _Superframe Specification_, _Association Permit_ `false`
- [2520] IHD sends an _Acknowledge Request_ to the coordinator
- [2523] Coordinator sends a _Discover Route_ to the IHD
  - This may be a _red-herring_ as the IHD doesn't seem to respond to this
  > Suspect that the devices are configured to send regular beacons and these are not _interesting_
- Coordinator immediately starts sending data to the IHD

> Question:/ Is the _Discover Route_ the only attempt the devices make to establish a connection?  Seems odd that devices don't try and formally establish a connection but perhaps they already believe that one exists.
>
> If that is so, how do we issue a challenge?

### Investigation - Preinstall code
- Configured TLSR8258 as normal
- Also used _DBD, , _preistall code_ to repload the IHD's MAC address and `0x00...ff` as the secret
- `respond4.pcapng` captured around 12:34 2023/01/15.

#### Outcomes
- [1] onwards [90] The TLSR8258 is trying to send some sort of encrypted data, apparently to a router? `0xfffc`?
  - This is before the MAC address of the IHD has been configured so we can probably ignore these
- [5] and [78]; TLSR8258 sends data to `0xffff`; again not to the IHD so we should ignore this
- _discover route_ requests were found towards `0xfffc` ([1]) and `0xffff` but not towards the IHD
- No frames were directed towards the IHD

> Conclusion: using _preinstall code_ appears to have caused transmissions but not of _discover routes_

### Investigation - Fake Coordinator Address
- Make the board use the same MAC address as the Zigbee hub!
- Write address to 0x76000 address (TLSR8258 is the 512kB variety)

> N.B. Code has to be entered "backwards" for some reason!

#### Outcomes
- TLSR8258 shows sending messages with EPID equal to the WistroN MAC address
- IHD attempts to rejoin
- TLSR8258 sends success response to the join but then nothing happens.

> Do we need to pre-install a code for the IHD and see what happens?