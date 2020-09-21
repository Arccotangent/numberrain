/*
Numberrain - A scriptable command line calculator
Copyright (C) 2020 Arccotangent

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <boost/algorithm/string.hpp>
#include "Configuration.h"
#include "OperationDispatcher.h"
#include "Version.h"

using namespace std;

void printUsage() {
	cout << "Numberrain " << VERSION_STR << " by Arccotangent" << endl;
	cout << "Usage: numberrain <operation> <arguments>" << endl;
	cout << endl;
	cout << "Operations:" << endl;
	cout << endl;
	cout << "-----Elementary Operations-----" << endl;
	cout << "\tadd <2+ numbers> - Add numbers" << endl;
	cout << "\tsub <2+ numbers> - Subtract numbers" << endl;
	cout << "\tmul <2+ numbers> - Multiply numbers" << endl;
	cout << "\tdiv <2+ numbers> - Divide numbers" << endl;
	cout << "\texp <2+ numbers> - Evaluate exponents" << endl;
	cout << "\tsqrt <number> - Evaluate the square root of a number" << endl;
	cout << "\tfct <integer> - Evaluate a factorial" << endl;
	cout << "\tmod <2+ integers> - Find the modulus (remainder) of the division of numbers" << endl;
	cout << "\tgcd <2+ integers> - Find the greatest common denominator (GCD) of numbers" << endl;
	cout << "\tlcm <2+ integers> - Find the least common multiple (LCM) of numbers" << endl;
	cout << endl;
	cout << "-----Algebra-----" << endl;
	cout << "\tln <number> - Evaluate the natural logarithm (base e) of a number" << endl;
	cout << "\tlog10 <number> - Evaluate the base-10 logarithm of a number" << endl;
	cout << "\tlogb <base> <number> - Evaluate the logarithm of a number at a custom base" << endl;
	cout << endl;
	cout << "-----Trigonometry-----" << endl;
	cout << "NOTICE: Trigonometric functions all accept and return angles in degrees." << endl;
	cout << endl;
	cout << "\tsin <angle> - Evaluate sin(angle)" << endl;
	cout << "\tcos <angle> - Evaluate cos(angle)" << endl;
	cout << "\ttan <angle> - Evaluate tan(angle)" << endl;
	cout << "\tarcsin <opposite> <hypotenuse> - Evaluate arcsin(opposite/hypotenuse)" << endl;
	cout << "\tarccos <adjacent> <hypotenuse> - Evaluate arccos(adjacent/hypotenuse)" << endl;
	cout << "\tarctan <opposite> <adjacent> - Evaluate arctan(opposite/adjacent)" << endl;
	cout << endl;
	cout << "-----Vector Operations-----" << endl;
	cout
			<< "NOTICE: Vectors are returned in rectangular format like so: xi + yj + zk, where i, j, and k represent the unit vectors."
			<< endl;
	cout << endl;
	cout << "\tvadd <2+ vectors> - Add vectors" << endl;
	cout << "\tvsub <2+ vectors> - Subtract vectors" << endl;
	cout << "\tvsmul <scalar> <vector> - Multiply a vector by a scalar (mind the order)" << endl;
	cout << "\tvdot <2 vectors> - Find the dot product of 2 vectors" << endl;
	cout << "\tvcross <2+ vectors> - Find the cross product of vectors" << endl;
	cout << "\tvptr <angle> <magnitude> - Find the rectangular coordinates of a vector given its angle and magnitude"
	     << endl;
	cout
			<< "\tvrtp <vector> - Find the polar coordinates of a vector given its rectangular coordinates (only x and y used) (angle is in degrees counterclockwise of +x axis)"
			<< endl;
	cout << endl;
	cout << "-----Scripting-----" << endl;
	cout << "NOTE: The conventional Numberrain script extension is .nrs" << endl;
	cout << "NOTE: Mathematical constants are available in scripts, but not in command line at the time." << endl;
	cout << "NOTE: Scripts cannot accept command line arguments at the time." << endl;
	cout << endl;
	cout << "\texec <file> - Execute a Numberrain script" << endl;
	cout << endl;
	cout << "-----Notes-----" << endl;
	cout << "How to enter vectors:" << endl;
	cout << "Vectors are entered in rectangular form, formatted like so: x,y,z (no spaces)" << endl;
	cout << "Examples:" << endl;
	cout << "\t5i + 3j - 2k would be entered as 5,3,-2" << endl;
	cout << "\t-7i + j + 4k would be entered as -7,1,4" << endl;
	cout << "Vector coefficients are real numbers, they can be decimals as well." << endl;
	cout << "Do not enter positive values with a + sign, this will crash Numberrain." << endl;
	cout << endl;
	cout << "Vector operations that take scalars technically accept vectors, but only x is used." << endl;
	cout
			<< "So entering 'numberrain vsmul 2,3,1 1,1,1' is exactly the same as 'numberrain vsmul 2 1,1,1' since y and z are ignored."
			<< endl;
}

string getHomeDirectory() {
#ifdef _WIN32
	string homeDrive = getenv("HOMEDRIVE");
	string homePath = getenv("HOMEPATH");
	
	return homeDrive + homePath;
#else
	string home = getenv("HOME");
	
	return home;
#endif
}

#ifdef _WIN32
#define FILE_SEPARATOR '\\'
#else
#define FILE_SEPARATOR '/'
#endif

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printUsage();
		return 1;
	}
	
	cout << fixed;
	
	cout << "Numberrain " << VERSION_STR << " by Arccotangent" << endl;
	
	string confDir = getHomeDirectory() + FILE_SEPARATOR + ".numberrain" + FILE_SEPARATOR;
	if (!filesystem::exists(confDir)) {
		bool success = filesystem::create_directory(confDir);
		if (!success) {
			cout << "Error: Could not create Numberrain configuration directory." << endl;
			cout << "Path: " << confDir << endl;
			return 1;
		}
	}
	
	if (filesystem::exists(confDir) && !filesystem::is_directory(confDir)) {
		cout << "Error: Configuration directory exists, but is not a directory." << endl;
		cout << "Path: " << confDir << endl;
		return 1;
	}
	
	string confFile = confDir + "config.json";
	
	cout << "Loading configuration from file: " << confFile << endl;
	
	Configuration config(confFile);
	config.createIfNotExist();
	config.load();
	
	int digits = config.getPrecision();
	boost::multiprecision::mpf_float::default_precision(digits);
	
	cout << "Precision was set to " << digits << " digits." << endl;
	
	bool showWork = config.shouldShowWork();
	GlobalVars::getInstance()->setShowWork(showWork);
	
	cout << "Numberrain show work is " << (showWork ? "ENABLED" : "DISABLED") << " (can be overridden by scripts)"
	     << endl;
	
	string operation = argv[1];
	cout << "Operation: " + operation << endl;
	
	OperationDispatcher dispatcher(operation);
	
	if (!dispatcher.verify()) {
		cout << "Invalid operation! Run Numberrain without any arguments to see usage." << endl;
		return 1;
	}
	
	ArgType argType = dispatcher.getArgType();
	
	switch (argType) {
		case REAL: {
			vector<Real> arguments;
			
			cout << "Arguments (real numbers): { ";
			
			for (int i = 2; i < argc; i++) {
				Real arg(argv[i]);
				
				arguments.emplace_back(arg);
				cout << fmt(arg) << " ";
			}
			
			cout << "}" << endl;
			
			if (!dispatcher.checkArgCount(arguments.size())) {
				cout << "Invalid argument count! Run Numberrain without any arguments to see usage." << endl;
				return 1;
			}
			
			RealOperation *oper = dispatcher.getRealOperation(arguments);
			
			if (oper == nullptr) {
				cout
						<< "Invalid operation! Run Numberrain without any arguments to see usage. (This is also a bug, please report it!)"
						<< endl;
				return 1;
			}
			
			cout << "===================================================================================" << endl;
			long time = oper->eval();
			
			Real result = oper->getResult();
			
			cout << "===================================================================================" << endl;
			cout << "Time: " << time << " microseconds" << endl;
			cout << "Final result: " << fmt(result) << endl;
			break;
		}
		case INTEGER: {
			vector<Integer> arguments;
			
			cout << "Arguments (integers): { ";
			
			for (int i = 2; i < argc; i++) {
				Integer arg(argv[i]);
				
				arguments.emplace_back(arg);
				cout << fmt(arg) << " ";
			}
			
			cout << "}" << endl;
			
			if (!dispatcher.checkArgCount(arguments.size())) {
				cout << "Invalid argument count! Run Numberrain without any arguments to see usage." << endl;
				return 1;
			}
			
			IntegerOperation *oper = dispatcher.getIntegerOperation(arguments);
			
			if (oper == nullptr) {
				cout
						<< "Invalid operation! Run Numberrain without any arguments to see usage. (This is also a bug, please report it!)"
						<< endl;
				return 1;
			}
			
			cout << "===================================================================================" << endl;
			long time = oper->eval();
			
			Real result = oper->getResult();
			
			cout << "===================================================================================" << endl;
			cout << "Time: " << time << " microseconds" << endl;
			cout << "Final result: " << fmt(result) << endl;
			break;
		}
		case VECTOR: {
			vector<Vector> arguments;
			
			cout << "Arguments (vectors): {     ";
			
			for (int i = 2; i < argc; i++) {
				vector<string> parts;
				boost::algorithm::split(parts, argv[i], boost::algorithm::is_any_of(","));
				
				Real x = Real(parts[0]);
				Real y = parts.size() >= 2 ? Real(parts[1]) : 0.0;
				Real z = parts.size() >= 3 ? Real(parts[2]) : 0.0;
				
				Vector vec(x, y, z);
				
				cout << fmt(vec) << "     ";
				
				arguments.emplace_back(vec);
			}
			
			cout << "}" << endl;
			
			if (!dispatcher.checkArgCount(arguments.size())) {
				cout << "Invalid argument count! Run Numberrain without any arguments to see usage." << endl;
				return 1;
			}
			
			VectorOperation *oper = dispatcher.getVectorOperation(arguments);
			
			if (oper == nullptr) {
				cout
						<< "Invalid operation! Run Numberrain without any arguments to see usage. (This is also a bug, please report it!)"
						<< endl;
				return 1;
			}
			
			cout << "===================================================================================" << endl;
			long time = oper->eval();
			
			Vector result = oper->getResult();
			
			cout << "===================================================================================" << endl;
			cout << "Time: " << time << " microseconds" << endl;
			cout << "Final result: " << fmt(result) << endl;
			break;
		}
		case STRING: {
			vector<string> arguments;
			
			cout << "Arguments (strings): {     ";
			
			for (int i = 2; i < argc; i++) {
				cout << argv[i] << "     ";
				
				arguments.emplace_back(argv[i]);
			}
			
			cout << "}" << endl;
			
			if (!dispatcher.checkArgCount(arguments.size())) {
				cout << "Invalid argument count! Run Numberrain without any arguments to see usage." << endl;
				return 1;
			}
			
			StringOperation *oper = dispatcher.getStringOperation(arguments);
			
			if (oper == nullptr) {
				cout
						<< "Invalid operation! Run Numberrain without any arguments to see usage. (This is also a bug, please report it!)"
						<< endl;
				return 1;
			}
			
			cout << "===================================================================================" << endl;
			long time = oper->eval();
			
			string result = oper->getResult();
			
			cout << "===================================================================================" << endl;
			cout << "Time: " << time << " microseconds" << endl;
			cout << "Final result: " << result << endl;
			break;
		}
		default: {
			cout << "Error occurred while retrieving argument type - invalid operation?" << endl;
			return 1;
		}
	}
	
	return 0;
}
