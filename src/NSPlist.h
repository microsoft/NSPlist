//******************************************************************************
//
// Copyright (c) 2015 Microsoft Corporation. All rights reserved.
//
// This code is licensed under the MIT License (MIT).
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
//******************************************************************************

#ifndef _NSPLIST_H_
#define _NSPLIST_H_

#include <string>
#include <vector>
#include <map>

typedef enum {
  NSPlistStringValue,
  NSPlistArrayValue,
  NSPlistDictionaryValue,
  NSPlistDataValue,
} NSPlistValueType;

typedef enum {
  NSPlistStringString,
  NSPlistIntegerString,
  NSPlistRealString,
  NSPlistDateString,
} NSPlistStringType;


class NSPlistValue {
public:
  virtual ~NSPlistValue() = 0;
  NSPlistValue(NSPlistValueType type) : m_type(type) {}

  NSPlistValueType m_type;
};

class NSPlistString : public NSPlistValue {
public:
  NSPlistString(const std::string& str, NSPlistStringType subType)
    : NSPlistValue(NSPlistStringValue), m_str(str), m_subType(subType) {}

  static NSPlistString* cast(NSPlistValue* val);
  static const NSPlistString* cast(const NSPlistValue* val);

  std::string m_str;
  NSPlistStringType m_subType;
};

class NSPlistData : public NSPlistValue {
public:
  NSPlistData() : NSPlistValue(NSPlistDataValue) {}
  void insert(const std::string& hexstr);

  static NSPlistData* cast(NSPlistValue* val);
  static const NSPlistData* cast(const NSPlistValue* val);

  std::vector<char> m_data;
};

typedef std::vector<NSPlistValue*> NSPlistValueArray;

class NSPlistArray : public NSPlistValue {
public:
  virtual ~NSPlistArray();
  NSPlistArray() : NSPlistValue(NSPlistArrayValue) {}
  void insert(NSPlistValue* val);

  static NSPlistArray* cast(NSPlistValue* val);
  static const NSPlistArray* cast(const NSPlistValue* val);

  NSPlistValueArray m_array;
};

typedef std::map<std::string, NSPlistValue*> NSPlistValueDict;

class NSPlistDictionary : public NSPlistValue  {
public:
  virtual ~NSPlistDictionary();
  NSPlistDictionary() : NSPlistValue(NSPlistDictionaryValue) {}
  void insert(NSPlistString* key, NSPlistValue* val);

  static NSPlistDictionary* cast(NSPlistValue* val);
  static const NSPlistDictionary* cast(const NSPlistValue* val);

  NSPlistValueDict m_dict;
};

extern bool loadPlistFromBuffer(const char* byteArray, NSPlistValue*& ret);
extern bool loadPlistFromFile(const char* filePath, NSPlistValue*& ret);

#endif /* _NSPLIST_H_ */