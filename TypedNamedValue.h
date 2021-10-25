/*
 * MIT License
 *
 * Copyright (c) 2019-2021 Christof Ruch
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include "JuceHeader.h"

enum class ValueType
{
    Integer,
    Bool,
    String,
    Lookup,
    Filename,
    Pathname,
    Color,
};

class TypedNamedValue {
public:
    //! Construct a Bool type
    TypedNamedValue(String const &name, String const &sectionName, bool defaultValue);
    //! Construct a String type (edit field)
    TypedNamedValue(String const &name, String const &sectionName, String const &defaultValue, int maxLength);
    //! Construct an Integer type
    TypedNamedValue(String const &name, String const &sectionName, int defaultValue, int minValue, int maxValue);
    //! Construct a lookup value type
    TypedNamedValue(String const &name, String const &sectionName, int defaultValue, std::map<int, std::string> const &lookup);
    //! Construct a Filepath value type
    TypedNamedValue(String const &name, String const &sectionName, File const &defaultValue, bool isDirectory);
    //! Construct a color value type
    TypedNamedValue(String const &name, String const &sectionName, Colour defaultValue);

    virtual ~TypedNamedValue() = default;

    Value &value();
    String name() const;
    String sectionName() const;
    ValueType valueType() const;
    int minValue() const;
    int maxValue() const;
    bool enabled() const;
    std::map<int, std::string> lookup() const;

    // For lookups only
    int indexOfValue(std::string const &text) const; // TODO - suboptimal linear search
    std::string lookupValue();
    void setLookup(std::map<int, std::string> const &newLookup);

protected:
    String name_;
    String sectionName_;
    Value value_;
    ValueType valueType_;
    int minValue_;
    int maxValue_;
    std::map<int, std::string> lookup_;
    bool enabled_;
};

class TypedNamedValueSet : public std::vector<std::shared_ptr<TypedNamedValue>> {
public:
    std::shared_ptr<TypedNamedValue> typedNamedValueByName(std::string const &name); // TODO - suboptimal linear search
    bool hasValue(std::string const &name);
    Value &valueByName(std::string const &name); // TODO - suboptimal linear search
    void addToValueTree(ValueTree &tree);
};
