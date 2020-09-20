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

#ifndef NUMBERRAIN_MULTIPLICATION_H
#define NUMBERRAIN_MULTIPLICATION_H

#include "../RealOperation.h"

class Multiplication : public virtual RealOperation {
public:
	using RealOperation::RealOperation;
	
	long eval() override;
};


#endif //NUMBERRAIN_MULTIPLICATION_H
