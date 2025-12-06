/**
 * NOTE: This is a generated file.
 *   (see https://github.com/Icedude907/WebGPU-Cpp-23 )
 */

#pragma once

{{webgpu_includes}}

#include <stdint.h>
#include <memory>
#include <string_view>
#include <span>
#include <bit>

#if __EMSCRIPTEN__
	#error "This template does not support emscripten"
#endif


/**
 * A namespace providing a more C++ idiomatic API to WebGPU.
 */
namespace wgpu {

struct DefaultFlag {};
constexpr DefaultFlag Default;

#define HANDLE(Type) \
struct Type { \
	using S = Type; /*Self*/ \
	using W = WGPU ## Type; /*Wrapped C Type*/ \
	constexpr Type() : m_raw(nullptr) {} \
	constexpr Type(const W& w) : m_raw(w) {} \
	constexpr operator W&() { return m_raw; } \
	constexpr operator W const&() const { return m_raw; } \
	constexpr operator bool() const { return m_raw != nullptr; } \
	constexpr bool operator==(Type const& other) const { return m_raw == other.m_raw; } \
	constexpr bool operator==(W const& other) const { return m_raw == other; } \
	W m_raw;

#define DESCRIPTOR(Type) \
struct Type : public WGPU ## Type { \
	using S = Type; /*Self*/ \
	using W = WGPU ## Type; /*Wrapped C Type*/ \
	constexpr Type() : W() { nextInChain = nullptr; } \
	constexpr Type(const W &other) : W(other) { nextInChain = nullptr; } \
	static constexpr S Default = S::setDefault();
	constexpr Type& operator=(DefaultFlag) { *this = S::Default; return *this; }

#define STRUCT(Type) \
struct Type : public WGPU ## Type { \
	using S = Type; /*Self*/ \
	using W = WGPU ## Type; /*Wrapped C Type*/ \
	constexpr Type() : W() {} \
	constexpr Type(W const& other) : W(other) {} \
	static constexpr S Default = S::setDefault();
	constexpr Type& operator=(DefaultFlag) { *this = S::Default; return *this; }

#define ENUM(Type) \
struct Type { \
	using S = Type; /*Self*/ \
	using W = WGPU ## Type; /*Wrapped C Type*/ \
	constexpr Type() : m_raw(W{}) {} /* Using default value-initialization */ \
	constexpr Type(W const& w) : m_raw(w) {} \
	constexpr operator W() const { return m_raw; } \
	W m_raw;

#define ENUM_ENTRY(Name, Value) \
	static constexpr W Name = (W)(Value);

#define END };

{{begin-inject}}
HANDLE(Instance)
	static inline S create(){ return wgpuCreateInstance(nullptr); }
	static inline S create(InstanceDescriptor const& descriptor){ return wgpuCreateInstance(&descriptor); }
	inline Adapter requestAdapter(RequestAdapterOptions const& options);
END

HANDLE(Adapter)
	inline Device requestDevice(DeviceDescriptor const& descriptor);
END
STRUCT(Color)
	constexpr Color(double r, double g, double b, double a) : WGPUColor{ r, g, b, a } {}
END
STRUCT(Extent3D)
	constexpr Extent3D(uint32_t width, uint32_t height, uint32_t depthOrArrayLayers) : WGPUExtent3D{ width, height, depthOrArrayLayers } {}
END
STRUCT(Origin3D)
	constexpr Origin3D(uint32_t x, uint32_t y, uint32_t z) : WGPUOrigin3D{ x, y, z } {}
END
STRUCT(StringView)
	constexpr StringView(std::string_view cpp) : WGPUStringView{ cpp.data(), cpp.length() } {}
	constexpr operator std::string_view() const {
		return length == WGPU_STRLEN
			? std::string_view(data)
			: std::string_view(data, length);
	}
END
{{end-inject}}

{{begin-blacklist}}
wgpuDeviceGetLostFuture
{{end-blacklist}}

// Other type aliases
{{type_aliases}}

// Enumerations
{{enums}}

// Structs
{{structs}}

// Descriptors
{{descriptors}}

// Handles forward declarations
{{handles_decl}}

// Callback types
{{callbacks}}

// Handles detailed declarations
{{handles}}

// Non-member procedures
{{procedures}}

// Handles members implementation
{{handles_impl}}

// Extra implementations
inline Adapter Instance::requestAdapter(const RequestAdapterOptions& options) {
	struct Context {
		Adapter adapter = nullptr;
		bool requestEnded = false;
	};
	Context context;

	RequestAdapterCallbackInfo{{ext_suffix}} callbackInfo;
	callbackInfo.nextInChain = nullptr;
	callbackInfo.userdata1 = &context;
	callbackInfo.callback = [](
		WGPURequestAdapterStatus status,
		WGPUAdapter adapter,
		WGPUStringView message,
		void* userdata1,
		[[maybe_unused]] void* userdata2
	) {
		Context& context = *std::bit_cast<Context*>(userdata1);
		if (status == RequestAdapterStatus::Success) {
			context.adapter = adapter;
		}
		context.requestEnded = true;
	};
	callbackInfo.mode = CallbackMode::AllowSpontaneous;
	wgpuInstanceRequestAdapter(*this, &options, callbackInfo);

	return context.adapter;
}

inline Device Adapter::requestDevice(const DeviceDescriptor& descriptor) {
	struct Context {
		Device device = nullptr;
		bool requestEnded = false;
	};
	Context context;

	RequestDeviceCallbackInfo{{ext_suffix}} callbackInfo;
	callbackInfo.nextInChain = nullptr;
	callbackInfo.userdata1 = &context;
	callbackInfo.callback = [](
		WGPURequestDeviceStatus status,
		WGPUDevice device,
		WGPUStringView message,
		void* userdata1,
		[[maybe_unused]] void* userdata2
	) {
		Context& context = *std::bit_cast<Context*>(userdata1);
		if (status == RequestDeviceStatus::Success) {
			context.device = device;
		}
		context.requestEnded = true;
	};
	callbackInfo.mode = CallbackMode::AllowSpontaneous;
	wgpuAdapterRequestDevice(*this, &descriptor, callbackInfo);
	return context.device;
}

#undef HANDLE
#undef DESCRIPTOR
#undef ENUM
#undef ENUM_ENTRY
#undef END

} // namespace wgpu
