/*
This file is part of Numberrain.

Numberrain is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

Numberrain is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with Numberrain.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Configuration.h"
#include <filesystem>

using namespace std;
using namespace boost;

Configuration::Configuration(const string &file) {
	this->file = file;
}

void Configuration::createIfNotExist() {
	if (filesystem::exists(file)) {
		return;
	}
	
	property_tree::ptree defaults;
	
	defaults.put("precision", 50);
	
	property_tree::write_json(file, defaults);
}

void Configuration::load() {
	property_tree::read_json(file, props);
}

int Configuration::getPrecision() {
	return props.get<int>("precision");
}
