/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2013 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef XENIA_APU_AUDIO_SYSTEM_H_
#define XENIA_APU_AUDIO_SYSTEM_H_

#include <xenia/core.h>
#include <xenia/xbox.h>


XEDECLARECLASS1(xe, Emulator);
XEDECLARECLASS2(xe, cpu, Processor);
XEDECLARECLASS2(xe, cpu, XenonThreadState);


namespace xe {
namespace apu {

class AudioDriver;


class AudioSystem {
public:
  virtual ~AudioSystem();

  Emulator* emulator() const { return emulator_; }
  Memory* memory() const { return memory_; }
  cpu::Processor* processor() const { return processor_; }

  virtual X_STATUS Setup();
  virtual void Shutdown();

  void RegisterClient(uint32_t callback, uint32_t callback_arg);
  void UnregisterClient();
  virtual void SubmitFrame(uint32_t samples_ptr) = 0;

  bool HandlesRegister(uint64_t addr);
  virtual uint64_t ReadRegister(uint64_t addr);
  virtual void WriteRegister(uint64_t addr, uint64_t value);

protected:
  virtual void Initialize();
  virtual void Pump() = 0;

private:
  static void ThreadStartThunk(AudioSystem* this_ptr) {
    this_ptr->ThreadStart();
  }
  void ThreadStart();

  static bool HandlesRegisterThunk(AudioSystem* as, uint64_t addr) {
    return as->HandlesRegister(addr);
  }
  static uint64_t ReadRegisterThunk(AudioSystem* as, uint64_t addr) {
    return as->ReadRegister(addr);
  }
  static void WriteRegisterThunk(AudioSystem* as, uint64_t addr,
                                 uint64_t value) {
    as->WriteRegister(addr, value);
  }

protected:
  AudioSystem(Emulator* emulator);

  Emulator*         emulator_;
  Memory*           memory_;
  cpu::Processor*   processor_;

  xe_run_loop_ref   run_loop_;
  xe_thread_ref     thread_;
  cpu::XenonThreadState* thread_state_;
  uint32_t          thread_block_;
  bool              running_;

  xe_mutex_t*       lock_;
  struct {
    uint32_t callback;
    uint32_t callback_arg;
    uint32_t wrapped_callback_arg;
  } client_;

  AudioDriver*      driver_;
};


}  // namespace apu
}  // namespace xe


#endif  // XENIA_APU_AUDIO_SYSTEM_H_
