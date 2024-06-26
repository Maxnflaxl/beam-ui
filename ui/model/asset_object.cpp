// Copyright 2019 The Beam Team
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#include "asset_object.h"
#include "viewmodel/ui_helpers.h"

AssetObject::AssetObject(uint64_t id)
   : _id(id)
{
}

bool AssetObject::operator==(const AssetObject& other) const
{
   return _id == other._id;
}

uint64_t AssetObject::id() const
{
    return _id;
}
