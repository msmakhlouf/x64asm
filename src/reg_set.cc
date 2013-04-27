/*
Copyright 2103 eric schkufza

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "src/alias.h"
#include "src/reg_set.h"

using namespace std;

namespace x64asm {

RegSet& RegSet::operator+=(const M& rhs) {
  if (rhs.get_addr_or()) {
    if (rhs.contains_base()) {
      *this += Alias::to_double(rhs.get_base());
    }
    if (rhs.contains_index()) {
      *this += Alias::to_double(rhs.get_index());
    }
  } else {
    if (rhs.contains_base()) {
      *this += rhs.get_base();
    }
    if (rhs.contains_index()) {
      *this += rhs.get_index();
    }
  }
  return *this;
}

} // namespace x64asm
