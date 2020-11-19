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

#include "theme.h"

// static
QString Theme::name()
{
#ifdef BEAM_BEAMX
    return "beamx";
#elif defined(BEAM_TESTNET)
    return "testnet";
#elif defined(BEAM_MAINNET)
    return "mainnet";
#else
    return "masternet";
#endif
}

// static
QString Theme::iconPath() 
{
#ifdef BEAM_BEAMX
    return ":/assets/icon_beamx.png";
#elif BEAM_TESTNET
    return ":/assets/icon_testnet.png";
#elif defined(BEAM_MAINNET)
    return ":/assets/icon.png";
#else
    return ":/assets/icon_masternet.png";
#endif
}
