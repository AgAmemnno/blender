/* SPDX-License-Identifier: GPL-2.0-or-later */

/** \file
 * \ingroup asset_system
 */

#include <string>

#include "BKE_blendfile.h"

#include "BLI_path_util.h"

#include "AS_asset_identifier.hh"

namespace blender::asset_system {

AssetIdentifier::AssetIdentifier(std::shared_ptr<std::string> library_root_path,
                                 std::string relative_asset_path)
    : library_root_path_(library_root_path), relative_asset_path_(relative_asset_path)
{
}

std::string AssetIdentifier::full_path() const
{
  char path[FILE_MAX];
  BLI_path_join(path, sizeof(path), library_root_path_->c_str(), relative_asset_path_.c_str());
  return path;
}

std::string AssetIdentifier::full_library_path() const
{
  std::string asset_path = full_path();

  char blend_path[1090 /*FILE_MAX_LIBEXTRA*/];
  if (!BKE_library_path_explode(asset_path.c_str(), blend_path, nullptr, nullptr)) {
    return {};
  }

  return blend_path;
}

}  // namespace blender::asset_system
