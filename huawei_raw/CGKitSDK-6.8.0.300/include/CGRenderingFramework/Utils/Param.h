/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Description: Plugin system parameter format.Parameter list used by the plug-in system.
 * Class used to encapsulate data. The class can encapsulate various types of basic data,
 * user-defined data, and enumeration types in containers, facilitating data transfer in
 * the plugin framework.
 */

#ifndef PARAM_H
#define PARAM_H

#include "Math/Color.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Matrix4.h"
#include "Math/Quaternion.h"
#include "nlohmann/json.hpp"

NS_CG_BEGIN
/* Parameter Type Enumeration */
enum ParameterType {
    PARAMETER_TYPE_BOOLEAN,
    PARAMETER_TYPE_INT,
    PARAMETER_TYPE_FLOAT,
    PARAMETER_TYPE_DOUBLE,
    PARAMETER_TYPE_VECTOR2,
    PARAMETER_TYPE_VECTOR3,
    PARAMETER_TYPE_VECTOR4,
    PARAMETER_TYPE_MATRIX,
    PARAMETER_TYPE_QUATERNION,
    PARAMETER_TYPE_COLOR,
    PARAMETER_TYPE_POINTER,
    PARAMETER_TYPE_STRING,
    PARAMETER_TYPE_ARRAY,
    PARAMETER_TYPE_OBJECT,
    PARAMETER_TYPE_MAX
};

/* Mapping between parameter types and JSON */
static std::map<u32, String> mapStringValues
{
    {PARAMETER_TYPE_VECTOR2, "vector2"},
    {PARAMETER_TYPE_VECTOR3, "vector3"},
    {PARAMETER_TYPE_VECTOR4, "vector4"},
    {PARAMETER_TYPE_MATRIX, "matrix4",},
    {PARAMETER_TYPE_QUATERNION, "quaternion"},
    {PARAMETER_TYPE_COLOR, "color"},
};

/* Value of the parameter type */
union Value {
    Value(){}
    Value(const Value& val);
    ~Value(){}

    bool booleanValue;
    s32 intValue;
    f32 floatValue;
    f64 doubleValue;
    Vector2 vector2Value;
    Vector3 vector3Value;
    Vector4 vector4Value;
    Matrix4 matrixValue;
    Quaternion quaternionValue;
    Color colorValue;
    void* pointerValue;

    Value& operator=(const Value& val);
};

class CGKIT_EXPORT Param {
public:
    typedef std::vector<Param> Array;
    typedef std::map<String, Param> Object;
    /* constructor */
    Param():type(PARAMETER_TYPE_MAX){}

    /* Destructor function, which releases memory. */
    ~Param();

    /* Clear the Param data. */
    void Clear();

    /* Template function, which obtains the constant Param type. */
    template<typename T>
    const T& Get() const;

    /* Template function, which obtains the Param type. */
    template<typename T>
    T& Get();

    /* Obtains pointer data. */
    const void *Get() const
    {
        return value.pointerValue;
    }

    /* Template function, which sets Param based on the input parameter type. */
    template<typename T>
    void Set(T val);

    /*
     * Add data to the container member variable std::vector of the Param class.
     * idx indicates the index number to be added.
     */
    void Set(u32 idx, const Param& param)
    {
        if (idx < 0) {
            return;
        }
        if (arrayValue.size() == 0) {
            arrayValue.resize(idx + 1);
        } else if ((arrayValue.size() > 0) && (arrayValue.size() < idx + 1)) {
            Array newArrayValue;
            newArrayValue.resize(idx + 1);
            for (u32 i = 0; i < arrayValue.size(); i++) {
                newArrayValue[i] = arrayValue[i];
            }
            arrayValue.resize(idx + 1);
            arrayValue = newArrayValue;
        }
        type = PARAMETER_TYPE_ARRAY;
        arrayValue[idx] = param;
        return;
    }

    /* Add data to the container member variable std::map<String, Param> of the Param class. */
    void Set(const String& name, const Param& param)
    {
        type = PARAMETER_TYPE_OBJECT;
        objectValue[name] = param;
    }

    /* explicit constructors, boolean parameters */
    explicit Param(const bool val):type(PARAMETER_TYPE_BOOLEAN)
    {
        value.booleanValue = val;
    }

    /* Explicit constructor. It is a 32-bit integer parameter. */
    explicit Param(const s32 val):type(PARAMETER_TYPE_INT)
    {
        value.intValue = val;
    }

    /* Explicit constructor, single-precision 32-bit floating-point parameter. */
    explicit Param(const f32 val):type(PARAMETER_TYPE_FLOAT)
    {
        value.floatValue = val;
    }

