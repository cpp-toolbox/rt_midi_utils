#include "rt_midi_utils.hpp"




bool initialize_midi_output(RtMidiOut*& midiout) {
  try {
    midiout = new RtMidiOut(choose_midi_api());
  } catch (RtMidiError &error) {
    error.printMessage();
    return false;
  }

  try {
    if (!choose_midi_port(midiout)) {
      return false;
    }
  } catch (RtMidiError &error) {
    error.printMessage();
    return false;
  }

  return true;
}


bool choose_midi_port(RtMidiOut *rtmidi) {
  std::cout << "\nWould you like to open a virtual output port? [y/N] ";

  std::string keyHit;
  std::getline(std::cin, keyHit);
  if (keyHit == "y") {
    rtmidi->openVirtualPort();
    return true;
  }

  std::string portName;
  unsigned int i = 0, nPorts = rtmidi->getPortCount();
  if (nPorts == 0) {
    std::cout << "No output ports available!" << std::endl;
    return false;
  }

  if (nPorts == 1) {
    std::cout << "\nOpening " << rtmidi->getPortName() << std::endl;
  } else {
    for (i = 0; i < nPorts; i++) {
      portName = rtmidi->getPortName(i);
      std::cout << "  Output port #" << i << ": " << portName << '\n';
    }

    do {
      std::cout << "\nChoose a port number: ";
      std::cin >> i;
    } while (i >= nPorts);
  }

  std::cout << "\n";
  rtmidi->openPort(i);

  return true;
}

RtMidi::Api choose_midi_api() {
  std::vector<RtMidi::Api> apis;
  RtMidi::getCompiledApi(apis);

  if (apis.size() <= 1)
    return RtMidi::Api::UNSPECIFIED;

  std::cout << "\nAPIs\n  API #0: unspecified / default\n";
  for (size_t n = 0; n < apis.size(); n++)
    std::cout << "  API #" << apis[n] << ": "
              << RtMidi::getApiDisplayName(apis[n]) << "\n";

  std::cout << "\nChoose an API number: ";
  unsigned int i;
  std::cin >> i;

  std::string dummy;
  std::getline(std::cin, dummy); // used to clear out stdin

  return static_cast<RtMidi::Api>(i);
}
