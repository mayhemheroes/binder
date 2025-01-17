// File: T32_call_guard.cpp
#include <T32.call_guard.hpp> // Methods
#include <T32.call_guard.hpp> // free
#include <sstream> // __str__

#include <functional>
#include <pybind11/pybind11.h>
#include <string>

#ifndef BINDER_PYBIND11_TYPE_CASTER
	#define BINDER_PYBIND11_TYPE_CASTER
	PYBIND11_DECLARE_HOLDER_TYPE(T, std::shared_ptr<T>)
	PYBIND11_DECLARE_HOLDER_TYPE(T, T*)
	PYBIND11_MAKE_OPAQUE(std::shared_ptr<void>)
#endif

void bind_T32_call_guard(std::function< pybind11::module &(std::string const &namespace_) > &M)
{
	// free(int) file:T32.call_guard.hpp line:16
	M("").def("free", (void (*)(int)) &free, "C++: free(int) --> void", pybind11::arg(""), pybind11::call_guard<pybind11::gil_scoped_release>());

	{ // Methods file:T32.call_guard.hpp line:20
		pybind11::class_<Methods, std::shared_ptr<Methods>> cl(M(""), "Methods", "");
		cl.def( pybind11::init( [](){ return new Methods(); } ) );
		cl.def("foo", (void (Methods::*)(int)) &Methods::foo, "C++: Methods::foo(int) --> void", pybind11::arg(""), pybind11::call_guard<pybind11::gil_scoped_release>());
	}
}


#include <map>
#include <algorithm>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>

#include <pybind11/pybind11.h>

typedef std::function< pybind11::module & (std::string const &) > ModuleGetter;

void bind_T32_call_guard(std::function< pybind11::module &(std::string const &namespace_) > &M);


PYBIND11_MODULE(T32_call_guard, root_module) {
	root_module.doc() = "T32_call_guard module";

	std::map <std::string, pybind11::module> modules;
	ModuleGetter M = [&](std::string const &namespace_) -> pybind11::module & {
		auto it = modules.find(namespace_);
		if( it == modules.end() ) throw std::runtime_error("Attempt to access pybind11::module for namespace " + namespace_ + " before it was created!!!");
		return it->second;
	};

	modules[""] = root_module;

	static std::vector<std::string> const reserved_python_words {"nonlocal", "global", };

	auto mangle_namespace_name(
		[](std::string const &ns) -> std::string {
			if ( std::find(reserved_python_words.begin(), reserved_python_words.end(), ns) == reserved_python_words.end() ) return ns;
			else return ns+'_';
		}
	);

	std::vector< std::pair<std::string, std::string> > sub_modules {
	};
	for(auto &p : sub_modules ) modules[p.first.size() ? p.first+"::"+p.second : p.second] = modules[p.first].def_submodule( mangle_namespace_name(p.second).c_str(), ("Bindings for " + p.first + "::" + p.second + " namespace").c_str() );

	//pybind11::class_<std::shared_ptr<void>>(M(""), "_encapsulated_data_");

	bind_T32_call_guard(M);

}

// Source list file: TEST/T32_call_guard.sources
// T32_call_guard.cpp
// T32_call_guard.cpp

// Modules list file: TEST/T32_call_guard.modules
// 
