#ifndef _CONFIG_PARAMETER_H
#define _CONFIG_PARAMETER_H

#include <globals.h>
#include <config.h>
#include <ArduinoJson.h>

template <typename C>
class ConfigParameterBase {
public:
  virtual uint8_t getMaxStrLen(void) = 0;
  virtual const char* getId() = 0;
  virtual const char* getLabel() = 0;
  virtual void print(const C config, char* str) = 0;
  virtual void save(C& config, const char* str) = 0;
  virtual bool isNumber() = 0;
  virtual bool isBoolean() = 0;
  virtual void getMinimum(char* str) = 0;
  virtual void getMaximum(char* str) = 0;
  virtual void setToDefault(C& config) = 0;
  virtual String toString(const C config) = 0;
  virtual void toJson(const C config, DynamicJsonDocument* doc) = 0;
  virtual bool fromJson(C& config, DynamicJsonDocument* doc, bool useDefaultIfNotPresent) = 0;
  virtual bool isRebootRequiredOnChange() = 0;
};

template <typename C, typename T>
class ConfigParameter :public ConfigParameterBase<C> {
public:
  ConfigParameter(const char* id, const char* label, T C::* valuePtr, uint8_t maxStrLen, bool rebootRequiredOnChange = false);
  virtual ~ConfigParameter() = default;
  uint8_t getMaxStrLen(void) override;
  const char* getId() override;
  const char* getLabel() override;
  void save(C& config, const char* str) override;
  bool isNumber() override;
  bool isBoolean() override;
  T* getValuePtr();
  void getMinimum(char* str) override;
  void getMaximum(char* str) override;
  String toString(const C config) override;
  bool isRebootRequiredOnChange() override;

protected:
  virtual void parse(C& config, T C::* valuePtr, const char* str) = 0;
  const char* id;
  const char* label;
  T C::* valuePtr;
  uint8_t maxStrLen;
  bool rebootRequiredOnChange;
};

template <typename C, typename T>
class NumberConfigParameter :public ConfigParameter<C, T> {
public:
  NumberConfigParameter(const char* id, const char* label, T C::* valuePtr, T defaultValue, uint8_t maxStrLen, T min, T max, bool rebootRequiredOnChange = false);
  ~NumberConfigParameter();
  bool isNumber() override;
  void getMinimum(char* str) override;
  void getMaximum(char* str) override;
  void setToDefault(C& config) override;
  void toJson(const C config, DynamicJsonDocument* doc) override;
  bool fromJson(C& config, DynamicJsonDocument* doc, bool useDefaultIfNotPresent = false) override;
protected:
  T defaultValue;
  T minValue;
  T maxValue;
};

template <typename C>
class Uint8ConfigParameter :public NumberConfigParameter<C, uint8_t> {
public:
  Uint8ConfigParameter(const char* id, const char* label, uint8_t C::* valuePtr, uint8_t defaultValue, uint8_t min = 0, uint8_t max = 255, bool rebootRequiredOnChange = false);
  Uint8ConfigParameter(const char* id, const char* label, uint8_t C::* valuePtr, uint8_t defaultValue, bool rebootRequiredOnChange);
  ~Uint8ConfigParameter();
  void print(const C config, char* str) override;

protected:
  void parse(C& config, uint8_t C::* valuePtr, const char* str) override;
};

template <typename C>
class Uint16ConfigParameter :public NumberConfigParameter<C, uint16_t> {
public:
  Uint16ConfigParameter(const char* id, const char* label, uint16_t C::* valuePtr, uint16_t defaultValue, uint16_t min = 0, uint16_t max = 65535, bool rebootRequiredOnChange = false);
  Uint16ConfigParameter(const char* id, const char* label, uint16_t C::* valuePtr, uint16_t defaultValue, bool rebootRequiredOnChange);
  ~Uint16ConfigParameter();
  void print(const C config, char* str) override;

protected:
  void parse(C& config, uint16_t C::* valuePtr, const char* str) override;
};

template <typename C>
class BooleanConfigParameter :public ConfigParameter<C, bool> {
public:
  BooleanConfigParameter(const char* id, const char* label, bool C::* valuePtr, bool defaultValue, bool rebootRequiredOnChange = false);
  ~BooleanConfigParameter();
  void print(const C config, char* str) override;
  bool isBoolean() override;
  void setToDefault(C& config) override;
  void toJson(const C config, DynamicJsonDocument* doc) override;
  bool fromJson(C& config, DynamicJsonDocument* doc, bool useDefaultIfNotPresent = false) override;

protected:
  void parse(C& config, bool C::* valuePtr, const char* str) override;
  bool defaultValue;
};

template <typename C>
class CharArrayConfigParameter :public ConfigParameter<C, char> {
public:
  CharArrayConfigParameter(const char* id, const char* label, char C::* valuePtr, const char* defaultValue, uint8_t maxLen, bool rebootRequiredOnChange = false);
  ~CharArrayConfigParameter();
  void print(const C config, char* str) override;
  void setToDefault(C& config) override;
  void toJson(const C config, DynamicJsonDocument* doc) override;
  bool fromJson(C& config, DynamicJsonDocument* doc, bool useDefaultIfNotPresent = false) override;

protected:
  void parse(C& config, char C::* valuePtr, const char* str) override;
  const char* defaultValue;
};

#endif