    /* Explicit constructor, double-precision 64-bit floating-point parameter. */
    explicit Param(const f64 val):type(PARAMETER_TYPE_DOUBLE)
    {
        value.doubleValue = val;
    }

    /* Explicit constructor, two-dimensional vector parameter. */
    explicit Param(const Vector2 val):type(PARAMETER_TYPE_VECTOR2)
    {
        value.vector2Value = val;
    }

    /* Explicit constructor, 3D vector parameter. */
    explicit Param(const Vector3 val):type(PARAMETER_TYPE_VECTOR3)
    {
        value.vector3Value = val;
    }

    /* Explicit constructor, four-dimensional vector parameter. */
    explicit Param(const Vector4 val):type(PARAMETER_TYPE_VECTOR4)
    {
        value.vector4Value = val;
    }

    /* Explicit constructor, matrix parameter. */
    explicit Param(const Matrix4 val):type(PARAMETER_TYPE_MATRIX)
    {
        value.matrixValue = val;
    }

    /* Explicit constructor, quaternion parameter. */
    explicit Param(const Quaternion val):type(PARAMETER_TYPE_QUATERNION)
    {
        value.quaternionValue = val;
    }

    /* Explicit constructor, color parameter. */
    explicit Param(const Color val):type(PARAMETER_TYPE_COLOR)
    {
        value.colorValue = val;
    }

    /* Explicit constructor, pointer parameter. */
    explicit Param(void* val):type(PARAMETER_TYPE_POINTER)
    {
        value.pointerValue = val;
    }

    /* Explicit constructor, which is a string parameter. */
    explicit Param(const String& val):type(PARAMETER_TYPE_STRING)
    {
        stringValue = val;
    }

    /* Explicit constructor, which is a formal parameter std::vector<Param>. */
    explicit Param(const Array& val):type(PARAMETER_TYPE_ARRAY)
    {
        arrayValue = Array(val);
    }

    /* Explicit constructor, std::map<String, Param> formal parameter. */
    explicit Param(const Object& val):type(PARAMETER_TYPE_OBJECT)
    {
        objectValue = Object(val);
    }

    /* Returns the Param data type. */
    char ParameterType() const
    {
        return static_cast<const char>(type);
    }

    /* Determines whether the current Param type is Boolean. */
    bool IsBool() const
    {
        return (type == PARAMETER_TYPE_BOOLEAN);
    }

    /* Determines whether the current Param type is an integer. */
    bool IsInt() const
    {
        return (type == PARAMETER_TYPE_INT);
    }

    /* Determines whether the current Param type is a single-precision floating-point type. */
    bool IsFloat() const
    {
        return (type == PARAMETER_TYPE_FLOAT);
    }

    /* Determines whether the current Param type is a double-precision floating-point type. */
    bool IsDouble() const
    {
        return (type == PARAMETER_TYPE_DOUBLE);
    }

    /* Determines whether the current Param type is a two-dimensional vector. */
    bool IsVector2() const
    {
        return (type == PARAMETER_TYPE_VECTOR2);
    }

    /* Determines whether the current Param type is a three-dimensional vector. */
    bool IsVector3() const
    {
        return (type == PARAMETER_TYPE_VECTOR3);
    }

    /* Determines whether the current Param type is a four-dimensional vector. */
    bool IsVector4() const
    {
        return (type == PARAMETER_TYPE_VECTOR4);
    }

    /* Determines whether the current Param type is a matrix. */
    bool IsMatrix() const
    {
        return (type == PARAMETER_TYPE_MATRIX);
    }

    /* Determines whether the current Param type is a quaternion. */
    bool IsQuaternion() const
    {
        return (type == PARAMETER_TYPE_QUATERNION);
    }

    /* Determines whether the current Param type is a color. */
    bool IsColor() const
    {
        return (type == PARAMETER_TYPE_COLOR);
    }

    /* Determines whether the current Param type is a pointer. */
    bool IsPointer() const
    {
        return (type == PARAMETER_TYPE_POINTER);
    }

    /* Check whether the current Param type is a character string. */
    bool IsString() const
    {
        return (type == PARAMETER_TYPE_STRING);
    }

    /* Check whether the current Param type is std::vector. */
    bool IsArray() const
    {
        return (type == PARAMETER_TYPE_ARRAY);
    }

    /* Check whether the current Param type is std::map. */
    bool IsObject() const
    {
        return (type == PARAMETER_TYPE_OBJECT);
    }

