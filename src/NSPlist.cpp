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

#include "NSPlist.h"

NSPlistValue::~NSPlistValue() {}

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

NSPlistDictionary::~NSPlistDictionary()
{
  NSPlistValueDict::iterator dIt = m_dict.begin();
  for (; dIt != m_dict.end(); dIt++)
    delete (dIt->second);
}

void NSPlistDictionary::insert(NSPlistString* key, NSPlistValue* val)
{
  m_dict[key->m_str] = val;
  delete key;
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