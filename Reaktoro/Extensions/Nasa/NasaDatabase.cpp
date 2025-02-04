// Reaktoro is a unified framework for modeling chemically reactive systems.
//
// Copyright (C) 2014-2020 Allan Leal
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library. If not, see <http://www.gnu.org/licenses/>.

#include "NasaDatabase.hpp"

// CMakeRC includes
#include <cmrc/cmrc.hpp>

CMRC_DECLARE(ReaktoroDatabases);

namespace Reaktoro {

NasaDatabase::NasaDatabase(Database database)
: Database(std::move(database))
{}

NasaDatabase::NasaDatabase(String name)
: NasaDatabase(NasaDatabase::withName(name))
{}

auto NasaDatabase::withName(String name) -> NasaDatabase
{
    errorif(!oneof(name, "nasa-cea"),
        "Could not load embedded NASA database file with name `", name, "`. ",
        "The currently supported names are: \n"
        "    - nasa-cea \n",
        "");
    auto fs = cmrc::ReaktoroDatabases::get_filesystem();
    auto file = fs.open("databases/reaktoro/" + name + ".yaml");
    const String contents(file.begin(), file.end());
    return fromContents(contents);
}

} // namespace Reaktoro
