#ifndef ABSTRACT_VALUE_H
#define ABSTRACT_VALUE_H

/*************************************************************
 * Copyright: (C) 2012 by Markus Schordan                    *
 * Author   : Markus Schordan                                *
 * License  : see file LICENSE in the CodeThorn distribution *
 *************************************************************/

#include <climits>
#include <string>
#include <sstream>
#include "BoolLattice.h"
#include "VariableIdMapping.h"

using std::string;
using std::istream;
using std::ostream;

namespace CodeThorn {

namespace AType {
 class AbstractValue;

 bool strictWeakOrderingIsSmaller(const AbstractValue& c1, const AbstractValue& c2);
 bool strictWeakOrderingIsEqual(const AbstractValue& c1, const AbstractValue& c2);

/*!
  \brief Implements semantic functions of an integer lattice.
  \date 2012
  \author Markus Schordan
  \details All lattice domain operators are implemented as overloaded functions.
 */
class AbstractValue {
 public:
  friend bool strictWeakOrderingIsSmaller(const AbstractValue& c1, const AbstractValue& c2);
  friend bool strictWeakOrderingIsEqual(const AbstractValue& c1, const AbstractValue& c2);
  enum ValueType { BOT, CONSTINT, PTR, RAW_PTR, TOP};
  AbstractValue();
  AbstractValue(bool val);
  // type conversion
  AbstractValue(AType::Top e);
  // type conversion
  AbstractValue(AType::Bot e);
  // type conversion
  AbstractValue(signed char x);
  AbstractValue(unsigned char x);
  AbstractValue(short int x);
  AbstractValue(unsigned short int x);
  AbstractValue(int x);
  AbstractValue(unsigned int x);
  AbstractValue(long int x);
  AbstractValue(unsigned long int x);
  AbstractValue(long long int x);
  AbstractValue(unsigned long long int x);
  bool isTop() const;
  bool isTrue() const;
  bool isFalse() const;
  bool isBot() const;
  // determines whether the value is known and constant. Otherwise it can be bot or top.
  bool isConstInt() const;
  bool isPtr() const;
  AbstractValue operatorNot();
  AbstractValue operatorUnaryMinus(); // unary minus
  AbstractValue operatorOr(AbstractValue other);
  AbstractValue operatorAnd(AbstractValue other);
  AbstractValue operatorEq(AbstractValue other) const;
  AbstractValue operatorNotEq(AbstractValue other) const;
  AbstractValue operatorLess(AbstractValue other) const;
  AbstractValue operatorLessOrEq(AbstractValue other) const;
  AbstractValue operatorMoreOrEq(AbstractValue other) const;
  AbstractValue operatorMore(AbstractValue other) const;

  AbstractValue operatorBitwiseAnd(AbstractValue other) const;
  AbstractValue operatorBitwiseOr(AbstractValue other) const;
  AbstractValue operatorBitwiseXor(AbstractValue other) const;
  AbstractValue operatorBitwiseComplement() const;

  AbstractValue operatorBitwiseShiftLeft(AbstractValue other) const;
  AbstractValue operatorBitwiseShiftRight(AbstractValue other) const;

  static AbstractValue operatorAdd(AbstractValue& a,AbstractValue& b);
  static AbstractValue operatorSub(AbstractValue& a,AbstractValue& b);
  static AbstractValue operatorMul(AbstractValue& a,AbstractValue& b);
  static AbstractValue operatorDiv(AbstractValue& a,AbstractValue& b);
  static AbstractValue operatorMod(AbstractValue& a,AbstractValue& b);

  static AbstractValue createAddressOfArray(SPRAY::VariableId arrayVariableId);
  static AbstractValue createAddressOfArrayElement(SPRAY::VariableId arrayVariableId, AbstractValue Index);
  // strict weak ordering (required for sorted STL data structures if
  // no comparator is provided)
  bool operator==(AType::AbstractValue other) const;
  bool operator<(AType::AbstractValue other) const;

  string toString() const;
  string toString(SPRAY::VariableIdMapping* vim) const;
  
  friend ostream& operator<<(ostream& os, const AbstractValue& value);
  friend istream& operator>>(istream& os, AbstractValue& value);
  void fromStream(istream& is);

  ValueType getValueType() const;
  int getIntValue() const;
  int getIndexIntValue() const;
  SPRAY::VariableId getVariableId() const;

  int intLength();   // returns length of integer dependent on valueType
  long hash() const;
  std::string valueTypeToString() const;
 private:
  ValueType valueType;
  int intValue;
  SPRAY::VariableId variableId;
};

// arithmetic operators
 AType::AbstractValue operator+(AType::AbstractValue& a,AType::AbstractValue& b);
 AType::AbstractValue operator-(AType::AbstractValue& a,AType::AbstractValue& b);
 AType::AbstractValue operator*(AType::AbstractValue& a,AType::AbstractValue& b);
 AType::AbstractValue operator/(AType::AbstractValue& a,AType::AbstractValue& b);
 AType::AbstractValue operator%(AType::AbstractValue& a,AType::AbstractValue& b);

 ostream& operator<<(ostream& os, const AbstractValue& value);
 istream& operator>>(istream& is, AbstractValue& value);

  /*! \brief Comparison class, allowing to use AbstractValue in ordered containers (e.g. set)
    \date 2012
    \author Markus Schordan
  */
  struct ConstIntLatticeCmp {
    bool operator()(const AType::AbstractValue& c1, const AType::AbstractValue& c2) const;
  };

} // end of namespace AType

typedef AType::AbstractValue AValue; 
typedef AType::ConstIntLatticeCmp AValueCmp; 

}

#endif
