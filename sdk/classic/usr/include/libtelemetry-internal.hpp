/**
 * Copyright (c) 2015 Parrot S.A.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of the Parrot Company nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE PARROT COMPANY BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * @file libtelemetry-internal.hpp
 *
 */

#ifndef _LIBTELEMETRY_INTERNAL_HPP_
#define _LIBTELEMETRY_INTERNAL_HPP_

#include <stdlib.h>
#include <type_traits>

namespace telemetry {
namespace internal {

/**
 * Helper to determine if a class support serialization by means of the
 * presence of the 'telemetryRegister(ClassDesc &)' method.
 */
template <typename T>
struct has_serialization_method {
private:
	typedef char Yes[1];
	typedef char No[2];

	template <typename U, U>
	struct TypeCheck;

	/* If this specialization matches, size of 'dummy' will be 'Yes' */
	template <typename C>
	static Yes &dummy(TypeCheck<void (C::*)(ClassDesc &), &C::telemetryRegister> *);

	/* Default specialization with size of 'dummy' as 'No' */
	template <typename>
	static No &dummy(...);

public:
	/* Avoid warning with '-Wctor-dtor-privacy' */
	void dummy();

	/* Will be true if the class has the method */
	static const bool value = (sizeof(dummy<T>(NULL)) == sizeof(Yes));
};

/** Signed types by size */
static const VarType sSignedTypes[9] = {
	TLM_TYPE_INVALID,
	TLM_TYPE_INT8,
	TLM_TYPE_INT16,
	TLM_TYPE_INVALID,
	TLM_TYPE_INT32,
	TLM_TYPE_INVALID,
	TLM_TYPE_INVALID,
	TLM_TYPE_INVALID,
	TLM_TYPE_INT64
};

/** Unsigned types by size */
static const VarType sUnsignedTypes[9] = {
	TLM_TYPE_INVALID,
	TLM_TYPE_UINT8,
	TLM_TYPE_UINT16,
	TLM_TYPE_INVALID,
	TLM_TYPE_UINT32,
	TLM_TYPE_INVALID,
	TLM_TYPE_INVALID,
	TLM_TYPE_INVALID,
	TLM_TYPE_UINT64
};

/** Floating point types by size */
static const VarType sFloatTypes[9] = {
	TLM_TYPE_INVALID,
	TLM_TYPE_INVALID,
	TLM_TYPE_INVALID,
	TLM_TYPE_INVALID,
	TLM_TYPE_FLOAT32,
	TLM_TYPE_INVALID,
	TLM_TYPE_INVALID,
	TLM_TYPE_INVALID,
	TLM_TYPE_FLOAT64
};

/** Get the type of an arithmetic type based on its size */
inline static constexpr VarType getArithmeticVarType(
		const VarType types[9], size_t size) {
	return size > 8 ? TLM_TYPE_INVALID : types[size];
}

/** Get the type of a variable at compilation time */
template <typename T>
inline static constexpr VarType getVarType() {
	/* Single return expression so function can be 'constexpr' */
	return std::is_same<T, bool>::value ? TLM_TYPE_BOOL :
		std::is_same<T, char>::value ? TLM_TYPE_STRING :
		std::is_enum<T>::value ? TLM_TYPE_INT32 :
		std::is_integral<T>::value ?
			getArithmeticVarType(std::is_signed<T>::value ?
				sSignedTypes : sUnsignedTypes,
				sizeof(T)) :
		std::is_floating_point<T>::value ?
			getArithmeticVarType(sFloatTypes, sizeof(T)) :
		std::is_pointer<T>::value ? TLM_TYPE_INVALID :
		std::is_pod<T>::value ? TLM_TYPE_BINARY :
		TLM_TYPE_INVALID;
}

/** */
class Registrator {
protected:
	typedef std::map<std::string, VarInfo>  VarInfoMap;
	std::map<std::string, std::string> mAliasMap;
	bool mUseAlias;

protected:
	VarInfoMap     mVarInfoMap;
	bool           mCompleted;
	std::string    mSection;

private:
	friend class telemetry::ClassDesc;

	template<typename T, bool WithSerialization>
	struct RegHelper {};

	/** Registration helper for basic types */
	template<typename T>
	struct RegHelper<T, false> {
		inline static int reg(Registrator &registrator, T &var,
				const std::string &section,
				const std::string &name,
				uint32_t flags,
				struct timespec *timestamp) {
			VarType type = getVarType<T>();
			return registrator.regInternal(&var, section, name,
					type, sizeof(T), 1, flags, timestamp);
		}
	};

