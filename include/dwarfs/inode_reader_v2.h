/* vim:set ts=2 sw=2 sts=2 et: */
/**
 * \author     Marcus Holland-Moritz (github@mhxnet.de)
 * \copyright  Copyright (c) Marcus Holland-Moritz
 *
 * This file is part of dwarfs.
 *
 * dwarfs is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * dwarfs is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dwarfs.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <memory>

#include "dwarfs/block_cache.h"
#include "dwarfs/fstypes.h"
#include "dwarfs/logger.h"
#include "dwarfs/metadata_types.h"

namespace dwarfs {

class inode_reader_v2 {
 public:
  inode_reader_v2() = default;

  inode_reader_v2(logger& lgr, block_cache&& bc);

  inode_reader_v2& operator=(inode_reader_v2&&) = default;

  ssize_t read(char* buf, size_t size, off_t offset, chunk_range chunks) const {
    return impl_->read(buf, size, offset, chunks);
  }

  ssize_t readv(iovec_read_buf& buf, size_t size, off_t offset,
                chunk_range chunks) const {
    return impl_->readv(buf, size, offset, chunks);
  }

  void
  dump(std::ostream& os, const std::string& indent, chunk_range chunks) const {
    impl_->dump(os, indent, chunks);
  }

  class impl {
   public:
    virtual ~impl() = default;

    virtual ssize_t
    read(char* buf, size_t size, off_t offset, chunk_range chunks) const = 0;
    virtual ssize_t readv(iovec_read_buf& buf, size_t size, off_t offset,
                          chunk_range chunks) const = 0;
    virtual void dump(std::ostream& os, const std::string& indent,
                      chunk_range chunks) const = 0;
  };

 private:
  std::unique_ptr<impl> impl_;
};
} // namespace dwarfs
