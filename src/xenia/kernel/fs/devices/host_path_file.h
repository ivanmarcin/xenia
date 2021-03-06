/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2013 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef XENIA_KERNEL_FS_DEVICES_HOST_PATH_FILE_H_
#define XENIA_KERNEL_FS_DEVICES_HOST_PATH_FILE_H_

#include <xenia/common.h>
#include <xenia/core.h>

#include <xenia/kernel/objects/xfile.h>


namespace xe {
namespace kernel {
namespace fs {

class HostPathEntry;


class HostPathFile : public XFile {
public:
  HostPathFile(KernelState* kernel_state, uint32_t desired_access,
               HostPathEntry* entry, HANDLE file_handle);
  virtual ~HostPathFile();

  virtual X_STATUS QueryInfo(XFileInfo* out_info);

protected:
  virtual X_STATUS ReadSync(
      void* buffer, size_t buffer_length, size_t byte_offset,
      size_t* out_bytes_read);

private:
  HostPathEntry* entry_;
  HANDLE         file_handle_;
};


}  // namespace fs
}  // namespace kernel
}  // namespace xe


#endif  // XENIA_KERNEL_FS_DEVICES_HOST_PATH_FILE_H_
