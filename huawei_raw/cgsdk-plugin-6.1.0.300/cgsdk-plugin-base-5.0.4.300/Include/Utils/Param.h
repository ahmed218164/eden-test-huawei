/*
* Copyright (c) Huawei Technologies Co., Ltd. 2020-2020. All rights reserved.
* Description:
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

static std::map<u32, String> mapStringValues
{
    {PARAMETER_TYPE_VECTOR2, "vector2"},
    {PARAMETER_TYPE_VECTOR3, "vector3"},
    {PARAMETER_TYPE_VECTOR4, "vector4"},
    {PARAMETER_TYPE_MATRIX, "matrix4",},
    {PARAMETER_TYPE_QUATERNION, "quaternion"},
    {PARAMETER_TYPE_COLOR, "color"},
};

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
    typedef std::unordered_map<String, Param> Object;

    Param():type(PARAMETER_TYPE_MAX){}
    ~Param();
    void Clear();

    template<typename T>
    const T& Get() const;
    template<typename T>
    T& Get();
    const void *Get() const
    {
        return value.pointerValue;
    }
    template<typename T>
    void Set(T val);

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

    void Set(const String& name, const Param& param)
    {
        type = PARAMETER_TYPE_OBJECT;
        objectValue[name] = param;
    }

    explicit Param(const bool val):type(PARAMETER_TYPE_BOOLEAN)
    {
        value.booleanValue = val;
    }

    explicit Param(const s32 val):type(PARAMETER_TYPE_INT)
    {
        value.intValue = val;
    }

    explicit Param(const f32 val):type(PARAMETER_TYPE_FLOAT)
    {
        value.floatValue = val;
    }

    explicit Param(const f64 val):type(PARAMETER_TYPE_DOUBLE)
    {
        value.doubleValue = val;
    }

    explicit Param(const Vector2 val):type(PARAMETER_TYPE_VECTOR2)
    {
        value.vector2Value = val;
    }

    explicit Param(const Vector3 val):type(PARAMETER_TYPE_VECTOR3)
    {
        value.vector3Value = val;
    }

    explicit Param(const Vector4 val):type(PARAMETER_TYPE_VECTOR4)
    {
        value.vector4Value = val;
    }

    explicit Param(const Matrix4 val):type(PARAMETER_TYPE_MATRIX)
    {
        value.matrixValue = val;
    }

    explicit Param(const Quaternion val):type(PARAMETER_TYPE_QUATERNION)
    {
        value.quaternionValue = val;
    }

    explicit Param(const Color val):type(PARAMETER_TYPE_COLOR)
    {
        value.colorValue = val;
    }

    explicit Param(void* val):type(PARAMETER_TYPE_POINTER)
    {
        value.pointerValue = val;
    }

    explicit Param(const String& val):type(PARAMETER_TYPE_STRING)
    {
        stringValue = val;
    }

    explicit Param(const Array& val):type(PARAMETER_TYPE_ARRAY)
    {
        arrayValue = Array(val);
    }

    explicit Param(const Object& val):type(PARAMETER_TYPE_OBJECT)
    {
        objectValue = Object(val);
    }

    char ParameterType() const
    {
        return static_cast<const char>(type);
    }
    bool IsBool() const
    {
        return (type == PARAMETER_TYPE_BOOLEAN);
    }
    bool IsInt() const
    {
        return (type == PARAMETER_TYPE_INT);
    }
    bool IsFloat() const
    {
        return (type == PARAMETER_TYPE_FLOAT);
    }
    bool IsDouble() const
    {
        return (type == PARAMETER_TYPE_DOUBLE);
    }
    bool IsVector2() const
    {
        return (type == PARAMETER_TYPE_VECTOR2);
    }
    bool IsVector3() const
    {
        return (type == PARAMETER_TYPE_VECTOR3);
    }
    bool IsVector4() const
    {
        return (type == PARAMETER_TYPE_VECTOR4);
    }
    bool IsMatrix() const
    {
        return (type == PARAMETER_TYPE_MATRIX);
    }
    bool IsQuaternion() const
    {
        return (type == PARAMETER_TYPE_QUATERNION);
    }
    bool IsColor() const
    {
        return (type == PARAMETER_TYPE_COLOR);
    }
    bool IsPointer() const
    {
        return (type == PARAMETER_TYPE_POINTER);
    }
    bool IsString() const
    {
        return (type == PARAMETER_TYPE_STRING);
    }
    bool IsArray() const
    {
        return (type == PARAMETER_TYPE_ARRAY);
    }
    bool IsObject() const
    {
        return (type == PARAMETER_TYPE_OBJECT);
    }
    // Lookup value from an array
    const Param& Get(u32 idx) const
    {
        static Param null_value;
        ASSERT(IsArray());
        ASSERT(idx >= 0);
        return (static_cast<size_t>(idx) < arrayValue.size())
               ? arrayValue[static_cast<size_t>(idx)]
               : null_value;
    }

    // Lookup value from a key-value pair
    const Param& Get(const String& key) const
    {
        static Param null_value;
        ASSERT(IsObject());
        Object::const_iterator it = objectValue.find(key);
        return (it != objectValue.end()) ? it->second : null_value;
    }

    size_t ArrayLen() const
    {
        if (!IsArray()) {
            return 0;
        }
        return arrayValue.size();
    }

    // Valid only for object type.
    bool Has(const String& key) const
    {
        if (!IsObject()) {
            return false;
        }
        Object::const_iterator it = objectValue.find(key);
        return (it != objectValue.end()) ? true : false;
    }

    // List keys
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

void Serialize(const String& key, const Param& val, nlohmann::json& obj);  // write
void Deserialize(Param* param, const nlohmann::json& jsonParam);           // read 2109

static bool ParamToJson(const Param& param, nlohmann::json* ret);
static void SpecialParamTOJSON(const Param& param, nlohmann::json& obj);
NS_CG_END
#endif
