# distance_trigger

Basic rx/tx pair for triggering an amateur rocket. 
Uses 433MHz Rx/Tx pair for comms, with led and buzzer indicators of state. 
The triggering is done by shorting a fuse on a 12V battery using a relay

Made using VSCode and PlatformIO

Code runs protothreads concurrently for better synchronization between led, buzzer and sensors.

Protothread lib by Adam Dunkels at http://dunkels.com/adam/pt/index.html (as of 08/01/2022)

VirtualWire lib by song940 at https://github.com/song940/VirtualWire (as of 08/01/2022)

States:
- Idle - No connection, not armed (no fuse installed), no go
- Waiting - Connected (to remote), not armed (no fuse installed), no go
- Armed - Connected (to remote), armed (fuse installed), no go
- Warning - Connected (to remote), armed (fuse installed), go signal received. Transitions automatically to igniting after a period
- Igniting - Connected (to remote), armed (fuse installed), go signal received. Attempting to light fuse



DISCLAIMER: I made it for my personal pyro uses and published only to show off my sexy protothreads. There is no license, i'm responsible for nothing. It will never be updated. Don't use it. Why are you even here? We all know you won't use my messy code either way.