	/** Registration helper for arrays of basic types */
	template<typename T, size_t N>
	struct RegHelper<T[N], false> {
		inline static int reg(Registrator &registrator, T (&var)[N],
				const std::string &section,
				const std::string &name,
				uint32_t flags,
				struct timespec *timestamp) {
			VarType type = getVarType<T>();
			return registrator.regInternal(&var, section, name,
					type, sizeof(T), N, flags, timestamp);
		}
	};

	/** Registration helper for std::vector of basic types */
	template<typename T>
	struct RegHelper<std::vector<T>, false> {
		inline static int reg(Registrator &registrator,
				std::vector<T> &var,
				const std::string &section,
				const std::string &name,
				uint32_t flags,
				struct timespec *timestamp) {
			VarType type = getVarType<T>();
			return registrator.regInternal((void*)&(var[0]),
					section, name,
					type, sizeof(T), var.size(), flags,
					timestamp);
		}
	};

	/** Registration helper for class types */
	template<typename T>
	struct RegHelper<T, true> {
		/* Implementation requires ClassDesc so it is in libtelemetry.hpp */
		static int reg(Registrator &registrator, T &var,
				const std::string &section,
				const std::string &name,
				uint32_t flags,
				struct timespec *timestamp);
	};

	/** Registration helper for arrays of class types */
	template<typename T, size_t N>
	struct RegHelper<T[N], true> {
		/* Implementation requires ClassDesc so it is in libtelemetry.hpp */
		static int reg(Registrator &registrator, T (&var)[N],
				const std::string &section,
				const std::string &name,
				uint32_t flags,
				struct timespec *timestamp);
	};

private:
	std::string getVarSection(const std::string varFullName) const;
	std::string getVarName(const std::string varFullName) const;

	/* Not implemented, just private to avoid copy */
	Registrator(const Registrator &);
	Registrator &operator=(const Registrator &);

protected:
	/* Constructor, can not be inlined due to incomplete type VarInfo */
	Registrator(bool useAlias = false);

	/* Destructor */
	~Registrator();

	/** Variable registration */
	template<typename T>
	inline int reg(T &var,
			const std::string &section,
			const std::string &name,
			uint32_t flags,
			struct timespec *timestamp) {
		/* Use helper to register with or without class serialization */
		return RegHelper<T, has_serialization_method<T>::value>::reg(
				*this, var, section, name, flags, timestamp);
	}

	/** Variable registration for arrays */
	template<typename T, size_t N>
	inline int reg(T (&var)[N],
			const std::string &section,
			const std::string &name,
			uint32_t flags,
			struct timespec *timestamp) {
		/* Use helper to register with or without class serialization */
		return RegHelper<T[N], has_serialization_method<T>::value>::reg(
				*this, var, section, name, flags, timestamp);
	}

	/** Registration of arrays of samples */
	template<typename T, size_t M>
	inline int regSamplesArray(T (&var)[M],
				    const std::string &section,
				    const std::string &name,
				    uint32_t flags,
				    struct timespec *timestamp) {
			VarType type = getVarType<T>();
			return regInternal(&var, section, name, type,
					sizeof(T), 1, flags, timestamp, M);
	}

	/** Registration of arrays of samples */
	template<typename T, size_t M, size_t N>
	inline int regSamplesArray(T (&var)[M][N],
				    const std::string &section,
				    const std::string &name,
				    uint32_t flags,
				    struct timespec *timestamp) {
			VarType type = getVarType<T>();
			return regInternal(&var, section, name, type,
					sizeof(T), N, flags, timestamp, M);
	}

	int regFieldInternal(uintptr_t base,
			const std::string &parent,
			const struct tlm_reg_field *field);

	int regStructEltInternal(uintptr_t base,
			const std::string &parent,
			size_t idx,
			bool isArray,
			const struct tlm_reg_field *field);

	int regStructInternal(uintptr_t base,
			const std::string &parent,
			const struct tlm_reg_struct *desc);

public:
	/**
	 * @see tlm_consumer_reg_struct_ptr
	 */
	int regStructPtr(const void *ptr,
			const std::string &name,
			const struct tlm_reg_struct *desc);

	/** Low level registration method */
	int regInternal(void *ptr,
			const std::string &section,
			const std::string &name,
			VarType type,
			size_t size, size_t count,
			uint32_t flags,
			struct timespec *timestamp,
			size_t nbSamples = 1);

	inline int regInternal(const void *ptr,
			const std::string &section,
			const std::string &name,
			VarType type,
			size_t size, size_t count,
			uint32_t flags,
			struct timespec *timestamp) {
		return regInternal((void *)ptr, section, name, type,
				size, count, flags, timestamp);
	}

	std::string resolveAlias(const std::string &name) const;

};

} /* namespace internal */
} /* namespace telemetry */

#endif /* !_LIBTELEMETRY_INTERNAL_HPP_ */
