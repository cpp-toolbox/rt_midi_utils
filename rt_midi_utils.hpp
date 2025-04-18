#ifndef RT_MIDI_UTILS
#define RT_MIDI_UTILS

#include "RtMidi.h"


bool initialize_midi_output(RtMidiOut*& midiout);

// these probably don't have to be public
bool choose_midi_port(RtMidiOut *rtmidi);
RtMidi::Api choose_midi_api();


#endif // RT_MIDI_UTILS
