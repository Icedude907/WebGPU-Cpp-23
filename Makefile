
.PHONY: clean webgpu-native

webgpu-native:
	mkdir -p build/webgpu-native
	python scripts/generate.py -t templates/webgpu.template.hpp -o build/webgpu-native/webgpu.hpp

clean:
	rm -rf build/