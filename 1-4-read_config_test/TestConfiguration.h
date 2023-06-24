#ifndef TESTCONFIGURATION_H
#define TESTCONFIGURATION_H

#include "Test.h"
#include <vector>
#include <fstream>
class Config {
public:
  std::string simTitle;
  int configNums;
  int modNums;
  std::string environment;
  std::string aerodynamics;
  std::string propulsion;
  std::string forces;
  std::string newton;
  std::string print;
  float printStep;
  float int_step;
  float endTime;
  std::string dev_name;
  double lonx;
  double latx;
  double alt;
  double psivgx;
  double thtvgx;
  double dvbe;
  double alphax;
  double phimvx;
  std::string aero_deck;
  double area;
  std::string prop_deck;
  int mprop;
  double mass0;
  double fmass0;
  double acowl;
  double throttle;
  double thrtl_idle;
  double thrtl_max;
  bool needParse;

  void parseConfig() {
    simTitle = "GHAME3_Sim";
    configNums = 2;
    modNums = 5;
    environment = "def,init,exec";
    aerodynamics = "def,exec";
    propulsion = "def,init,exec";
    forces = "def,exec";
    newton = "def,init,exec";
  }

  void parseModules1() {
    print = "ON";
    printStep = 0.5;
    int_step = 0.01;
    endTime = 1000;
  }

  void parseModules2() {
    dev_name = "ghame3";
    lonx = -80.55;
    latx = 28.43;
    alt = 3000;
    psivgx = 90;
    thtvgx = 0;
    dvbe = 250;
    alphax = 7;
    phimvx = 0;
    aero_deck = "ghame3_aero_deck.txt";
    area = 557.42;
    prop_deck = "ghame3_prop_deck.txt";
    mprop = 1;
    mass0 = 136077;
    fmass0 = 81646;
    acowl = 27.87;
    throttle = 0.2;
    thrtl_idle = 0.05;
    thrtl_max = 2;
  }
  Config(bool needParse): needParse(needParse) {
    if (needParse) {
      parseConfig();
      parseModules1();
      parseModules2();
    }
  }
};

class TestConfiguration : public TestSuite::Test {
  const Config rawConfig=Config(true);
  // enum { NPARAMS = 6 };
  // static std::string params[NPARAMS];
  Config paramValues=Config(false);
  // std::vector<std::string> paramValues;

public:
  void testConfiguration() {
    test_(paramValues.simTitle == rawConfig.simTitle);
    test_(paramValues.configNums == rawConfig.configNums);
    test_(paramValues.modNums == rawConfig.modNums);
    test_(paramValues.environment == rawConfig.environment);
    test_(paramValues.aerodynamics == rawConfig.aerodynamics);
    test_(paramValues.propulsion == rawConfig.propulsion);
    test_(paramValues.forces == rawConfig.forces);
    test_(paramValues.newton == rawConfig.newton);
    test_(paramValues.print == rawConfig.print);
    test_(paramValues.printStep == rawConfig.printStep);
    test_(paramValues.int_step == rawConfig.int_step);
    test_(paramValues.endTime == rawConfig.endTime);
    test_(paramValues.dev_name == rawConfig.dev_name);
    test_(paramValues.lonx == rawConfig.lonx);
    test_(paramValues.latx == rawConfig.latx);
    test_(paramValues.alt == rawConfig.alt);
    test_(paramValues.psivgx == rawConfig.psivgx);
    test_(paramValues.thtvgx == rawConfig.thtvgx);
    test_(paramValues.dvbe == rawConfig.dvbe);
    test_(paramValues.alphax == rawConfig.alphax);
    test_(paramValues.phimvx == rawConfig.phimvx);
    test_(paramValues.aero_deck == rawConfig.aero_deck);
    test_(paramValues.area == rawConfig.area);
    test_(paramValues.prop_deck == rawConfig.prop_deck);
    test_(paramValues.mprop == rawConfig.mprop);
    test_(paramValues.mass0 == rawConfig.mass0);
    test_(paramValues.fmass0 == rawConfig.fmass0);
    test_(paramValues.acowl == rawConfig.acowl);
    test_(paramValues.throttle == rawConfig.throttle);
    test_(paramValues.thrtl_idle == rawConfig.thrtl_idle);
    test_(paramValues.thrtl_max == rawConfig.thrtl_max);
  }

  void readConfiguration();
  void writeConfiguration();

  void run() {
    readConfiguration();
    testConfiguration();
    writeConfiguration();
  }
};

#endif
