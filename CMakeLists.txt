cmake_minimum_required(VERSION 3.8)
project(Proj1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp license.txt sample.txt.xml AttackCondition.cpp AttackCondition.h Attack.h Border.h Container.h containersample.xml Creature.h creaturesample.xml item.h itemsample.xml rapidxml.hpp rapidxml_iterators.hpp rapidxml_print.hpp rapidxml_utils.hpp Room.h roomsample.xml Trigger.h TriggerOwner.h triggersample.xml TriggerStatus.h TurnOn.h Attack.cpp Border.cpp Creature.cpp Game.h Game.cpp Item.cpp Room.cpp Trigger.h TriggerOwner.cpp Trigger.cpp TriggerStatus.cpp TurnOn.cpp Container.cpp manual.html)
add_executable(Proj1 ${SOURCE_FILES})