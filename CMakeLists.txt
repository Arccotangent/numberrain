cmake_minimum_required(VERSION 3.16)
project(numberrain)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.70.0 REQUIRED COMPONENTS system regex)
find_library(gmp REQUIRED)

set(NUMBERRAIN_SOURCES
        src/main.cpp
        src/Version.h
        src/ops.h
        src/Structures.h
        src/Configuration.cpp src/Configuration.h
        src/OperationDispatcher.cpp src/OperationDispatcher.h
        src/RealOperation.cpp src/RealOperation.h
        src/IntegerOperation.cpp src/IntegerOperation.h
        src/VectorOperation.cpp src/VectorOperation.h
        src/StringOperation.cpp src/StringOperation.h
        src/GlobalVars.cpp src/GlobalVars.h
        src/logging/Logger.cpp src/logging/Logger.h
        src/elementary/Addition.cpp src/elementary/Addition.h
        src/elementary/Subtraction.cpp src/elementary/Subtraction.h
        src/elementary/Multiplication.cpp src/elementary/Multiplication.h
        src/elementary/Division.cpp src/elementary/Division.h
        src/elementary/Exponentiation.cpp src/elementary/Exponentiation.h
        src/elementary/SquareRoot.cpp src/elementary/SquareRoot.h
        src/elementary/Factorial.cpp src/elementary/Factorial.h
        src/elementary/Modulus.cpp src/elementary/Modulus.h
        src/elementary/GreatestCommonDenominator.cpp src/elementary/GreatestCommonDenominator.h
        src/elementary/LeastCommonMultiple.cpp src/elementary/LeastCommonMultiple.h
        src/algebra/NaturalLogarithm.cpp src/algebra/NaturalLogarithm.h
        src/algebra/Base10Logarithm.cpp src/algebra/Base10Logarithm.h
        src/algebra/CustomBaseLogarithm.cpp src/algebra/CustomBaseLogarithm.h
        src/trigonometry/Sine.cpp src/trigonometry/Sine.h
        src/trigonometry/Cosine.cpp src/trigonometry/Cosine.h
        src/trigonometry/Tangent.cpp src/trigonometry/Tangent.h
        src/trigonometry/Arcsine.cpp src/trigonometry/Arcsine.h
        src/trigonometry/Arccosine.cpp src/trigonometry/Arccosine.h
        src/trigonometry/Arctangent.cpp src/trigonometry/Arctangent.h
        src/vector/VectorAddition.cpp src/vector/VectorAddition.h
        src/vector/VectorSubtraction.cpp src/vector/VectorSubtraction.h
        src/vector/VectorScalarMultiplication.cpp src/vector/VectorScalarMultiplication.h
        src/vector/VectorDotProduct.cpp src/vector/VectorDotProduct.h
        src/vector/VectorCrossProduct.cpp src/vector/VectorCrossProduct.h
        src/vector/VectorPolarToRectangular.cpp src/vector/VectorPolarToRectangular.h
        src/vector/VectorRectangularToPolar.cpp src/vector/VectorRectangularToPolar.h
        src/matrix/Matrix.cpp src/matrix/Matrix.h
        src/scripting/ScriptEngine.cpp src/scripting/ScriptEngine.h
        src/scripting/Script.cpp src/scripting/Script.h
        src/scripting/ScriptReader.cpp src/scripting/ScriptReader.h)

add_executable(numberrain ${NUMBERRAIN_SOURCES})

target_link_libraries(numberrain ${Boost_LIBRARIES} gmp)