    /* Obtains data at a specified subscript position from std::vector. */
    const Param& Get(u32 idx) const
    {
        static Param null_value;
        ASSERT(IsArray());
        ASSERT(idx >= 0);
        return (static_cast<size_t>(idx) < arrayValue.size())
               ? arrayValue[static_cast<size_t>(idx)]
               : null_value;
    }

    /* Obtain the corresponding data from std::map. */
    const Param& Get(const String& key) const
    {
        static Param null_value;
        ASSERT(IsObject());
        Object::const_iterator it = objectValue.find(key);
        return (it != objectValue.end()) ? it->second : null_value;
    }

    /*
     * If the current Param type is std::vector, the length of the Param is returned.
     * Otherwise, 0 is returned.
     */
    size_t ArrayLen() const
    {
        if (!IsArray()) {
            return 0;
        }
        return arrayValue.size();
    }

    /* Check whether the current Param internal std::map contains a key. */
    bool Has(const String& key) const
    {
        if (!IsObject()) {
            return false;
        }
        Object::const_iterator it = objectValue.find(key);
        return (it != objectValue.end()) ? true : false;
    }

    /* Returns all keys contained in std::map. */
    std::vector<String> Keys() const
    {
        std::vector<String> keys;
        if (!IsObject()) {
            return keys;    // empty
        }
        for (Object::const_iterator it = objectValue.begin(); it != objectValue.end(); ++it) {
            keys.push_back(it->first);
        }
        return keys;
    }

    /* Returns the total number of data contained in the current Param. */
    s32 Size() const
    {
        return (IsArray() ? ArrayLen():Keys().size());
    }

public:
    s32 type;
    Value value;
    String stringValue;
    Array arrayValue;
    Object objectValue;
};

#define PARAM_GET(ctype, var)                     \
    template<>                                    \
    inline const ctype& Param::Get<ctype>() const \
    {                                             \
        return var;                               \
    }                                             \
    template<>                                    \
    inline ctype& Param::Get<ctype>()             \
    {                                             \
        return var;                               \
    }
PARAM_GET(bool, value.booleanValue)
PARAM_GET(s32, value.intValue)
PARAM_GET(f32, value.floatValue)
PARAM_GET(f64, value.doubleValue)
PARAM_GET(Vector2, value.vector2Value)
PARAM_GET(Vector3, value.vector3Value)
PARAM_GET(Vector4, value.vector4Value)
PARAM_GET(Matrix4, value.matrixValue)
PARAM_GET(Quaternion, value.quaternionValue)
PARAM_GET(Color, value.colorValue)
PARAM_GET(String, stringValue)
PARAM_GET(Param::Array, arrayValue)
PARAM_GET(Param::Object, objectValue)
#undef Param_GET

#define PARAM_SET(ctype, var, paramType)     \
    template<>                               \
    inline void Param::Set<ctype>(ctype val) \
    {                                        \
        var = val;                           \
        type = paramType;                    \
        return;                              \
    }
PARAM_SET(bool, value.booleanValue, PARAMETER_TYPE_BOOLEAN)
PARAM_SET(s32, value.intValue, PARAMETER_TYPE_INT)
PARAM_SET(f32, value.floatValue, PARAMETER_TYPE_FLOAT)
PARAM_SET(f64, value.doubleValue, PARAMETER_TYPE_DOUBLE)
PARAM_SET(Vector2, value.vector2Value, PARAMETER_TYPE_VECTOR2)
PARAM_SET(Vector3, value.vector3Value, PARAMETER_TYPE_VECTOR3)
PARAM_SET(Vector4, value.vector4Value, PARAMETER_TYPE_VECTOR4)
PARAM_SET(Matrix4, value.matrixValue, PARAMETER_TYPE_MATRIX)
PARAM_SET(Quaternion, value.quaternionValue, PARAMETER_TYPE_QUATERNION)
PARAM_SET(Color, value.colorValue, PARAMETER_TYPE_COLOR)
PARAM_SET(void*, value.pointerValue, PARAMETER_TYPE_POINTER)
PARAM_SET(String, stringValue, PARAMETER_TYPE_STRING)
PARAM_SET(Param::Array, arrayValue, PARAMETER_TYPE_ARRAY)
PARAM_SET(Param::Object, objectValue, PARAMETER_TYPE_OBJECT)
#undef PARAM_SET

/* Parsing param serialization to JSON format. */
void Serialize(const String& key, const Param& val, nlohmann::json& obj);

/* Deserialization in JSON format is parsed as param. */
void Deserialize(Param* param, const nlohmann::json& jsonParam);

NS_CG_END
#endif
