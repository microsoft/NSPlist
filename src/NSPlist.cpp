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

#include <assert.h>
#include <stdio.h>
#include <iostream>

#include "NSPlist.h"

static char getEscapedChar(char c)
{
  switch (c) {
    case '\t': return 't';
    case '\r': return 'r';
    case '\n': return 'n';
    default: return c;
  }
}

static std::string addEscapes(const std::string& str)
{
  static std::string specialChars("\\\"\t\r\n");

  std::string ret;
  for (unsigned i = 0; i < str.length(); i++) {
    if (std::string::npos != specialChars.find_first_of(str[i])) {
      ret += '\\';
      ret += getEscapedChar(str[i]);
    } else {
      ret += str[i];
    }
  }

  return ret;
}

static bool mustQuote(char c)
{
  static std::string allowedChars("_-.$/");
  return !isalnum(c) && allowedChars.find_first_of(c) == std::string::npos;
}

static std::string quoteString(const std::string& str, bool forceQuote = false) {
  std::string escapedStr = addEscapes(str);
  for (unsigned i = 0; !forceQuote && i < escapedStr.length(); i++)
    forceQuote |= mustQuote(escapedStr[i]);

  if (forceQuote)
    return "\"" + escapedStr + "\"";
  else
    return escapedStr;
}

static void indent(std::ostream& out, unsigned indentLevel = 0)
{
  for (unsigned i = 0; i < indentLevel; i++) out << "\t";
}

NSPlistValue::~NSPlistValue() {}

void NSPlistValue::write(std::ostream& out) const
{
  out << "// !$*UTF8*$!" << std::endl;
  write(out, 0);
  out << std::endl;
}

void NSPlistString::write(std::ostream& out, unsigned indentLevel) const
{
  out << quoteString(m_str);
}

void NSPlistData::insert(const std::string& hexstr)
{
  const char* src = hexstr.c_str();
  assert(hexstr.length() % 2 == 0);

  unsigned int u;
  while (sscanf(src, "%2x", &u) == 1) {
    m_data.push_back(u);
    src += 2;
  }
}

void NSPlistData::insert(const std::vector<char>& data)
{
  m_data.insert(m_data.end(), data.begin(),data.end());
}

void NSPlistData::write(std::ostream& out, unsigned indentLevel) const
{
  char hexbuf[3];

  out << "<";
  for (unsigned i = 0; i < m_data.size(); i++) {
    sprintf(hexbuf, "%02X", static_cast<unsigned char>(m_data[i]));
    out << hexbuf;
    if (i < m_data.size() - 1)
      out << " ";
  }
  out << ">";
}

NSPlistArray::~NSPlistArray()
{
  NSPlistValueArray::iterator aIt = m_array.begin();
  for (; aIt != m_array.end(); aIt++)
    delete (*aIt);
}

void NSPlistArray::insert(NSPlistValue* val)
{
  m_array.push_back(val);
}

void NSPlistArray::write(std::ostream& out, unsigned indentLevel) const
{
  out << "(" << std::endl;
  for (unsigned i = 0; i < m_array.size(); i++) {
    indent(out, indentLevel + 1);
    m_array[i]->write(out, indentLevel + 1);
    out << "," << std::endl;
  }
  indent(out, indentLevel);
  out << ")";
}

NSPlistDictionary::~NSPlistDictionary()
{
  NSPlistValueDict::iterator dIt = m_dict.begin();
  for (; dIt != m_dict.end(); dIt++)
    delete (dIt->second);
}

void NSPlistDictionary::insert(NSPlistString* key, NSPlistValue* val)
{
  insert(key->m_str, val);
  delete key;
}

void NSPlistDictionary::insert(const std::string& key, NSPlistValue* val)
{
  m_dict[key] = val;
}

void NSPlistDictionary::write(std::ostream& out, unsigned indentLevel) const
{
  out << "{" << std::endl;
  NSPlistValueDict::const_iterator dIt = m_dict.begin();
  for (; dIt != m_dict.end(); dIt++) {
    indent(out, indentLevel + 1);
    out << quoteString(dIt->first) << " = ";
    dIt->second->write(out, indentLevel + 1);
    out << ";" << std::endl;
  }
  indent(out, indentLevel);
  out << "}";
}

NSPlistString* NSPlistString::cast(NSPlistValue* val)
{
  return dynamic_cast<NSPlistString*>(val);
}

const NSPlistString* NSPlistString::cast(const NSPlistValue* val)
{
  return dynamic_cast<const NSPlistString*>(val);
}

NSPlistData* NSPlistData::cast(NSPlistValue* val)
{
  return dynamic_cast<NSPlistData*>(val);
}

const NSPlistData* NSPlistData::cast(const NSPlistValue* val)
{
  return dynamic_cast<const NSPlistData*>(val);
}

NSPlistArray* NSPlistArray::cast(NSPlistValue* val)
{
  return dynamic_cast<NSPlistArray*>(val);
}

const NSPlistArray* NSPlistArray::cast(const NSPlistValue* val)
{
  return dynamic_cast<const NSPlistArray*>(val);
}

NSPlistDictionary* NSPlistDictionary::cast(NSPlistValue* val)
{
  return dynamic_cast<NSPlistDictionary*>(val);
}

const NSPlistDictionary* NSPlistDictionary::cast(const NSPlistValue* val)
{
  return dynamic_cast<const NSPlistDictionary*>(val);
}